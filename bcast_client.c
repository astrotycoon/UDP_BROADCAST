#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>	/* struct ifconf */

#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, const char *argv[])
{
	int sock;

	if (argc < 2) {
		(void)fprintf(stderr, "Usage: %s + <Server Port>\n", argv[0]);	
		exit(EXIT_FAILURE);
	}

	/* 1. create socket */
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		handle_error("socket error");	
	}

	/* 2. set socket to allow broadcast*/
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, 
					&(int){1}, (socklen_t)sizeof(int)) < 0) {
		perror("setsockopt");	
		goto err;
	}

	/* 3. get eth0's broadcast address */
	struct sockaddr_in serv_addr;	/* information about broadcast server */
	struct ifconf ifc;
	struct ifreq *ifr = ifc.ifc_req;
	__caddr_t buf[1024];

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = buf;	
	if (ioctl(sock, SIOCGIFCONF, &ifc) < 0) {
		perror("ioctl");	
		goto err;
	}


	exit(EXIT_SUCCESS);

err:
	if (sock != -1) {
		close(sock);	
	}
	exit(EXIT_FAILURE); 
} 
