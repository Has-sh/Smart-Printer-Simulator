#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.h"
#define TRUE 1
#define FALSE 0



int main(int argc, char *argv[]){
//Generate different random values:
        srand(time(NULL));
//Store the command line data:
        int *information;
        information = malloc(sizeof(int)*4);
        if(information == NULL){
                printf("Failed to allocate Memory for information\n");
        }
//Calling the ParseInput Function to store command line data into information array:
        information = parseInput(information,argv);
//used for for loop;
                int i;
//this is going to keep count of job request type in this array;
        int *request_type;
        request_type = malloc(sizeof(int)*4);
        if(request_type == NULL){
                printf("Failed to allocate Memory");
        }
        for(i=0;i<4;i++){
            request_type[i] = 0;
            }
//This is going to keep count of job request info:
                int same=0,different=0;
//This is going to keep count of Type of job:
                int Short=0,Medium=0,Long=0;

//Declaring and creating the empty Queue and an integer array to keep the availability of the printers:
        Queue Job;
        int *printer_availability;
        int no_of_printers;
        no_of_printers = information[1];
        printer_availability = malloc(sizeof(int)*information[1]);
        if(printer_availability == NULL){
                printf("Memory Allocation Failed\n");
        }

        Job = initialiseSimulator(Job,&printer_availability[0],no_of_printers);

//Function will allocate data randomly and store it in linked list:
        struct Node *head;
        head = createJobList(information);

//Insering the jobs in the Queue one by one based on arrival time,data is sorted in createjoblist function:
        struct Node *t;
        t = head->next;
        while(t!=NULL){
                newJob(Job,t);

//Counting Job Request Type
                if(strcmp("Personal",t->Job_Request_Type) == 0){
                        request_type[0]++;
                                }
                                else if(strcmp("Exam",t->Job_Request_Type) == 0){
                        request_type[1]++;
                                }
                                else if(strcmp("Attendance",t->Job_Request_Type) == 0){
                        request_type[2]++;
                                }
                                else if(strcmp("Assignment",t->Job_Request_Type) == 0){
                        request_type[3]++;
                                }

//Counting job request info:
                                if(strcmp("Different",t->Job_Request_Info) == 0){
                                        different++;
                                }
                            else if(strcmp("Same",t->Job_Request_Info) == 0){
                                        same++;
                                }
                                //Counting the job type:
                                if(strcmp("Short",t->Type) == 0){
                                        Short++;
                                }
                            else if(strcmp("Medium",t->Type) == 0){
                                        Medium++;
                                }
                                else if(strcmp("Long",t->Type) == 0){
                                        Long++;
                                }


                t = t->next; //Moving to the next Node;
        }

//Keep record of number of printers available;
        int availability=0;
//Point to the dequeued node:
        struct Node *Dequeued_Job;
//These variables help to control and keep record of data inside the main while loop function:
        int time=0,maximum_waiting_time=0,total_time;
        float total_waiting_time=0,Job_done=0;
//Assign Id to every printer and printer job will keep record of number of j:
        int *printer_ID,*printer_job;
        printer_job = malloc(sizeof(int)*information[1]);
        if(printer_job == NULL){
                printf("Failed allocation Memory\n");
        }
        printer_ID = malloc(sizeof(int)*information[1]);
        if(printer_ID == NULL){
                printf("Memory Allocation Failed");
        }
        for (i = 0; i <information[1]; i++)
        {

                availability = availability + printer_availability[i];
                printer_ID[i] = i+1;
                printer_job[i] = 0;
        }

//These variables help to control and keep record of data inside the main while loop function:
     int *arrival_time,*start_service_time,*service_time,*waiting_time;
     arrival_time = malloc(sizeof(int)* information[1]);
     if(arrival_time == NULL){
        printf("Failed to allocate Memory");
     }
     start_service_time = malloc(sizeof(int)* information[1]);
     if(start_service_time == NULL){
        printf("Failed to allocate Memory");
     }
     service_time = malloc(sizeof(int)* information[1]);
     if(service_time == NULL){
        printf("Failed to allocate Memory");
     }
     waiting_time = malloc(sizeof(int)* information[1]);
     if(waiting_time == NULL){
        printf("Failed to allocate Memory");
     }


//This is our main while loop which will control everything: From dequeuing to calculating the waiting time:
     while(!isemptyqueue(Job) || availability==0)
     {

        for(i=0;i<information[1];i++){

                 if(!isemptyqueue(Job) && time>=Job->front->next->Arrival_Time && printer_availability[i] == 1)
                    {
                        printer_job[i]++;
                        printer_availability[i] = 0;
						availability--;
						Dequeued_Job = serveJob(Job,time,information);
                        arrival_time[i] = Dequeued_Job->Arrival_Time;


                        start_service_time[i] = time;
                        service_time[i] = Dequeued_Job->Service_Time;
                        waiting_time[i] = start_service_time[i] - arrival_time[i];
                        if(waiting_time[i]>=maximum_waiting_time)
                        {
                            maximum_waiting_time = waiting_time[i];
                        }
                        total_waiting_time = total_waiting_time + waiting_time[i];

                                //printf("I came till end of the if statement\n\n");

                    }//End of if statement;

    }//End of for loop statement;
            for(i=0;i<information[1];i++){

            if(start_service_time[i] + service_time[i]==time && printer_availability[i] == 0)
            {
                availability++;
                printer_availability[i]=1;

                Job_done++;

                time--;
            }//End of else statement;

    }//End of for loop;
            time++;


     }//End of the while loop;

reportStatistics(total_waiting_time,time,maximum_waiting_time,Job_done,information,request_type,same,different,Short,Medium,Long,printer_ID,printer_job);
    return 0;
}

//This function will generate the report of everything after dequeuing and calculations are completed;
void reportStatistics(float total_waiting_time,int time,int maximum_waiting_time,float Job_done,int *info,int *request_type,int same,int different,int Short,int Medium,int Long,int *printer_ID,int *printer_job){
        //Finding the popular Request Type;
        int i,max=-1,index;
        for(i=0;i<4;i++){
                if(request_type[i]>max){
                        max = request_type[i];
                        index = i; //index will store the index of popular request type:
                }
        }



        printf("***************Smart Printer Statistics*****************\n");
        printf("The number of printers: %d\n", info[1]);
        printf("The number of jobs: %d\n",info[0]);
        printf("The number of jobs for each job type:\n");
        printf("\t Short: %d\n",Short);
        printf("\t Medium: %d\n",Medium);
        printf("\t Long: %d\n",Long);
        printf("The number of jobs for each printer:\n");
        for(i=0;i<info[1];i++){
                printf("\t Printer %d:%d\n",printer_ID[i],printer_job[i]);
        }
        printf("Completion time: %d\n",time);
        printf("Average time spent in the queue: %.1f\n",total_waiting_time/Job_done);
        printf("Maximum waiting time: %d\n",maximum_waiting_time);
        if(index == 0){ //Index 0 contain the count for Personal, you can see in the while loop of main function:
                printf("Popular job request type: Personal\n");
        }
        else if(index == 1){//Index 1 contain the count for Exam, you can see in the while loop of main function:
                printf("Popular job request type: Exam\n");
        }
        else if(index == 2){//Index 2 contain the count for Attendance, you can see in the while loop of main function:
                printf("Popular job request type: Attendance\n");
        }
        else if(index == 3){//Index 3 contain the count for Assignment, you can see in the while loop of main function:
                printf("Popular job request type: Assignment\n");
        }
        if(same>different){
                printf("Popular job request info: Same\n");
        }
        else{
                printf("Popular job request info: Different\n");
        }
        printf("************************************************************\n");


}

//This function is going to take the data from the command line:
//after it will convert the char into integer using the atoi function and
//store it into the information array:
int *parseInput(int *information,char *argv[])
{
    int i;
    for(i=0;i<4;i++)
    {
        information[i]= atoi(argv[i+1]);
    }
    return information;
}

//Creating the queue:
Queue initialiseSimulator(Queue Job,int *printer_availability, int no_of_printers){

                int i;
                for(i=0;i<no_of_printers;i++){
                        printer_availability[i]=1;
                }

        //Creating the queue:
        Job = malloc(sizeof(Queue));
        if(Job == NULL){
                printf("Failed to Allocate Memory for your Queue\n");
        }
        else{
//Making the queue empty:
                MakeEmptyQueue(Job);
        }
        return Job; // returing it back to main function after the empty queue is created;
}

//This function will check if queue is empty or there are job still waiting:
int isemptyqueue(Queue q)
{
        //printf("I came here after call from main\n");
    if(q->size==0)
    {
        return TRUE; //Means queue is empty
    }
    return FALSE; //means queue have some valued stored;

}


void MakeEmptyQueue(Queue Job){
	//This is the dummy node:
        struct Node *Dummy;
        Dummy = malloc(sizeof(struct Node));
        if(Dummy == NULL){
                printf("Failed to allocate Memory");
        }
        //Making dummy next eaquals to NULL:
        Dummy->next = NULL;
        //making the front and rear pointer to point to the dummy node in the start:
        Job->front = Job->rear = Dummy;
        Job->size = 0;
}

//This function will generate random values and store it into the linked list:
struct Node *createJobList(int *information){
        int i;
        struct Node *temp,*head,*rear;
        struct Node *p1,*p2; //These two point will help me to sort the data according to arrival time and priority:

//head is dummy node:
                head = malloc(sizeof(struct Node));
                if(head == NULL){
                        printf("Unable to allocate Memory:");
                }
                head->next = NULL;

//information[0] stores the number of jobs to be generated:
        for(i=0;i<information[0];i++){
                temp = malloc(sizeof(struct Node));
                if(temp == NULL){
                        printf("Failed to Allocate Memory");
                }
                temp->next = NULL;
                temp->Arrival_Time = 1 + rand() % information[2];
                temp->Service_Time = 1 + rand() % information[3];
                temp->Service_Start_Time = 0;
                strcpy(temp->Job_Request_Info ,Generate_Random_Value(1));
                strcpy(temp->Type, Generate_Random_Value(2));
                strcpy(temp->Job_Request_Type, Generate_Random_Value(3));
                temp->priority_type = assign_priority(temp->Type);


                if(head->next == NULL){
                        head->next = temp;
                        rear = temp;
                }
                else{
                    rear->next = temp;
                    rear = temp;
                }
        }
//Temp Varables which will store the values for some duration during the sorting;
                        char temp_type[20],temp_job_request_type[20],temp_job_request_info[20];
                        int temp_arrival,temp_service,temp_priority;


//Soring the linked list based on the arrival time:
                p1 = head->next;
                while(p1 != NULL){
                    p2 = p1->next;
                    while(p2 !=NULL){
                        if(p2->Arrival_Time < p1->Arrival_Time){
                            temp_arrival = p2->Arrival_Time;
                            temp_service = p2->Service_Time;
                            temp_priority = p2->priority_type;
                            strcpy(temp_type,p2->Type);
                            strcpy(temp_job_request_type,p2->Job_Request_Type);
                            strcpy(temp_job_request_info,p2->Job_Request_Info);

                            p2->Arrival_Time = p1->Arrival_Time;
                            p2->Service_Time = p1->Service_Time;
                            p2->priority_type = p1->priority_type;
                            strcpy(p2->Job_Request_Info,p1->Job_Request_Info);
                            strcpy(p2->Job_Request_Type,p1->Job_Request_Type);
                            strcpy(p2->Type,p1->Type);

                            p1->Arrival_Time = temp_arrival;
                            p1->Service_Time = temp_service;
                            p1->priority_type = temp_priority;
                            strcpy(p1->Job_Request_Info,temp_job_request_info);
                            strcpy(p1->Job_Request_Type,temp_job_request_type);
                            strcpy(p1->Type,temp_type);


                        }
                            p2 = p2->next;
                        }
                    p1 = p1->next;
                }


    return head;
}

//This program will randomly generate Customer Type and return it to createjoblist:
char *Generate_Random_Value(int val){
        int random;
        char *s;
        s = malloc(sizeof(char)*25);

//If val is equals to 2:
//Then program will randomly generate Customer Type and return it to createjoblist:
        if(val == 2){
                random = 1 + rand() % 3;
                //printf("Value = %d\n",random);
                if(random == 3){
                        strcpy(s,"Short");
                }
                else if(random == 2){
                        strcpy(s,"Medium");
                }
                else if(random == 1){
                        strcpy(s,"Long");
                }
                return s;
        }
//If val is equals to 1:
//Then program will randomly generate Job Request Info and return it to createjoblist:
        else if(val == 1){
                random = rand() % 2;
                if(random == 0){
                        strcpy(s,"Different");
                }
                else if(random == 1){
                        strcpy(s,"Same");
                }
                return s;
        }
//If val is equals to 3:
//Then program will randomly generate Job Request type and return it to createjoblist:
        else if(val == 3){
                random = 1 + rand() % 4;
                if(random == 1){
                        strcpy(s,"Exam");
                }
                else if(random == 2){
                        strcpy(s,"Assignment");
                }
                else if(random == 3){
                        strcpy(s,"Attendance");
                }
                else if(random == 4){
                        strcpy(s,"Personal");
                }
                return s;
        }
}

//This function taking the job from the linked list one by one
//based on arrival time and putiing it in the queue:
void newJob(Queue Job, struct Node *t){
//Creating memory for the queue:
        struct Node *temp;
        temp= malloc(sizeof(struct Node ));
        if(temp == NULL){
                printf("Memory Allocation Failed");
        }
//copying the data from the linked list to the new memory of queue:
        temp->next = NULL;
        temp->Arrival_Time = t->Arrival_Time;
        temp->Service_Time = t->Service_Time;
        strcpy(temp->Job_Request_Info,t->Job_Request_Info);
        strcpy(temp->Job_Request_Type,t->Job_Request_Type);
        strcpy(temp->Type,t->Type);
        temp->Service_Start_Time = t->Service_Start_Time;
        temp->priority_type = t->priority_type;
        // printf("Priority Type: %d\n", temp->priority_type);
        Job->size++;


        if(Job->front->next == NULL){
                Job->rear->next = temp;
                Job->rear = temp;
        }
        else{
                Job->rear->next = temp;
                Job->rear = temp;
        }
}

//This function will dequeue the jobs based of the current time and priority of the job:
struct Node *serveJob(Queue Job,int time,int *information){
//Index will store the index of the node to be removed from the queue:
        int index,count=0,i;
       struct Node *forward,*backward,*temp;
       forward = Job->front->next;

        //At the start, counting how many jobs are in queue based on the arrival time;
       while(forward != NULL){
               if(time>=forward->Arrival_Time){
                       count++;
               }
               forward = forward->next;
       }
       int max_priority=0;
                forward = Job->front->next;
                //When there are only two jobs in the queue:
                if(count == 2){
                	//program will compare both of them and store the index of the node with higest priority:
                        if(forward->next->priority_type>forward->priority_type){
                                index =2;
                        }
                        else{
                                index = 1;
                        }
                        forward = Job->front->next;
                        backward = Job->front;
                        for(i=1;i<=count;i++){
                                if(index == i){
                                        temp = forward;
                                        backward->next = temp->next;
                                        temp->next = NULL;
                                        Job->size--;
                                        if(Job->size == 0){
                                        Job->rear = Job->front;
                                        }
                                        return temp;

                                }
                                forward = forward->next;
                                backward = backward->next;
                }



                }
                //When there are more than 1 job in the queue:
                else if(count>1){

                        forward = Job->front->next;
                        for(i=1;i<count;i++){
                                		//finding the correct node:
                                         //These if and else if statements are comparing the priority of every job:
                                        if(forward->priority_type>forward->next->priority_type && forward->priority_type>max_priority){

                                                        index = i;
                                                        max_priority = forward->priority_type;


                                        }
                                        else if(forward->priority_type<forward->next->priority_type && forward->next->priority_type > max_priority){
                                                        max_priority = forward->next->priority_type;
                                                        index = i+1;


                                        }

                                        else if(forward->priority_type == forward->next->priority_type && forward->priority_type>max_priority){

                                                        index = i;
                                                        max_priority = forward->priority_type;


                                        }

                                forward = forward->next; //moving to the next node:


                        }
                        //when program will find the correct node then it will be dequeued from the queue and returned to the main function:
                        forward = Job->front->next;
                        backward = Job->front; //backward pointer is pointing to the back of front node:
                        for(i=1;i<=count;i++){
                                if(index == i){
                                        temp = forward;
                                        backward->next = temp->next;
                                        temp->next = NULL;
                                        Job->size--;
                                        if(Job->size == 0){
                                        Job->rear = Job->front;
                                        }
                                        return temp;

                                }
                                forward = forward->next;
                                backward = backward->next;
                }
                }
                //When there is only one job in the queue:
                //front->next is removed and return to the main function:
                else if(count == 1){
                        temp= Job->front->next;
                        Job->front->next = Job->front->next->next;
                        temp->next = NULL;
                        Job->size--;
                        if(Job->size == 0){
                                Job->rear = Job->front;
                        }
                        return temp;
                }
}

//This function is taking job type from createjolist fuction
//then it will return priority in form of integer back to the function:
int assign_priority(char *type){
        char x;
        x = type[0];
        if(x == 'S'){
                return 3;
        }
        else if(x == 'M'){
                return 2;
        }
        else if(x == 'L'){
                return 1;
        }

}
