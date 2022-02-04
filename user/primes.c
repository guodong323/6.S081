#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define NUMS 36
#define ONE '1'
#define ZERO '0'

void helper(int pipe_read,int pipe_write) {
    char buf[NUMS];
    read(pipe_read,buf,NUMS);
    int val = 0;
    for (int i = 0;i < NUMS; i++) {
        if (buf[i] == ONE) {
            val = i;
            break;
        }
    }
    if (val == 0) {
        exit(1);
    }
    printf("prime %d\n",val);
    buf[val] = ZERO;
    
    for (int i = val;i < NUMS; i++) {
        if (i % val == 0) {
            buf[i] = ZERO;
        }
    }

    int pid = fork();
    if (pid < 0) {
        fprintf(2,"fork error");
        exit(0);
    } else if (pid == 0) {
        write(pipe_write,buf,NUMS);
        wait(0);
    } else if (pid > 0) {
        helper(pipe_read,pipe_write);
        wait(0);
    }
}
int main(int argc,char *argv[]) {
    char source[NUMS];
    source[0] = ZERO;
    source[1] = ZERO;
    for (int i = 2;i < NUMS; i++) {
        source[i] = ONE;
    }

    int fd[2];
    pipe(fd);
    int pid = fork();
    if (pid < 0) {
        fprintf(2,"fork error");
        exit(1);
    } else if (pid == 0) {
        write(fd[1],source,NUMS);
        wait(0);
    } else if (pid > 0) {
        helper(fd[0],fd[1]);
        wait(0);
    }
    exit(0);
}