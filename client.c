#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
// Only 2kb message
#define MAX_MESSAGE_LENGTH 2048

// Driver code
int main()
{
    int sockfd;
    char *word;
    word = (char *)malloc(sizeof(char) * (50));
    char *words_stack[MAX_MESSAGE_LENGTH];
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

    printf("Write a word please: ");
    scanf("%s", word);
    printf("The word that you write is: %s\n", word);
    // sendto(sockfd, (const char *)word, sizeof(word),
    //        MSG_CONFIRM, (const struct sockaddr *)&servaddr,
    //        sizeof(servaddr));
    // printf("Word 1 sent.");

    return 0;
}