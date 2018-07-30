/*  
* printf(); fprintf(); sprintf()
*
*  https://stackoverflow.com/questions/38832230/copy-paste-in-bash-on-ubuntu-on-windows
*
*  in a nutshell:
*  printf(..) == fprintf(stdout,...)
*  sprintf writes formated text to a char array instead of writting it to a stream
*
*
* exit()
*  The C library function void exit(int status) terminates the calling process immediately.
*  Any open file descriptors belonging to the process are closed and any children of the process 
*  are inherited by process 1, init, and the process parent is sent a SIGCHLD signal.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/* Handler for SIGINT and SIGTERM */
static void signal_handler (int signo)
{
	if (signo == SIGINT)
	{
		printf("Caught SIGINT!\n");
	}
	else if (signo == SIGTERM)
	{
		printf("Caught SIGTERM!\n");
	}
	else
	{
		printf("Caught unexpected signal!\n");
		exit (EXIT_FAILURE);
	}
	exit (EXIT_SUCCESS);
}

int main(void)
{
	/* Register signal_handler as our signal handler for SIGINT
	*
	* SIGINT
	*  This signal is sent to all processes in the foreground process group when
	*  the user enters the interrupt character (CTRL-C).
	*  Default behaviour: Terminate
	*  But processes can also catch and handle the signal to clean up before terminating.
	*/	
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		fprintf (stderr, "Cannot handle SIGINT!\n");
		exit (EXIT_FAILURE);
	}
	/* Register signal handler as our signal handler for SIGTERM
	*
	* SIGTERM
	*  This signal is sent only by kill(). It allows the user to gracefully terminate a
	*  process (the default action). Processes may catch and handle the signal, but should
	*  terminate promptly.
	*/
	if (signal(SIGTERM, signal_handler) == SIG_ERR)
	{
		fprintf (stderr, "Cannot reset SIGPROF!\n");
		exit (EXIT_FAILURE);
	}
	/* Reset SIGPROFs behaviour to the default
	*
	* SIGPROF
	*  The setitimer() function, when used with the ITIMER_PROF flag, 
	*  generates this signal when a profiling timer expires. 
	*  The default action is to terminate the process
	*/
	if (signal(SIGPROF, SIG_DFL) == SIG_ERR)
	{
		fprintf(stderr, "Cannot reset SIGPROF!\n");
		exit (EXIT_FAILURE);
	}
	/* IGNORE SIGHUP
	*
	* SIGHUP
	*  The kernel sends this signal to the session leader whenever the session’s terminal
	*  disconnects. The kernel also sends this signal to each process in the foreground
	*  process group when the session leader terminates. The default action is to terminate,
	*  which makes sense—the signal suggests that the user has logged out. Daemon pro‐
	*  cesses “overload” this signal with a mechanism to instruct them to reload their
	*  configuration files. Sending SIGHUP to Apache, for example, instructs it to reread
	*  httpd.conf. Using SIGHUP for this purpose is a common convention but not manda‐
	*  tory. The practice is safe because daemons do not have controlling terminals and
	*  thus should never normally receive this signal.
	*/
	if (signal(SIGHUP, SIG_IGN) == SIG_ERR)
	{
		fprintf(stderr, "Cannot ignore SIGHUP!\n");
		exit (EXIT_FAILURE);
	}
	
	for (;;)
	{
		pause();
	}
	return 0;
}
