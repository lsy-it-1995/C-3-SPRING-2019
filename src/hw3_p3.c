#include "hw3_p3.h"

/*check condition
 *1)all packets have a valid checksum
 *2)all fragments required to rebuild the transmitted data are present in the list
 *each valid packet in the list. shifted offset, payload, payload_len field of the node in the list
 *
 *
 */
IPV4_validation validateIPV4List(List_t* packets) {
    IPV4_validation valid;
    valid.packet = NULL;
    valid.errcode = NOERR;
    node_t *head_packet = packets->head;

    int len = packets->length;
    int index = 0;
    for(index = 0; index<len; index++){

        IPV4_node *head_value = (IPV4_node*)head_packet->value;
        IPV4_header *head_header = (IPV4_header*)(((IPV4_node*)head_packet->value)->sop);

        head_value->payload_len = head_header->total_length - (head_header->header_length*4);
        head_value->payload = (char*)(head_value->sop) + (head_header->header_length*4);
        head_value->fragment_offset = head_header->fragment_offset;
        IPV4_header *temp = (IPV4_header*)(((IPV4_node*)head_packet->value)->sop);

        head_packet = head_packet->next;
    }
    head_packet = packets->head;
    index = 0;
    for(index = 0; index < len ; index++){

        IPV4_node *head_value = (IPV4_node*)head_packet->value;
        IPV4_header *head_header = (IPV4_header*)(head_value->sop);

        if(verifyIPV4Checksum(head_header)!=NOERR){
            valid.errcode = ERRSUM;
            valid.packet = head_value;
            return valid;
        }
        if(index == len - 1)
            break;
        IPV4_node *next_value = (IPV4_node*)head_packet->next->value;

        if(head_value->fragment_offset +head_value->payload_len != next_value->fragment_offset){
            valid.packet = head_value;
            valid.errcode = ERRHOLE;
            return valid;
        }
        head_packet = head_packet->next;
    }
    return valid;

}
