#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void init_list(list_t *lst)
{
  lst->head = NULL;
}

int add_list_node(list_t *lst, int data)
{
  list_node_t *new_node = (list_node_t *)malloc(sizeof(list_node_t));
  
  if (!new_node)
    return -1;
  
  new_node->data = data;
  
  if (lst->head == NULL) {
    new_node->next = NULL;
    lst->head = new_node;
  }
  else {
    new_node->next = lst->head;
    lst->head = new_node;
  }
  
  return 0;
}

void clear_list(list_t *lst)
{
  list_node_t *current;
  
  if (lst == NULL)
    return;
  
  if (lst->head == NULL)
    return;
  
  current = lst->head;
  
  while (current)
    {
      list_node_t *temp;
      temp = current;
      current = current->next;
      free(temp);
      temp = NULL;
    }
}

void print_list_t(list_t *obj)
{
  print_list_node_t(obj->head); 
}

void print_list_node_t(list_node_t *obj)
{
  if (obj != NULL)
    printf("Value:%d\n", obj->data);
  else
    return;
  
  print_list_node_t(obj->next);
}

int sum_list(list_t *obj)
{
  list_node_t *current;
  int sum = 0;
  
  if (obj == NULL)
    return 0;
  
  current = obj->head;
  
  while(current) {
    sum+=current->data;
    current = current->next;
  }
  
  return sum;
}
