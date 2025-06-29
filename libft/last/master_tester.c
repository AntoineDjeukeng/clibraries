
#include "ft_printf.h"

#include <stdio.h>
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"


int main(void)
{
    int x = 123;
    void *ptr = &x;
    
    printf("Pointer: %p\n", ptr);
    ft_my_printf("Pointer: %p\n", ptr);
    return 0;
}

// int main(void)
// {
//     int num = 42;
//     void *ptr = &num;
//     int x ;
//     x = 123;
//     printf( "\n=== Basic Tests ===\n" );
//     printf( "Char: "   "%c\n" , 'A');
//     printf( "String: "   "%s\n" , "Hello");
//     printf( "Pointer: "   "%p\n" , ptr);

//     my code 
//     Pointer: 0x1ffeffefd8
//     printf
//     Pointer: 0x7ffef0c0ab48
//     printf( "Signed: "   "%d %i\n" , -123, 456);
//     printf( "Unsigned: "   "%u\n" , 3000000000u);
//     printf( "Hex: "   "%x %X\n" , 255, 255);
//     printf( "Percent sign: "   "%%\n" );

//     printf( "\n=== Width and Precision ===\n" );
//     printf( "Width: "   "%10d\n" , 42);
//     printf( "Left align: "   "%-10d\n" , 42);
//     printf( "Zero pad: "   "%010d\n" , 42);
//     printf( "Precision: "   "%.5d\n" , 42);
//     printf( "Width + Prec: "   "%10.5d\n" , 42);

//     printf( "\n=== Flags ===\n" );
//     printf( "Plus: "   "%+d\n" , 42);
//     printf( "Space: "   "% d\n" , 42);
//     printf( "Hash x: "   "%#x\n" , 255);
//     printf( "Hash X: "   "%#X\n" , 255);
//     printf( "Zero + Hash: "   "%#010x\n" , 255);

//     printf( "\n=== Edge Cases ===\n" );
//     printf( "Unsupported: "   "%q %z\n" );
//     printf( "Null str: "   "%s\n" , (char *)NULL);
//     printf( "Edge: "   "%%abc%%\n" );
//     printf("Zero-pad + Width: %010d\n", 42);             // → 0000000042
//     printf("Left align + Width: %-10d!\n", 42);          // → 42        !
//     printf("Precision + Width: %10.5d\n", 42);           // →      00042
//     printf("Zero ignored with precision: %010.5d\n", 42);// →      00042
//     printf("Plus and zero: %+05d\n", 42);                // → +0042
//     printf("Space and precision: % .4d\n", 42);          // →  0042
//     printf("Char width: %5c!\n", 'A');                   // → "    A!"
//     printf("String precision: %.3s!\n", "Hello");        // → "Hel!"
//     printf("Left align string: %-10s!\n", "Hi");         // → "Hi        !"
//     printf("String width + precision: %8.3s!\n", "World");// → "     Wor!"
//     printf("NULL string: %s\n", NULL);                   // → "(null)"
//     printf("Unsigned width: %10u\n", 123);               // → "       123"
//     printf("Hex zero padded: %08x\n", 255);              // → "000000ff"
//     printf("HEX with #: %#X\n", 255);                    // → "0XFF"
//     printf("Hex with #: %#x\n", 255);                    // → "0xff"
//     printf("Pointer (non-null): %p\n", (void*)0x1234);   // → "0x1234"
//     printf("Pointer (null): %p\n", NULL);                // → "0x0"
//     printf("Percent: %%\n");                             // → "%"
//     printf("Weird percent chain: %%abc%%def%%\n");       // → "%abc%def%"
//     printf("Mix: %d %u %x %X %s %c %p %%\n", -1, 42u, 255u, 255u, "text", 'Z', (void*)&x);
//     printf("Unsupported: %q %n %y\n");                   // Should fallback or print as-is


//     printf("==== Flags & Width ====\n");
//     printf("1: %+05d\n", 42);
//     printf("2: %-10d!\n", 42);
//     printf("3: %10.5d\n", 42);

//     printf("\n==== Strings ====\n");
//     printf("1: %.3s!\n", "Hello");
//     printf("2: %-10s!\n", "Hi");
//     printf("3: %8.3s!\n", "World");

//     printf("\n==== Hex / Pointer ====\n");
//     printf("1: %#x\n", 255);
//     printf("2: %p\n", (void*)0x1234);
//     printf("3: %p\n", NULL);

//     printf("\n==== Edge / Invalid ====\n");
//     printf("1: %%abc%%\n");
//     printf("2: Unsupported: %q %z\n");

//     printf("\n==== Mix ====\n");
  
//     printf("Mix: %d %u %x %X %s %c %p %%\n", -1, 42u, 255u, 255u, "text", 'Z', (void*)&x);

// 	return 0;
// }



