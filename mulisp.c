#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "lex.h"
#include "parse.h"

int main(int argc, char** argv) {
    char in[1024];
    fgets(in, 1024, stdin);
    struct token* tokens = lex(in);
    // iterate through the lexxed list
    while (1) {
        switch(tokens->type) {
            case T_BEGIN: puts("T_BEGIN"); break;
            case T_END: puts("T_END"); break;
            case T_OPEN_PAREN: puts("T_OPEN_PAREN"); break;
            case T_CLOSE_PAREN: puts("T_CLOSE_PAREN"); break;
            case T_QUOTE: puts("T_QUOTE:"); break;
            case T_CONS: puts("T_CONS"); break;
            case T_IDENTIFIER: puts("T_IDENTIFIER"); printf("    %s\n", tokens->content.str); break;
            case T_STRING: puts("T_STRING:"); printf("    \"%s\"\n", tokens->content.str); break;
            case T_FLOAT: puts("T_FLOAT:"); printf("    %Lf\n", tokens->content.floating); break;
            case T_INTEGER: puts("T_INTEGER:"); printf("    %lld\n", tokens->content.integer); break;
        }
        if (tokens->type == T_END) break;
        tokens = tokens->next;
    }
}
