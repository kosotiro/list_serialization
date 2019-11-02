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

void init_list(list_t *lst);
int add_list_node(list_t *lst, int data);
void clear_list(list_t *lst);
void print_list_t(list_t *obj);
void print_list_node_t(list_node_t *obj);
int sum_list(list_t *obj);

#endif
