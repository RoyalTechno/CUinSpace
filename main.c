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
    unsigned char filter[8];
    char cur_name[MAX_STR];
    SubsystemCollection systems;
    subsys_collection_init(&systems);
    SubsystemCollection filtered_systems;
    subsys_collection_init(&filtered_systems);
    
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
		    	continue;
		    }
		    printf("System added successfully.\n");
		    
    	} else if (query==MENU_PRINT){
		    printf("Enter subsystem name to print: ");
		    scanf("%s", cur_name);
		    while (getchar() != '\n');
		    //print cur_name system in collection
		    result = subsys_find(&systems,cur_name);
		    if (result==ERR_SYS_NOT_FOUND){
		    	printf("Error: Subsystem Not Found. Please try again.\n");
		    	continue;
		    }
		    printf("\n");
		    subsys_print(&(systems.subsystems[result]));
		    
    	} else if (query==MENU_PRINTALL){
    		//print all subsystems in collection
		    printf("\n");
    		result = subsys_collection_print(&systems);
    		if(result==ERR_NO_DATA){
    			printf("No subsystems to print.\n");
    		}
    		
    	} else if (query==MENU_STATUS){
    		printf("Enter: <Subsystem Name> <Status ID, 7,6,5,4,2, or 0)> <New Value (0-3)>: ");
		    scanf("%s %hhu %hhu",cur_name,&status_id,&status_value);
		    while (getchar() != '\n');
		    //find valid system
		    result = subsys_find(&systems,cur_name);
		    if (result==ERR_SYS_NOT_FOUND){
		    	printf("Error: Subsystem Not Found. Please try again.\n");
		    	continue;
		    } //set status of system
		    result = subsys_status_set(&(systems.subsystems[result]),status_id,status_value);
		    if (result==ERR_INVALID_STATUS){
		    	printf("Error: Status ID or Value Invalid. Please try again.\n");
		    	continue;
		    }
		    printf("Status updated successfully.\n");
		    
    	} else if (query==MENU_REMOVE){
    		printf("Enter subsystem name to remove: ");
		    scanf("%s", cur_name);
		    while (getchar() != '\n');
		    //find index in collection and remove
		    result = subsys_remove(&systems,subsys_find(&systems,cur_name));
		    if (result==ERR_INVALID_INDEX){
		    	printf("Error: Subsystem Not Found. Please try again.\n");
		    	continue;
		    }
		    printf("Removed subsystem successfully.\n");
		    
    	} else if (query==MENU_FILTER){
    		printf("Enter filter string (8 characters of 1, 0, *): ");
		    scanf("%s",filter);
		    while (getchar() != '\n');
		    //filter systems in main collection
    		result = subsys_filter(&systems,&filtered_systems,filter);
    		if (result==ERR_NO_DATA){
    			printf("Error: Invalid Filter Provided. Please try again.\n");
    			continue;
    		}  //print all subsystems in collection
		    printf("\n");
    		result = subsys_collection_print(&filtered_systems);
    		if (result==ERR_NO_DATA){
    			printf("No subsystems to prints.\n");
    		}
    		
    	} else if (query==MENU_DATA){
    		printf("Enter: <Subsystem Name> <Data, uppercase hex without 0x>: ");
		    scanf("%s %X",cur_name,&data);
		    while (getchar() != '\n');
    		//find valid system
		    result = subsys_find(&systems,cur_name);
		    if (result==ERR_SYS_NOT_FOUND){
		    	printf("Error: Subsystem Not Found. Please try again.\n");
		    	continue;
		    } //set data of system
		    subsys_data_set(&(systems.subsystems[result]),data,NULL);
		    printf("Data updated successfully.\n");
		    
    	} else{
    		break;
    	}	
    }
    
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
