#include <stdint.h>
#include <stdbool.h>


int main(void)
{
    volatile int a = 0;

    while (1) {
        a++;
    }

    return 0;
}
