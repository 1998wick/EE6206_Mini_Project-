#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <time.h>


typedef struct student_marks
{
char student_index[12];
float assgnmt01_marks; //15%
float assgnmt02_marks; //15%
float project_marks; //20%
float finalExam_marks; //50%
}student_marks;

void addnewone();
void readAll();
void generateRecords();
char *randIndex();


// void updateRecord();
// void deleteRecord();
// void generateData();

student_marks *marksPtr;

void main(){
    int choice;
    //addnewone();
    generateRecords();
    readAll();   

}

void inputNewStudent(){

    student_marks student;

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
    addnewone(student);

}

void addnewone(student_marks student){

    
    FILE *data;
    int writeFile;

    data = fopen("student_marks.csv" , "a+");
    if (data == NULL){
        printf("Failed to open file for adding new record");
        perror("student_marks.csv");
        exit(1);
    }

    writeFile = fwrite(&student, sizeof(struct student_marks),1,data);
    if (writeFile < 0) 
    {
        printf("Failed to write data for adding new record \n Error No: %d\n", errno);
        perror("student_marks.csv");
        exit(1);
    }
    
    fclose(data);
    
}

void readAll(){

    student_marks student;
    FILE *data;
    int errno;

    printf("| %-6s | %-20s | %-20s | %-20s | %-20s | %-20s  | \n","count" ,"Student Index", "Assignment 01",
                   "Assignment 02", "Project Marks", "Final Marks");

    data = fopen("student_marks.csv" , "r");
    if (data == NULL){
        printf("Failed to open file for reading all");
        perror("student_marks.csv");
        exit(1);
    }
    while (1)
    {
        fread(&student, sizeof(student_marks), 1, data);
        if (feof(data))
        {
            break;
        }
        if ((errno = ferror(data)) > 0)
        {
            perror("fread student_marks.csv: ");
            printf("ferror: %d\n", errno);
            exit(1);
        }
        else
        {
            printf("| %-20s | %-20.2f | %-20.2f | %-20.2f | %-20.2f  | \n", student.student_index, student.assgnmt01_marks,
                   student.assgnmt02_marks, student.project_marks, student.finalExam_marks); // print record
        }
    }

    printf("\n\n");
    fclose(data); // close file
    

}

void generateRecords()
{
    student_marks studentData;
    int count = 0;
    while (count < 100)
    {
       
        strcpy(studentData.student_index, randIndex());
        studentData.assgnmt01_marks = rand() % 100 + 1;
        studentData.assgnmt02_marks = rand() % 100 + 1;
        studentData.project_marks = rand() % 100 + 1;
        studentData.finalExam_marks = rand() % 100 + 1;
        addnewone(studentData);
        count++;
    }

    printf("Generated 100 records\n\n");
}

char *randIndex(){
    const char charset[] = "1234567890";
    char index[4];
    char perfix[] = "EG/2018/";

    

    for (int i = 0; i < 12; i++)
    {
        if (i<8)
        {
            index[i] = perfix[i];
        }

        else{
            
            int data = rand() %(int)(sizeof charset - 1);
            index[i] = charset[data];
        }
        
        
    }
    char * indexnumber = index;
    index[12] = '\0';  
    return indexnumber; 


}