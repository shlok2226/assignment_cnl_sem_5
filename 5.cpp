#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return 1;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);
    
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return 1;
    }
    
    if (listen(server_fd, 5) < 0) {
        perror("Listen failed");
        close(server_fd);
        return 1;
    }
    
    printf("Server waiting for client...\n");
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        return 1;
    }
    printf("Client connected.\n");
    
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0)
            break;
        buffer[n] = '\0';
        printf("Client: %s\n", buffer);
        if (strcmp(buffer, "exit") == 0)
            break;
            
        printf("Enter reply: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;
        buffer[strcspn(buffer, "\n")] = '\0';
        if (send(client_fd, buffer, strlen(buffer), 0) < 0)
            break;
        if (strcmp(buffer, "exit") == 0)
            break;
    }
    
    close(client_fd);
    close(server_fd);
    printf("Connection closed.\n");
    return 0;
}

//client side code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }
    
    printf("Connected to server.\n");
    printf("Type 'exit' to end the chat.\n");
    
    while (1) {
        printf("Enter message: ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            break;
        buffer[strcspn(buffer, "\n")] = '\0';
        if (send(sock, buffer, strlen(buffer), 0) < 0)
            break;
        if (strcmp(buffer, "exit") == 0)
            break;
            
        memset(buffer, 0, sizeof(buffer));
        int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0)
            break;
        buffer[n] = '\0';
        printf("Server: %s\n", buffer);
        if (strcmp(buffer, "exit") == 0)
            break;
    }
    
    close(sock);
    printf("Disconnected from server.\n");
    return 0;
}
}
