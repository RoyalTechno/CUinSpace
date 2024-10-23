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
//gcc -o main main.c subsys.c subsys_collection.c subsystem.h
int print_menu(int *choice);

int main() {
    // Use a while loop to print the menu for the user and call the appropriate functions.
    // The definitions above are provided to assist with this.
    int query;
    
    while (print_menu(&query)==ERR_SUCCESS){
    	if (query==MENU_ADD){
    	} else if (query==MENU_PRINT){
    	} else if (query==MENU_PRINTALL){
    	} else if (query==MENU_STATUS){
    	} else if (query==MENU_REMOVE){
    	} else if (query==MENU_FILTER){
    	} else if (query==MENU_DATA){
    	} else{
    		break;
    	}	
    }
    
    Subsystem sub;
    const char *n = "mike";
    char j='j';
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
