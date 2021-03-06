// Write another program using `fork()`. The child process should print "hello";
// the parent process should print "goodbye". You should ensure that the child
// process always prints first.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    // Your code here
    int rc = fork();

    if (rc < 0) {   // fork failed; exit
      fprintf(stderr, "fork failed, exiting\n");
      exit(1);
    } else if (rc == 0) {   // child process satisfies this branch
      printf("hello, via child process (pid: %d)\n", (int)getpid());
    } else {
      int wc = waitpid(rc, NULL, 0);
      printf("goodbye, via parent process (pid: %d) of child %d\n", (int)getpid(), rc);
    }

    return 0;
}
