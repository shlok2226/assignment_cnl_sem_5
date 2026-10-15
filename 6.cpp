//Server side
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    while (1) {
        printf("Enter a string (exit to quit): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, len);
        
        memset(buffer, 0, sizeof(buffer));
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
        if (n < 0) {
            perror("Receive failed");
            break;
        }
        buffer[n] = '\0';
        printf("Server response: %s\n", buffer);
        if (strcmp(buffer, "Server disconnected.") == 0)
            break;
    }
    
    close(sockfd);
    printf("Client socket closed.\n");
    return 0;
}

//client side
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    while (1) {
        printf("Enter a string (exit to quit): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, len);
        
        memset(buffer, 0, sizeof(buffer));
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, NULL, NULL);
        if (n < 0) {
            perror("Receive failed");
            break;
        }
        buffer[n] = '\0';
        printf("Server response: %s\n", buffer);
        if (strcmp(buffer, "Server disconnected.") == 0)
            break;
    }
    
    close(sockfd);
    printf("Client socket closed.\n");
    return 0;
}
return 0;[span_1](start_span)[span_1](end_span)
