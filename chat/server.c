#include "loader.h"

int main() {
	int server_fd, new_socket;
	int client_sockets[MAX_CLIENTS];
	struct sockaddr_in address;
	socklen_t addrlen = sizeof(address);
	char buffer[1024];
	fd_set readfds;
	
	for (int i = 0; i < MAX_CLIENTS; i++) {
		client_sockets[i]	= 0;
	}
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == 0) {
		perror("Socket f-ed up!");
		exit(1);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	bind(server_fd, (struct sockaddr *)&address; sizeof(address));

	listen(server_fd, 5);

	printf("Server started on port %d\n", PORT);
	
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        int max_sd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_sockets[i];
            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_sd) max_sd = sd;
        }

        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);
        if ((activity < 0)) {
            perror("select error");
            continue;
        }

        if (FD_ISSET(server_fd, &readfds)) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            printf("New connection, socket fd is %d, ip is %s, port %d\n",
                    new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            int added = 0;
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = new_socket;
                    added = 1;
                    break;
                }
            }
            if (!added) {
                printf("Max clients reached. Rejecting new client.\n");
                close(new_socket);
            }
        }`

			return 0;
}
