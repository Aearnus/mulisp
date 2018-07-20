#pragma once

enum expression_type {
    E_EXPRESSION,
    E_TOKEN
};
struct expression {
    enum expression_type type;
    // only used for E_EXPRESSION
    long long length;
    struct expression* expression;
    // only used for E_TOKEN
    struct token* token;
};
struct program {
    // the amount of expressions in the program
    long long length;
    // an array of expressions
    struct expression* expressions;
};

struct program parse(struct token* lexed);
