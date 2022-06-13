# Predictive-Maintenance-Simulation

## Table of contents
* [General Info](general-info)
* [Languages](#languages)
* [Configuration](#configuration)

## General Info
Simulation for Cordis Machine which has TCP/IP communication and which  can create temperature simulation datas and save those to .csv files to be used in CPM-79-update-predictive-algorithm.  

## Languages
C++ used as a main programming language.  

## Configuration 
To use this software you need to make some minor changes from the code according to your wishes:  
* If you want to create a fault simulation and save it to .csv file, change the definition ```#define CREATE_FAULT_TEMP_SIM (0)``` to ```#define CREATE_FAULT_TEMP_SIM (1)``` in main.  
* If you want to create a normal simulation and save it to .csv file, change the definition ```#define CREATE_TEMP_SIM (0)``` to ```#define CREATE_TEMP_SIM (1)``` in main.  
* Set port and IP of the server according to your setup from definitions ```#define PORT 54000``` and ```#define IP "192.168.80.107"``` from TCP_IP.h .  
* Set deviceRole to ```device.deviceRole = device.deviceClient;``` if the device will be client. If the device will be a server change this line to ```device.deviceRole = device.deviceServer;``` from main.cpp .  

