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

/*
	Removes subsystem at given index and keeps order by shifting

	out: subsystems, collection from which to remove system at index
	in: index, int specifying index of system to remove
	
	Returns:
		- ERR_NULL_POINTER if subsystems is NULL
		- ERR_INVALID_INDEX if index is outside of expected range
		- ERR_NO_DATA if there is no systems to remove
		- ERR_SUCCESS if there is no error
*/
int subsys_remove(SubsystemCollection *subsystems, int index){
	if (subsystems==NULL){
		return ERR_NULL_POINTER;
	}
	if (subsystems->size==0){
		return ERR_NO_DATA;
	}
	if (index < 0 || index >= subsystems->size){
		return ERR_INVALID_INDEX;
	}
	
	for(int i=index; i<(subsystems->size)-1; i++){
		subsystems->subsystems[i] = subsystems->subsystems[i+1];
	}
	subsystems->size--;
	return ERR_SUCCESS;
}

/*
	Outputs filtered collection of systems to dest according to filter
	
	in: src, collection of systems to filter
	out: dest, collection to store filtered systems
	in: filter, 8-character string specifying filtering
	
	Returns:
		- ERR_NULL_POINTER if src or dest or filter is NULL
		- ERR_SUCCESS if there is no error
		- ERR_NO_DATA if the filter string has no matching data
*/
int subsys_filter(const SubsystemCollection *src, SubsystemCollection *dest, const unsigned char *filter){
	if (src==NULL||dest==NULL||filter==NULL){
		return ERR_NULL_POINTER;
	}
	if (strlen(filter)!=8){
		return ERR_NO_DATA;
	}
	unsigned char wildcard = 0;
	unsigned char filter_mask = 0;
	//construct bitmasks
	for (int i=0; i<8; i++){
		if (filter[i] == '1'){
			filter_mask = (filter_mask | (1 << (7-i)));
		} else if (filter[i] == '*'){
			wildcard = wildcard | (1 << (7-i));
		} else if (filter[i] != '0'){
			return ERR_NO_DATA;
		}
	}
	filter_mask = ~filter_mask;
	dest->size = 0;
	//check statuses
	for (int n=0; n<src->size; n++){
		if(((filter_mask ^ src->subsystems[n].status) | wildcard)==255){
			dest->subsystems[dest->size] = src->subsystems[n];
			dest->size++;
		}
	}
	return ERR_SUCCESS;
}






