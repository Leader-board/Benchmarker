#include <sched.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
void sched_tester()
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
    case SCHED_BATCH:
        printf("Policy is batch\n");
        break;
    case SCHED_IDLE:
        printf("Policy is idle\n"); // reference = https://lwn.net/Articles/3866/
        break;
    case -1:
        perror("sched_getscheduler");
        break;
    default:
        fprintf(stderr, "Unknown policy!\n");
    }
}
int main()
{
    // get the current parameter of the current process - https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux_for_real_time/7/html/reference_guide/sect-using_library_calls_to_set_priority
    struct sched_param sp;
    int ret;
    ret = sched_getparam(getpid(), &sp);
    if (ret == -1)
    perror("Getting scheduling parameters failed!\n");
    sched_tester(); // retrieve scheduling policy of current process
    ret = sched_setscheduler(getpid(), SCHED_RR, &sp);
    if (ret == -1)
    perror("Setting scheduling parameters failed\n");
    sched_tester();
}