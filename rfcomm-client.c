#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <errno.h>

int main(int argc, char **argv)
{
	if (argc < 2) {
		puts("Please provide an endpoint address.");
		return 1;
	}

	if (strlen(argv[1]) != 17) {
		puts("Please provide a valid endpoint address.");
		return 1;
	}

	struct sockaddr_rc addr = {0};
	int s, status;
	const char *dest = argv[1];

	//ALlocate a new socket. */
	s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

	addr.rc_family = AF_BLUETOOTH;
	/* Destination port 1. */
	addr.rc_channel = (uint8_t) 1;
	/* Convert our textual MAC address t a bdaddr_t struct. */
	str2ba(dest, &addr.rc_bdaddr);

	/* Connect to the remote endpoint. */
	status = connect(s, (struct sockaddr *)&addr, sizeof(addr));

	if (status == 0)
		/* Send data to the endpoint. */
		status = write(s, "ahoy", 5);
	else
		printf("Connection failed %s.\n", strerror(errno)), status = 0;;

	if (status < 0)
		puts("Write failed.");

	close(s);
	return 0;
}
