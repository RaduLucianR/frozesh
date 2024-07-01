/**
 * Frozesh commands parser.
*/

struct TreeNode {
    char * token;
    struct TreeNode ** children;
};

struct TreeNode * parser(char ** tokens);
void print_ast(struct TreeNode * node, int level);
void free_ast(struct TreeNode * node);
