#include <inttypes.h>

#include <stdint.h>

#include <stdio.h>

#include <stdlib.h>



typedef uint64_t ticks;

static inline ticks getticks(void)

{

    uint64_t result;

    uint32_t l, h, h2;

    asm volatile(

        "rdcycleh %0\n"

        "rdcycle %1\n"

        "rdcycleh %2\n"

        "sub %0, %0, %2\n"

        "seqz %0, %0\n"

        "sub %0, zero, %0\n"

        "and %1, %1, %0\n"

        : "=r"(h), "=r"(l), "=r"(h2));

    result = (((uint64_t) h) << 32) | ((uint64_t) l);

    return result;

}





int* decode(int* encoded, int encodedSize, int first){

    int* result = (int*)malloc(sizeof(int)*(encodedSize+1));

    result[0]=first;

    for(int i=0;i<encodedSize;i++){

        result[i+1]=result[i] ^ encoded[i];

    }

    return result;

}



int main()

{

    ticks t0 = getticks();

    int nums1[4] = {6,2,7,3};

    int* result1 = decode(nums1, 4, 4);

    printf("THe result is : ");

    for(int j=0; j<5; j++){

        printf("%d ", result1[j]);

    }

    ticks t1 = getticks();

    printf("elapsed cycle: %" PRIu64 "\n", t1 - t0);

    return 0;

}
