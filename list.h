#ifndef __LIST__
#define __LIST__

typedef struct list_node_
{
  int data;
  struct list_node_ *next;
}list_node_t;

typedef struct list_
{
  list_node_t *head;
}list_t;

int add_list_node(list_t *lst, int data);
void clear_list(list_t *lst);