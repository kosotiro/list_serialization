// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include "list.h"
#include "serialize.h"
#include "serial_list.h"
  
#define PORT     8080 
#define MAXLINE 1024 
  
// Driver code 
int main() { 
  int sockfd; 
  char buffer[MAXLINE]; 
  char *hello = "Hello from server"; 
  int len, n, sum;
  list_t *lst;
  ser_buff_t *b;
  struct sockaddr_in servaddr, cliaddr; 
      
  // Creating socket file descriptor 
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
    perror("socket creation failed"); 
    exit(EXIT_FAILURE); 
  } 
      
  memset(&servaddr, 0, sizeof(servaddr)); 
  memset(&cliaddr, 0, sizeof(cliaddr)); 
      
  // Filling server information 
  servaddr.sin_family    = AF_INET; // IPv4 
  servaddr.sin_addr.s_addr = INADDR_ANY; 
  servaddr.sin_port = htons(PORT); 
      
  // Bind the socket with the server address 
  if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
    perror("bind failed"); 
    exit(EXIT_FAILURE); 
  } 
      
    
  n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
               MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
               &len); 

  init_serialized_buffer(&b);
  b->size = n;
  b->b = buffer;
  b->next = 0;
  lst = de_serialize_list_t(b);
  printf("printing deserialized object on receiving machine:\n");
  print_list_t(lst);
  sum = sum_list(lst);
  
  sendto(sockfd, &sum, sizeof(int), MSG_CONFIRM, 
         (const struct sockaddr *) &cliaddr, len); 
      
  return 0; 
}
