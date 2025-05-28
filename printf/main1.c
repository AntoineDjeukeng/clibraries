#include <stdarg.h>
#include <stdio.h>

typedef enum {
    TYPE_SIGNED_CHAR,
    TYPE_SHORT,
    TYPE_INT,
    TYPE_LONG,
    TYPE_LONG_LONG,
    TYPE_INTMAX_T,
    TYPE_SSIZE_T,
    TYPE_PTRDIFF_T,
    TYPE_UNSIGNED_CHAR,
    TYPE_UNSIGNED_SHORT,
    TYPE_UNSIGNED_INT,
    TYPE_UNSIGNED_LONG,
    TYPE_UNSIGNED_LONG_LONG,
    TYPE_UINTMAX_T,
    TYPE_SIZE_T,
    TYPE_DOUBLE,
    TYPE_LONG_DOUBLE,
    TYPE_SIGNED_CHAR_PTR,
    TYPE_SHORT_PTR,
    TYPE_INT_PTR,
    TYPE_LONG_PTR,
    TYPE_LONG_LONG_PTR,
    TYPE_INTMAX_T_PTR,
    TYPE_SIZE_T_PTR,
    TYPE_PTRDIFF_T_PTR,
    TYPE_WINT_T,
    TYPE_WCHAR_T_PTR,
    TYPE_CHAR_PTR,
    TYPE_VOID_PTR,
    TYPE_UNKNOWN,
    TYPE_COUNT
} ExpectedTypeID;

// A dummy function to show how to get argument from va_list by type id
void print_arg_by_type(ExpectedTypeID type, va_list *args) {
    switch(type) {
        case TYPE_INT:
            printf("int: %d\n", va_arg(*args, int));
            break;
        case TYPE_LONG:
            printf("long: %ld\n", va_arg(*args, long));
            break;
        case TYPE_DOUBLE:
            printf("double: %f\n", va_arg(*args, double));
            break;
        case TYPE_CHAR_PTR:
            printf("string: %s\n", va_arg(*args, char*));
            break;
        case TYPE_VOID_PTR:
            printf("void *: %p\n", va_arg(*args, void*));
            break;
        // Add cases for other types...
        default:
            printf("Unknown or unhandled type\n");
            break;
    }
}

// Example variadic function
void my_printf_like_function(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Let's pretend we parsed format and expect the types like this:
    ExpectedTypeID expected_types[] = {
        TYPE_INT,
        TYPE_DOUBLE,
        TYPE_CHAR_PTR,
        TYPE_LONG
    };

    int num_args = sizeof(expected_types)/sizeof(expected_types[0]);
    for (int i = 0; i < num_args; ++i) {
        print_arg_by_type(expected_types[i], &args);
    }

    va_end(args);
}

int main() {
    my_printf_like_function("dummy", 42, 3.14, "hello world", 100000L);
    return 0;
}
