#include "list.h"

int add_list_node(list_t *lst, int data)
{
  list_node_t *new_node = (list_node_t *)malloc(sizeof(list_node_t));
  
  if (!new_node)
    return -1;
  
  new_node->data = data;
  
  if (lst->head == NULL)
    lst->head = new_node;
  else {
    new_node->next = lst->head;
    lst->head = new_node;
  }
  
  return 0;
}

void clear_list(list_t *lst)
{
  list_node_t *current;
  
  if (list == NULL)
    return;
  
  if (list->head == NULL)
    return;
  
  current = lst->head;
  
  while (current)
    {
      list_node_t *temp;
      temp = current;
      current = current->next;
      free(temp);
      temp = null;
    }
}