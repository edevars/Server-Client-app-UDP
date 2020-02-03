
// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

// Driver code
int main()
{
    int sockfd;
    int *number = malloc(sizeof(int));
    char *answer_number = malloc(sizeof(int));
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr); //len is value/resuslt

    n = recvfrom(sockfd, (int *)number, sizeof(number),
                 MSG_WAITALL, (struct sockaddr *)&cliaddr,
                 &len);

    printf("Client : %d\n", *number);
    *answer_number = *number * 2;
    sendto(sockfd, (int *)answer_number, sizeof(answer_number),
           MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
           len);
    printf("Response sent.\n");

    return 0;
}
