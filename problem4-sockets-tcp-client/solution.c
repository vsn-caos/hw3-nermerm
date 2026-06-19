#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Программе передаются два аргумента:
//   argv[1] — IPv4-адрес сервера в десятичной записи (например, "127.0.0.1")
//   argv[2] — номер порта
//
// Программа должна:
//   1. Установить TCP-соединение с указанным сервером.
//   2. В цикле читать со stdin целые знаковые числа в текстовом формате.
//   3. Отправлять каждое число на сервер в бинарном виде (int32, Little Endian).
//   4. Получать от сервера int32 LE в ответ и выводить его в stdout в текстовом виде.
//   5. Если сервер закрыл соединение — завершиться с кодом возврата 0.

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <ipv4_addr> <port>\n", argv[0]);
        return 1;
    }
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in pupu;
    memset(&pupu, 0, sizeof(pupu));
    pupu.sin_family = AF_INET;
    pupu.sin_port = htons(atoi(argv[2]));

    inet_aton(argv[1], &pupu.sin_addr);

    connect(sockfd, &pupu, sizeof(pupu));
    char buffer[128];
    int num;
    int ans;
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        num = atoi(buffer);
        send(sockfd, &num, sizeof(num), 0);
        recv(sockfd, &ans, sizeof(ans), 0);
        printf("%d\n", ans);
        fflush(stdout);
    }
    
    close(sockfd);
    // TODO: создайте TCP-сокет (AF_INET, SOCK_STREAM),
    //       заполните struct sockaddr_in с помощью inet_aton/inet_pton,
    //       подключитесь через connect,
    //       реализуйте цикл чтения/отправки/приёма/вывода чисел.
    //       Порядок байт — Little Endian (на x86/x86_64 это нативный порядок).

    return 0;
}
