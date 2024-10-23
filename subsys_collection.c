#include "subsystem.h"
#include <string.h>

/*
    This file should contain your documentation and implementations for SubsystemCollection 
    specific functionality; initialization, appending, removal, printing, finding, and filtering.
*/

/*
	Initializes a SubsystemCollection with size 0
	
	in/out: subsystems, initializes SubsystemCollection structure that is passed in
	
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
	printf("            name| status| data\n");
	printf("------------------------------\n");
	for (int i=0; i<subsystems->size; i++){
		subsys_print(&(subsystems->subsystems[i]));
	}
	return ERR_SUCCESS;
}
