# STM32-F4XX FreeRTOS Task Management Demo

## Project Overview
This project demonstrates dynamic task management using FreeRTOS on the STM32-F401Re microcontroller. The system implements real-time task priority control and deletion based on queue data values, showcasing advanced RTOS concepts for embedded applications.

**Hardware:** STM32-F401Re Microcontroller  
**RTOS:** FreeRTOS  
**Communication:** UART Serial Output (COM3)

---

## Test Cases and Results
### "ExampleTask2 takes data from Queue2 whenever data is available," -- In this i am assuming "Queue2" is a typo mistake as it is not defined in the problem statement.

### CASE 1: if(dataID==0) | Delete ExampleTask2

<img width="469" alt="CASE-1" src="https://github.com/user-attachments/assets/dcb7f781-94b8-4498-9420-16bf420fcbd7" />


**In this case the ExampleTask2 gets deleted and the ExampleTask1 keeps running that's why we see "ExampleTask1 is sending data to the queue" repitatively** 

---

### CASE 2: if(DataValue==0) | Increase the Priority of ExampleTask2 by 2 from the value given to it at creation

<img width="326" alt="CASE-2" src="https://github.com/user-attachments/assets/e2e22a91-b2b3-4950-896b-53fedda5118f" />

**This case is SubCase of "if(dataID==1)" in this the priority of ExampleTask2 is increased by 2**


---

### CASE 3: if(DataValue==1) | Decrease the Priority of ExampleTask2 if previously increased

<img width="332" alt="CASE-3" src="https://github.com/user-attachments/assets/22964464-0493-4775-b88d-30ace1b851f5" />

**This is also a SubCase which should decrease the priority of the task if it is previously increased but, if DataValue ==1 then the priority of the task will never increase resulting in not decreasing of the ExampleTask2**

---

### CASE 4: Task Deletion (dataID == 0)

<img width="298" alt="CASE-4" src="https://github.com/user-attachments/assets/1d5a64b7-e48e-4079-972d-ba21d2255b2b" />

**Just like first case The Ecample Task2 gets deleted**
---

## System Requirements
- **Microcontroller:** STM32-F401Re
- **IDE:** STM32CubeIDE or compatible
- **RTOS:** FreeRTOS kernel
- **Communication:** UART for serial output monitoring
- **Debugger:** ST-Link or compatible for programming and monitoring
