#include "parse.h"

#include <stdlib.h>
#include <stdio.h>

#include "lex.h"

struct program parse(struct token* token_list) {
    struct program out;
    out.length = 0;
    out.expressions = malloc(0);
    while (token_list->type != T_END) {
        // first, we see if we're looking at a paren or a literal
        // if we're looking at a starting string just skip it
        if (token_list->type == T_BEGIN) {
            token_list = token_list->next;
            continue;
        }
        // if we're looking at a open paren
        else if (token_list->type == T_OPEN_PAREN) {
            // we're gonna do some wonky stuff.
            // first, we're going to iterate through the list and find the matching close paren
            // once that's found, we're going to temporarily replace it with a `T_END`
            // then, we're going to call `parse` on that little section of list and use the results
            // finally, we're going to restore the T_CLOSE_PAREN instead of the T_END we placed there
            int paren_depth = 1;
            struct token* depth_peek = token_list;
            while (paren_depth) {
                depth_peek = depth_peek->next;
                switch (depth_peek->type) {
                    case T_OPEN_PAREN: paren_depth++; break;
                    case T_CLOSE_PAREN: paren_depth--; break;
                    case T_END: puts ("Unbalanced parens (extra open paren)"); exit(-1); break;
                    default: break;
                }
            }
            // now depth_peek has a pointer to the balancing paren
            depth_peek->type = T_END;
            struct program nested = parse(token_list->next);
            depth_peek->type = T_CLOSE_PAREN;
            // once we have a struture that's a parsed tree of the inside of those parens,
            // we append it to our current tree
            out.length += 1;
            out.expressions = realloc(out.expressions, out.length * sizeof(struct expression));
            out.expressions[out.length - 1].type = E_EXPRESSION;
            out.expressions[out.length - 1].expression = nested.expressions;
            //then update token_list to point past that last close paren
            token_list = depth_peek->next;
        }
        // our parser should seamlessly skip over all close parens
        // if we hit one, there's a syntax error (someone included too many close parens)
        else if (token_list->type == T_CLOSE_PAREN) {
            puts("Unbalanced parens (extra close paren)");
            exit(-1);
        }
        // if we're looking at anything else, itll be parsed as a normal token and appended to out.expressions
        else {
            out.length += 1;
            out.expressions = realloc(out.expressions, out.length * sizeof(struct expression));
            out.expressions[out.length - 1].type = E_TOKEN;
            out.expressions[out.length - 1].token = token_list;
            token_list = token_list->next;
        }
    }
    return out;
}
