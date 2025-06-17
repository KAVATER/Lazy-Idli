<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>STM32-F401Re FreeRTOS Task Management</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            line-height: 1.6;
            color: #333;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
        }

        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
            background: rgba(255, 255, 255, 0.95);
            backdrop-filter: blur(10px);
            border-radius: 20px;
            margin-top: 20px;
            margin-bottom: 20px;
            box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
        }

        h1 {
            text-align: center;
            color: #2c3e50;
            font-size: 2.5em;
            margin-bottom: 30px;
            background: linear-gradient(45deg, #667eea, #764ba2);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            background-clip: text;
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.1);
        }

        .overview {
            background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);
            padding: 25px;
            border-radius: 15px;
            margin-bottom: 30px;
            border-left: 5px solid #667eea;
        }

        .overview h2 {
            color: #2c3e50;
            margin-bottom: 15px;
            font-size: 1.5em;
        }

        .tech-info {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
            gap: 20px;
            margin-bottom: 30px;
        }

        .tech-card {
            background: linear-gradient(135deg, #667eea, #764ba2);
            color: white;
            padding: 20px;
            border-radius: 15px;
            text-align: center;
            transform: translateY(0);
            transition: transform 0.3s ease, box-shadow 0.3s ease;
        }

        .tech-card:hover {
            transform: translateY(-5px);
            box-shadow: 0 15px 30px rgba(102, 126, 234, 0.3);
        }

        .case-section {
            margin-bottom: 40px;
            background: white;
            border-radius: 15px;
            overflow: hidden;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.1);
            transition: transform 0.3s ease;
        }

        .case-section:hover {
            transform: translateY(-2px);
        }

        .case-header {
            background: linear-gradient(135deg, #667eea, #764ba2);
            color: white;
            padding: 20px;
            font-size: 1.3em;
            font-weight: bold;
        }

        .case-content {
            padding: 25px;
        }

        .case-description {
            background: #f8f9ff;
            padding: 20px;
            border-radius: 10px;
            margin-bottom: 20px;
            border-left: 4px solid #667eea;
        }

        .case-description h4 {
            color: #2c3e50;
            margin-bottom: 10px;
            font-size: 1.1em;
        }

        .image-container {
            text-align: center;
            margin: 25px 0;
            background: #f8f9ff;
            padding: 20px;
            border-radius: 10px;
        }

        .case-image {
            max-width: 100%;
            height: auto;
            border-radius: 10px;
            box-shadow: 0 10px 25px rgba(0, 0, 0, 0.1);
            transition: transform 0.3s ease;
        }

        .case-image:hover {
            transform: scale(1.02);
        }

        .output-section {
            background: #2c3e50;
            color: #ecf0f1;
            padding: 20px;
            border-radius: 10px;
            margin-top: 20px;
            font-family: 'Courier New', monospace;
            overflow-x: auto;
        }

        .output-section h4 {
            color: #3498db;
            margin-bottom: 15px;
            font-family: 'Segoe UI', sans-serif;
        }

        .output-text {
            background: #34495e;
            padding: 15px;
            border-radius: 8px;
            white-space: pre-wrap;
            font-size: 0.9em;
            line-height: 1.4;
        }

        .note-section {
            background: linear-gradient(135deg, #ffeaa7, #fab1a0);
            padding: 20px;
            border-radius: 10px;
            margin: 30px 0;
            border-left: 5px solid #e17055;
        }

        .note-section h3 {
            color: #2d3436;
            margin-bottom: 10px;
        }

        .footer {
            text-align: center;
            margin-top: 40px;
            padding-top: 20px;
            border-top: 2px solid #667eea;
            color: #666;
        }

        @media (max-width: 768px) {
            .container {
                margin: 10px;
                padding: 15px;
            }
            
            h1 {
                font-size: 2em;
            }
            
            .tech-info {
                grid-template-columns: 1fr;
            }
        }

        .highlight {
            background: linear-gradient(120deg, #a8edea 0%, #fed6e3 100%);
            padding: 2px 6px;
            border-radius: 4px;
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>STM32-F401Re FreeRTOS Task Management Demo</h1>
        
        <div class="overview">
            <h2>Project Overview</h2>
            <p>This project demonstrates advanced FreeRTOS task management using the STM32-F401Re microcontroller. The program showcases dynamic task priority manipulation and task deletion based on queue data values, implementing real-time operating system concepts for embedded applications.</p>
        </div>

        <div class="tech-info">
            <div class="tech-card">
                <h3>Microcontroller</h3>
                <p>STM32-F401Re</p>
            </div>
            <div class="tech-card">
                <h3>RTOS</h3>
                <p>FreeRTOS</p>
            </div>
            <div class="tech-card">
                <h3>Features</h3>
                <p>Queue Management<br>Dynamic Priority Control<br>Task Deletion</p>
            </div>
        </div>

        <div class="note-section">
            <h3>Important Note</h3>
            <p><strong>Queue Assumption:</strong> The original specification mentioned "ExampleTask2 takes data from Queue2 whenever data is available," but since Queue2 is not defined in the problem statement, this appears to be a typo. The implementation uses the primary queue for data communication.</p>
        </div>

        <div class="case-section">
            <div class="case-header">
                CASE 1: Task Deletion (dataID == 0)
            </div>
            <div class="case-content">
                <div class="case-description">
                    <h4>Condition:</h4>
                    <p>When <span class="highlight">dataID equals 0</span>, the system performs task deletion operations.</p>
                    <h4>Action:</h4>
                    <p>ExampleTask2 is completely removed from the FreeRTOS scheduler, freeing up system resources.</p>
                </div>
                
                <div class="image-container">
                    <img src="https://github.com/user-attachments/assets/dcb7f781-94b8-4498-9420-16bf420fcbd7" alt="Case 1 Output" class="case-image">
                    <p><em>Serial output showing task deletion when dataID = 0</em></p>
                </div>

                <div class="output-section">
                    <h4>Expected Output:</h4>
                    <div class="output-text">Serial Port COM3 opened
Integer Queue Created successfully

ExampleTask1
is sending data to the queue

Received data with ID 1 and Value 0 from the queue

After evaluation dataID: 1 and DataValue: 0
New priority of ExampleTask2 is: 4
Serial Port COM3 closed</div>
                </div>
            </div>
        </div>

        <div class="case-section">
            <div class="case-header">
                CASE 2: Priority Increase (DataValue == 0)
            </div>
            <div class="case-content">
                <div class="case-description">
                    <h4>Condition:</h4>
                    <p>When <span class="highlight">DataValue equals 0</span>, the system increases task priority.</p>
                    <h4>Action:</h4>
                    <p>ExampleTask2's priority is increased by 2 from its original creation value, giving it higher scheduling precedence.</p>
                </div>
                
                <div class="image-container">
                    <img src="https://github.com/user-attachments/assets/e2e22a91-b2b3-4950-896b-53fedda5118f" alt="Case 2 Output" class="case-image">
                    <p><em>Serial output showing priority increase when DataValue = 0</em></p>
                </div>

                <div class="output-section">
                    <h4>Expected Output:</h4>
                    <div class="output-text">Serial Port COM3 opened
Integer Queue Created successfully

ExampleTask1
is sending data to the queue

Received data with ID 1 and Value 0 from the queue

After evaluation dataID: 1 and DataValue: 0
Serial Port COM3 closed</div>
                </div>
            </div>
        </div>

        <div class="case-section">
            <div class="case-header">
                CASE 3: Priority Decrease (DataValue == 1)
            </div>
            <div class="case-content">
                <div class="case-description">
                    <h4>Condition:</h4>
                    <p>When <span class="highlight">DataValue equals 1</span>, the system decreases task priority.</p>
                    <h4>Action:</h4>
                    <p>If ExampleTask2's priority was previously increased, it is restored to its original value, effectively reversing the priority boost.</p>
                </div>
                
                <div class="image-container">
                    <img src="https://github.com/user-attachments/assets/22964464-0493-4775-b88d-30ace1b851f5" alt="Case 3 Output" class="case-image">
                    <p><em>Serial output showing priority decrease when DataValue = 1</em></p>
                </div>

                <div class="output-section">
                    <h4>Expected Output:</h4>
                    <div class="output-text">Serial Port COM3 opened
Integer Queue Created successfully

ExampleTask1
is sending data to the queue

Received data with ID 1 and Value 1 from the queue

After evaluation dataID: 1 and DataValue: 1
Serial Port COM3 closed</div>
                </div>
            </div>
        </div>

        <div class="case-section">
            <div class="case-header">
                CASE 4: Task Deletion (DataValue == 2)
            </div>
            <div class="case-content">
                <div class="case-description">
                    <h4>Condition:</h4>
                    <p>When <span class="highlight">DataValue equals 2</span>, the system performs task deletion.</p>
                    <h4>Action:</h4>
                    <p>Similar to Case 1, ExampleTask2 is completely removed from the system, but triggered by DataValue instead of dataID.</p>
                </div>
                
                <div class="image-container">
                    <img src="https://github.com/user-attachments/assets/1d5a64b7-e48e-4079-972d-ba21d2255b2b" alt="Case 4 Output" class="case-image">
                    <p><em>Serial output showing task deletion when DataValue = 2</em></p>
                </div>

                <div class="output-section">
                    <h4>Expected Output:</h4>
                    <div class="output-text">Serial Port COM3 opened
Integer Queue Created successfully

ExampleTask1
is sending data to the queue

Received data with ID 1 and Value 2 from the queue

After evaluation dataID: 1 and DataValue: 2
ExampleTask2 deleted
Serial Port COM3 closed</div>
                </div>
            </div>
        </div>

        <div class="footer">
            <p>This demonstration showcases the flexibility and power of FreeRTOS task management on STM32 microcontrollers.</p>
            <p><strong>Developed for STM32-F401Re | FreeRTOS Real-Time Operating System</strong></p>
        </div>
    </div>
</body>
</html>
