#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
// 父进程先写，子线程读
int main(int argc,char *argv[]) {
    int parent[2];
    int child[2];
    int pid;
    int p = pipe(parent);
    int c = pipe(child);
    char buff[1];
    if (p == -1 || c == -1) {
        fprintf(2,"pipe error");
        exit(1);
    }
    if ((pid = fork()) < 0) {
        fprintf(2,"fork error");
        exit(1);
    } else if (pid == 0) {
        close(child[0]);
        close(parent[1]);
        read(parent[0], buff, 1);
        printf("%d: received p%sng\n", getpid(), buff);
        write(child[1], "o", 1);
        close(child[1]); 
    } else if (pid > 0) {
        close(parent[0]);
        close(child[1]);
        write(parent[1], "i", 1);
        close(parent[1]);
        read(child[0], buff, 1);
        printf("%d: received p%sng\n", getpid(), buff);
    }
    exit(0);
}