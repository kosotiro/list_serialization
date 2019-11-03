#ifndef __SERIAL_LIST__
#define __SERIAL_LIST__

/*Serialization functions*/
void serialize_list_t(list_t *obj, ser_buff_t *b);
void serialize_list_node_t(list_node_t *obj, ser_buff_t *b);

/*DeSerialization function*/
list_t *de_serialize_list_t(ser_buff_t *b);
list_node_t *de_serialize_list_node_t(ser_buff_t *b);

#endif
