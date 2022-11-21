
#include <stdio.h>    // printf function
#include <stdlib.h>   // exit function
#include <errno.h>    // error handling
#include <unistd.h>   // low IO


// structure of Student Data
typedef struct student_marks
{
    char student_index[20];
    float assignmt01_marks;
    float assignmt02_marks;
    float project_marks;
    float finalExam_marks;
} student_marks;

void calc(int min,int max,int *pass,int* fail);


int main(void)
{

    int FD1[2];
    int FD2[2];
    int FD3[2];
    int FD4[2];
    int p1 = pipe(FD1);
    int p2 = pipe(FD2); 
    int p3 = pipe(FD3); 
    int p4 = pipe(FD4);

    if((p1==-1)||(p2==-1)||(p3==-1)||(p4==-1))
    {
        printf("\nPipe could not be created");
        perror("\nPipe: ");
        printf("\nError number is %d", errno);
        exit(0);
    }
    else 
    {
        //printf("\nParent: Pipes created successfully");
        pid_t PID1 = fork();
        if(PID1==-1)
        {
            //Error
            printf("\nChild process(C1) could not be created");
            perror("\nChild process(C1): ");
            printf("\nError number is %d", errno);
            exit(0);
            
        }
        else if(PID1==0)//Child 1
        {
            int passCount = 0;
            int failCount = 0;
            calc(1,25,&passCount,&failCount);
            
            close(FD1[0]);

            if(write(FD1[1],&passCount,sizeof(int))<0){
                perror("Write error number: ");
                printf("Error No: %d\n",errno);
                exit(0);
            }

            if(write(FD1[1],&failCount,sizeof(int))<0){
                perror("Write error number: ");
                printf("Error No: %d\n",errno);
                exit(0);
            }

            close(FD1[1]);


        }
        else //Parent
        {
            pid_t PID2 = fork();
            if(PID2==-1)
            {
                //Error
                printf("\nChild process(C1) could not be created");
                perror("\nChild process(C1): ");
                printf("\nError number is %d", errno);
                exit(0);
                
            }
            else if(PID2==0)//Child 2
            {
                int passCount = 0;
                int failCount = 0;
                calc(26,50,&passCount,&failCount);
                

                close(FD2[0]);

                if(write(FD2[1],&passCount,sizeof(int))<0){
                    perror("Write error number: ");
                    printf("Error No: %d\n",errno);
                    exit(0);
                }

                if(write(FD2[1],&failCount,sizeof(int))<0){
                    perror("Write error number: ");
                    printf("Error No: %d\n",errno);
                    exit(0);
                }

                close(FD2[1]);

            }
            else //Parent
            {
                pid_t PID3 = fork();
                if(PID3==-1)
                {
                    //Error
                    printf("\nChild process(C1) could not be created");
                    perror("\nChild process(C1): ");
                    printf("\nError number is %d", errno);
                    exit(0);
                    
                }
                else if(PID3==0)//Child 3
                {
                    int passCount = 0;
                    int failCount = 0;
                    calc(51,75,&passCount,&failCount);
                    

                    close(FD3[0]);

                    if(write(FD3[1],&passCount,sizeof(int))<0){
                        perror("Write error number: ");
                        printf("Error No: %d\n",errno);
                        exit(0);
                    }

                    if(write(FD3[1],&failCount,sizeof(int))<0){
                        perror("Write error number: ");
                        printf("Error No: %d\n",errno);
                        exit(0);
                    }

                    close(FD3[1]);
                }
                else //Parent
                {
                    pid_t PID4 = fork();
                    if(PID4 ==-1)
                    {
                        //Error
                        printf("\nChild process(C1) could not be created");
                        perror("\nChild process(C1): ");
                        printf("\nError number is %d", errno);
                        exit(0);
                        
                    }
                    else if(PID4==0)//Child 4
                    {
                        int passCount = 0;
                        int failCount = 0;
                        calc(76,100,&passCount,&failCount);
                        

                        close(FD4[0]);

                        if(write(FD4[1],&passCount,sizeof(int))<0){
                            perror("Write error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }

                        if(write(FD4[1],&failCount,sizeof(int))<0){
                            perror("Write error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }

                        close(FD4[1]);
                    }
                    else //Parent
                    {
                        int pass = 0;
                        int fail = 0;
                        int passFromChiled = 0;
                        int faileFromChiled = 0;

                        close(FD1[1]);
                         if(read(FD1[0],&passFromChiled,sizeof(int))<0){
                            perror("read error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }
                        if(read(FD1[0],&faileFromChiled,sizeof(int))<0){
                            perror("read error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }
                        close(FD1[0]);
                        pass += passFromChiled;
                        fail += faileFromChiled;
                        passFromChiled = 0;
                        faileFromChiled = 0;

                        close(FD2[1]);
                         if(read(FD2[0],&passFromChiled,sizeof(int))<0){
                            perror("read error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }
                        if(read(FD2[0],&faileFromChiled,sizeof(int))<0){
                            perror("read error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }
                        close(FD2[0]);
                        pass += passFromChiled;
                        fail += faileFromChiled;
                        passFromChiled = 0;
                        faileFromChiled = 0;

                        close(FD3[1]);
                         if(read(FD3[0],&passFromChiled,sizeof(int))<0){
                            perror("read error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }
                        if(read(FD3[0],&faileFromChiled,sizeof(int))<0){
                            perror("read error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }
                        close(FD3[0]);
                        pass += passFromChiled;
                        fail += faileFromChiled;
                        passFromChiled = 0;
                        faileFromChiled = 0;

                        close(FD4[1]);
                         if(read(FD4[0],&passFromChiled,sizeof(int))<0){
                            perror("read error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }
                        if(read(FD4[0],&faileFromChiled,sizeof(int))<0){
                            perror("read error number: ");
                            printf("Error No: %d\n",errno);
                            exit(0);
                        }
                        close(FD4[0]);
                        pass += passFromChiled;
                        fail += faileFromChiled;

                        printf("pass(<75%%) count %d  faile (>40%%) count %d\n",pass,fail);
                    }

                }

            }
    

        }



     }


    
    return  0;
}


void calc(int min,int max,int *pass,int* fail){


    FILE* file = fopen("student_marks.dat","r");
    int errNo;
    int count = 1;
    if (file == NULL){
        printf("Error opening file: %d\n",errno);
        perror("fopen Error: \n");
        exit(1);
    }
    student_marks student;
     while (1){
        //read data from file
        fread(&student, sizeof(student_marks), 1, file);

        if (feof(file)){
            break;
        }
        if ((errNo = ferror(file)) > 0){
            perror("fread dox1.txt: ");
            printf("ferror: %d\n", errNo);
            exit(1);
        }
        else{
            float totle = 0;
            if(count>=min){
                totle = student.assignmt01_marks + student.assignmt02_marks+student.project_marks+student.finalExam_marks;

                if(totle>75.00){
                    (*pass)++;
                }
                if(totle<40.00){
                    (*fail)++;
                }
            }
            if(count == max)break;
            count++;
        }
     }
    fclose(file);
}