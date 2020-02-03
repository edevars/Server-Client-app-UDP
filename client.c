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

// Driver code
int main()
{
    int sockfd;
    int *number = malloc(sizeof(int));
    int *response = malloc(sizeof(int));
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

    printf("\nSet a number please: ");
    scanf("%d", number);

    sendto(sockfd, (int *)number, sizeof(number),
           MSG_CONFIRM, (const struct sockaddr *)&servaddr,
           sizeof(servaddr));
    printf("\nNumber sent.\n");

    n = recvfrom(sockfd, (int *)response, sizeof(response),
                 MSG_WAITALL, (struct sockaddr *)&servaddr,
                 &len);

    printf("Server : %d\n", *response);

    close(sockfd);
    return 0;
}