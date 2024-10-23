#include "subsystem.h"
#include <string.h>

/*
    This file should contain the implementations for Subsystem specific functionality.
    Initialization, printing, setting and getting data and statuses.
*/

/*
	Initializes a subsystem with provided name and status with default data at 0
	
	in/out: subsystem, initializes Subsystem structure that is passed in
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
	Appends a copy of the subsystem parameter into the collection
	
	in/out: subsystems, appends subsystem to its array attribute
	in: subsystem, subsystem to be added to collection array
	Returns: 
        - ERR_SUCCESS if there is no error
        - ERR_NULL_POINTER if subsystems or subsystem is NULL
        - ERR_MAX_CAPACITY if array is full
*/
int subsys_append(SubsystemCollection *subsystems, const Subsystem *subsystem){
	if(subsystems==NULL||subsystem==NULL){
		return ERR_NULL_POINTER;
	}
	if(subsystems->size >= MAX_ARR){
		return ERR_MAX_CAPACITY;
	}
	subsystems->subsystems[subsystems->size] = *subsystem;
	subsystems->size++;
	return ERR_SUCCESS;
}

/*
	Finds index of subsystem in subsystems based on name
	
	in: subsystems, collection in which to search through its subsystem array
	in: name, pointer to string we want to match in the subsystem name attribute
	
	Returns:
		- ERR_NULL_POINTER if subsystems or name is NULL
		- INDEX of matching subsystem
		- ERR_SYS_NOT_FOUND if name had no match in collection array
*/
int subsys_find(const SubsystemCollection *subsystems, const char *name){
	if (subsystems==NULL||name==NULL){
		return ERR_NULL_POINTER;
	}
	
	for(int idx=0; idx<subsystems->size;idx++){
		if(strcmp(name,subsystems->subsystems[idx].name)==0){
			return idx;
		}
	}
	return ERR_SYS_NOT_FOUND;
}


int subsys_print(Subsystem *subsystem){
	if(subsystem==NULL){
		return ERR_NULL_POINTER;
	}
	printf("%16s|%7d|%5d\n",subsystem->name,subsystem->status,subsystem->data);
	return ERR_SUCCESS;
}


