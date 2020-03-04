#include "hw3_p2.h"


uint16_t verifyIPV4Checksum(IPV4_header* header) {
    //if the summation >= 2^16,perform end-around carry (flip the bits)
    //if the result = 0, the packet has no error
    //if there are other values, an error occurred
    //First, as doc Hint suggests, typecast IPV4_header* to a primitive datatype that is size of 16-bit, or 2-byte.
    //
    //You are going to iterate through the whole header by 2-byte each iteration, and sum up all those 2-byte values.
    //
    //Then you need to perform end-around-carry to that summation as described in this WIki.
    //
    //Lastly, one's complement to that value would give you the final value to return (look up C bitwise operators for a hint).
//    uint32_t value);

    int j;
    int pow = 2;
    for(j = 2; j < 17; j ++)
        pow = pow*2;

    Storage *storage = (Storage*)(header);
    int len = header->header_length;
    len = len * 2;
    uint32_t value =0;
    int i = 0;
    for(; i < len;i++){
        value += storage->arr[i];
    }
    if(value>=pow) {
        while (value >= pow) {
            uint16_t low = value & 0xffff;
            uint16_t high = value >> 16;
            value = low+high;
        }
    }
    value = ~value;


    return value;

}
