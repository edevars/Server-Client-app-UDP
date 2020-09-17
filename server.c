#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAX_WORD_LENGTH 200
#define WORDS_LEN 100

int main()
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char words[WORDS_LEN][MAX_WORD_LENGTH];
    int c = 0;

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

    printf("\n\nServer listening in port %d\n\n", PORT);
    while (1)
    {
        char *word = malloc(sizeof(char) * MAX_WORD_LENGTH);
        recvfrom(sockfd, (char *)word, MAX_WORD_LENGTH,
                 MSG_WAITALL, (struct sockaddr *)&servaddr,
                 &len);

        if (strcmp(word, "stop") == 0)
        {
            int i;

            for (i = 0; i < c; i++)
            {
                printf("Words %d: %s\n", i + 1, words[i]);
            }

            return 0;
        }
        else
        {
            strcpy(words[c], word);
            c++;
        }
    }
}
