#include <stdlib.h>
#include "list.h"
#include "serialize.h"
#include "serial_list.h"
#include <stdio.h>
#include <memory.h>
#include "sentinel.h"

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
  /* In the beginning of every Serialization routine, always encode     *
   * 0XFFFFFFFF in the serialized buffer if the object being serialized *
   * is NULL                                                            *
   * This is Sentinel insertion code                                    */
   SENTINEL_INSERTION_CODE(obj, b);
   serialize_data(b, (char *)&obj->data, sizeof(unsigned int));
   /* call recursively for the next node */
   serialize_list_node_t(obj->next, b);
}

list_t *de_serialize_list_t(ser_buff_t *b)
{
  /* In the beginning of ever derialization routine, always write *
   * sentinel detection code                                     */
   SENTINEL_DETECTION_CODE(b);
   
   list_t *lst = (list_t *)malloc(sizeof(list_t));
   lst->head = de_serialize_list_node_t(b);
   
   return lst;
}

list_node_t* de_serialize_list_node_t(ser_buff_t* b)
{
  unsigned int sentinel = 0;
  
  SENTINEL_DETECTION_CODE(b);
  
  list_node_t *obj = (list_node_t *)malloc(sizeof(list_node_t));
  
  de_serialize_data((char *)&obj->data, b, sizeof(int));
  de_serialize_data((char *)&sentinel, b, sizeof(int));
  
  if (sentinel == 0XFFFFFFFF)
    obj->next = NULL;
  else {
    serialize_buffer_skip(b, -1 * sizeof(unsigned int));
    obj->next = de_serialize_list_node_t(b);    
  }
  
  return obj;
}
