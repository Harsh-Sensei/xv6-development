-/* tour.c
 * To learn the basic signal handling in c
 * Can send the interrupt signal via Ctrl-c in a terminal.
 *
 * Complete TODO items for this question
 */

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_FRIEND 5 // Number of friends visiting the Dinosaurs Park

int friend_count = 0; // Current count of friends completed the tour

// TODO: Add a signal handling function which handle SIGINT and SIGCHLD signals
void sigint_handler(int sig)
{
    printf("You have interrupted the tour.\n");
    if (friend_count < 5)
    {
        printf("Oh Sorry! Only %d out of the 5 friends have completed the tour.\n", friend_count);
    }
    else
    {
        printf("All 5 friends have completed the tours.\n");
        printf("Thank you for visiting the Dinosaurs park\n");
        exit(0);
    }
    return;
}


// END TODO
int main(int argc, char *argv[])
{

    printf("Welcome to the Dinosaurs Park.\n");

    /*
     * TODO: add struct/calls to sigaction() to handle SIGINT and SIGCHLD.
     * Use sigaction() and associated structs.
     * Ensure that the flag SA_RESTART is set as well to ensure system calls are automatically restarted.
     */

    struct sigaction sigint_struct;
    sigint_struct.sa_handler = sigint_handler;
    sigint_struct.sa_flags = SA_RESTART; // Deals with interrupts when files are opened and some other stuff

    sigaction(SIGINT, &sigint_struct, NULL);

    // END TODO
    printf("The Process ID of Dinosaurs Park: %d \n", getpid());
    for (size_t friend = 1; friend <= NUM_FRIEND; friend++)
    {
        if (fork() == 0)
        {
            // TODO Note that, you must carefully place the various children in different process groups
            //  that is different from the default process group of its parent
            // say, using the setpgid system call.
            sigset_t sigset;
            sigfillset(&sigset);
            sigprocmask(SIG_SETMASK, &sigset, NULL);

            sleep(5 * friend); // sleep emulates "touring" time
            printf("Friend #%zu with process ID - %d has completed the tour.\n", friend, getpid());
            exit(0);
            // END TODO
        }
    }
    while (wait(NULL) > 0)
        friend_count++;
    for (;;)
        pause(); // wait for all friends to complete tour
    return 0;
}
