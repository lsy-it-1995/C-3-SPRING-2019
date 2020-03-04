#ifndef HW3P2_H
#define HW3P2_H

#include "packets.h"


typedef struct{
    uint16_t arr[30];
}Storage;

uint16_t verifyIPV4Checksum(IPV4_header* header);

#endif
