#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <errno.h> 
#include <time.h>

typedef struct student_marks
{
char student_index[12];
float assgnmt01_marks; 
float assgnmt02_marks; 
float project_marks; 
float finalExam_marks; 
}student_marks;



void addnewone();
void inputNewStudent();
void readAll();
void generateRecords();
char *randIndex();
void deleteAllData();
//void deleteRecord() ;
//void updateRecord();
//void deleteRecord();

// void generateData();

int main(){

    int choice;

    do
    {   
        printf("---------------------------------------------------------------------------------------------------------------------");
        printf("\n Menu \n");
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("1. Add New Student\n");
        printf("2. Read all \n");
        printf("3. Delete All\n");
        printf("4. Update Record \n");
        printf("5. Generate 100 Records \n");
        printf("6. Exit \n");
        printf("---------------------------------------------------------------------------------------------------------------------\n");
        printf("Enter Number : ");
        scanf("%d", &choice);
        printf("---------------------------------------------------------------------------------------------------------------------\n");

        switch (choice)
        {
        case 1:
            inputNewStudent();
            break;
        case 2:
            readAll();
            break;
        case 3:
            deleteAllData();
            break;
        case 4:
            //deleteRecord() ;
            break;
        case 5:
            generateRecords();
            break;
        case 6:
            exit(0);
            break;
        default:
            printf("Invalid Choice \n");
            break;
        }
    } while (choice != 6);

return 0;


}

student_marks *marksPtr;

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

    data = fopen("student_marks.dat" , "a+");
    if (data == NULL){
        printf("Failed to open file for adding new record");
        perror("student_marks.dat");
        exit(1);
    }

    writeFile = fwrite(&student, sizeof(struct student_marks),1,data);
    if (writeFile < 0) 
    {
        printf("Failed to write data for adding new record \n Error No: %d\n", errno);
        perror("student_marks.dat");
        exit(1);
    }
    
    fclose(data);
    
}

void readAll(){

    student_marks student;
    FILE *data;
    int errno;

    printf("| %-20s | %-20s | %-20s | %-20s | %-20s  | \n","Student Index", "Assignment 01",
                   "Assignment 02", "Project Marks", "Final Marks");

    printf("---------------------------------------------------------------------------------------------------------------------\n");
    data = fopen("student_marks.dat" , "r");
    if (data == NULL){
        printf("Failed to open file for reading all");
        perror("student_marks.dat");
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
            perror("fread student_marks.dat: ");
            printf("ferror: %d\n", errno);
            exit(1);
        }
        else
        {
            printf("| %-20s | %-20.2f | %-20.2f | %-20.2f | %-20.2f  | \n", student.student_index, student.assgnmt01_marks,
                   student.assgnmt02_marks, student.project_marks, student.finalExam_marks); 
        }
    }

    printf("\n\n");
    fclose(data); 
    

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
   
    char index[4];
    char perfix[] = "EG/2018/";
    const char num[] = "1234567890";
    

    for (int i = 0; i < 12; i++)
    {
        if (i<8)
        {
            index[i] = perfix[i];
        }

        else{
            
            int data = rand() %(int)(sizeof num - 1);
            index[i] = num[data];
        }
        
        
    }
    char * indexnumber = index;
    index[12] = '\0';  
    return indexnumber; 


}



void deleteAllData()
{
   if (remove("student_marks.dat") == 0)
      printf("Deleted successfully\n");
   else
      printf("Unable to delete the file");
  
}



