#include "subsystem.h"
#include <string.h>

/*
    This file should contain the implementations for Subsystem specific functionality.
    Initialization, printing, setting and getting data and statuses.
*/

/*
	Initializes a subsystem with provided name and status with default data at 0
	
	out: subsystem, initializes Subsystem structure that is passed in
	in: name, pointer to string to set subsystem name attribute to
	in: status, value to set subsystem status attribute to
	
	Returns: 
        - ERR_SUCCESS if there is no error
        - ERR_NULL_POINTER if subsystem or name is NULL
*/
int subsys_init(Subsystem *subsystem, const char *name, char status){
	if (subsystem==NULL||name==NULL){ 
		return ERR_NULL_POINTER;
	}
	strncpy(subsystem->name,name,MAX_STR);
	subsystem->name[MAX_STR - 1] = '\0';
	subsystem->status = status;
	subsystem->data = 0;
	return ERR_SUCCESS;
}

/*
	Print all info of subsystem formatted
	
	in: subsystem, specifies subsystem to print
	
	Returns:
		- ERR_NULL_POINTER if subsystem is NULL
		- ERR_SUCCESS if no errors
*/
int subsys_print(Subsystem *subsystem){
	if(subsystem==NULL){
		return ERR_NULL_POINTER;
	}
	printf("- [Name: %16s, ",subsystem->name);
	subsys_status_print(subsystem);
	unsigned int data = 0;
    int result = subsys_data_get(subsystem,&data);
    if (result==ERR_NO_DATA){
    	printf("]\n");
    } else {
		printf(", Data: 0x%08X]\n",data);
	}
	return ERR_SUCCESS;
}

/*
	Updates status of subsystem with the provided value fint subsys_status_print(const Subsystem *subsystem);or the system matching status
	
	out: subsystem, status of this system will be updated
	in: status, identifier for which system to update
	in: value, specifies value to set in system
	
	Returns:
		- ERR_NULL_POINTER if subsystem is NULL
		- ERR_INVALID_STATUS if status or value out of range
		- ERR_SUCCESS if no errors
*/
int subsys_status_set(Subsystem *subsystem, unsigned char status, unsigned char value){
	if(subsystem==NULL){
		return ERR_NULL_POINTER;
	}
	
	if((status!=STATUS_POWER && status!=STATUS_DATA && status!=STATUS_ACTIVITY &&
		status!=STATUS_ERROR && status!=STATUS_PERFORMANCE && status!=STATUS_RESOURCE) ||
		value < 0 || value > 3 || (status!=STATUS_PERFORMANCE&&status!=STATUS_RESOURCE&&value>1)){
		return ERR_INVALID_STATUS;
	}
	
	int i=0;
	//update 1 to 1 to clear second bit
	if (status==STATUS_PERFORMANCE||status==STATUS_RESOURCE){
		i=1;
	}
	//clear bit at position status and status+i
	subsystem->status = (subsystem->status) & (~((1 << status)|(1 << (status+i))));
	//set bit
	subsystem->status = (subsystem->status) | (value << status);
	return ERR_SUCCESS;
}

/*
	Prints status of subsystem formatted
	
	in: subsystem, system to use and print its status info
	
	Returns:
		- ERR_NULL_POINTER if subsystem is NULL
		- ERR_SUCCESS if no errors
*/
int subsys_status_print(const Subsystem *subsystem){
	if (subsystem==NULL){
		return ERR_NULL_POINTER;
	}
	int pwr = (subsystem->status & (1 << STATUS_POWER)) >> STATUS_POWER;
	int data = (subsystem->status & (1 << STATUS_DATA)) >> STATUS_DATA;
	int act = (subsystem->status & (1 << STATUS_ACTIVITY)) >> STATUS_ACTIVITY;
	int err = (subsystem->status & (1 << STATUS_ERROR)) >> STATUS_ERROR;
	int perf = (subsystem->status & (3 << STATUS_PERFORMANCE)) >> STATUS_PERFORMANCE;
	int res = (subsystem->status & (3 << STATUS_RESOURCE)) >> STATUS_RESOURCE;
	
	printf("Status: (PWR: %d|DATA: %d|ACT: %d|ERR: %d|PERF: %d|RES: %d)",pwr,data,act,err,perf,res);
	return ERR_SUCCESS;
}

/*
	Sets data in subsystem and indicates in data queue status field
	
	out: subsystem, indicates system to update
	in: new_data, data value to set in subsystem
	out(optional): old_data, set passed in pointer to previous data value
	
	Returns:
		- ERR_NULL_POINTER if subsystem is NULL
		- ERR_SUCCESS if no errors
*/
int subsys_data_set(Subsystem *subsystem, unsigned int new_data, unsigned int *old_data){
	if (subsystem==NULL){
		return ERR_NULL_POINTER;
	}
	if(old_data!=NULL){
		*old_data = subsystem->data;
	}
	subsystem->data = new_data;
	subsys_status_set(subsystem,STATUS_DATA,1);
	return ERR_SUCCESS;
}


/*
	Retrieves data of subsystem and clears data and queue
	
	out: subsystem, system to retrieve from and reset
	out: dest, pointer to update with data value
	
	Returns:
		- ERR_NULL_POINTER if subsystem or dest is NULL
		- ERR_NO_DATA if no data queued
		- ERR_SUCCESS if no errors
*/
int subsys_data_get(Subsystem *subsystem, unsigned int *dest){
	if(subsystem==NULL||dest==NULL){
		return ERR_NULL_POINTER;
	}
	//read bit at data position
	if((subsystem->status & (1 << STATUS_DATA)) >> STATUS_DATA){
		*dest = subsystem->data;
		subsystem->data = 0;
		//clear bit at data position
		subsystem->status = (subsystem->status) & (~(1 << STATUS_DATA));
		return ERR_SUCCESS;
	} else {
		*dest = 0;
		return ERR_NO_DATA;
	}
}










