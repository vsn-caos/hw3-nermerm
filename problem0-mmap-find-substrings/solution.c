#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

// Программе передаются два аргумента: имя файла и строка для поиска.
// Необходимо найти все вхождения строки в текстовом файле,
// используя отображение на память с помощью системного вызова mmap.
// На стандартный поток вывода вывести список всех позиций (с нуля),
// где встречается искомая строка, по одной на строку.

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <search_string>\n", argv[0]);
        return 1;
    }

    const char* file_name = argv[1];
    int fd = open(file_name, O_RDONLY);
    struct stat st;
    fstat(fd, &st);
    int file_size = st.st_size;
    int str_size = strlen(argv[2]);
    const char* cmp_str = argv[2];

    char* in_file = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    for (int i = 0; i <= file_size - str_size; ++i) {
        if(memcmp(in_file + i, cmp_str, str_size) == 0) {
            printf("%i\n", i);
        }
    }

    munmap(in_file, file_size);
    close(fd);

    // TODO: откройте файл, получите его размер через fstat,
    //       отобразите в память через mmap,
    //       найдите все вхождения argv[2] и выведите их позиции

    return 0;
}
