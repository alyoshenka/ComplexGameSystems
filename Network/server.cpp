#include "server.h"

namespace GameNetwork
{
	bool server::check_if_new_player(address_struct queried_client)
	{
		bool found_player = false;
		for (int i = 0; i < current_player_count; i++)
		{
			if (connections[i]->get_address() == queried_client) { found_player = true; }
		}
		return found_player;
	}

	bool server::check_address_equality(SOCKADDR_IN addr_1, SOCKADDR_IN addr_2)
	{
		return addr_1.sin_addr.S_un.S_un_b.s_b1 == addr_2.sin_addr.S_un.S_un_b.s_b1
			&& addr_1.sin_addr.S_un.S_un_b.s_b2 == addr_2.sin_addr.S_un.S_un_b.s_b2
			&& addr_1.sin_addr.S_un.S_un_b.s_b3 == addr_2.sin_addr.S_un.S_un_b.s_b3
			&& addr_1.sin_addr.S_un.S_un_b.s_b4 == addr_2.sin_addr.S_un.S_un_b.s_b4;
	}

	client* server::add_new_player(address_struct new_address)
	{
		if (current_player_count >= MAX_PLAYER_COUNT)
		{
			printf("cannot add new player: server full\n");
			return nullptr;
		}

		client* new_player = new client();
		new_player->set_address(new_address);

		connections[current_player_count] = new_player; 
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
		SOCKADDR f;
		int bytes_recieved = recvfrom(sock, buffer, IDENTIFY_BUFFER_SIZE, flags, (SOCKADDR*)& from, &from_size);
		if (bytes_recieved == SOCKET_ERROR)
		{
			printf("recvfrom returned SOCKET_ERROR, WSAGetLastError() %d\n", WSAGetLastError());
			return FAIL;
		}

		char* from_char = inet_ntoa(((sockaddr_in)from).sin_addr);
		address_struct from_address = char_to_address(from_char);

		client* current_player = nullptr;
		current_player = find_player(from_address);
		if (nullptr == current_player) { current_player = add_new_player(from_address); }

		char client_input = buffer[0];
		std::cout << "player " << current_player->get_address_string() << " sent data: " << client_input << std::endl;

		current_player->data.value++;
		std::cout << "player " << current_player->get_address_string() << " data updated to: " << current_player->data.value << std::endl;

		// create state packet, copy into buffer
		write_index = 0;
		memcpy(&buffer[write_index], &current_player->data.value, sizeof(&current_player->data.value));
		write_index++;

		// send back to client
		int buffer_length = sizeof(current_player->data.value);
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

	client* server::find_player(address_struct player_address)
	{
		for (int i = 0; i < current_player_count; i++)
		{
			if (connections[i]->get_address() == player_address) { return connections[i]; }
		}
		return nullptr;
	}
}