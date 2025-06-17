I use STM32-F401Re microcontroller for this program.
"ExampleTask2 takes data from Queue2 whenever data is available," -- In this i am assuming "Queue2" is a typo mistake as it is not defined in the problem statement.

<img width="469" alt="CASE-1" src="https://github.com/user-attachments/assets/dcb7f781-94b8-4498-9420-16bf420fcbd7" />
This is the output for CASE: if(dataID==0) | Delete ExampleTask2


<img width="326" alt="CASE-2" src="https://github.com/user-attachments/assets/e2e22a91-b2b3-4950-896b-53fedda5118f" />
Output for CASE: if(DataValue==0) | Increase the Priority of ExampleTask2 by 2 from the value given to it at creation

<img width="332" alt="CASE-3" src="https://github.com/user-attachments/assets/22964464-0493-4775-b88d-30ace1b851f5" />
Output for CASE: if(DataValue==1) | Decrease the Priority of ExampleTask2 if previously increased

<img width="298" alt="CASE-4" src="https://github.com/user-attachments/assets/1d5a64b7-e48e-4079-972d-ba21d2255b2b" />
Output for CASE: if(DataValue==2) Delete ExampleTask2



