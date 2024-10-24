#include "subsystem.h"
#include <string.h>

/*
    This file should contain your documentation and implementations for SubsystemCollection 
    specific functionality; initialization, appending, removal, printing, finding, and filtering.
*/

/*
	Initializes a SubsystemCollection with size 0
	
	out: subsystems, initializes SubsystemCollection structure that is passed in
	
	Returns: 
        - ERR_SUCCESS if there is no error
        - ERR_NULL_POINTER if subsystems is NULL
*/
int subsys_collection_init(SubsystemCollection *subsystems){
	if (subsystems==NULL){
		return ERR_NULL_POINTER;
	}
	subsystems->size = 0;
	return ERR_SUCCESS;
}

/*
	Appends a copy of the subsystem parameter into the collection
	
	out: subsystems, appends subsystem to its array attribute
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

/*
	Prints all subsystems within the collection's array
	
	in: subsystems, collection which we want to use
	
	Returns:
		- ERR_NULL_POINTER if subsystems is NULL
		- ERR_NO_DATA if subsystems' array is empty
		- ERR_SUCCESS if there is no error
*/
int subsys_collection_print(SubsystemCollection *subsystems){
	if (subsystems==NULL){
		return ERR_NULL_POINTER;
	}
	if (subsystems->size==0){
		return ERR_NO_DATA;
	}
	for (int i=0; i<subsystems->size; i++){
		subsys_print(&(subsystems->subsystems[i]));
	}
	return ERR_SUCCESS;
}



int subsys_remove(SubsystemCollection *subsystems, int index){
	return ERR_SUCCESS;
}


int subsys_filter(const SubsystemCollection *src, SubsystemCollection *dest, const unsigned char *filter){
	return ERR_SUCCESS;
}






