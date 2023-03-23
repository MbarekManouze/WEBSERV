#include <errno.h>
#include <iostream>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define BUFFER_SIZE 2047

int main() {

    int received = 0;
    char buffer[BUFFER_SIZE + 1];
    char resp[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n"
                  "<html>hello, world</html>\r\n";

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("webserver (socket)");
        return 1;
    }
    std::cout << "socket created successfully\n";

    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Create client address
    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);


    if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(host_addr)) != 0) {
        perror("webserver (bind)");
        return 1;
    }
    std::cout << "socket successfully bound to address\n";

    if (listen(sockfd, SOMAXCONN) != 0) {
        perror("webserver (listen)");
        return 1;
    }
    std::cout << "server listening for connections\n";

    while (1) {
        int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr, (socklen_t *)&host_addrlen);
        if (newsockfd < 0) {
            perror("webserver (accept)");
            continue;
        }
        printf("connection accepted\n");

        // Get client address
        int sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);

        if (sockn < 0) {
            perror("webserver (getsockname)");
            continue;
        }

        //int valread = read(newsockfd, buffer, BUFFER_SIZE);
        int valread = recv(newsockfd, buffer + received, BUFFER_SIZE - received, 0);  
        if (valread < 0) {
            perror("webserver (read)");
            continue;
        }
        received += valread;
        buffer[received] = 0;

        std::cout << buffer << std::endl;

        char method[BUFFER_SIZE];
        char uri[BUFFER_SIZE];
        char version[BUFFER_SIZE];

        sscanf(buffer, "%s %s %s", method, uri, version);

        printf("[%s:%u]\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));


        int valwrite = write(newsockfd, resp, strlen(resp));
        if (valwrite < 0) {
            perror("webserver (write)");
            continue;
        }

        close(newsockfd);
    }


    return 0;
}
