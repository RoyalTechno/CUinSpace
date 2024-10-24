#include <stdio.h>
#include <stdlib.h>
#include "subsystem.h"

#define MENU_ADD 1
#define MENU_PRINT 2
#define MENU_PRINTALL 3
#define MENU_STATUS 4
#define MENU_REMOVE 5
#define MENU_FILTER 6
#define MENU_DATA 7
#define MENU_EXIT 0
#define MENU_MIN 0
#define MENU_MAX 7

int print_menu(int *choice);

int main() {
    // Use a while loop to print the menu for the user and call the appropriate functions.
    // The definitions above are provided to assist with this.
    //initialize all needed variables and structures
    int query;
    int result=0;
    unsigned char status_id;
    unsigned char status_value;
    unsigned int data;
    char cur_name[MAX_STR];
    SubsystemCollection systems;
    subsys_collection_init(&systems);
    
    while (print_menu(&query)==ERR_SUCCESS){
    	if (query==MENU_ADD){
		    printf("Enter subsystem name (no spaces): ");
		    scanf("%s", cur_name);
		    while (getchar() != '\n');
		    //create system and append
		    Subsystem cur_sys;
		    subsys_init(&cur_sys,cur_name,0);
		    result = subsys_append(&systems,&cur_sys);
		    if(result==ERR_MAX_CAPACITY){
		    	printf("Error: Max System Capacity Reached.\n");
		    }
		    printf("System added successfully.\n");
		    
    	} else if (query==MENU_PRINT){
		    printf("Enter subsystem name to print: ");
		    scanf("%s", cur_name);
		    while (getchar() != '\n');
		    //print cur_name system in collection
		    result = subsys_find(&systems,cur_name);
		    if (result==ERR_SYS_NOT_FOUND){
		    	printf("Error: System Not Found. Please try again.\n");
		    	continue;
		    }
		    printf("\n");
		    subsys_print(&(systems.subsystems[result]));
		    
    	} else if (query==MENU_PRINTALL){
    		//print all subsystems in collection
		    printf("\n");
    		subsys_collection_print(&systems);
    		
    	} else if (query==MENU_STATUS){
    		printf("Enter: <Subsystem Name> <Status ID, 7,6,5,4,2, or 0)> <New Value (0-3)>: ");
		    scanf("%s %hhu %hhu",cur_name,&status_id,&status_value);
		    while (getchar() != '\n');
		    //find valid system
		    result = subsys_find(&systems,cur_name);
		    if (result==ERR_SYS_NOT_FOUND){
		    	printf("Error: System Not Found. Please try again.\n");
		    	continue;
		    } //set status of system
		    result = subsys_status_set(&(systems.subsystems[result]),status_id,status_value);
		    if (result==ERR_INVALID_STATUS){
		    	printf("Error: Status ID or Value Invalid. Please try again.\n");
		    }
		    printf("Status updated successfully.\n");
		    
    	} else if (query==MENU_REMOVE){
    	
    	} else if (query==MENU_FILTER){
    	
    	} else if (query==MENU_DATA){
    		printf("Enter: <Subsystem Name> <Data, uppercase hex without 0x>: ");
		    scanf("%s %X",cur_name,&data);
		    while (getchar() != '\n');
    		//find valid system
		    result = subsys_find(&systems,cur_name);
		    if (result==ERR_SYS_NOT_FOUND){
		    	printf("Error: System Not Found. Please try again.\n");
		    	continue;
		    } //set data of system
		    subsys_data_set(&(systems.subsystems[result]),data,NULL);
		    printf("Data updated successfully.\n");
		    
    	} else{
    		break;
    	}	
    }
    /*
    Subsystem sub;
    const char *n = "mike";
    char j=0;
    printf("subsystem test: %d\n",subsys_init(&sub,n,j));
    
    Subsystem sub2;
    const char *n2 = "john";
    printf("subsystem test: %d\n",subsys_init(&sub2,n2,j));
    
    Subsystem sub3;
    const char *n3 = "fella";
    printf("subsystem test: %d\n",subsys_init(&sub3,n3,j));
    
    Subsystem sub4;
    const char *n4 = "broski";
    printf("subsystem test: %d\n",subsys_init(&sub4,n4,j));
    
    Subsystem sub5;
    const char *n5 = "mate";
    printf("subsystem test: %d\n",subsys_init(&sub5,n5,j));
    
    Subsystem sub6;
    const char *n6 = "bro";
    printf("subsystem test: %d\n",subsys_init(&sub6,n6,j));
    
    Subsystem sub7;
    const char *n7 = "johnny";
    printf("subsystem test: %d\n",subsys_init(&sub7,n7,j));
    Subsystem sub8;
    const char *n8 = "mo";
    printf("subsystem test: %d\n",subsys_init(&sub8,n8,j));
    Subsystem sub9;
    const char *n9 = "pman";
    printf("subsystem test: %d\n",subsys_init(&sub9,n9,j));
    
    SubsystemCollection col;
    printf("collections test: %d\n",subsys_collection_init(&col));
    printf("%d\n",col.size);
    
    printf("append test: %d\n",subsys_append(&col,&sub));
    printf("%d\n",col.size);
    printf("%s\n",col.subsystems[0].name);
    printf("append test: %d\n",subsys_append(&col,&sub2));
    printf("append test: %d\n",subsys_append(&col,&sub3));
    printf("append test: %d\n",subsys_append(&col,&sub4));
    printf("append test: %d\n",subsys_append(&col,&sub5));
    printf("append test: %d\n",subsys_append(&col,&sub6));
    printf("append test: %d\n",subsys_append(&col,&sub7));
    printf("append test: %d\n",subsys_append(&col,&sub8));
    printf("append test: %d\n",subsys_append(&col,&sub9));
    const char *name = "bro";
    printf("find test: %s is at index %d\n",name,subsys_find(&col,name));
    subsys_collection_print(&col);
    printf("status: %d\n",subsys_status_print(&sub));
    unsigned char val = 0;
    printf("status print test: %d\n",subsys_status_set(&sub,STATUS_POWER,val));
    val = 2;
    printf("status set test: %d\n",subsys_status_set(&sub,STATUS_DATA,val));
    printf("status set test: %d\n",subsys_status_set(&sub,STATUS_ACTIVITY,val));
    val = 0;
    printf("status set test: %d\n",subsys_status_set(&sub,STATUS_ERROR,val));
    val = 2;
    printf("status set test: %d\n",subsys_status_set(&sub,STATUS_PERFORMANCE,val));
    val = 1;
    printf("status set test: %d\n",subsys_status_set(&sub,STATUS_RESOURCE,val));
    printf("status print test: %d\n",subsys_status_print(&sub));
    unsigned int old = 0;
    printf("data set test: %d\n",subsys_data_set(&sub2,0x80FA,&old));
    subsys_print(&sub2);
    printf("old data: %u\n",old);
    printf("data set test: %d\n",subsys_data_set(&sub2,2,&old));
    subsys_print(&sub2);
    printf("old data: %u\n",old);
    printf("data set test w/ NULL: %d\n",subsys_data_set(&sub2,10,NULL));
    subsys_print(&sub2);
    printf("data get test: %d\n",subsys_data_get(&sub2,&old));
    subsys_print(&sub2);
    printf("data: %u\n",old);
    printf("data get test: %d\n",subsys_data_get(&sub2,&old));
    subsys_print(&sub2);
    printf("data: %u\n",old);
    printf("data set test: %d\n",subsys_data_set(&sub2,5,&old));
    subsys_print(&sub2);
    printf("data get test: %d\n",subsys_data_get(&sub2,&old));
    subsys_print(&sub2);
    printf("data: %u\n",old);
    printf("data get test: %d\n",subsys_data_get(&sub2,&old));
    subsys_print(&sub2);
    */
    return ERR_SUCCESS;
}

/* 
    Prints a menu to the user and prompts them until they enter a valid menu option.

    out: *choice, an integer corresponding to a MENU_ definition defining the choice made by the user.

    Returns: 
        - ERR_SUCCESS if there is no error
        - ERR_NULL_POINTER if `choice` is NULL

*/
int print_menu(int *choice) {
    if (choice == NULL) {
        return ERR_NULL_POINTER;
    }
    
    *choice = 0;

    do {
        printf("\n--- Subsystem Management Menu ---\n");
        printf("%d. Add Subsystem\n", MENU_ADD);
        printf("%d. Print Subsystem\n", MENU_PRINT);
        printf("%d. Print All Subsystems\n", MENU_PRINTALL);
        printf("%d. Set Subsystem Status\n", MENU_STATUS);
        printf("%d. Remove Subsystem\n", MENU_REMOVE);
        printf("%d. Filter Subsystems\n", MENU_FILTER);
        printf("%d. Set Subsystem Data\n", MENU_DATA);
        printf("%d. Exit\n", MENU_EXIT);
        printf("Select an option: ");
        scanf("%d", choice);
        while (getchar() != '\n');

        if (*choice < MENU_MIN || *choice > MENU_MAX) {
            printf("Error: Invalid choice. Please try again.\n");
        }
    } while (*choice < MENU_MIN || *choice > MENU_MAX);

    return ERR_SUCCESS;
}
