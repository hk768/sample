/*
 * The program remvoes leading spaces, trailing spaces and entirely
 * blank lines
 */

#include <stdio.h>
#define MAXSPACELEN 81

int main()
{
        char spaces[MAXSPACELEN];
        int spacelen = 0;
        int blank = 1;
        int leadingspace = 1;
        int c;

        while ((c = getchar()) != EOF) {
                if (c == ' ' || c == '\t') {
                        if (!leadingspace)
                                spaces[spacelen++] = c;
                }else if (c == '\n') {
                        if (!blank) {
                                putchar(c);
                                blank = 1;
                                leadingspace = 1;
                                spacelen = 0;
                        }
                }else {
                        if (spacelen) {
                                spaces[spacelen] = '\0';
                                printf(spaces);
                                spacelen = 0;
                        }
                        putchar(c);
                        blank = 0;
                        leadingspace = 0;
                }
        }
        return 0;
}
