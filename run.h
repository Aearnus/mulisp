struct variable {
    char* name;
    struct expression* definition; 
};
struct variable_table {
    long long length;
    struct variable* table;
};

struct scope {
    struct variable_table* variables;
    struct variable_table* functions;
    struct variable_table* macros;
};

void run(struct program ast);
