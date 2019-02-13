#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>


//! Get process CPU usage
/** Use a chain of bash commands to retrieve the % of the CPU in use by the process with the
  * given PID. */
void getProcessCpuUsage(int pid) {
  char bash_cmd[256];
  sprintf(bash_cmd, "ps -eo pid,pcpu | grep %d | awk '{print $2}'", pid );

  char buffer[1000];
  FILE *pipe;
  int len;
  pipe = popen(bash_cmd, "r");

  if (NULL == pipe) {
    perror("pipe");
    exit(1);
  }

  char* cpu_usage = fgets(buffer, sizeof(buffer), pipe);
  len = strlen(bash_cmd);
  bash_cmd[len-1] = '\0';
  pclose(pipe);

  printf("Uso de UCP: %s", cpu_usage);
}


//! Get process RAM usage.
/** Use a chain of bash commands to retrieve the % of the RAM in use by the process with the
  * given PID. */
void getProcessMemUsage(int pid) {
  char bash_cmd[256];
  sprintf(bash_cmd, "ps v %i | grep -v MEM | awk '{print $9}'", pid );

  char buffer[1000];
  FILE *pipe;
  int len;
  pipe = popen(bash_cmd, "r");

  if (NULL == pipe) {
    perror("pipe");
    exit(1);
  }

  char* mem_usage = fgets(buffer, sizeof(buffer), pipe);
  len = strlen(bash_cmd);
  bash_cmd[len-1] = '\0';
  pclose(pipe);

  printf("Uso de RAM: %s", mem_usage);
}



//! Kill process.
/** Use a chain of bash commands to kill the process with the given PID. */
void killProcess(int pid) {
  char bash_cmd[256];
  sprintf(bash_cmd, "kill -9 %i", pid );

  char buffer[1000];
  FILE *pipe;
  int len;
  pipe = popen(bash_cmd, "r");

  if (NULL == pipe) {
    perror("pipe");
    exit(1);
  }

  char* mem_usage = fgets(buffer, sizeof(buffer), pipe);
  len = strlen(bash_cmd);
  bash_cmd[len-1] = '\0';
  pclose(pipe);
}


//! Perform tests with RAM and/or CPU usage.
/** Use: bin [ucp|ucp-mem]
  * Calling as 'bin ucp' causes the program to launch a child process which will use a lot of
  * CPU resources, then the parent process will monitor it for 10 seconds and print out
  * the child process each half second.
  * Calling as 'bin ucp-mem' will behave the same, but the child process will also consume
  * increasingly RAM over time and the parent will monitor that as well. */
int main(int argc, char **argv) {

  // Report use error and exit, if missing argument. User must specify type of test.
  if (argc < 2) {
    printf("Uso deve ser com argumento 'ucp' ou 'ucp-mem'.\n");
    exit(1);
  }

  // Create a child and get it's PID into the original process.
  int pid = fork();

  // If PID is 0, the current running process is the child and shall perform those actions.
  if (pid == 0) {
    // CPU intensive loop.
    if (strcmp("ucp", argv[1]) == 0) {
      for (;;) {}
    }
    // CPU and RAM intesive loop.
    else if (strcmp("ucp-mem", argv[1]) == 0) {
      for (;;) {
        malloc(8);
      }
    }
    // Don't do anything if argument received is not valid, just quit silently.
    else {
      exit(1);
    }
  }

// If PID is > 0, this process is the parent and shall monitor the child for 10s then kill it and exit.
  else if(pid > 0) {
    // If running the CPU only tests, check only for the CPU usage.
    if (strcmp("ucp", argv[1]) == 0) {
      int i;
      for (i = 0; i < 20; i++) {
        usleep(500000);
        getProcessCpuUsage(pid);
      }
    }

    // If running the CPU and RAM tests, check both.
    else if (strcmp("ucp-mem", argv[1]) == 0) {
      int i;
      for (i = 0; i < 20; i++) {
        usleep(500000);
        getProcessCpuUsage(pid);
        getProcessMemUsage(pid);
        printf("\n");
      }
    }

    // If argument given by the user isn't valid, inform it then exit.
    else {
      printf("Uso deve ser com argumento 'ucp' ou 'ucp-mem'.\n");
      exit(1);
    }

    // Kill the child process.
    killProcess(pid);

  }
  else {
    // Something went wrong in fork(), inform it then exit.
    printf("Erro %d\n", pid);
    return pid;
  }

  // Success finish!
  return 0;
}
