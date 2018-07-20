#include "run.h"

void runExpression(struct expression expr) {
    // first, we check if it's a cons cell
    if (expr.length == 3 && expr.expression[1].type == T_CONS) {
        // append the two lists
        return;
    }
    for (long long expr_index = 0; expr_index < expr.length; expr_index++) {
    }
}

void run(struct program ast) {
    // a program is a list of expressions
    // so, let's iterate through the expressions and run them
    for (long long expression_index = 0; expression_index < ast.length; expression_index++) {
        struct expression expr = ast.expressions[expression_index];
        switch (expr.type) {
            case E_EXPRESSION: runExpression(expr); break;
            case E_TOKEN: puts("Naked token at top level"); exit(-1); break;
        }
    }
}
