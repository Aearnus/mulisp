#include <stdlib.h>
#include <stdio.h>

#define allocate_token() malloc(sizeof(struct token))
enum token_type {
    T_BEGIN,
    T_END,
    T_OPEN_PAREN,
    T_CLOSE_PAREN,
    T_QUOTE,
    T_CONS,
    T_IDENTIFIER
};
union token_content { 
    char* str;
    char* ident;
    long long num;
};
struct token {
    enum token_type type;
    union token_content content;
    struct token* next;
    struct token* prev;
};
struct token* lex(char* in) {
    // create the first token in the linked list
    struct token* first = allocate_token();
    first->type = T_BEGIN;
    // iterate through the string, linking together the list
    struct token* current;
    struct token* previous = first;
    while (*in != '\0') {
        printf("character %c\n", *in);
        // skip over all whitespace characters
        switch(*in) {
            case ' ':
            case '\t':
            case '\n':
                in++;
                continue;
                break;
        }
        current = allocate_token();
        current->prev = previous;
        previous->next = current;
        switch(*in) {
            // handle one character tokens
            case '(':  current->type = T_OPEN_PAREN;  break;
            case ')':  current->type = T_CLOSE_PAREN; break;
            case '\'': current->type = T_QUOTE;       break;
            case '.':  current->type = T_CONS;        break;
            default: /*todo: multicharacter tokens*/  break;
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
            case T_QUOTE: puts("T_QUOTE"); break;
            case T_CONS: puts("T_CONS"); break;
            case T_IDENTIFIER: puts("T_IDENTIFIER"); break;
        }
        if (tokens->type == T_END) break;
        tokens = tokens->next;
    }
}