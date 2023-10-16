#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
uint64_t int_mul(uint32_t A, uint32_t B) {
	uint64_t result=0;
    for (int i = 0; i < 32; i++) {
        if ((A >> i) & 1) {
            result += ((uint64_t)B << i);
        }
    }

    return result;
}

int main(){
	uint32_t A = 0x12345678; 
    uint32_t B = 0xffffdddd; 

    uint64_t result=0; 
	result = int_mul(A, B);
    printf("uint64: %"PRIX64"\n", result);
    return 0;
}
