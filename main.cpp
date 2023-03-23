/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanouze <mmanouze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:15 by mmanouze          #+#    #+#             */
/*   Updated: 2023/03/22 15:01:05 by mmanouze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "servers.hpp"


#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{

	servers serv;

	for (int i = 0; i < 10; i++)
		serv.create_server_sockets(8080 + i);
	serv.fill_fd();
	while (1)
	{
		serv.clients_waiting_room();
	}
	

	return 0;
}
