#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int priority(char operator);

typedef struct stack {
    char token;
    int prior;
    struct stack *next;
} Stack;

typedef struct eval_stack {
    double number;
    struct eval_stack *next;
} Eval_Stack;

void push(char op);
void pop();
void push_num(double data);
double pop_num();
int isempty();

Stack *head = NULL;
Eval_Stack *evalhead = NULL;
FILE *fp1 = NULL, *fp2 = NULL;

int main() {
    char input[100], output[100];
    memset(input, '\0', sizeof(input));
    if (!(fp1 = fopen("infix.txt", "r"))) {
        fprintf(stderr, "reading infix.txt failed");
        exit(-1);
    }
    if (!(fp2 = fopen("postfix.txt", "w"))) {
        fprintf(stderr, "writing postfix.txt failed");
        exit(-1);
    }
    int i = 0, j = 0;
    while (fgets(input, 100, fp1) != NULL) {
        memset(output, '\0', sizeof(output));
        head = NULL;
        j = 0;
        int length = strlen(input) - 1;
        for (i = 0; i < length; i++) {
            if (isdigit(input[i])) {
                if (isdigit(input[i + 1])) {
                    fprintf(fp2, "%c", input[i]);
                    output[j++] = input[i];
            } else {
                fprintf(fp2, "%c ", input[i]);
                output[j++] = input[i]; output[j++] = ' ';
            }
            } else {
                if (isempty()) {
                    push(input[i]);
                } else {
                    if (input[i] != '(' && input[i] != ')') {
                        if (priority(input[i]) > head->prior) {
                            push(input[i]);
                        } else {
                            output[j++] = head->token;
                            output[j++] = ' ';
                            pop();
                            push(input[i]);
                        }
                    } else {
                        if (input[i] == '(') {
                            push(input[i]);
                        } else {
                            while (head->token != '(') {
                                output[j++] = head->token; output[j++] = ' ';
                                pop();
                            }
                            Stack *tmp = head;
                            head = head->next;
                            free(tmp);
                            tmp = NULL;
                        }
                    }
                }
            }
        }
        while (!isempty(head)) {
            output[j++] = head->token; output[j++] = ' ';
            pop();
        }                            
        // print the postfix format
        output[strlen(output)] = '\0';
        //evaluate the result
        double data = -1, operand1, operand2, result;
        evalhead = NULL;
        for (i = 0; i < strlen(output); i++) {
            while (isdigit(output[i])) {
                data = (data == -1)? 0: data;
                data = data * 10 + output[i] - '0';
                i++;
            }
            if (data != -1)
                push_num(data);
            if (output[i] == '+' || output[i] == '-'
                || output[i] == '*' || output[i] == '/') {
                operand2 = pop_num();
                operand1 = pop_num();
                switch (output[i]) {
                    case '+': {
                        result = operand1 + operand2;
                        push_num(result);
                        break;
                    } 
                    case '-': {
                        result = operand1 - operand2;
                        push_num(result);
                        break;
                    } 
                    case '*': {
                        result = operand1 * operand2;
                        push_num(result);
                        break;
                    } 
                    case '/': {
                        result = operand1 / operand2;
                        push_num(result);
                        break;
                    }
                }
            }
            data = -1;
        }
        if (evalhead != NULL)
            fprintf(fp2, "%lf\n", evalhead->number);
    }
    fclose(fp1); fclose(fp2);
    fp1 = fp2 = NULL;
    return 0;
}

int priority(char op) {
    int ret = 0;
    switch(op) {
        case '+': case '-': ret = 1; break;
        case '*': case '/': ret = 2; break;
        default : ret = 0;
    }
    return ret;
}



void push(char op) {
    Stack *insert = malloc(sizeof(Stack));
    if (insert != NULL) {
        insert->token = op;
        insert->prior = priority(op);
        insert->next = head;
        head = insert;
    }
}

void pop() {
    if (head != NULL) {
        Stack *temp = head;
        fprintf(fp2, "%c ", head->token);
        head = head->next;
        free(temp);
    }
}

int isempty() {
    return head == NULL;
}

void push_num(double data) {
    Eval_Stack *in = (Eval_Stack *)malloc(sizeof(Eval_Stack));
    if (in != NULL) {
        in->number = data;
        in->next = evalhead;
        evalhead = in;
    }
}

double pop_num() {
    double data = 0.0;
    Eval_Stack *tmp = NULL;
    data = evalhead->number;
    tmp = evalhead;
    evalhead = evalhead->next;
    free(tmp);
    return data;
}
