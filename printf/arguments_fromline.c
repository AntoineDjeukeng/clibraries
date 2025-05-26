#include <stdio.h>
#include <unistd.h>
#include <string.h>

void print_substring(char *str, int start, int end) {
    while (start < end) {
        write(1, &str[start], 1);
        start++;
    }
}

void parse_format_string(char *str) {
    int i = 0, b = 0;
    while (str[i]) {
        if (str[i] == '%') {
            // Print text before %
            if (b != i) {
                write(1, "\n\n*", 3);
                print_substring(str, b, i);
                write(1, "*\n\n", 3);
            }

            if (str[i + 1] == '%') {
                // Handle %%
                write(1, "\n\n'", 3);
                write(1, "%%", 2);
                write(1, "'\n\n", 3);
                i += 2;
            } else {
                // Find end of format specifier
                int j = i + 1;
                while (str[j] && !strchr("diouxXfFeEgGaAcspn%", str[j])) {
                    j++;
                }
                if (str[j]) {
                    write(1, "\n\n'", 3);
                    print_substring(str, i, j + 1);
                    write(1, "'\n\n", 3);
                    i = j + 1;
                } else {
                    // Broken format specifier at end
                    write(1, "\n\n'", 3);
                    print_substring(str, i, j);
                    write(1, "'\n\n", 3);
                    i = j;
                }
            }
            b = i;
        } else {
            i++;
        }
    }

    if (b < i) {
        write(1, "\n\n*", 3);
        print_substring(str, b, i);
        write(1, "*\n\n", 3);
    }
}


int main() {



char *tests[] = {
    "Simple string with no percent.",
    "Hello %s, your score is %d out of %u.",
    "Literal percent: %%",
    "Multiple formats: %f %e %g %x %X",
    "Edge case with end: percent only at end %",
    "%% double percent first then %d later",
    "Random chars before format spec %abc%d and after",
    "Weird spacing %   d still captures format",
    "Broken format at end: %",
    "%d%d%d triple digits",
    "Mixed text and formats: One %s, two %f, three %% end.",
    ""
};

for (int t = 0; tests[t][0]; t++) {
    printf(">>> Test %d\n", t + 1);
    parse_format_string(tests[t]);
    printf("\n========================\n");
}
    return 0;
}
