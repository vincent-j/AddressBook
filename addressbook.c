/*
 * addressbook.c
 *
 *         Ver.: 0.1b
 *   Created on: July 20, 2012
 *  Finished on: July 23, 2012
 *       Author: Vincent
 */

/***************************** Include Files *********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************** Global variable definition *****************************/

/* address entry data structure */
struct personal{
    char name[30];                  /* name of the person */  
    char mobile[12];                /* mobile number of the person */
    char address[40];               /* home address of the person */
    struct personal *next;          /* pointer to next entry */
 };

struct personal *head, *last;       /* head & tail pointer of the address linklist */
int addr_num = 0;                   /* number of address entries */
struct personal *addr_info[100];    /* search result */
char file_name[100];                /* file name record */

/************************** Sub-function declaration *****************************/
int addr_command();                                            /* Command line */
void inputs(char *explain, char *valueAddr, int count);        /* Input function */
struct personal *des_store(struct personal *info);             /* Add a node to linklist */
void addr_add();                                               /* Add an address entry */
void addr_display_all(struct personal *head);                  /* Display all the address entries */
int addr_find(int choice);                                     /* Find address entries */
void addr_delete();                                            /* Delete address entries by name|mobile|address */
void addr_search();                                            /* Search address entries by name|mobile|address */
void addr_help();                                              /* Help information */
void addr_display_a(struct personal **info, int result);       /* Display node infomation */
int addr_strcmp(char * dest, char *src);                       /* Sub-string matching */
int addr_save(int argc);                                       /* Save to an addressbook file */
int addr_reload();                                             /* Reload an addressbook file */
int addr_load_file();                                          /* To edit an existed addressbook file ,load the file first */
void validate_arg(int argc, char **argv);                      /* Validate command line arguments */

/************************** Main function *****************************/
int main(int argc, char **argv){
	FILE *cf_ptr;
    head = last = NULL;
    validate_arg(argc, argv);
    if (argc == 3){
        if ((strcmp(&argv[2][0], "-new")) == 0){
        	if ((cf_ptr = fopen(&argv[1][3], "w+")) == NULL){
        		printf("Could not open file! First create Failed! \n");
        		return 1;
            }
            printf("First create OK!\n");
            strcpy(file_name, &argv[1][3]);
        }
    printf("The file path and name is: %s\n", &argv[1][3]);
    }
    if (argc == 2){
    	if ((cf_ptr = fopen(&argv[1][3], "r+")) == NULL){
        		printf("Could not open file! \n");
        		printf("The file which you assigned may be NOT exist.\n");
        		return 1;
            }
            printf("Open file: %s successfully!\n", &argv[1][3]);            
            strcpy(file_name, &argv[1][3]);
            addr_load_file();
    }
    printf("-------------------------------\n");
    printf("AddressBook released by Vincent\n");
    printf("----------- Ver. 0.1b ---------\n");
    
    while (1){
        switch (addr_command()){
        case 1:    addr_add(); 
                   break;
        case 2:    addr_display_all(head); 
                   break;
        case 3:    addr_delete(); 
                   break;
        case 4:    addr_search(); 
                   break;
        case 5:    addr_reload(); 
                   break;
        case 6:    addr_save(argc); 
                   break;
        case 7:    addr_help(); 
                   break;
        case 8:    return(0);
         
        }
   }
}

/* Command line */
int addr_command(){
    int choice;
    char command[30];
    printf("addressbook>");  
    fgets(command, sizeof(command), stdin);  
    command[strlen(command) - 1] = '\0';
    
    while (strcmp(command, "add") && strcmp(command, "display") && strcmp(command, "delete") && strcmp(command, "search") 
           && strcmp(command, "reload") && strcmp(command, "!help") && strcmp(command, "!quit") && strcmp(command, "save")){
        printf("%s: COMMAND NOT FOUND\n", command);
        printf("Please type '!help' to get more help.\n");
        printf("addressbook>");
        fgets(command, sizeof(command), stdin);  
        command[strlen(command) - 1] = '\0';
    }
    if (!strcmp(command, "add")) choice = 1;
    if (!strcmp(command, "display")) choice = 2;
    if (!strcmp(command, "delete")) choice = 3;
    if (!strcmp(command, "search")) choice = 4;
    if (!strcmp(command, "reload")) choice = 5;
    if (!strcmp(command, "save")) choice = 6;
    if (!strcmp(command, "!help")) choice = 7;
    if (!strcmp(command, "!quit")) choice = 8;		
   
    return(choice);
}

/* Add a node to linklist */
struct personal *des_store(struct personal *info){
    if (last){ 
        last->next = info;
    }
    info->next = NULL;
    last = info;
    return(info);
}

/* Add an address entry */
void addr_add(){
    struct personal *info;
    info = (struct personal *)malloc(sizeof(struct personal));
    if (info == NULL){ 
        printf("\nOut of memory!\n");
        return;
    }
    inputs("name:", info->name, 30);
    inputs("mobile:", info->mobile, 12);
    inputs("address:", info->address, 40);    
    info = des_store(info);
    if (addr_num == 0) head = info; 
    printf("Address entry added.\n\n");
    addr_num++;
}

/* Input function */
void inputs(char *explain, char *valueAddr, int count){
    char valueStr[40];
    do{
        printf("%s", explain);
        fgets(valueStr, sizeof(valueStr), stdin);  
        valueStr[strlen(valueStr) - 1] = '\0';
        if (strlen(valueStr) >= count) printf("Too long!\n\n");
    }while (strlen(valueStr) >= count);
    strcpy(valueAddr, valueStr);
}

/* Display node infomation */
void addr_display_a(struct personal **info, int result){
    int i;
    if (result == 1)
    	printf("1 search result:\n");
    else
        printf("%d search results:\n", result);
    printf("---------------------------\n");
    for (i = 0; i < result; i++){
        printf("name: %s\n", (*info)->name);
        printf("mobile: %s\n", (*info)->mobile);
        printf("address: %s\n\n", (*info)->address);
        printf("---------------------------\n");
        info++;
    }
}

/* Display all the address entries */
void addr_display_all(struct personal *head){
    struct personal *p;
    int count = 1;
    p = head;
    if(head != NULL){
        do{
            printf("record %d:\n",count++);
            printf("---------------------------\n");
            printf("name: %s\n", p->name);
            printf("mobile: %s\n", p->mobile);
            printf("address: %s\n\n", p->address);
            p = p->next;
        }while (p != NULL);
    }
    else  
        printf("No data!\n\n");
}

/* Find address entries */
int addr_find(int choice){
    struct personal *info;
    info = head;
    char entry[30]; 
    size_t n;
    int result = 0;
    switch (choice){
    case 1:  printf("name:");
    	     fgets(entry, sizeof(entry), stdin);  
             entry[strlen(entry) - 1] = '\0';
      	     n = strlen(entry);
             if ((entry[n - 2] == '.') && (entry[n - 1] == '*')){            //use '.*' command to search
                 entry[n - 2] = '\0';
                 while (info){
                     if (!addr_strcmp(entry, info->name)){
                         addr_info[result++] = info;
                         info = info->next;
                     }
                     else info = info->next;
                 }
                 break;	
             }
      	     while (info){
                 if (!strcmp(entry, info->name)){
                     addr_info[result++] = info;
                     info = info->next;
                 }
                 else info = info->next;
             } break;
    case 2:  printf("mobile:");
      	     fgets(entry, sizeof(entry), stdin);  
             entry[strlen(entry) - 1] = '\0';
      	     n = strlen(entry);
             if ((entry[n - 2] == '.') && (entry[n - 1] == '*')){             //use '.*' command to search
                 entry[n - 2] = '\0';
                 while (info){
                     if (!addr_strcmp(entry, info->mobile)){
                         addr_info[result++] = info;
                         info = info->next;
                     }
                     else info = info->next;
                 }
                 break;	
             }    
      	     while (info){
                 if (!strcmp(entry, info->mobile)){ 
                     addr_info[result++] = info;
                     info = info->next;
                 }
                 else info = info->next;
             } break;
    case 3:  printf("address:");
      	     fgets(entry, sizeof(entry), stdin);  
             entry[strlen(entry) - 1] = '\0';
      	     n = strlen(entry);
             if ((entry[n - 2] == '.') && (entry[n - 1] == '*')){              //use '.*' command to search
                 entry[n - 2] = '\0';
                 while (info){
                     if (!addr_strcmp(entry, info->address)){
                         addr_info[result++] = info;
                         info = info->next;
                     }
                     else info = info->next;
                 }
                 break;	
      	     }
      	     while (info){
                 if (!strcmp(entry,info->address)){
                     addr_info[result++] = info;
                     info = info->next;
                 }
                 else info = info->next;
             } break;
    }       
    return(result);
}

/* Search address entries by name|mobile|address */
void addr_search(){
    char entry[30];
    int result;
    int choice;
    printf("by (name|mobile|address): ");
    fgets(entry, sizeof(entry), stdin);  
    entry[strlen(entry) - 1] = '\0';
    while (strcmp(entry, "name") && strcmp(entry, "mobile") && strcmp(entry, "address")){
        printf("Invalid input! Please reenter your choice.\n");
        printf("by (name|mobile|address): ");
        fgets(entry, sizeof(entry), stdin);  
        entry[strlen(entry) - 1] = '\0';
    }
   
    if (!strcmp(entry, "name")) choice = 1;
    if (!strcmp(entry, "mobile")) choice = 2;
    if (!strcmp(entry, "address")) choice = 3;
   
    if (!(result = addr_find(choice))){
        printf("Address entry not found!\n\n");
    }
    else
        addr_display_a(addr_info, result);
}


/* Delete address entries by name|mobile|address */
void addr_delete(){
    char entry[30];
    int result, choice, n;
    struct personal *p1, *p2;
    struct personal **info_ptr = addr_info;
    
    printf("by (name|mobile|address): ");
    fgets(entry, sizeof(entry), stdin);  
    entry[strlen(entry) - 1] = '\0';
    
    while (strcmp(entry, "name") && strcmp(entry, "mobile") && strcmp(entry, "address")){
        printf("Invalid input! Please reenter your choice.\n");
        printf("by (name|mobile|address): ");
        fgets(entry, sizeof(entry), stdin);  
        entry[strlen(entry) - 1] = '\0';
    }
    if (!strcmp(entry, "name")) choice = 1;
    if (!strcmp(entry, "mobile")) choice = 2;
    if (!strcmp(entry, "address")) choice = 3;

    if (result = n = addr_find(choice)){ 
    	while (result--){
            if (addr_num == 1){                                          /* if only 1 node */
                head = last = NULL;
                free(*info_ptr);
                *info_ptr = NULL;
            }
            else{
                if (*info_ptr == last){                                  /* to delete the tail node */
                    p2 = head;
                    p1 = head->next;
                    while(p1->next != NULL){ 
                        p2 = p1;
                        p1 = p1->next;
                    }
                    p2->next = NULL;
                    last = p2;
                    free(*info_ptr);
                    *info_ptr = NULL;
                    info_ptr++;
                }
                else if (head == *info_ptr){                             /* to delete the head node */
                    head = (*info_ptr)->next;
                    free(*info_ptr); 
                    *info_ptr = NULL;
                    info_ptr++;
                }
                else if ((*info_ptr != head) && (*info_ptr != last)){    /* to delete the intermediate node */
                    p2 = head; 
                    p1 = head->next; 
                    while (*info_ptr != p1){
                        p2 = p1;
                        p1 = p1->next;
                    }
                    p2->next = p1->next;
                    free(*info_ptr);
                    *info_ptr = NULL;
                    info_ptr++;
                
                }
            }
            addr_num--;
        }
        if (n == 1)
            printf("1 address entry deleted.\n");  
        else
        	printf("%d address entries deleted.\n", n);   
    }
    else{ 
        printf("Address entry not found!\n");
    }
    printf("\n");
}

/* Help information */
void addr_help(){
	printf("---------Help information--------\n");
	printf("The address commands are defined internally.\n");
	printf("------To create or reload file-----\n");
	printf(" ./a.out -f:[path][filename] [-new]\n");
    printf(" '-f:' to assign the file path and name.\n");
    printf(" '-new' to creat a new addressbook file. \n");
    printf("------ Address entries operation -----\n");
    printf(" Type 'add'    command to add new address entry.\n");
    printf(" Type 'search' command to get one or more address entries.\n");
    printf(" Type 'delete' command to remove one or more address entries.\n");
    printf(" Type 'reload' command to reload an addressbook file.\n");
    printf(" Type 'save'   command to save to an addressbook file.\n");
    printf(" Type '!help'  command to get help.\n");
    printf(" Type '!quit'  command to quit from the application.\n");
}   

/* Sub-string matching */
int addr_strcmp(char *dest, char *src){
    while (*dest != '\0'){
        if (*dest == *src){
            dest++;
            src++;
        }
        else 
            return 1;	
    }
    return 0;    
}

/* Save to an addressbook file */
int addr_save(int argc){
    FILE *cf_ptr; 
    struct personal *node_ptr;
    if (argc == 1){
        printf("file path: ");
        fgets(file_name, sizeof(file_name), stdin);  
        file_name[strlen(file_name) - 1] = '\0';
        cf_ptr = fopen(file_name, "w+");
    }
    cf_ptr = fopen(file_name, "w+");
    if (cf_ptr == NULL){
        printf("Could not open file! \n");
        printf("The file which you assigned may be NOT exist.\n");
        return 1;
    }
    printf("Now saving...\n");
    fwrite(&addr_num, sizeof(int), 1, cf_ptr);
    for (node_ptr = head; node_ptr != NULL; node_ptr = node_ptr->next){
        fwrite(node_ptr, sizeof(struct personal), 1, cf_ptr);
    }
    printf("Successfully saved!\n");
    fclose(cf_ptr);
    return 0;
}

/* Reload an addressbook file */
int addr_reload(){
	FILE *cf_ptr; 
    struct personal *node_ptr;
    int n = 0;
    printf("file path: ");
    fgets(file_name, sizeof(file_name), stdin);  
    file_name[strlen(file_name) - 1] = '\0';
    printf("Now reloading...\n");
    if ((cf_ptr = fopen(file_name, "r+")) == NULL){
        printf("Could not open file! \n");
        printf("The file which you assigned may be NOT exist.\n");
        return 1;
    }
    fread(&addr_num, sizeof(int), 1, cf_ptr);
    while (n < addr_num){
    	node_ptr = (struct personal *)malloc(sizeof(struct personal));
    	if (node_ptr == NULL){ 
            printf("\nOut of memory!\n");
            return 1;
        }  
        fread(node_ptr, sizeof(struct personal), 1, cf_ptr);
        node_ptr = des_store(node_ptr);
        if (n == 0) head = node_ptr; 
        n++;
    }
    printf("Successfully reloaded!\n");
    fclose(cf_ptr);
    return 0;
}

/* To edit an existed addressbook file ,load the file first */
int addr_load_file(){
	FILE *cf_ptr; 
    struct personal *node_ptr;
    int n = 0;   
    if ((cf_ptr = fopen(file_name, "r+")) == NULL){
        printf("Could not open file! \n");
        printf("The file which you assigned may be NOT exist.\n");
        return 1;
    }
    fread(&addr_num, sizeof(int), 1, cf_ptr);
    while (n < addr_num){
    	node_ptr = (struct personal *)malloc(sizeof(struct personal));
    	if (node_ptr == NULL){ 
            printf("\nOut of memory!\n");
            return 1;
        }  
        fread(node_ptr, sizeof(struct personal), 1, cf_ptr);
        node_ptr = des_store(node_ptr);
        if (n == 0) head = node_ptr; 
        n++;
    }
    fclose(cf_ptr);
    return 0;
}

/* Validate command line arguments */
void validate_arg(int argc, char **argv){
    if ((argc != 1) && (argc != 2) && (argc != 3)){
    	printf("Invalid Arguments!\n");
    	printf("Please type '!help' to get more help.\n\n");
    	exit(1);
    }
    if (argc==3){ 
        if ((strcmp(&argv[2][0], "-new")) != 0){
            printf("If you want creat new file ,use '-new'.\n");
            printf("Please type '!help' to get more help.\n\n");
            exit(1);
        }
        else
            printf("Creat new file for the first use of this software.\n");

    }
    if (argc == 2){
        if ((argv[1][0] != '/') && (argv[1][0] != '-')){ 
        	printf("Invalid Arguments!\n");
        	printf("Argument must start with character '/' or '-'.\n");
        	printf("Please type '!help' to get more help.\n\n");
        	exit(1);
        }
        if (argv[1][1] != 'f'){
        	printf("Invalid Arguments!\n");
        	printf("the character assigned file path and name must be 'f'.\n");
        	printf("Please type '!help' to get more help.\n\n");
        	exit(1);
        }
        if (argv[1][2] != ':'){
        	printf("Invalid Arguments!\n");
        	printf("Between '-f' and [path][filename] must be ':'.\n");
        	printf("Please type '!help' to get more help.\n\n");
        	exit(1);
        }
    }
}
