// simply returns the default scheduling policy
// from file:///C:/Users/vishn/OneDrive/Documents/Linux%20System%20Programming%20Talking%20Directly%20to%20the%20Kernel%20and%20C%20Library.pdf
// updated with documentation from Red Hat to account for batch and idle processes
#include <sched.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
int main()
{
    int policy = sched_getscheduler(getpid());
    switch (policy)
    {
    case SCHED_OTHER:
        printf("Policy is normal\n"); // 0
        break;
    case SCHED_RR:
        printf("Policy is round-robin\n"); // 2
        break;
    case SCHED_FIFO:
        printf("Policy is first-in, first-out\n"); // 1
        break;
    case SCHED_BATCH:
        printf("Policy is batch\n"); // 3
    case SCHED_IDLE:
        printf("Policy is idle\n"); // 5
    case -1:
        perror("sched_getscheduler");
        break;
    default:
        fprintf(stderr, "Unknown policy!\n");
    }
    printf("%d %d %d %d %d\n", SCHED_OTHER, SCHED_RR, SCHED_FIFO, SCHED_BATCH, SCHED_IDLE);
}