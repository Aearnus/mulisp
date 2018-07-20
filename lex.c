#include "lex.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define allocate_token() malloc(sizeof(struct token))

char* consume_until(char** in, const char* stop) {
    // consider the next bunch of characters an identifier
    // until it hits a special character contained in `in`
    // this uses a similar turing-machine esq method as string parsing does
    unsigned int i = 0;
    unsigned int max = 1;
    char* str = calloc(max, sizeof(char));
    while (!strchr(stop, **in)) {
        if (**in == '\0') {
            break;
        }
        // alloc more string if we went over
        if (i >= max) {
            max += 1;
            str = realloc(str, max);
        }
        str[i] = **in;
        (*in)++;
        i++;
    }
    return str;
}

int are_all_characters_one_of(char* these, char* in) {
    for (; *in != '\0'; in++) {
        if (!strchr(these, *in)) return 0;
    }
    return 1;
}

struct token* lex(char* in) {
    // create the first token in the linked list
    struct token* first = allocate_token();
    first->type = T_BEGIN;
    // iterate through the string, linking together the list
    struct token* current;
    struct token* previous = first;
    while (*in != '\0') {
        // skip over all whitespace characters
        if (strchr(" \t\n", *in)) {
            in++;
            continue;
        }
        current = allocate_token();
        current->prev = previous;
        previous->next = current;
        switch(*in) {
            // handle simple one character tokens
            case '(':  current->type = T_OPEN_PAREN;  break;
            case ')':  current->type = T_CLOSE_PAREN; break;
            case '\'': current->type = T_QUOTE;       break;
            case '.':  current->type = T_CONS;        break;
            // handle more complicated one character tokens
            case '"': current->type = T_STRING;
            // start out with a length 16 string
            // if we need more, we realloc
            unsigned int str_i = 0;
            unsigned int str_max = 2;
            current->content.str = calloc(str_max, sizeof(char));
            // skip the current '"'
            in++;
            // repeat this until we find another '"'
            while (*in != '"') {
                // alloc more string if we went over
                if (str_i >= str_max) {
                    str_max += 1;
                    current->content.str = realloc(current->content.str, str_max);
                }
                if (*in == '\0') {
                    puts("Unterminated string literal");
                    exit(-1);
                }
                current->content.str[str_i] = *in;
                in++;
                str_i++;
            }
            break;
            default:
            // this could either be a number or an identifier. let's check and find out
            current->content.str = consume_until(&in, " \t\n()");
            if (are_all_characters_one_of("-.0123456789", current->content.str)) {
                // see if the string is a float or an int
                // it's a float if it contains a dot
                if (strchr(current->content.str, '.')) {
                    current->type = T_FLOAT;
                    current->content.floating = strtold(current->content.str, NULL);
                } else {
                    current->type = T_INTEGER;
                    current->content.integer = atoll(current->content.str);
                }
            } else {
                current->type = T_IDENTIFIER;
            }
            break;
        }
        // prepare for the next iteration
        in++;
        previous = current;
    }
    // the loop breaks when the in string ends
    struct token* last = allocate_token();
    last->type = T_END;
    last->prev = previous;
    previous->next = last;
    return first;
}
