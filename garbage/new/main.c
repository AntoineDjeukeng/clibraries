#include "ft.h"
const char flag_chars[7] = { '#', '0', '-', ' ', '+', '\'', 'I' };
const char *specifier_str[] = {
    "d", "i", "o", "u", "x", "X", "f", "F",
    "e", "E", "g", "G", "a", "A", "c", "s", "p", "n"
};

const char *length_str[] = {
    "", "h", "hh", "l", "ll", "L", "z", "j", "t"
};


int main() {
    // const char *fmt =  "%%%%%d %10d %*d %2$*3$d %.5f %.*f %.*3$f %4$*2$.*3$Lf %-+ #0d %lld";
    const char *fmt =  "%-+ #0d %0d %+#d % d %10d %-05d %*3$d %-+0#12d";

    List parts, formats;
    init_list(&parts);
    init_list(&formats);
    parse_printf_string(fmt, &parts, &formats);

    Node *cur = formats.head;
    printf("number of required positional arguement are %d\n",formats.count);
    printf("the positional are set to %d\n", formats.positional);
    while (cur) {
        analyze_format(cur);
        cur = cur->next;
    }

    // print_list(&formats, "Formats");
   
    return 0;
}
