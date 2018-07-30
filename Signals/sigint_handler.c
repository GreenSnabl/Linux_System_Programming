#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sigint_handler (int signo)
{
	/* technically you shouldn't use printf in a
	* signal handler, but it isn't the end of the world */
	printf("Caught SIGINT!\n");
	exit (EXIT_SUCCESS);
}

int main(int argc, char** argv)
{
	/* Register sigint_handler as our signal handler for sigint
	*  void (*signal(int signo, (void*)(int)))(int)
	*/
	
	if (signal (SIGINT, sigint_handler) == SIG_ERR) {
		fprintf(stderr, "Cannot handle SIGINT!\n");
		exit(EXIT_FAILURE);
	}	
	for (;;)
	{
		pause();
	}
	return 0;
}

