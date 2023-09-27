#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Define token types
typedef enum {
    TOKEN_INT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF
} TokenType;

// Define token structure
typedef struct {
    TokenType type;
    int value; // Only used if the type is TOKEN_INT
} Token;

// Define AST node types
typedef enum {
    AST_INT,
    AST_BINARY_OP
} AstNodeType;

// Define AST node structure
typedef struct AstNode {
    AstNodeType type;
    union {
        int int_value; // Only used if the type is AST_INT
        struct {
            TokenType op;
            struct AstNode* left;
            struct AstNode* right;
        } binary_op; // Only used if the type is AST_BINARY_OP
    } data;
} AstNode;

// Function to create an AST node for an integer
AstNode* create_ast_int(int value) {
    AstNode* node = (AstNode*)malloc(sizeof(AstNode));
    node->type = AST_INT;
    node->data.int_value = value;
    return node;
}

// Function to create an AST node for a binary operation
AstNode* create_ast_binary_op(TokenType op, AstNode* left, AstNode* right) {
    AstNode* node = (AstNode*)malloc(sizeof(AstNode));
    node->type = AST_BINARY_OP;
    node->data.binary_op.op = op;
    node->data.binary_op.left = left;
    node->data.binary_op.right = right;
    return node;
}

// Function to free an AST
void free_ast(AstNode* root) {
    if (root == NULL) return;
    if (root->type == AST_BINARY_OP) {
        free_ast(root->data.binary_op.left);
        free_ast(root->data.binary_op.right);
    }
    free(root);
}

// Recursive descent parser functions
AstNode* parse_expression(FILE* input);
AstNode* parse_term(FILE* input);
AstNode* parse_factor(FILE* input);

// Function to report syntax errors
void syntax_error() {
    fprintf(stderr, "Syntax error\n");
    exit(1);
}

// Function to match a token and consume it
void match(TokenType expected, Token* current_token, FILE* input) {
    if (current_token->type == expected) {
        if (current_token->type != TOKEN_EOF) {
            *current_token = get_token(input);
        }
    } else {
        syntax_error();
    }
}

// Function to get the next token from input
Token get_token(FILE* input) {
    Token token;
    int c = fgetc(input);

    while (isspace(c)) {
        c = fgetc(input);
    }

    if (c == EOF) {
        token.type = TOKEN_EOF;
    } else if (isdigit(c)) {
        ungetc(c, input);
        fscanf(input, "%d", &token.value);
        token.type = TOKEN_INT;
    } else {
        switch (c) {
            case '+':
                token.type = TOKEN_PLUS;
                break;
            case '-':
                token.type = TOKEN_MINUS;
                break;
            case '*':
                token.type = TOKEN_MULTIPLY;
                break;
            case '/':
                token.type = TOKEN_DIVIDE;
                break;
            case '(':
                token.type = TOKEN_LPAREN;
                break;
            case ')':
                token.type = TOKEN_RPAREN;
                break;
            default:
                syntax_error();
        }
    }
    return token;
}

// Recursive descent parser for expressions
AstNode* parse_expression(FILE* input) {
    AstNode* left = parse_term(input);
    Token current_token = get_token(input);

    while (current_token.type == TOKEN_PLUS || current_token.type == TOKEN_MINUS) {
        TokenType op = current_token.type;
        current_token = get_token(input);
        AstNode* right = parse_term(input);
        left = create_ast_binary_op(op, left, right);
    }

    return left;
}

// Recursive descent parser for terms
AstNode* parse_term(FILE* input) {
    AstNode* left = parse_factor(input);
    Token current_token = get_token(input);

    while (current_token.type == TOKEN_MULTIPLY || current_token.type == TOKEN_DIVIDE) {
        TokenType op = current_token.type;
        current_token = get_token(input);
        AstNode* right = parse_factor(input);
        left = create_ast_binary_op(op, left, right);
    }

    return left;
}

// Recursive descent parser for factors
AstNode* parse_factor(FILE* input) {
    Token current_token = get_token(input);

    if (current_token.type == TOKEN_INT) {
        return create_ast_int(current_token.value);
    } else if (current_token.type == TOKEN_LPAREN) {
        AstNode* expr = parse_expression(input);
        match(TOKEN_RPAREN, &current_token, input);
        return expr;
    } else {
        syntax_error();
        return NULL; // To satisfy the compiler; this line will never be reached
    }
}

// Main program
int main() {
    printf("Enter an arithmetic expression: ");
    char input_expr[100];
    fgets(input_expr, sizeof(input_expr), stdin);

    FILE* input = fmemopen(input_expr, sizeof(input_expr), "r");
    Token current_token = get_token(input);
    AstNode* ast = parse_expression(input);

    printf("AST built successfully.\n");

    // Free the AST when done
    free_ast(ast);

    return 0;
}
