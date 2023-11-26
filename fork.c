/*
The Fork system call is used for creating a new process in Linux, and Unix systems, which is called the child process, which runs concurrently with the process that makes the fork() call (parent process).

The different values returned by fork().

-ve value : The creation of a child process was unsuccessful.
0 : Returned to the newly created child process.
+ve value : Returned to parent or caller. The value contains the process ID of the newly created child process.

*/

#include <stdio.h>
#include <unistd.h>

int main(){
    fork();
    fork();

    printf("Hello World!\n");

    printf("Get PID: %d\n\n", getpid());


    return 0;
}
