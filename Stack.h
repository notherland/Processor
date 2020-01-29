#include <stdio.h>
#include <cmath>
#include <assert.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_WHITE     "\x1b[37m"
#define ANSI_COLOR_YELLOW    "\x1b[33m"
#define ANSI_COLOR_GREEN   "\x1b[32m"

const char FAIL = 0;
const char SUCCESS = 1;
const char ST_FULL = 101;
const char ST_EMPTY = 102;
const char NULL_PTRS = 103;
const char DATANULLPTR = 104;
const char SIZENULLPTR = 105;
const int MAXSIZE = 120;
const int MINSIZE = 0;
struct stack {
    char *data; //указательн на начало памяти стека
    int size; //количество элементов в стеке
    //size_t maxsize;
    int Errorcode;
};

char Pop(struct stack *st_ptrs);

void Push(struct stack *st_ptrs, char x);

bool StackOK(struct stack *st_ptrs);

void Dump(struct stack *st_ptrs);

void Mem_increase(struct stack *st_ptrs);

void Mem_reduce(struct stack *st_ptrs);

struct stack *Stack_Init();

void Stack_Destraction(struct stack *st_ptrs);

struct stack *Stack_Init() {
    struct stack *st_ptrs = (struct stack*) calloc (1, sizeof(struct stack));
    st_ptrs->size = 0;
    //st_ptrs->maxsize = MAXSIZE;
    st_ptrs->data = (char *) calloc(0, sizeof(char));
    st_ptrs->Errorcode = -1;
    if (!StackOK(st_ptrs)) {
        Dump(st_ptrs);
        return NULL;
    }
    return st_ptrs;
}

void Push(struct stack *st_ptrs, char x) {
    assert (st_ptrs);
    printf( "Putting element %d into stack\n", x);
    st_ptrs->size = st_ptrs->size + 1;
    if (!StackOK(st_ptrs)) {
        Dump(st_ptrs);
        return;
    }
    Mem_increase(st_ptrs);
    st_ptrs->data[st_ptrs->size - 1] = x;
    if (!StackOK(st_ptrs)) {
        Dump(st_ptrs);
        return;
    }
    printf("Elem %d has been put in Stack\n", x);
}

char Pop(struct stack *st_ptrs) {
    assert(st_ptrs);
    printf(ANSI_COLOR_YELLOW"Taking last element out of stack\n" ANSI_COLOR_WHITE);
    //printf ("|%d|", st_ptrs->size);
    st_ptrs->size = st_ptrs->size - 1;
    if (!StackOK(st_ptrs)) {
        Dump(st_ptrs);
        return -1;
    }
    Mem_reduce(st_ptrs);
    //printf("%d", st_ptrs->size);
    printf(ANSI_COLOR_GREEN "Element %d has been taken out of stack\n" ANSI_COLOR_WHITE, st_ptrs->data[st_ptrs->size + 1]);
    return st_ptrs->data[st_ptrs->size + 1];

}

bool StackOK(struct stack *st_ptrs) {
    assert(st_ptrs);
    if (st_ptrs->data == nullptr) {
        st_ptrs->Errorcode = DATANULLPTR;
    }
    if (st_ptrs->size < MINSIZE) {
        st_ptrs->size += 1;
        st_ptrs->Errorcode = ST_EMPTY;
    }
    if (st_ptrs->size > MAXSIZE) {
        st_ptrs->size = st_ptrs->size - 1;
        st_ptrs->Errorcode = ST_FULL;
    }
    switch (st_ptrs->Errorcode) {
        case ST_FULL: {
            printf(ANSI_COLOR_RED  "Error! Stack is overflow\n", ANSI_COLOR_WHITE);
            return FAIL;
        }
        case ST_EMPTY: {
            printf(ANSI_COLOR_RED  "Error! Stack is empty\n", ANSI_COLOR_WHITE);
            return FAIL;
        }
        case DATANULLPTR: {
            printf(ANSI_COLOR_RED  "Error! Null pointer to data\n", ANSI_COLOR_WHITE);
            return FAIL;
        }
        case SIZENULLPTR: {
            printf(ANSI_COLOR_RED  "Error! Null pointer to size\n", ANSI_COLOR_WHITE);
            return FAIL;
        }
    }
    return SUCCESS;
}

void Dump(struct stack *st_ptrs) {
    int i = 0;
    printf(ANSI_COLOR_WHITE"Stack size: %d\n", st_ptrs->size);
    printf("Elements in stack: ");
    for (i = 0; i < st_ptrs->size; i += 1)
        printf (ANSI_COLOR_RED"%d ", st_ptrs->data[i]);
    printf ("\n", ANSI_COLOR_WHITE);
    return;

}

void Mem_increase(struct stack *st_ptrs) {
    st_ptrs->data = (char *) realloc(st_ptrs->data, st_ptrs->size);
}

void Mem_reduce(struct stack *st_ptrs) {
    st_ptrs->data = (char *) realloc(st_ptrs->data, st_ptrs->size);
}

void Stack_Destraction(struct stack *st_ptrs) {
    free(st_ptrs->data);
    st_ptrs->size = 0;
    st_ptrs->Errorcode = 0;
    //  st_ptrs->maxsize = 0;
}