#include <stdint.h>
#include <stdio.h>

extern uint64_t get_cycles();
extern uint64_t get_instret();

uint16_t count_leading_zeros(uint64_t x)
{
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);

    /* count ones (population count) */
    x -= ((x >> 1) & 0x5555555555555555);
    x = ((x >> 2) & 0x3333333333333333) + (x & 0x3333333333333333);
    x = ((x >> 4) + x) & 0x0f0f0f0f0f0f0f0f;
    x += (x >> 8);
    x += (x >> 16);
    x += (x >> 32);

    return (64 - (x & 0x7f));
}

// log base power of 2
uint16_t logp2(int power, uint16_t clz)
{
    uint16_t result = 0;
    int tmp = 64 - clz;
    while (1) {
        tmp -= power;
        if (tmp <= 0)
            break;
        result++;
    }
    return result;
}

int main(void)
{  
    /* measure cycles */
    uint64_t instret = get_instret();
    uint64_t oldcount = get_cycles();
    
    uint64_t a = 64;
    uint16_t clz = count_leading_zeros(a);
    uint16_t ans = logp2(1, clz);
    
    uint64_t cyclecount = get_cycles() - oldcount;

    printf("cycle count: %u\n", (unsigned int) cyclecount);
    printf("instret: %x\n", (unsigned) (instret & 0xffffffff));
    
    printf("Input data is : %lld\n", a);
    printf("The log based 2 is : %d\n", ans);
    return 0;
}