#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>

int main() {
  int sockfd = 0;
  int port = 5000;
  char *SERVADDR = "172.23.125.186";

  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[1024];
  bzero(buffer, 1024);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  server = gethostbyname(SERVADDR);

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
  serv_addr.sin_port = htons(port);

  connect(sockfd,(struct sockaddr *) &serv_addr ,sizeof(serv_addr));

  write(sockfd,"Hello There!, I\'m C\n",20);
  bzero(buffer, 1024);
  read(sockfd,buffer,1024);
  printf("Received:\n    %s",buffer);
  close(sockfd);
  return 0;
}
