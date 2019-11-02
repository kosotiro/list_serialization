#include <stdlib.h>
#include "list.h"
#include "serialize.h"
#include <stdio.h>
#include <memory.h>
#include "sentinel.h"

/*Serialization functions*/
void serialize_list_t(list_t *obj, ser_buff_t *b);
void serialize_list_node_t(list_node_t *obj, ser_buff_t *b);

/*DeSerialization function*/
company_t *de_serialize_list_t(ser_buff_t *b);
person_t *de_serialize_list_node_t(ser_buff_t *b);

/*print functions*/
void print_list_t(list_t *obj);
void print_list_node_t(list_node_t *obj);

void serialize_list_t(list_t *obj, ser_buff_t *b)
{
  /* In the beginning of every Serialization routine, always encode 
   * 0XFFFFFFFF in the serialized buffer if the object being serialized
   * is NULL
   *
   * This is Sentinel insertion code*/
   SENTINEL_INSERTION_CODE(obj, b);
   serialize_list_node_t(obj->head, b);
}

void serialize_list_node_t(list_node_t *obj, ser_buff_t *b)
{
  /* In the beginning of every Serialization routine, always encode 
   * 0XFFFFFFFF in the serialized buffer if the object being serialized
   * is NULL
   *
   * This is Sentinel insertion code*/
   SENTINEL_INSERTION_CODE(obj, b);
   serialize_data(b, (char *)&obj->data, sizeof(unsigned int));
   /* call recursively for the next node */
   serialize_list_node_t(obj->next, b);
  
}