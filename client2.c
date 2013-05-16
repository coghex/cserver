#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h>

int main() {
  printf("Beginning...");
  int sockfd = 0;
  int port = 4242;
  char *SERVADDR = "n-t.colorado.edu";

  printf("Beginning...");

  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[1024];
  bzero(buffer, 1024);

  printf("Opening Connection");
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Success!");

  server = gethostbyname(SERVADDR);

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
  serv_addr.sin_port = htons(port);

  printf("Connecting to %s", inet_ntoa(serv_addr.sin_addr));
  connect(sockfd,(struct sockaddr *) &serv_addr ,sizeof(serv_addr));
  printf("Success!");

  write(sockfd,"HELP\n",5);
  bzero(buffer, 1024);
  read(sockfd,buffer,1024);
  printf("Received:\n    %s\n",buffer);
  close(sockfd);
  return 0;
}
