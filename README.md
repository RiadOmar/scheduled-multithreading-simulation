# Scheduled Multithreading Simulation

## Overview
 This is a project where the behavior of a single-core CPU with multithreading was simulated using various shecduling algorithms usuing the pThread library in c. This project has the purpose of showcasing the scheduling function that an operating system performs.

## Team Members

- Ahmed Khedr 
- Marawan Salah
- Mohammad Rageh 
- Omar Farouk 
- Omar Riad 

## Key Objectives

- Demonstrate the capabilities of multithreading and concurrent programming.
- Compare and contrast the performance of different scheduling algorithms/policies.

## Methodology

### Thread Creation

  In order to create our desired threads for each of our scheduling policies, which we’ll talk about later, we created a method that created 4 identical threads while recording a timestamp right before the creation of each thread. Each of the threads was passed a pointer to our thread function and a structure of parameters that contains the previously created timestamp along with an integer denoting the order in which the threads were created. The thread function itself prints 5 statements, each containing the statement number as well as the printing thread’s number, a loop that creates some delay without blocking the thread, and a few more timestamps and calculations that allow us to measure our desired KPIs.

  In order to attain the turnaround time, execution time, wait time and CPU utilization percentage, some calculations were required of each thread. The turnaround time was calculated by recording a timestamp just before the thread exists and is calculated by subtracting the timestamp recorded right before the thread creation from it. The execution time was acquired using a built-in function of the time.h library that returns the CPU time used by the calling thread. The wait time was the execution time subtracted from the turnaround time and the CPU utlization percentage was a ratio of the execution time to the turnaround time.

### Scheduling Policies

  The scheduling policies that have been used in the implementation are the predefined scheduling procedure in the Pthread library, First In First Out (FIFO), which should executes the thread that was created first no matter how long it takes, Round Robin (RR), which should allocates a time frame to each running thread and preempts it when it is over, thus running the threads concurrently, and OTHER, which theoretically allocates CPU time to the threads using a fair-share algorithm, similar to round robin. We are unsure of the exact algorithm OTHER uses to allocate CPU time. After making sure that the program was running in a Uni-Core environment in order to get reliable results, the scheduling policy was applied to the main thread, and the created threads inherited that policy by default, thus eliminating the need to manually set the scheduling policy of each thread. The method used to set the scheduling policy is one that takes in the thread ID (or a 0 for the current thread), one of the scheduling policies mentioned above and a scheduling parameter that sets the priority of this scheduler. FIFO and RR required a priority between 1-99 while OTHER required a priority of 0.

## Results 

  While the threads and KPI calculations were implemented without encountering any major roadblocks, the scheduling policies went through more than a few iterations. The first was attempting to set each thread’s scheduling policy by passing it a Pthread attribute during the thread creation, which disappointingly failed to set the threads’ scheduling policies. The next attempt was setting the scheduler of the main thread using a method in the sched.h library; although this is the approach used in our final deliverables, at that point in time we had not realized that it is a must for the program to run in a Uni-core environment in order to yield an expected outcome. The last 2 iterations were attempting to PThread attribute during creation and once again setting the scheduler of the main thread in that order and with the latter succeeding, only this time we had made the code run in a Uni-Core environment, which yielded us consistent results that are in-line with what was expected, within a margin or error.


![image](https://github.com/RiadOmar/scheduled-multithreading-simulation/assets/126183421/d82d1029-4d14-48b0-84c2-18621939f01d)

[Fig. 1.1]

  According to the results shown in fig 1.1, The useful CPU work in RR was lower than FF for all the 4 threads and its average too. The default “OTHER” scheduler ’s average results was between FF and Round robin, Although its execution time was better than RR and FIFO but it has higher turnaround time and lower useful cpu work than FF. Overall results, FIFO performed better than RR and default scheduler in this iteration.

## References

- https://stackoverflow.com/questions/23483261/using-clock-process-cputime-id-in-clock-gettime
- https://stackoverflow.com/questions/23483261/using-clock-process-cputime-id-in-clock-gettime
- https://man7.org/linux/man-pages/man3/clock_gettime.3.html
- https://man7.org/linux/man-pages/man3/pthread_setaffinity_np.3.html
- https://man7.org/linux/man-pages/man3/CPU_SET.3.html
- https://stackoverflow.com/questions/8223742/how-to-pass-multiple-parameters-to-a-thread-in-c
- https://stackoverflow.com/questions/52962351/starvation-in-priority-thread-schedule-by-setting-affinity-to-single-cpu
- https://stackoverflow.com/questions/41661288/calculate-running-time-of-thread-in-c
- https://man7.org/linux/man-pages/man2/sched_setscheduler.2.html#LIBRARY
