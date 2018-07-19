#pragma once

enum token_type {
    T_BEGIN,
    T_END,
    T_OPEN_PAREN,
    T_CLOSE_PAREN,
    T_QUOTE,
    T_CONS,
    T_IDENTIFIER,
    T_STRING,
    T_INTEGER,
    T_FLOAT
};
union token_content {
    char* str;
    char* ident;
    long long integer;
    long double floating;
};
struct token {
    enum token_type type;
    union token_content content;
    struct token* next;
    struct token* prev;
};

struct token* lex(char* in);
