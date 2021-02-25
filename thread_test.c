#include "threads.h"


struct TCB_t *runQ = NULL;
int global = 0;
int num_executed;
int num_threads;
int threadID = 1;
int before_countb =0;
int after_countb =0;


void test1()
{	

    int counter_executed = 1;

    while(counter_executed <= num_executed)
    {

        // printf("\n--------------------------------- start while loop---------");
        // printf("\ncount before yield : %d  VS count after : %d", before_countb, after_countb);
        if(before_countb == after_countb)
        {
            global+= 1;
        }
        else{
            global+= num_threads;
        }
        printf("This is the %d th execution of thread %d with global var value %d\n", counter_executed, threadID, global);
       
        counter_executed++;
        threadID ++;

        before_countb = counter_executed;
        // printf("\ncount before yield: %d ", before_countb);
	    yield();
        after_countb = counter_executed;
        // printf("\ncount after yield: %d ", after_countb);

        // printf("\ncount before yield : %d  VS count after : %d", before_countb, after_countb);
        if(before_countb == after_countb)
        {
            threadID = 1;
        }

    }

}

int main()
{
    scanf("%d, %d", &num_threads,&num_executed); 
    // 1. create queue
	InitQueue(&runQ);
	
    // 2. create threads
	struct TCB_t *threads[num_threads]; //create array of TCB threads
	for (int i = 0; i < num_threads; i++)
    {
        startThread(threads[i], test1);

    }

    run();
	puts("Run ended");
}
