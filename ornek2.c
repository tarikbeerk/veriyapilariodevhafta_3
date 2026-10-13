#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

void push(StackNode** top, char ch) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = ch;
    newNode->next = *top;
    *top = newNode;
}

char pop(StackNode** top) {
    if (*top == NULL) {
        return '\0'; 
    }
    StackNode* temp = *top;
    char poppedChar = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedChar;
}

int isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '[' && close == ']') return 1;
    return 0;
}

int checkBalanced(const char* expr) {
    StackNode* top = NULL;

    for (int i = 0; i < strlen(expr); i++) {
        char ch = expr[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(&top, ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == NULL) {
                return 0;
            }
            char popped = pop(&top);
            if (!isMatchingPair(popped, ch)) {
                while (top != NULL) pop(&top);
                return 0;
            }
        }
    }

    int balanced = (top == NULL);
    
    while (top != NULL) {
        pop(&top);
    }

    return balanced;
}

int main() {
    char expr[100];

    printf("Ifade: ");
    scanf("%s", expr);

    if (checkBalanced(expr)) {
        printf("Sonuc: Parantezler dengede!\n");
    } else {
        printf("Sonuc: Parantezler dengede DEGIL!\n");
    }

    return 0;
}