// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write 
// the three messages to the parent and have the parent print out 
// the messages. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGSIZE 16

char* msg1 = "hello world #1";
char* msg2 = "hello world #2";
char* msg3 = "hello world #3";

int main()
{
    // Your code here
    char inbuf[MSGSIZE];
    int p[2];
    int nbytes;

    if (pipe(p) < 0) {
      fprintf(stderr, "pipe failed\n");
      exit(2);
    }

    int rc = fork();

    if (rc < 0) {   // fork failed; exit
      fprintf(stderr, "fork failed, exiting\n");
      exit(1);

    } else if (rc == 0) {
      printf("child writing to pipe\n");
      write(p[1], msg1, MSGSIZE);
      write(p[1], msg2, MSGSIZE);
      write(p[1], msg3, MSGSIZE);

    } else {
      close(p[1]);
      printf("parent reading from pipe\n");

      // typical fashion, instead of below for loop
      while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0) {
        printf("%s\n", inbuf);
      }

      // for (int i = 0; i < 3; i++) {
      //   read(p[0], inbuf, MSGSIZE);
      //   printf("%s\n", inbuf);
      // }

      printf("finished reading\n");
    }
    
    return 0;
}
