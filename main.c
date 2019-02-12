#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {

  if (argc < 2) {
    printf("Uso deve ser com argumento 'ucp' ou 'ucp-mem'.\n");
    exit(1);
  }

  int pid = fork();

  if (pid == 0) {
    if (strcmp("ucp", argv[1]) == 0) {
      for (;;) {}
    }
    else if (strcmp("ucp-mem", argv[1]) == 0) {
      for (;;) {
        malloc(100);
      }
    }
    else {
      exit(1);
    }
  }

  else if(pid > 0) {
    if (strcmp("ucp", argv[1]) == 0) {
      int i;
      for (i = 0; i < 20; i++) {
        usleep(500000);

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

        printf("Uso de UCP: %s\n", cpu_usage);
        printf("PID do filho: %d\n", pid);

      }
    }
    else if (strcmp("ucp-mem", argv[1]) == 0) {
      int i;
      for (i = 0; i < 10; i++) {
        usleep(50000);

        char bash_cmd[256];
        sprintf(bash_cmd, "ps v %i | grep -v MEM | awk '{print $9}'", pid );
        // ps -eo pid,pcpu

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

        printf("mem_usage == %s", mem_usage);

      }
    }
    else {
      printf("Uso deve ser com argumento 'ucp' ou 'ucp-mem'.\n");
      exit(1);
    }

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

    exit(1);
  }
  else {
    printf("Erro!\n");
    return 255;
  }

  return 0;
}
