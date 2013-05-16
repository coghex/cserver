#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <signal.h>


void sigchld_handler(int sig) 
{
  while(wait() != -1);
  printf("...Disconnected\n");
}

void sigint_handler(int sig)
{
  printf("\nHave a Great Day!\n");
  exit(0);
}

int main() {
  int sockfd = 0;
  int connfd = 0;
  int port = 8000;

  signal(SIGCHLD, sigchld_handler);
  signal(SIGINT, sigint_handler); 

  struct sockaddr_in servaddr, cliaddr;

  char buffer[1024];
  bzero(buffer, 1024);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero((char *) &servaddr, sizeof(servaddr));    // clears memory at
                                                  // this location in 
                                                  // the buffer
 
  bzero((char *) &cliaddr, sizeof(cliaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(port);                // need to convert to
                                                  // right bitordering
  servaddr.sin_addr.s_addr = inet_addr("0.0.0.0");          // local address

  bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  listen(sockfd, 1);

  while (1) {
    int n = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr *) &cliaddr, &n);
   
    int pid = fork();
    if (pid < 0) printf("forking error");
    if (pid == 0)
    {
      close(sockfd);
      printf("Connected... (%s)\n", inet_ntoa(cliaddr.sin_addr));

      bzero(buffer, 1024);
      read(connfd,buffer,255);

      printf("Received:\n    %s", buffer);
      write(connfd,"Well Hello to You Too\n",22);
      printf("Sent:\n    Well Hello to You Too\n");
      exit(0);
   }
   else
     close(connfd);
  }
  close(sockfd);
  return 0;
}
