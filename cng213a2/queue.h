struct Node{
        char Type[10];
        int priority_type;
        int Arrival_Time;
        int Service_Time;
        int Service_Start_Time;
        int Agent_ID;
        char Job_Request_Type[20];
        char Job_Request_Info[20];
        struct Node *next;
};

struct QueueRecord{
        struct Node *front; //Keep record of first node;
        struct Node *rear;  //Keep record of last node;
        int size;           //Keep record of size of the list;
};

typedef struct QueueRecord *Queue;

//Function prototypes:
int *parseInput(int *,char *[]); // storing command line data into the information aray:
Queue initialiseSimulator(Queue,int *,int);//Creating the queue:
void MakeEmptyQueue(Queue);// making the queue empty:
int isemptyqueue(Queue);//Checking if queue is empty or not:
struct Node *createJobList(int *);// randomly generate data and store into the linked list:
char *Generate_Random_Value(int);//It will a int from the function. if it's 1 then program will randomly generate Job Request Info and return it to createjoblist and so on:
int assign_priority(char *); //Take the type of job(short/medium/large) and return the int value priority
void newJob(Queue,struct Node *);// taking the data from the linked list and storing it into the queue:
struct Node *serveJob(Queue,int,int *); //Dequeueing according the question conditions
void reportStatistics(float,int,int,float,int *,int *,int,int,int,int,int,int *,int *);// At the end it will generate the report:




