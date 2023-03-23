/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:08:08 by mmanouze          #+#    #+#             */
/*   Updated: 2023/03/22 15:04:36 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERS_HPP
# define SERVERS_HPP

#include <errno.h>
#include <iostream>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>

#define BUFFER_SIZE 2047

class servers
{
	private :
 		std::vector<int> 		server_list;
		struct sockaddr_in 		client_addr;
	    struct sockaddr_in 		host_addr;
		int 					host_addrlen;
		int 					client_addrlen;
		int 					received;
		char 					buffer[BUFFER_SIZE + 1];
		fd_set 					readfds;
		fd_set 					writefds;
		fd_set 					original;
	public :
		servers();
		~servers();
		void fill_fd();
		void clients_waiting_room();
		void accept_clients(int sockfd);
		std::vector<int> get_list() const;
		void create_server_sockets(size_t port);
};




#endif