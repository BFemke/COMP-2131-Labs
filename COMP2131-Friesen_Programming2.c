/*
Name:Barbara Emke
ID: T00721475
Class: COMP 2131

Program that helps manage Student records
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// student type definition
typedef struct{
        char id[10];
        char name[30];
        char email[30];
        char course[10];
        char grade[4];
} StudentRecord;

bool write_data(char *file, StudentRecord *record, int num);
StudentRecord *read_data(char *filename, int *num);
bool create_file();
void print_data(StudentRecord *record, int num);
bool seek_record(StudentRecord *record, int num, char *identifier);
bool edit_record(StudentRecord *record, int num, char *identifier);
bool delete_record(StudentRecord *record, int num, char *identifier);

int main(){
        int input = 0;

        //Creates Main menu
        printf("\tM A I N  M E N U\n");
        printf("1. Create the Binary File\n");
        printf("2. Display the contents of the file\n");
        printf("3. Seek a specific record\n");
        printf("4. Update the contents of a record\n");
        printf("5. Delete a record for a specific student\n");
        printf("6. Exit\n\n");

       //Gets first input action
        printf("\tPlease enter your choice... ");
        scanf("%d", &input);
        printf("\n****************************************************\n\n");

        //Will continue looping until user enters exit key
        while(input != 6){

                //For Creatung file
                if(input == 1){
                        create_file();  //Calls method to create file
                }

                //For displaying contents of file
                else if(input == 2){
                        int num = 0;

                        //Reads data from file into a StudentRecord array
                        StudentRecord *file_data;
                        file_data = read_data("records.bin", &num);

                        //Checks for error reading file
                        if(file_data == NULL){
                                printf("Error reading file.\n");
                                return 1;
                        }

                        //Calls method to print the records
                        print_data(file_data, num);

                        free(file_data);        //Frees memory no longer being used
                }

                //For printing specific record
                else if(input == 3){
                        int num = 0;
                        char id[10];

                        //Reads data from file into a StudentRecord array
                        StudentRecord *file_data;
                        file_data = read_data("records.bin", &num);

                        //Gets user input of what student ID to find
                        printf("Please enter id of student to seek: ");
                        scanf("%s", id);
                        printf("\n");

                        //Checks for error reading file
                        if(file_data == NULL){
                                printf("Error reading file.\n");
                                return 1;
                        }

                        //Calls method to find record, if not found announces input matches no record
                        if(seek_record(file_data, num, id) == false){
                                printf("No record matches that ID\n");
                                printf("\n****************************************************\n\n");
                        }

                        free(file_data);        //Frees memory no longer being used
                }

                //For Updating contents of a record
                else if(input == 4){
                        int num = 0;
                        char identifier[30];

                        //Reads data from file into a StudentRecord array
                        StudentRecord *file_data;
                        file_data = read_data("records.bin", &num);

                        //Gets name or ID of student of record to be changed from user
                        printf("Please enter id or name of student's record you want to update:");
                        scanf(" %[^\n]s", identifier);
                        printf("\n");

                        //Checks for error reading file
                        if(file_data == NULL){
                                printf("Error reading file.\n");
                                return 1;
                        }

                        //Calls method to update record, if not found announces input matches no record
                        if(edit_record(file_data, num, identifier) == false){
                                printf("No file matching your input was found\n");
                        }

                        printf("\n****************************************************\n\n");

                        free(file_data);        //Frees memory no longer being used
                }

                //For deleting a record
                else if(input == 5){
                        int num = 0;
                        char identifier[30];

                        //Reads data from file into a StudentRecord array
                        StudentRecord *file_data;
                        file_data = read_data("records.bin", &num);

                        //Gets name or ID of student of record to be deleted from user
                        printf("Please enter id or name of student's record you want to delete: ");
                        scanf(" %[^\n]s", identifier);
                        printf("\n");

                        //Checks for error reading file
                        if(file_data == NULL){
                                printf("Error reading file.\n");
                                return 1;
                        }

                        //Calls method to delete record, if not found announces input matches no record
                        if(delete_record(file_data, num, identifier) == false){
                                printf("No file matching your input was found\n");
                        }

                        printf("\n****************************************************\n\n");

                        free(file_data);        //Frees memory no longer being used
                }

                //For exiting program
                else if(input == 6){
                        return 0;
                }

                //Handles unexpected inputs
                else{
                        //clears stdin to prevent fscan errors
                        char buffer[5];
                        fgets(buffer, 5, stdin);

                        //Informs user of invalid input
                        printf("Input not valid!\n");
                        printf("\n****************************************************\n\n");
                }

                //Creates Main Menu
                printf("\tM A I N  M E N U\n");
                printf("1. Create the Binary File\n");
                printf("2. Display the contents of the file\n");
                printf("3. Seek a specific record\n");
                printf("4. Update the contents of a record\n");
                printf("5. Delete a record for a specific student\n");
                printf("6. Exit\n\n");

                //Gets user input for which function they want
                printf("\tPlease enter your choice... ");
                scanf(" %d", &input);
                printf("\n****************************************************\n\n");
        }

        return 0;
}

/*
*filename       pointer to char array containing filename
*record         struct array to be wriiten into file
num             number of items in record to be written

Creates new file records.bin and writes Data to it
*/
bool write_data(char *filename, StudentRecord *record, int num){

        //opens file in binary write mode
        FILE *file;
        file = fopen(filename, "wb");

        //Checks for file errors
        if(file == NULL) return false;
        if (fwrite(&num, sizeof(int), 1, file) != 1)
                return false;

        //Checks if correct number of items were written
        if(fwrite(record, sizeof(StudentRecord), num, file) != num)
                return false;

        //Closes file and checks for error closing
        if(fclose(file) == EOF) return false;

        return true;
}

/*
*filename       pointer to char array containing filename
*num            pointer to num value of what is read

Reads file named records.bin and returns a struct array with all records contained in the file
*/
StudentRecord *read_data(char *filename, int *num){

        //opens file in binary read mode
        FILE *file;
        file = fopen(filename, "rb");

        //Checks for file errors
        if(file == NULL) return NULL;
        if(fread(num, sizeof(int), 1, file) !=1) return NULL;

        //Allocates space on heap for struct array
        StudentRecord *data = malloc(sizeof(StudentRecord) * *num);

        //Reads data and checks number of elements read
        if(fread(data, sizeof(StudentRecord), *num, file) != *num){
                free(data);
                return NULL;
        }

        //Closes file and checks for error closing
        if (fclose(file) == EOF){
                free(data);
                return NULL;
        }

        return data;

}

/*
Creates new file using preset of records using write_data method
*/
bool create_file(){

        //Allocates size for struct array records
        StudentRecord *records;
        records = malloc(sizeof(StudentRecord)*5);

        strcpy(records[0].id, "T00856317");
        strcpy(records[0].name, "Zoro Roronoa");
        strcpy(records[0].email, "zoro22@tru.ca");
        strcpy(records[0].course, "COMP 2131");
        strcpy(records[0].grade, "B-");

        strcpy(records[1].id, "T00756314");
        strcpy(records[1].name, "Robin Nico");
        strcpy(records[1].email, "robin13@tru.ca");
        strcpy(records[1].course, "COMP 2161");
        strcpy(records[1].grade, "A");

        strcpy(records[2].id, "T00931542");
        strcpy(records[2].name, "Tony Chopper");
        strcpy(records[2].email, "tony22@tru.ca");
        strcpy(records[2].course, "COMP 3271");
        strcpy(records[2].grade, "A+");

        strcpy(records[3].id, "T00856317");
        strcpy(records[3].name, "Luffy Monkey");
        strcpy(records[3].email, "luffy1@tru.ca");
        strcpy(records[3].course, "COMP 1630");
        strcpy(records[3].grade, "F");

        strcpy(records[4].id, "T00856317");
        strcpy(records[4].name, "Ace Roger");
        strcpy(records[4].email, "ace7@tru.ca");
        strcpy(records[4].course, "COMP 3261");
        strcpy(records[4].grade, "C+");

        //Calls write_data method prints message id successfu;
        if(write_data("records.bin", records, 5)){
                printf("File has been created.\n");
                printf("\n****************************************************\n\n");
        }

        //Informs user of error if there is an error creating file
        else{
                printf("Error creating File...\n");
                printf("\n****************************************************\n\n");
                return false;
        }

        free(records);          //frees up memory
        return true;

}

/*
*record         pointer to struct array containing student records
num             number of records

Prints all the records in the struct array
*/
void print_data(StudentRecord *record, int num){

        for(int i = 0; i<num;i++){
                printf("Student ID:\t%s\n", record[i].id);
                printf("Student Name:\t%s\n", record[i].name);
                printf("Email ID:\t%s\n", record[i].email);
                printf("Course ID:\t%s\n", record[i].course);
                printf("Grade:\t\t%s\n\n", record[i].grade);
        }
        printf("\n****************************************************\n\n");

        return;
}

/*
*record         pointer to struct array containing student records
num             number of records
*id             Student ID to be found and printed

Uses for loop to find element in struct array that matches given ID and prints record,
displays error of record not found
*/
bool seek_record(StudentRecord *record, int num, char *id){
        bool found = false;

        //Loops through all structs
        for(int i = 0; i<num;i++){
                int res = strcmp(record[i].id, id); // compares struct id with given id

                //if ids match the record gets printed
                if(res == 0){
                        found = true;
                        printf("Here is your desired record.\n\n");
                        printf("Student ID:\t%s\n", record[i].id);
                        printf("Student Name:\t%s\n", record[i].name);
                        printf("Email ID:\t%s\n", record[i].email);
                        printf("Course ID:\t%s\n", record[i].course);
                        printf("Grade:\t\t%s\n\n", record[i].grade);
                        printf("\n****************************************************\n\n");
                }
        }
        return found;
}

/*
*record         pointer to struct array containing student records
num             number of records
*identifier     Student ID or name to be found in order to edit record

Uses for loop to find element in struct array that matches given ID or name and asks what value should be ediited and recieves new input
*/
bool edit_record(StudentRecord *record, int num, char *identifier){
        int attr;
        bool found = false;
        char attrVal[30];

        //Loops through struct array
        for(int i = 0; i<num;i++){

                //Checks if record id matches given value
                int resId = strcmp(record[i].id, identifier);
                //Checks if record name mataches given value
                int resName = strcmp(record[i].name, identifier);

                //If either record value matches the given value
                if(resId == 0 || resName ==0){
                        found = true;
                        printf("1. Student ID\n");
                        printf("2. Student Name\n");
                        printf("3. Email ID\n");
                        printf("4. Course ID\n");
                        printf("5. Grade\n\n");

                        //Gets input of what attribute to change
                        printf("Please enter what you wish to update: ");
                        scanf(" %d", &attr);
                        printf("\n");

                        //for updating student ID
                        if(attr == 1){
                                //Gets new student id
                                printf("Please enter the new student ID: ");
                                scanf(" %[^\n]s", attrVal);
                                printf("\n");

                                //copies new  value to replace old
                                strcpy(record[i].id, attrVal);
                        }
                        //for updating student name
                        else if(attr == 2){
                                //Gets new name
                                printf("Please enter the new student name: ");
                                scanf(" %[^\n]s", attrVal);
                                printf("\n");

                                //copies new  value to replace old
                                strcpy(record[i].name, attrVal);
                        }
                        //For updating email
                        else if(attr == 3){
                                //Gets new email
                                printf("Please enter  the new email ID: ");
                                scanf(" %[^\n]s", attrVal);
                                printf("\n");

                                //copies new  value to replace old
                                strcpy(record[i].email, attrVal);
                        }
                        //For updating course ID
                        else if(attr == 4){
                                //Gets new course ID
                                printf("Please enter the new course ID: ");
                                scanf(" %[^\n]s", attrVal);
                                printf("\n");

                                //copies new  value to replace old
                                strcpy(record[i].course, attrVal);
                        }
                        //for updating grade
                        else if(attr == 5){
                                //Gets new grade
                                printf("Please enter the new grade: ");
                                scanf(" %[^\n]s", attrVal);
                                printf("\n");

                                //copies new  value to replace old
                                strcpy(record[i].grade, attrVal);
                        }
                        //Handles unexpected input
                        else{
                                //Clear excess values in stdin
                                char buffer[5];
                                fgets(buffer, 5, stdin);

                                //Informs user of invalid input
                                printf("Input not valid.\n");
                                return true;
                        }

                        //Rewrites data to file with updated struct array
                        //Informs user of success upon success
                        if(write_data("records.bin", record, 5)){
                                printf("record has been updated.\n");
                        }
                        //Informs user of error if file not rewritten
                        else{
                                printf("Error updating record...\n");
                        }

                 }
        }
        return found;
}

/*
*record         pointer to struct array containing student records
num             number of records
*identifier     Student ID or name to be found in order to edit record

Uses for loop to find element in struct array that matches given ID or name and deletes specifed record by moving indices and rewriting the file
*/
bool delete_record(StudentRecord *record, int num, char *identifier){
        bool found = false;

        //Loops through the struct array
        for(int i = 0; i<num;i++){
                //Compares record id and given value
                int resId = strcmp(record[i].id, identifier);
                //Compares record name and given value
                int resName = strcmp(record[i].name, identifier);

                //if record id or name matches given value
                if(resId == 0 || resName ==0){
                        found = true;
                        int last = num - 1;

                        //increments index of subsequent records to eliminate desired record
                        for(int j = i; j < last; j++){
                                record[j] = record[j+1];
                        }

                        //Rewrites updated struct array into file with decremented size
                        //Informs user of success upon success
                        if(write_data("records.bin", record, num-1)){
                                printf("Record has been deleted.\n");
                        }
                        //Informs user of error if failed
                        else{
                                printf("Error deleting record...\n");
                        }
                }
        }
        return found;
}