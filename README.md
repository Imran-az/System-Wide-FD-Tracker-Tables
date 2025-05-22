# System Wide FD Tracker Tables

## 1. Metadata
Title: System-Wide FD Tables

Author: Imran Aziz

Date: 09/03/2025

## 2. Introduction/Rationale
The following project allows users to view and display information on files on their computer, which contains PIDs, File Descriptors, Inodes, Filenames.
By levaraging proc we are able to access this information and display it in real time to the users.

## 3. Description of how you solved/approached the problem
The first thing I did when approaching this problem was I began researching through proc and playing around with various commands in the terminal to see and learn how to access 
the information on PIDs, FDs, Inodes, and filenames, and to come up with a general understanding on how each component is related to each other, along with what was available to access.
After this leveraging dirent.h I learned how to open directories and access the information that is stored in them. After having a general idea of how everything works and how to access it, 
I spent some time designing a CDT that would work efficently to store all my data. After I had an idea how I wanted to save my data, I then began to data process, collecting the various data needed
such as PIDs, FDs, Inodes, and Filenames, and saved all the data in my CDT so when any flags were given I could provide the necessary data requested. Finally I then created a way to detect the flags requested by
user and displayed that data.

## 4. Implementation
  1. Createda a CDT which was a linked list of PID values and another linked list inside of it reffering to the FDs, Inodes, and filenames
  2. Processed all the PID values in first
  3. Then by having the PID values I was then able to access all the FDs, Inodes, and Filenames
  5. After having all this information stored in my CDT I then worked on detecting which flags are requested by the user and depending on which
  are I printed that information

## 5. Pseudo-code 
  1. Parse in PID Values
  2. Parse in FDs, Inodes, and Filenames
  3. Created printing functions for each CLA
  4. Parse in CLA
  5. Check if CLA is valid
  6. CLA 1: --per-process - displays PIDs and FDs
  7. CLA 2: --systemWide - displays PIDs, FDs, and Filenames
  8. CLA 3: --Vnodes - displays FDs and Inodes
  9. CLA 4: --composite - displays PIDs, FDs, Inodes, and Filenames
  10. CLA 5: --summary - displays PIDs along with how many FDs it has 
  11. CLA 6: --threshold - Given a threshold displays all PIDs where the number of FDs are greater than the threshold
  12. Prints out the data related to the flagged CLA

  FLOW DIAGRAM:
  
  
  ![B09 A2 drawio](https://gist.github.com/user-attachments/assets/e390fdc8-bfb9-4472-a3cc-a98a4c33198d)


  
 ## 6. Instructions on how to compile your code
 IMPORTANT: whenever giving CLAs at the end please provide ( | less), also the positional argument must always follow the executable file and be the first argument after ./output
 FIRST: Ensure all files are open so all c files header files and makefile then: 
  1. type in make to compile the code:
  ```sh
  make
  ``` 
  4. type in ./output and what ever CLA you want: Please add: (| less) to see all information clearly:
  ```sh
  ./output --per-process | less  
  ```
  5. example of providing a certain PID along with the CLA:
  ```sh
  ./output 46581 --composite --Vnodes | less  
  ```
  
  ## 7. Expected Results
  1. If ./output is only provided the composite table will be shown
  ```sh
  ./output | less  
  ```
  2. If ./output and a specific PID value is given all CLAs will be flagged and display all tables related to that specific   PID whihc include per-process, systemWide, Vnodes, composite
  ```sh
  ./output 719566 | less  
  ```
  3. If ./output and a specific PID value is given along with certain CLAs information on the CLAs flagged will only show up
  ```sh
  ./output 719566 --per-process --Vnodes | less 
  ```
  4. If ./output and summary is given a summary of all PIDs along with their FDs are given, this remains true even if a       specific PID value is given. The summary flag will always show all the PID values
  ```sh
  ./output --summary | less  
  ```
  5. If ./output and threshold CLA is given all PIDS that have number of FDs greater than the threshold will be displayed
  ```sh
  ./output --threshold=15 | less  
  ```
  6. if ./output, summary and threshold CLA are given, then the table for both summary and threshold will be printed
  ```sh
  ./output --summary --threshold=20 | less  
  ```
  7. CLA can also be given in any order
  ```sh
  ./output --Vnodes --per-process --composte | less  
  ```
## 8. Test Cases for unexpected behaviour or ERRORS
  1. if ./output is given and the same given CLA is given twice this will result in an ERROR
  ```sh
  ./output --summary --per-process --summary | less  
  ```
  2. if ./output is given along with a threshold where the threshold provided is not a number value this will result in an      ERROR
  ```sh
  ./output --threshold=20dgfg5 | less  
  ```
  3. if ./output is given along with a CLA spelt wrong this will result in an ERROR
  ```sh
  ./output --summarygreer | less  
  ```
## 9. Disclaimers
  1. Always provide ( | less) after CLAs 

## 10. References
  1. Used linux/limts so I can use PATH_MAX - https://stackoverflow.com/questions/73168335/difference-between-include-limits-h-and-inlcude-linux-limits-h
  2. For printing used width specfiers - https://stackoverflow.com/questions/59993878/using-width-specifier-with-printf-with-no-variable
  3. For printing used left align - https://www.geeksforgeeks.org/printf-in-c/, https://pubs.opengroup.org/onlinepubs/009696799/functions/stat.html
  4. For stat I used the following resources - https://man7.org/linux/man-pages/man2/stat.2.html,             https://stackoverflow.com/questions/3138600/correct-use-of-stat-on-c, 
  5. For readlink I used the following resources - https://man7.org/linux/man-pages/man2/readlink.2.html, https://stackoverflow.com/questions/16117610/using-file-descriptors-with-readlink
  6. For opendir, readdir I used the following resources - https://pubs.opengroup.org/onlinepubs/009604599/functions/opendir.html, https://pubs.opengroup.org/onlinepubs/009604599/basedefs/dirent.h.html
  7. For linked list - https://www.geeksforgeeks.org/linked-list-of-linked-list/
  8. To ensure I do not get a defined implicitly error, I used the following -D_POSIX_C_SOURCE=200809L which I got from the following resource - https://stackoverflow.com/questions/66862654/why-does-my-compiler-think-my-readlink-is-implicitly-declared-if-i-set-the-sta
