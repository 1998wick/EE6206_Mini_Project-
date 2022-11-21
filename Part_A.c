#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 

typedef struct student_marks
{
char student_index[12];
float assgnmt01_marks; //15%
float assgnmt02_marks; //15%
float project_marks; //20%
float finalExam_marks; //50%
}student_marks;

void addNewRecord();
// void readAllRecord();
// void updateRecord();
// void deleteRecord();
// void generateData();



void main(){
    int choice;
    addNewRecord();
    

}

void addNewRecord(){

    student_marks student;
    FILE *openFile;
    int writeFile;


    printf("Enter Student Registation Number:");
    scanf("%s", student.student_index);
    printf("Enter Assgnment_01 Marks:");
    scanf("%f",& student.assgnmt01_marks);
    printf("Enter Assgnment_01 Marks:");
    scanf("%f",&student.assgnmt02_marks);
    printf("Enter Project Marks:");
    scanf("%f",&student.project_marks);
    printf("Enter Final marks:");
    scanf("%f",&student.finalExam_marks);

    openFile = fopen("student_marks.csv" , "a+");
    if (openFile == NULL){
        printf("Failed to open file for adding new record");
        perror("student_marks.csv");
        exit(1);
    }

    writeFile = fwrite(&student, sizeof(struct student_marks),1,openFile);
    if (writeFile < 0) 
    {
        printf("Failed to write data for adding new record \n Error No: %d\n", errno);
        perror("student_marks.csv");
        exit(1);
    }
    
    fclose(openFile);
    
}