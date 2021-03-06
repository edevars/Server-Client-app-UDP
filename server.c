#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_MESSAGE_LENGTH 200

// Driver code
int main()
{
    int sockfd;
    int *number1 = malloc(sizeof(int));
    int *number2 = malloc(sizeof(int));
    int *solution = malloc(sizeof(int));
    char *message = malloc(sizeof(char) * MAX_MESSAGE_LENGTH);
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

    do
    {
        *number1 = 0;
        *number2 = 0;
        *solution = 0;

        printf("\n\nServer listening in port %d\n\n", PORT);
        recvfrom(sockfd, (int *)number1, sizeof(number1),
                 MSG_WAITALL, (struct sockaddr *)&cliaddr,
                 &len);

        printf("Number 1 : %d\n", *number1);

        recvfrom(sockfd, (int *)number2, sizeof(number2),
                 MSG_WAITALL, (struct sockaddr *)&cliaddr,
                 &len);

        printf("Number 2 : %d\n", *number2);

        *solution = (*number1 * *number1) + (*number2 * *number2);
        

        if (*solution >= 100)
        {
            message = "Sorry! Wrong data introduced";
        }
        else
        {
            message = "Ok, the sum of the power of both numbers is less than 100";
        }

        sendto(sockfd, (const char *)message, strlen(message),
               MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
               len);

        printf("\n\nDATA SENT");   
        printf("\nResponse sent: %s", message);

        sendto(sockfd, (int *)solution, sizeof(solution),
               MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
               len);

        printf("\nSolution sent: %d \n", *solution);
    } while (*solution >= 100);

    return 0;
}
