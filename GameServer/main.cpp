#include <iostream>

#include "network_connection.h"
#include "server.h"


int main()
{
	GameNetwork::server host;

	host.initialize_connection();

	while (true)
	{
		host.run_connection();
	}

	return 0;
}