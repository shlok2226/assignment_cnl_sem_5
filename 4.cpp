#include <stdio.h>
#define MAX 10
#define INF 999

int main() {
    int n, cost[MAX][MAX], dist[MAX][MAX];
    int nextHop[MAX][MAX], i, j, k, changed;
    int src, dest, path[MAX], count;
    
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    
    printf("Enter cost matrix (999 for no direct link):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            dist[i][j] = cost[i][j];
            if (i == j)
                nextHop[i][j] = i;
            else if (cost[i][j] != INF)
                nextHop[i][j] = j;
            else
                nextHop[i][j] = -1;
        }
    }
    
    printf("\nInitial Routing Tables:\n");
    for (i = 0; i < n; i++) {
        printf("\nRouter %c:\n", 'A' + i);
        printf("Destination\tCost\tNext Hop\n");
        for (j = 0; j < n; j++) {
            printf("%c\t\t", 'A' + j);
            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
            if (nextHop[i][j] == -1)
                printf("-\n");
            else
                printf("%c\n", 'A' + nextHop[i][j]);
        }
    }
    
    do {
        changed = 0;
        int newDist[MAX][MAX];
        int newNext[MAX][MAX];
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                newDist[i][j] = dist[i][j];
                newNext[i][j] = nextHop[i][j];
            }
        }
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (i == j)
                    continue;
                for (k = 0; k < n; k++) {
                    if (cost[i][k] != INF &&
                        dist[k][j] != INF &&
                        cost[i][k] + dist[k][j] < newDist[i][j]) {
                        newDist[i][j] = cost[i][k] + dist[k][j];
                        newNext[i][j] = k;
                        changed = 1;
                    }
                }
            }
        }
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                dist[i][j] = newDist[i][j];
                nextHop[i][j] = newNext[i][j];
            }
        }
    } while (changed);
    
    printf("\nFinal Routing Tables:\n");
    for (i = 0; i < n; i++) {
        printf("\nRouter %c:\n", 'A' + i);
        printf("Destination\tCost\tNext Hop\n");
        for (j = 0; j < n; j++) {
            printf("%c\t\t", 'A' + j);
            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
            if (nextHop[i][j] == -1)
                printf("-\n");
            else
                printf("%c\n", 'A' + nextHop[i][j]);
        }
    }
    
    printf("\nEnter source node (0 to %d): ", n - 1);
    scanf("%d", &src);
    printf("Enter destination node (0 to %d): ", n - 1);
    scanf("%d", &dest);
    
    if (src < 0 || src >= n || dest < 0 || dest >= n) {
        printf("Invalid node number.\n");
        return 1;
    }
    if (dist[src][dest] == INF) {
        printf("Destination is unreachable.\n");
        return 0;
    }
    
    printf("\nShortest path: ");
    printf("%c", 'A' + src);
    count = 0;
    path[count++] = src;
    int curr = src;
    
    while (curr != dest && count < n) {
        curr = nextHop[curr][dest];
        if (curr == -1)
            break;
        path[count++] = curr;
    }
    
    if (curr != dest) {
        printf("\nUnable to reconstruct path.\n");
        return 1;
    }
    
    for (int idx = 1; idx < count; idx++)
        printf(" -> %c", 'A' + path[idx]);
    printf("\nMinimum cost: %d\n", dist[src][dest]);
    
    return 0;
}
```[cite: 1, 2, 3, 4, 5, 6, 7]

---

### 2. TCP Socket Programming (`CN A5.pdf`)[cite: 8]

#### **Server Side**
```c
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
```[cite: 8, 9, 10]

#### **Client Side**
```c
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
```[cite: 11, 12, 13]

---

### 3. UDP Socket Programming (`CN A6.pdf`)[cite: 14]

#### **Server Side**
```c
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
```[cite: 14, 15]

#### **Client Side**
```c
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
```[cite: 16, 17, 18]
