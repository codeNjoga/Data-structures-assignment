#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SIZE 100
struct node{
    char data;
    struct node* next;
};

struct stack{
    struct node* top;
};

struct  stack* new_stack(){
    struct stack* the_stack = (struct Stack*)malloc((sizeof(struct stack)));

    the_stack ->top = NULL;
    return the_stack;
}

struct node* newnode(char letter){
    struct node* the_node = (struct node*) malloc(sizeof (struct node));

    the_node -> data = letter;
    the_node ->next = NULL;
    return the_node;
}

int is_empty(struct stack* the_stack){
    return the_stack -> top == NULL;
}

void push(struct stack* the_stack, char letter){
    struct node* the_node = newnode(letter);

    the_node -> next = the_stack -> top;
    the_stack -> top = the_node;
}

char peek(struct stack* the_stack){
    if(is_empty(the_stack)){
        printf("Stack is empty\n");
        return '\0';

    }return the_stack -> top -> data;
}

char pop(struct stack* the_stack) {

    if (is_empty(the_stack)) {
        printf("Stack is empty\n");

        return '\0';
    }
    char data = the_stack->top->data;
    struct Node *temp = the_stack->top;

    the_stack->top = the_stack->top->next;
    free(temp);

    return data;
}

int isoperator(char op){
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '%';

}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
    }
    return -1;
}
void infixToPostfix(char* infix, char* postfix) {
    struct stack* the_stack = new_stack(strlen(infix));
    int i, k;
    for (i = 0, k = -1; infix[i]; ++i) {
        if ((infix[i] >= '0' && infix[i] <= '9') || (infix[i] >= 'a' && infix[i] <= 'z') || (infix[i] >= 'A' && infix[i] <= 'Z'))
            postfix[++k] = infix[i];
        else if (infix[i] == '(')
            push(the_stack, infix[i]);
        else if (infix[i] == ')') {
            while (!is_empty(the_stack) && peek(the_stack) != '(') {
                postfix[++k] = pop(the_stack);
            }
            if (!is_empty(the_stack) && peek(the_stack) == '(') {
                pop(the_stack); // Discard the '('
            } else {
                printf("INVALID!!\n\n");
                return;
            }
        }
        else if (isoperator(infix[i])){
            while (!is_empty(the_stack) && precedence(infix[i]) <= precedence(peek(the_stack)))
                postfix[++k] = pop(the_stack);
            push(the_stack, infix[i]);
        }
    }
    while (!is_empty(the_stack))
        postfix[++k] = pop(the_stack);
    postfix[++k] = '\0';
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Enter the infix expression: ");
    fgets(infix, MAX_SIZE, stdin);
    infix[strlen(infix) - 1] = '\0'; // removing the newline character from fgets

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
