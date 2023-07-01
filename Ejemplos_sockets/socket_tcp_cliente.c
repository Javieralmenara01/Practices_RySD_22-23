#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#include "common.h"

int conectarTCP(char *host, int port) {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
  if (sockfd == -1) {
    perror("socket");
    return -1; // Return -1 on error
  }

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET; // IPv4
  serv_addr.sin_port = htons(port); // Convert port to network byte order
  serv_addr.sin_addr.s_addr = address; // Set address directly without conversion

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    perror("connect");
    close(sockfd);
    return -1; // Return -1 on error
  }

  return sockfd; // Return the socket descriptor
}





int main(int argc, char *argv[ ])

{
   
   int s = -1;
   int cuenta = -1;
   char *host;
   int puerto;
   int n;
   
   if (argc != 3) {
      printf("Número de argumentos incorrecto:\n");	
      printf("%s <host> <puerto>\n", argv[0]);
      exit(-1);
   }
   
   host = argv[1];
   puerto = atoi(argv[2]);
    // Conectamos con el servidor usando un socket UDP
   s = conectarTCP(host, puerto);

    while(1) 
    {
	if (recv(s, (char*)&cuenta , sizeof(int),0)!=sizeof(int)) {
	    errexit("Error de lectura\n");
	}
	int cuenta_reord = ntohl(cuenta);
	printf("\r%02d", cuenta_reord);
	fflush(stdout);
	
	if (cuenta_reord == 0) {
	     close(s);
	     break;
	}
      
    }

}