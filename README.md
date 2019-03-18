# OpenMPAWSLambdaV2
OpenMPAWSLambda but with multiple binaries

This is an improved version of the [https://github.com/Craigspaz/OpenMPAWSLambda](https://github.com/Craigspaz/OpenMPAWSLambda)

In this version the setup is the same except that there are two binary files and the fork and execvp system calls are being used.

test.c can be compiled with the following command

```
gcc test.c -o test -fopenmp
```

test2.c can be compiled with the following command

```
gcc test2.c -o test2
```

test2 is a simple program which just prints "Hello World!" and then terminates. test is a OpenMP based program which will create 4 threads. The thread with index 0 is considered the master thread and does some random task. The other three threads will do other work which in this case is launching another binary file. It launches the test2 program by doing a fork and then execvp. This creates a master process and a child process. The master process which is running the "test" program will use waitpid to check to see if the child process has terminated. The child proces will run the test2 program. Once the child processes have terminated and the master thread in the master process finishes the entire program terminates.
