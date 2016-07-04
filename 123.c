/*
 * The program removes all comments from a C program.
 */

#include <stdio.h>

typedef unsigned char u8;
int main()
{
        enum {
                CODE,
                LCOMMENT,
                SCOMMENT,
                DQUOTE,
                SQUOTE
        } state;
        int c;
        int nextc;
        u8 bslash;
        u8 star;

        bslash = 0;
        star = 0;
        state = CODE;
        while ((c = getchar()) != EOF) {
                if (state == SCOMMENT) {
                        if (c == '\n') {
                                putchar(c);
                                state = CODE;
                        }
                } else if (state == LCOMMENT) {
                        if (c == '/' && star) {
                                state = CODE;
                                star = 0;
                        } else if (c == '*') {
                                star = 1;
                        } else {
                                star = 0;
                        }
                } else if (state == SQUOTE) {
                        putchar(c);
                        if (c == '\'' && !bslash) {
                                state = CODE;
                        } else if (c == '\\') {
                                bslash ^= 1U;
                        } else {
                                bslash = 0;
                        }
                } else if (state == DQUOTE) {
                        putchar(c);
                        if (c == '\"' && !bslash) {
                                state = CODE;
                        } else if (c == '\\') {
                                bslash ^= 1U;
                        } else {
                                bslash = 0;
                        }
                } else if (state == CODE) {
                        if (c == '/') {
                                nextc = getchar();
                                if (nextc == '*') {
                                        state = LCOMMENT;
                                        continue;
                                } else if (nextc == '/') {
                                        state = SCOMMENT;
                                        continue;
                                } else {
                                        putchar(c);
                                        if (nextc == EOF)
                                                break;
                                        c = nextc;
                                }
                        }
                        putchar(c);
                        if (c == '\"')
                                state = DQUOTE;
                        else if (c == '\'')
                                state = SQUOTE;
                }
        }
        return 0;
}
