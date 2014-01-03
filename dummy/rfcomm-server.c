#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

int main()
{
	struct sockaddr_rc loc_addr = {0}, rem_addr = {0};
	char buf[1024] = {0};
	int s, client, bytes_read;
	socklen_t opt = sizeof(rem_addr);

	/* Allocate a socket. */
	s = socket(AF_BLUETOOTH, /* Addressing family. */
		SOCK_STREAM, 	/* Socket type (unrelated to Bluetooth). */
		BTPROTO_RFCOMM);/* RFCOMM protocol. */

	/* Addressing family for the socket is Bluetooth. */
	loc_addr.rc_family = AF_BLUETOOTH;
	/* Use any local Bluetooth adaptor. */
	loc_addr.rc_bdaddr = *BDADDR_ANY;
	/* Use port 1. */
	loc_addr.rc_channel = (uint8_t) 1;

	/* Bind the socket to the local socket address. */
	bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

	/* Put the socket into listening mode. */
	listen(s, 1);

	/* Wait for someone to connect to us and assign the new connection file
	 * descriptor to the client variable. */
	client = accept(s, (struct sockaddr *)&rem_addr, &opt);

	/* Print out the MAC address of the client who connected. */
	ba2str(&rem_addr.rc_bdaddr, buf);
	fprintf(stderr, "Accepted connection from %s\n", buf);

	/* Read data from the client socket. */
	memset(buf, 0, sizeof(buf));
	bytes_read = read(client, buf, sizeof(buf));

	/* Print out the received data. */
	if (bytes_read > 0)
		printf("Received [%s]\n", buf);

	/* Cleanup. */
	close(client);
	close(s);
	return 0;
}
