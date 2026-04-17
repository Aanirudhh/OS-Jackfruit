#define GET_MEM 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define MAX_CONTAINERS 10

struct container {
    int id;
    pid_t pid;
    int active;
};

struct container containers[MAX_CONTAINERS];
int container_count = 0;

void handle_sigchld(int sig) {
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void start_container() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);

        close(pipefd[1]);

        execl("/bin/ls", "ls", NULL);
        perror("exec failed");
        exit(1);
    } else {
        close(pipefd[1]);

        containers[container_count].id = container_count;
        containers[container_count].pid = pid;
        containers[container_count].active = 1;

        printf("Started container ID: %d, PID: %d\n", container_count, pid);

		int fd = open("/dev/monitor", O_RDWR);
if (fd >= 0) {
    ioctl(fd, GET_MEM, &pid);
    close(fd);
} else {
    perror("open /dev/monitor failed");
}

        char buffer[1024];
        int n;

        while ((n = read(pipefd[0], buffer, sizeof(buffer)-1)) > 0) {
            buffer[n] = '\0';
            printf("[Container %d]: %s", container_count, buffer);
        }

        close(pipefd[0]);
        container_count++;
    }
}

void list_containers() {
    printf("\nActive containers:\n");
    for (int i = 0; i < container_count; i++) {
        if (containers[i].active) {
            printf("ID: %d, PID: %d\n", containers[i].id, containers[i].pid);
        }
    }
    printf("\n");
}

void stop_container(int id) {
    if (id < 0 || id >= container_count) {
        printf("Invalid ID\n");
        return;
    }

    kill(containers[id].pid, SIGKILL);
    containers[id].active = 0;

    printf("Stopped container %d\n", id);
}

int main() {
    char command[100];

    signal(SIGCHLD, handle_sigchld);

    while (1) {
        printf("cmd> ");

        if (fgets(command, sizeof(command), stdin) == NULL) break;

        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "start") == 0) {
            start_container();
        }
        else if (strcmp(command, "list") == 0) {
            list_containers();
        }
        else if (strncmp(command, "stop", 4) == 0) {
            int id;
            if (sscanf(command, "stop %d", &id) == 1)
                stop_container(id);
        }
        else if (strcmp(command, "exit") == 0) {
            break;
        }
        else {
            printf("Unknown command\n");
        }
    }

    return 0;
}
