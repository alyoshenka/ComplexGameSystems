#include "server.h"

namespace GameNetwork
{

	player* server::add_new_player(address_struct new_address)
	{
		if (current_player_count >= MAX_PLAYER_COUNT)
		{
			printf("cannot add new player: server full\n");
			return nullptr;
		}

		player* new_player = new player();
		new_player->set_address(new_address);

		app->add_player(new_player);
		current_player_count++;
		std::cout << "added new player " << new_player->get_address_string() << std::endl;

		return new_player;
	}

	server::server() : network_connection::network_connection()
	{
		current_player_count = 0;

		printf("server started\n");
	}

	bool server::initialize_connection()
	{
		if (! initialize_win_sock()
			|| ! initialize_socket()
			|| ! initialize_address()
			|| ! bind_socket())
		{
			printf("server failed\n");
			return FAIL;
		}
		printf("server connected\n");
		return PASS;
	}

	bool server::run_connection()
	{
		int bytes_recieved = recvfrom(sock, buffer, IDENTIFY_BUFFER_SIZE, flags, (SOCKADDR*)& from, &from_size);
		if (bytes_recieved == SOCKET_ERROR)
		{
			printf("recvfrom returned SOCKET_ERROR, WSAGetLastError() %d\n", WSAGetLastError());
			return FAIL;
		}

		char* from_char = inet_ntoa(((sockaddr_in)from).sin_addr);
		address_struct from_address = char_to_address(from_char);

		player* current_player = nullptr;
		current_player = app->find_player(from_address);
		if (nullptr == current_player) { current_player = add_new_player(from_address); }

		char client_input = buffer[0];
		std::cout << "player " << current_player->get_address_string() << " sent data: " << client_input << std::endl;

		current_player->x += 5;
		std::cout << "player " << current_player->get_address_string() << " data updated to: " << current_player->x << std::endl;

		// create state packet, copy into buffer
		write_index = 0;
		memcpy(&buffer[write_index], &(current_player->x), sizeof(&(current_player->x)));
		write_index++;

		// send back to client
		int buffer_length = sizeof(current_player->x);
		SOCKADDR* to = (SOCKADDR*)& from;
		int to_length = sizeof(from);
		if (sendto(sock, buffer, buffer_length, flags, to, to_length) == SOCKET_ERROR)
		{
			printf("sendto failed: %d", WSAGetLastError());
			return FAIL;
		}

		return PASS;
	}

	bool server::bind_socket()
	{
		if (bind(sock, (SOCKADDR*)& server_address, sizeof(server_address)) == SOCKET_ERROR)
		{
			printf("socket bind failed: %d", WSAGetLastError());
			return FAIL;
		}
		return PASS;
	}
}