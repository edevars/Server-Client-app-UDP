
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
    int *number1 = malloc(sizeof(int));
    int *number2 = malloc(sizeof(int));
    int *solution = malloc(sizeof(int));
    char *message = "Datos correctos";
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

    int len;

    len = sizeof(cliaddr); //len is value/resuslt

    printf("Server listening in port %d\n\n",PORT);
    recvfrom(sockfd, (int *)number1, sizeof(number1),
                 MSG_WAITALL, (struct sockaddr *)&cliaddr,
                 &len);

    printf("Number 1 : %d\n", *number1);

    recvfrom(sockfd, (int *)number2, sizeof(number2),
                 MSG_WAITALL, (struct sockaddr *)&cliaddr,
                 &len);

    printf("Number 2 : %d\n", *number2);

    sendto(sockfd, (const char *)message, strlen(message),
           MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
           len);

    printf("\nResponse sent: %s", message);

    *solution = (*number1 * *number1) + (*number2 * *number2);

    sendto(sockfd, (int *)solution, sizeof(solution),
           MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
           len);

    printf("\nSolution sent: %d \n", *solution);

    return 0;
}
