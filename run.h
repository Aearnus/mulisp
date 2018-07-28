struct variable {
    char* name;
    struct expression* value; 
};
struct variable_table {
    long long length;
    struct variable* table;
};

typedef (struct expression*)(*native_lisp_function)(struct scope, struct variable_table);
struct function {
    char* name;
    variable_table arguments;
    int is_c_function;
    // if is_c_function
    native_lisp_function function;
    // else
    struct expression* definition; 
};
struct function_table {
    long long length;
    struct function* table;
};

struct scope {
    struct variable_table* variables;
    struct function_table* functions;
    struct function_table* macros;
};

void run(struct program ast);
