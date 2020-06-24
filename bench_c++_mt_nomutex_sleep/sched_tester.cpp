// simply returns the default scheduling policy
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
        printf("Policy is normal\n");
        break;
    case SCHED_RR:
        printf("Policy is round-robin\n");
        break;
    case SCHED_FIFO:
        printf("Policy is first-in, first-out\n");
        break;
    case -1:
        perror("sched_getscheduler");
        break;
    default:
        fprintf(stderr, "Unknown policy!\n");
    }
}