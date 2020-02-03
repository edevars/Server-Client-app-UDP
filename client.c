// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_MESSAGE_LENGTH 100

// Driver code
int main()
{
    int sockfd;
    int *number1 = malloc(sizeof(int));
    int *number2 = malloc(sizeof(int));
    char *response [MAX_MESSAGE_LENGTH];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed"); //like console error
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    printf("\nSet number 1 please: ");
    scanf("%d", number1);

    sendto(sockfd, (int *)number1, sizeof(number1),
           MSG_CONFIRM, (const struct sockaddr *)&servaddr,
           sizeof(servaddr));
    printf("\nNumber 1 sent.");

    printf("\nSet number 2 please: ");
    scanf("%d", number2);

     sendto(sockfd, (int *)number2, sizeof(number2),
           MSG_CONFIRM, (const struct sockaddr *)&servaddr,
           sizeof(servaddr));
    printf("Number 2 sent.\n");

    n = recvfrom(sockfd, (char *)response, MAX_MESSAGE_LENGTH,
                 MSG_WAITALL, (struct sockaddr *)&servaddr,
                 &len);

    response[n] = '\0'; 

    printf("Server : %s\n", response);

    close(sockfd);
    return 0;
}