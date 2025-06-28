
#include "ft_prinf.h"



int main(void)
{
    ft_my_printf("Hello %d, %% %s!\n", 42, "Antoine");
    ft_my_printf("Unsigned: %u, Hex: %x, HEX: %X\n", 12345u, 0x1a3f, 0x1a3f);
    ft_my_printf("Percent sign: %%\n");
    ft_my_printf("Multiple ints: %d %i %d\n", -10, 20, 0);
    ft_my_printf("String with width: %10s!\n", "align");
    ft_my_printf("Float (if implemented): %f\n", 3.14159);  // if you implement float
    ft_my_printf("Unsupported specifier: %q\n");
    ft_my_printf("Edge case: %%abc%%\n");
    int x = 42;
    ft_my_printf("Char: %c, Pointer: %p\n", 'A', (void*)&x);
    ft_my_printf("Mix: %d %u %x %X %s %c %p %%\n", -1, 42u, 255u, 255u, "text", 'Z', (void*)&x);

    return 0;
}

