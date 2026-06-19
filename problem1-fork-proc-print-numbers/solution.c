#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Программе передается аргумент — целое число N > 0.
// Необходимо создать N-1 дополнительных процессов таким образом,
// чтобы у каждого процесса было не более одного дочернего процесса.
// Каждый из процессов должен вывести ровно одно число так,
// чтобы на выходе получилась строка: 1 2 3 4 ... N
// Между числами — ровно один пробел, строка завершается символом '\n'.

void process(int cur, int n) {
    printf("%i", cur);
    fflush(stdout);
    if (cur < n) {
        printf(" ");
        fflush(stdout);
        pid_t pid = fork();
        if (pid == 0) {
            process(cur + 1, n);
            exit(0);
        } else {
            wait(NULL);
            exit(0);
        }

    } else if (cur == n) {
        printf("\n");
        fflush(stdout);
        exit(0);
    }



}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    process(1, n);

    // TODO: создайте цепочку из N процессов (каждый не более чем с одним потомком).
    //       Каждый процесс выводит одно число. Порядок вывода должен быть 1 2 3 ... N.

    return 0;
}
