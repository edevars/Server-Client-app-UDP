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
    struct sockaddr_in servaddr, cliaddr;
    char message[10000] = ""; 

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

    int n, len;

    printf("\n\nServer listening in port %d\n\n", PORT);
    while (1)
    {
        char *word = malloc(sizeof(char) * MAX_MESSAGE_LENGTH);
        recvfrom(sockfd, (char *)word, MAX_MESSAGE_LENGTH,
                     MSG_WAITALL, (struct sockaddr *)&servaddr,
                     &len);
                     
        strcat(message, word);
        strcat (message, ",");
        
        printf("Final message : %s\n", message);
    }

    return 0;
}
