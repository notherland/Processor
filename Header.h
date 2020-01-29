#include <stdio.h>
#include "Stack.h"
#include "Compilator.h"


void Processing ();
int FLength(FILE *fcode);
void Implementation (struct lexem *exe, struct stack *stack);

void Processing ()
{
    struct lexem *exe = Compile();
    struct stack *st;

    st = Stack_Init ();
    Implementation (exe, st);
    Stack_Destraction (st);
}

void Implementation (struct lexem *exe, struct stack *stack) {
    assert (exe);
    assert(stack);
    int nlexem = 0;
    int reg_arr[4] = {0};
    while (exe[nlexem].flagcmd != END)
    {
        switch (exe[nlexem].numcmd) {
            case PUSH : {
                if (exe[nlexem].flagnum == NUM)
                    Push (stack, exe[nlexem].num);
                if (exe[nlexem].flagnum == REG)
                    reg_arr[exe[nlexem].num] = stack->data[stack->size];
                break;
            }
            case POP:{
                if (exe[nlexem].flagnum == ZERO)
                {
                    int pop = Pop(stack);
                    if (pop != -1)
                    printf ("%d", pop);
                }
                if (exe[nlexem].flagnum == REG)
                    Push (stack, reg_arr[exe[nlexem].num]);
                break;
            }
            case ADD:{
                //printf ("add %d %d", stack->data[stack->size], stack->data[stack->size - 1]);
                stack->data[stack->size - 1] = stack->data[stack->size - 2] + stack->data[stack->size - 1];
                break;
            }
            case SUB:{
                stack->data[stack->size - 1] = stack->data[stack->size - 2] - stack->data[stack->size - 1];
                break;
            }
            case MULT:{
                stack->data[stack->size - 1] = stack->data[stack->size - 2] * stack->data[stack->size - 1];
                break;
            }
            case DIV:{
                stack->data[stack->size - 1] = stack->data[stack->size - 2] / stack->data[stack->size - 1];
                break;
            }
            case IN:{
                int in = NAN;
                printf (ANSI_COLOR_YELLOW "Enter the number:\n" ANSI_COLOR_WHITE);
                if (scanf ("%d", &in))
                {
                    Push(stack, in);
                    break;
                }
                printf ("Input error");
            }
            case OUT:{
                if (stack->size > 0)
                    printf (ANSI_COLOR_GREEN "Result:%d\n", stack->data[stack->size - 1], ANSI_COLOR_WHITE);
                else
                {
                    printf("There is nothing to output.\n");
                    Dump(stack);
                }
                break;
            }
            case DUMP:{
                Dump(stack);
                break;
            }

        }
        nlexem += 1;
    }
}