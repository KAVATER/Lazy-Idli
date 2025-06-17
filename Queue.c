/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#include "string.h"
#include "stdio.h"

/* Private includes ----------------------------------------------------------*/

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;


/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/*************** Task handle ***************/
	xTaskHandle ExampleTask1_Handler;
	xTaskHandle ExampleTask2_Handler;

	/*************** Queue handle ***************/
	xQueueHandle Queue1;

	  /*************** Task Functions ***************/
	void ExampleTask1(void *argument);
	void ExampleTask2(void *argument);

	uint8_t G_DataID =1;//global variables
	int32_t G_DataValue =2;

	typedef struct{
	uint8_t dataID;
	int32_t DataValue;
	} Data_t;
/* USER CODE BEGIN 0 */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();



  /*************** Create Queue ***************/
Queue1 = xQueueCreate(5, sizeof(Data_t));
if(Queue1 == 0)
{
	char *str = "Unable to create Integer Queue\n\n";
	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen (str), HAL_MAX_DELAY);
}
else
{
	char *str = "Integer Queue Created successfully\n\n";
	 HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen (str), HAL_MAX_DELAY);
}
/*************** Task Related ***************/
xTaskCreate(ExampleTask1, "ExampleTask1", 128, NULL, 1, &ExampleTask1_Handler);
xTaskCreate(ExampleTask2, "ExampleTask2", 128, NULL, 2, &ExampleTask2_Handler);

uint8_t Rx_data;
HAL_UART_Receive_IT(&huart2, &Rx_data, 1);
  vTaskStartScheduler();



  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
/*************** Sender Function ***************/
void ExampleTask1(void *argument)
{
	Data_t data;
	//uint32_t TickDelay = pdMS_TO_TICKS(500);
	const TickType_t delay = pdMS_TO_TICKS(500);
	while(1)
	{


		data.dataID = G_DataID;
		data.DataValue = G_DataValue;
		char *str = "ExampleTask1\n is sending data to the queue\n\n";
		HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen (str), HAL_MAX_DELAY);

//		if(xQueueSend(Queue1, &data, portMAX_DELAY) == pdPASS)
//		{
//			char *str2 = "Successfully sent the data to the queue\nLeaving ExampleTask1 Task\n\n";
//			HAL_UART_Transmit(&huart2, (uint8_t*)str2, strlen(str2), HAL_MAX_DELAY);
//		}
		xQueueSend(Queue1, &data, portMAX_DELAY);
		vTaskDelay(delay);
	}
	}

/*************** Receiver Task ***************/
void ExampleTask2(void *argument)
{
	Data_t received;
	char buffer[150];
	    const TickType_t delay = pdMS_TO_TICKS(500);
	    static UBaseType_t originalPriority = 0;
	    static BaseType_t priorityIncreased = pdFALSE;

	originalPriority = uxTaskPriorityGet(NULL);
	while(1)
	{
		if(xQueueReceive(Queue1, &received, portMAX_DELAY) != pdTRUE)
		{
			HAL_UART_Transmit(&huart2, (uint8_t *)"Error in Receiving from Queue\n\n", 31, 1000);
		}
		else
		{
			sprintf(buffer, "Received data with ID %d and Value %ld from the queue\n\n", received.dataID, received.DataValue);
			HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);

			if(received.dataID == 0 )// Case 1: Delete if dataID == 0
			{
				sprintf(buffer, "After evaluation dataID: %d and DataValue: %ld \n",received.dataID,received.DataValue);
			    HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);

				char *str= "Deleting ExampleTask2\n\n";
				HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
				vTaskDelete(NULL); // Delete the task if condition is met

			}
			else if(received.dataID ==1)// Case 2: Process DataValue if dataID == 1
			{
				sprintf(buffer, "After evaluation dataID: %d and DataValue: %ld \n",received.dataID,received.DataValue);
			     HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
				if(received.DataValue ==0 && !priorityIncreased)// Sub-case: Increase priority
				{
					vTaskPrioritySet(NULL, originalPriority +2);
					priorityIncreased = pdTRUE;
					sprintf(buffer, "New priority of ExampleTask2 is : %d\n",originalPriority+2);
				    HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
//					sprintf(buffer, "After evaluation dataID: %d and DataValue: %ld \n",received.dataID,received.DataValue);
//			        HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
				}
				else if(received.DataValue ==1 && priorityIncreased) // Sub-case: Decrease priority back
				{
					vTaskPrioritySet(NULL, originalPriority);
					priorityIncreased = pdFALSE;
					sprintf(buffer, "Priority decreased! Priority of ExampleTask2 restored to: %d\n\n", originalPriority);
					HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
				}
				 // Sub-case: Delete on DataValue == 2
				        else if (received.DataValue == 2)
				       {
				        sprintf(buffer, "After evaluation dataID: %d and DataValue: %ld \n",received.dataID,received.DataValue);
				        HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
		              HAL_UART_Transmit(&huart2, (uint8_t *)"Deleting ExampleTask2 (DataValue == 2)\n\n", 40, HAL_MAX_DELAY);
				      vTaskDelete(NULL);
				  }
			}
		}
        	vTaskDelay(delay);
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}


void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {

  }
  /* USER CODE END 5 */
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM5)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
