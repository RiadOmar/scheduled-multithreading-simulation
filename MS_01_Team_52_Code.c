
#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <pthread.h>
#include <unistd.h>

struct args
{
    int val;
    struct timespec *stamp;
};

void *threadFunc(void *arg)
{
    // importing parameters and setting up clocks
    struct args *parameters = (struct args *)arg;

    struct timespec start = *((*parameters).stamp);
    struct timespec end;

    struct timespec turnaroundTime;
    clock_gettime(CLOCK_REALTIME, &turnaroundTime);
    struct timespec execTime;
    struct timespec waitTime;
    clock_gettime(CLOCK_REALTIME, &waitTime);

    int thread_no = (*parameters).val;
    // printf("Scheduling Policy of Thread No. %d: %d\n", thread_no, sched_getscheduler(0));
    for (int i = 1; i <= 5; i++)
    {
        // Creating a loop to extend the execution time, extends less for later threads
        for (long j = 0; j < 46116850 * 5; j++)
        {
        }
        printf("Print No.%d | Thread: %d (ID: %ld)\n", i, thread_no, pthread_self());
    }
    // Getting the execution time of the thread
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &execTime);
    clock_gettime(CLOCK_REALTIME, &end);

    double startTime = (double)start.tv_sec + ((double)start.tv_nsec) / 1e9;
    double endTime = (double)end.tv_sec + ((double)end.tv_nsec) / 1e9;
    double turnTime = endTime - startTime;
    double execT = (double)execTime.tv_sec + ((double)execTime.tv_nsec) / 1e9;
    double waitT = turnTime - execT;

    printf("Turnaround Time of Thread No. %d: %fs \n", thread_no, turnTime);
    printf("Execution Time of Thread No. %d: %fs \n", thread_no, execT);
    printf("Wait Time of Thread No. %d: %fs \n", thread_no, waitT);

    float Useful_CPU_Work;
    if (execT + waitT != 0)
    {
        Useful_CPU_Work = execT / (execT + waitT);
    }
    else
    {
        Useful_CPU_Work = 0.0;
    }
    printf("Useful CPU Work: %.1f%%\n", Useful_CPU_Work * 100);
    // Terminate Thread & grabbing its timestamp
    pthread_exit(NULL);
}

void createThreads()
{
    // Thread Declaration
    pthread_t th1, th2, th3, th4;

    // Variables holding thread numbers Creation
    int val1 = 1;
    int val2 = 2;
    int val3 = 3;
    int val4 = 4;

    struct timespec start1, start2, start3, start4;

    struct args arg1, arg2, arg3, arg4;
    arg1.val = val1;
    arg1.stamp = &start1;
    arg2.val = val2;
    arg2.stamp = &start2;
    arg3.val = val3;
    arg3.stamp = &start3;
    arg4.val = val4;
    arg4.stamp = &start4;

    // Thread Creation
    printf("Creating Threads\n");
    clock_gettime(CLOCK_REALTIME, &start1);
    pthread_create(&th1, NULL, &threadFunc, &arg1);
    clock_gettime(CLOCK_REALTIME, &start2);
    pthread_create(&th2, NULL, &threadFunc, &arg2);
    clock_gettime(CLOCK_REALTIME, &start3);
    pthread_create(&th3, NULL, &threadFunc, &arg3);
    clock_gettime(CLOCK_REALTIME, &start4);
    pthread_create(&th4, NULL, &threadFunc, &arg4);

    //   Threads Join
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    printf("All Threads Joined\n");
}

int main()
{
    printf("Make sure to compile using: gcc MS_01_Team_52_Code.c -o MS_01_Team_52_Code -lpthread\n");
    printf("Make sure to run using: sudo ./MS_01_Team_52_Code\n");
    printf("Since is sometimes causes issues otherwise\n");

    cpu_set_t cpuSet;
    CPU_ZERO(&cpuSet);
    CPU_SET(0, &cpuSet);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuSet);
    // continue prompt varialble
    char tmp = ' ';

    // Scheduling Policies
    struct sched_param rrParam, fifoParam, otherParam;
    rrParam.sched_priority = 50;
    fifoParam.sched_priority = 50;
    otherParam.sched_priority = 0;

    //////REDUNDANT CODE : Although it has been taught in the lectures that passing the
    //////                 attribute while creating the pthread, no matter what we did,
    //////                 the scheduler would not function as expected using it, so
    //////                 we used sched_setScheduler instead.
    // pthread_attr_t rrAttr, fifoAttr, otherAttr;

    // pthread_attr_init(&rrAttr);
    // pthread_attr_init(&fifoAttr);
    // pthread_attr_init(&otherAttr);

    // pthread_attr_setschedpolicy(&rrAttr, SCHED_RR);
    // pthread_attr_setschedpolicy(&fifoAttr, SCHED_FIFO);
    // pthread_attr_setschedpolicy(&otherAttr, SCHED_OTHER);

    // pthread_attr_setscope(&rrAttr, PTHREAD_SCOPE_SYSTEM);
    // pthread_attr_setscope(&fifoAttr, PTHREAD_SCOPE_SYSTEM);
    // pthread_attr_setscope(&otherAttr, PTHREAD_SCOPE_SYSTEM);

    // pthread_attr_setschedparam(&rrAttr, &rrParam);
    // pthread_attr_setschedparam(&fifoAttr, &fifoParam);
    // pthread_attr_setschedparam(&otherAttr, &otherParam);
    //////REDUNDANT CODE

    // Main Thread Info.
    int main_thread_ID = pthread_self();
    printf("Main Thread ID: %d\n", main_thread_ID);

    // Setting main thread policy to RR
    sched_setscheduler(0, SCHED_RR, &rrParam);
    printf("Main Scheduling Policy: %d\n", sched_getscheduler(0));
    createThreads();

    // Chosing to continue or terminate program
    printf("Continue? [Y/n]: ");
    scanf("%c", &tmp);
    if (tmp == 'n' || tmp == 'N')
    {
        printf("program Terminated\n");
        return 0;
    }
    // clearing the buffer in order to use the same variable for input again
    getchar();

    // Setting main thread policy to FIFO
    sched_setscheduler(0, SCHED_FIFO, &fifoParam);
    printf("\n");
    printf("Main Scheduling Policy: %d\n", sched_getscheduler(0));

    createThreads();

    // Chosing to continue or terminate program
    printf("Continue? [Y/n]: ");

    scanf("%c", &tmp);
    if (tmp == 'n' || tmp == 'N')
    {
        printf("program Terminated\n");
        return 0;
    }

    // Setting main thread policy to OTHER
    sched_setscheduler(0, SCHED_OTHER, &otherParam);
    printf("\n");
    printf("Main Scheduling Policy: %d\n", sched_getscheduler(0));

    createThreads();

    printf("End of Program\n");

    return 0;
}