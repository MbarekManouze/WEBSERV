/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:11:29 by mmanouze          #+#    #+#             */
/*   Updated: 2023/03/22 15:08:23 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "servers.hpp"

servers::servers():received(0)
{
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&original);
}

servers::~servers()
{
	for (size_t i = 0; i < server_list.size(); i++)
		FD_CLR(server_list[i], &original);
}

std::vector<int> servers::get_list() const {
	return (this->server_list);
}

void servers::fill_fd(){
	for (std::vector<int>::iterator it = server_list.begin(); it != server_list.end(); it++)
		FD_SET(*it, &original);
}

void servers::clients_waiting_room()
{
	readfds = original;
	int max = this->server_list.back() + 1;

	printf("%d\n", max);

	if (select(max, &readfds, 0, 0, 0) < 0) {
        perror("select() failed.");
        exit(1);
	}

	for (std::vector<int>::iterator it = server_list.begin(); it != server_list.end(); it++)
	{
		if (FD_ISSET(*it, &readfds))
		{
			accept_clients(*it);
			return ;
		}
	}
	return ;
}

void servers::accept_clients(int sockfd)
{
    char resp[] = "HTTP/1.0 200 OK\r\n"
                  "Server: webserver-c\r\n"
                  "Content-type: text/html\r\n\r\n"
                  "<html>hello, world</html>\r\n";

        int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr, (socklen_t *)&host_addrlen);
        if (newsockfd < 0) {
            perror("webserver (accept)");
            return ;
        }
        printf("connection accepted\n");

        // Get client address
        int sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addrlen);

        if (sockn < 0) {
            perror("webserver (getsockname)");
            return ;
        }

        //int valread = read(newsockfd, buffer, BUFFER_SIZE);
        int valread = recv(newsockfd, buffer + received, BUFFER_SIZE - received, 0);  
        if (valread < 0) {
            perror("webserver (read)");
            return ;
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
            return ;
        }

        close(newsockfd);

}

void servers::create_server_sockets(size_t port)
{
    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(port);
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	host_addrlen = sizeof(host_addr);
	client_addrlen = sizeof(client_addr);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		perror("SOCKET :");
		exit(1);
	}
	printf("port : %lu\n", port);
	this->server_list.push_back(sock);

	if (bind(sock, (struct sockaddr *)&host_addr, sizeof(host_addr)) != 0)
	{
		perror("BIND :");
		exit(1);
	}

	if (listen(sock, SOMAXCONN) != 0)
	{
		perror("LISTEN :");
		exit(1);
	}
}