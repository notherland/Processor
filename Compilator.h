#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const char ZERO = 100;
const char ax = 2;
const char bx = 3;
const char cx = 4;
const char dx = 5;
const char CMD = 10;
const char REG = 11;
const char NUM = 12;
const char PUSH = 20;
const char POP = 21;
const char ADD = 22;
const char SUB = 23;
const char MULT = 24;
const char DIV = 25;
const char IN = 26;
const char OUT = 27;
const char DUMP = 28;
const char END = 77;

struct lexem {
    char flagcmd;
    char numcmd;
    char flagnum;
    char num;
};

struct lexem *Compile();

char *Read_File();

int FLength(FILE *fcode);

int *Make_arr(char *code);

void Make_elem(char *ptr_str, int *arrcode, int nsymbols);

struct lexem *Make_lexem_arr(int *arr_code);

struct lexem *Compile() {
    int i = 0;
    char *code = Read_File();
    printf ("Your code:\n");                                  //making char arr
    printf("%s\n", code);

    int *arr_code = Make_arr(code);
    struct lexem *lexem_arr = Make_lexem_arr (arr_code);             //making lexem arr
    printf ("Your compilated code:\n");
    while (lexem_arr[i].flagcmd != END) {
        printf("%d %d %d %d \n", lexem_arr[i].flagcmd, lexem_arr[i].numcmd, lexem_arr[i].flagnum, lexem_arr[i].num);
        i += 1;
    }

    return lexem_arr;
}

char *Read_File() {
    char *code = NULL;
    int flen = 0;
    FILE *fcode = fopen("/home/ksenia/Desktop/Everything for Processor/Processor/code.txt", "r");
    if (fcode == NULL) {
        printf("There is error: file cannot be opened.");
        return NULL;
    }
    flen = FLength(fcode);

    code = (char *) calloc(flen, sizeof(char));
    if (fread(code, sizeof(char), flen, fcode) == 0) {
        printf("There is error: the file is empty.");
        return NULL;
    }
    fclose(fcode);
    return code;
}

int FLength(FILE *fcode) {
    assert (fcode);
    int length = 0;
    fseek(fcode, 0, SEEK_END);
    length = ftell(fcode);
    fseek(fcode, 0, SEEK_SET);
    return length;
}

int *Make_arr(char *code) {
    assert(code);
    int nsymbols = 2;
    int *arrcode = (int *) calloc(nsymbols, sizeof(int));
    char *ptr_str = strtok(code, " \n");
    while (ptr_str) {
        Make_elem(ptr_str, arrcode, nsymbols);
        ptr_str = (char *) strtok(NULL, " \n");
        nsymbols = nsymbols + 2;
        arrcode = (int *) realloc(arrcode, nsymbols * sizeof(int));
    }
    arrcode[nsymbols - 2] = arrcode[nsymbols - 1] = END;
    return arrcode;
}

void Make_elem(char *ptr_str, int *arrcode, int nsymbols) {
    if (!strcmp(ptr_str, "push")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = PUSH;
        return;
    }
    if (!strcmp(ptr_str, "pop")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = POP;
        return;
    }
    if (!strcmp(ptr_str, "add")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = ADD;

        return;
    }
    if (!strcmp(ptr_str, "sub")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = SUB;
        return;
    }
    if (!strcmp(ptr_str, "mult")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = MULT;
        return;
    }
    if (!strcmp(ptr_str, "div")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = DIV;
        return;
    }
    if (!strcmp(ptr_str, "in")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = IN;
        return;
    }
    if (!strcmp(ptr_str, "out")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = OUT;
        return;
    }
    if (!strcmp(ptr_str, "dump")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = DUMP;
        return;
    }

    if (!strcmp(ptr_str, "ax")) {
        arrcode[nsymbols - 2] = REG;
        arrcode[nsymbols - 1] = ax;
        return;
    }
    if (!strcmp(ptr_str, "bx")) {
        arrcode[nsymbols - 2] = REG;
        arrcode[nsymbols - 1] = bx;
        return;
    }
    if (!strcmp(ptr_str, "cx")) {
        arrcode[nsymbols - 2] = REG;
        arrcode[nsymbols - 1] = cx;
        return;
    }
    if (!strcmp(ptr_str, "dx")) {
        arrcode[nsymbols - 2] = REG;
        arrcode[nsymbols - 1] = dx;
        return;
    }

    int number = 0;
    if (atoi(ptr_str)) {
        number = atoi(ptr_str);
        arrcode[nsymbols - 2] = NUM;
        arrcode[nsymbols - 1] = number;
        return;
    }
    printf("There is syntax error:%ls code can not be compiled.", *(ptr_str));
    exit(0);

}

struct lexem *Make_lexem_arr(int *arr_code) {
    assert (arr_code);
    int nlexem = 0, i = 0;
    struct lexem *arr = (struct lexem*) calloc (nlexem, sizeof (struct lexem));
    while (arr_code[i] != END)
    {
        arr = (struct lexem*) realloc(arr, sizeof (struct lexem) * (nlexem + 1));
        arr[nlexem].flagcmd = CMD;
        i += 1;
        arr[nlexem].numcmd = arr_code[i];
        i += 1;
        if (arr[nlexem].numcmd == PUSH) {
            if (arr_code[i] == REG) {
                arr[nlexem].flagnum = REG;
                arr[nlexem].num = arr_code[i + 1];
                i += 2;
            } else {
                arr[nlexem].flagnum = NUM;
                arr[nlexem].num = arr_code[i + 1];
                i += 2;
            }
        }

        else {
            arr[nlexem].flagnum = arr[nlexem].num = ZERO;
            }
        nlexem += 1;
    }
    arr[nlexem] = {END, END, END, END};
    return arr;
}

