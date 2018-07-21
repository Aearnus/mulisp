#include "run.h"

// these 4 functions return a null pointer if they can't find the variable/function/macro
struct variable* findintable(struct variable_table* table, char* name) {
    for (long long i; i < table->length; i++) {
        if (!strcmp(table[i].name, name)) return &(table[i]);
    }
    return NULL;
}
struct variable* findvariable(struct scope scope, char* name) {
    return findintable(scope.variables, name);
}
struct variable* findfunction(struct scope scope, char* name) {
    return findintable(scope.functions, name);
}
struct variable* findmacro(struct scope scope, char* name) {
    return findintable(scope.macros, name);
}

void runexpression(struct expression expr, struct scope current_scope) {
    // first, we check if it's a cons cell
    if (expr.length == 3 && expr.expression[1].type == T_CONS) {
        // append the two lists
        return;
    }
    // cons cells are the only special syntax
    // if it's not a cons cell, let's just run through the code like normal
    // first of all, empty parens (that aren't quoted) are invalid
    if (expr.length < 1) puts("Tried to execute an empty list"); exit(-1); break;
    // if it's not empty, take the first element of the list as a 1) macro or 2) function
    char* run_name = expr.expression[0].name;
    struct variable* run_var;
    if (run_var = findmacro(current_scope, run_name)) {
        // TODO
    } 
    else if (run_var = findfunction(current_scope, run_name)) {
        // TODO
    }
    else {
        printf("Unrecognized function `%s'", run_name);
        exit(-1);
    }
    for (long long expr_index = 0; expr_index < expr.length; expr_index++) {
        // first, we check and see if the 
    }
}

void run(struct program ast) {
    // a program is a list of expressions
    // so, let's iterate through the expressions and run them
    // TODO: set up the default scope
    for (long long expression_index = 0; expression_index < ast.length; expression_index++) {
        struct expression expr = ast.expressions[expression_index];
        switch (expr.type) {
            case E_EXPRESSION: runExpression(expr); break;
            case E_TOKEN: puts("Naked token at top level"); exit(-1); break;
        }
    }
}
