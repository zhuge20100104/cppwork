#include <iostream> 
#include <stdio.h>

#ifndef AV_RB16
#   define AV_RB16(x)                           \
        ((((const uint8_t*)(x))[0] << 8) |          \
               ((const uint8_t*)(x))[1])
#endif

void print_bits(uint16_t *ele) {
    printf("%p \n", ele);
    printf("%8u \n",((const uint8_t*)ele)[0]);
    printf("%8u \n",((const uint8_t*)ele)[1]);
    

    printf("AV_RB16: %d \n", AV_RB16(ele));
}

int main() {
    uint16_t e = 255;
    print_bits(&e);
}
