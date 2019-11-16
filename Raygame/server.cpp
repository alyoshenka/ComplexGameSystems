#include "server.h"

bool server::check_if_new_player(SOCKADDR_IN queried_client)
{
	bool found_player = false;
	for (int i = 0; i < current_player_count; i++)
	{
		if (check_address_equality(players[i]->get_address(), queried_client)) { found_player = true; }
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

bool server::check_address_equality(client player, SOCKADDR_IN address)
{
	return check_address_equality(player.get_address(), address);
}

client* server::add_new_player(SOCKADDR_IN new_address)
{
	if (current_player_count >= MAX_PLAYER_COUNT) 
	{ 
		printf("cannot add new player: server full\n");
		return nullptr; 
	}

	client* new_player = new client();
	new_player->set_address(new_address);

	players[current_player_count] = new_player;
	current_player_count++;
	printf("added new player %s\n", new_player->get_address_string());

	return new_player;
}

server::server() : network_connection()
{
	current_player_count = 0;
}

bool server::initialize_connection()
{
	if(initialize_win_sock() == -1
		|| initialize_socket() == -1
		|| initialize_address() == -1
		|| bind_socket() == -1)
	{ 
		printf("server failed\n");
		return FAIL; 
	}
	printf("server started\n");
	return PASS;
}

bool server::run_connection()
{
	int bytes_recieved = recvfrom(sock, buffer, IDENTIFY_BUFFER_SIZE, flags, (SOCKADDR*)&from, &from_size);
	if (bytes_recieved == SOCKET_ERROR)
	{
		printf("recvfrom returned SOCKET_ERROR, WSAGetLastError() %d\n", WSAGetLastError());
		return FAIL;
	}

	if (check_if_new_player(from)) { add_new_player(from); }

	char client_input = buffer[0];
	printf("player %d.%d.%d.%d:%d sent data: %c\n",
		from.sin_addr.S_un.S_un_b.s_b1,
		from.sin_addr.S_un.S_un_b.s_b2,
		from.sin_addr.S_un.S_un_b.s_b3,
		from.sin_addr.S_un.S_un_b.s_b4,
		from.sin_port,
		client_input);

	client * current_player = nullptr;
	current_player = find_player(from);
	if (nullptr == current_player) { current_player = add_new_player(from); }

	current_player->data.value++;
	printf("player %s data updated to: %d", current_player->get_address_string(), current_player->data.value);

	// create state packet, copy into buffer
	write_index = 0;
	memcpy(&buffer[write_index], &current_player->data.value, sizeof(&current_player->data.value));
	write_index++;

	// send back to client
	int buffer_length = sizeof(current_player->data.value);
	SOCKADDR* to = (SOCKADDR*)&from;
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
	if (bind(sock, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR)
	{
		printf("socket bind failed: %d", WSAGetLastError());
		return FAIL;
	}
	return PASS;
}

client * server::find_player(SOCKADDR_IN player_address)
{
	for (int i = 0; i < current_player_count; i++)
	{
		if (check_address_equality(*players[i], player_address)) { return players[i]; }
	}
	return nullptr;
}
