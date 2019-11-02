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
  ser_buff_t *b;
  list_t num_lst;
  int sockfd; 
  char buffer[MAXLINE];
  int n, len, sum;  
  char *hello = "Hello from client"; 
  struct sockaddr_in     servaddr; 

  init_list(&num_lst);
  add_list_node(&num_lst, 11);
  add_list_node(&num_lst, 100);
  add_list_node(&num_lst, 233);
  add_list_node(&num_lst, 416);

  printf("printing the object to be serialized on sending machine:\n");
  print_list_t(&num_lst);

  init_serialized_buffer(&b);
  serialize_list_t(&num_lst, b);
  
  // Creating socket file descriptor 
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
    perror("socket creation failed"); 
    exit(EXIT_FAILURE); 
  } 
  
  memset(&servaddr, 0, sizeof(servaddr)); 
      
  // Filling server information 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_port = htons(PORT); 
  servaddr.sin_addr.s_addr = INADDR_ANY; 
          
  sendto(sockfd, (const char *)b->b, get_serialize_buffer_data_size(b), 
         MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
         sizeof(servaddr)); 
   
          
  n = recvfrom(sockfd, &sum, sizeof(int),  
               MSG_WAITALL, (struct sockaddr *) &servaddr, 
               &len); 
  
  printf("Sum of list : %d\n", sum); 
  
  close(sockfd); 
  return 0; 
} 
