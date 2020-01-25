#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const char ZERO = 0;
const char ax = 1;
const char bx = 2;
const char cx = 3;
const char dx = 4;
const char CMD = 10;
const char REG = 11;
const char NUM = 12;
const char PUSH = 20;
const char POP = 21;
const char ADD = 22;
const char SUB = 23;
const char END = 77;
const int MAXCOUNT = 100;

struct lexem {
    char flagcmd;
    char numcmd;
    char flagnum;
    char num;
};


void Compile();

char *Read_File();

int FLength(FILE *fcode);

int *Make_arr(char *code);

void Make_elem(char *ptr_str, int *arrcode, int nsymbols);

struct lexem *Make_lexem_arr(int *arr_code);

void Write_File(struct lexem *arr);
//struct lexem Make_struct(int* arrcode, int *nelem);


int main() {
    Compile();
}

void Compile() {
    int i = 0;
    char *code = Read_File();
    printf("%s", code);
    int *arr_code = Make_arr(code);
    printf("%d", arr_code[2]);
    while (arr_code[i] != END) {
        printf("?%d| ", arr_code[i]);
        i += 1;
    }
//printf ("%d ", arr_code[1]);
    i = 0;
    struct lexem *lexem_arr = Make_lexem_arr (arr_code);
    while (lexem_arr[i].flagcmd != END) {
        printf("%d %d %d %d \n ", lexem_arr[i].flagcmd, lexem_arr[i].numcmd, lexem_arr[i].flagnum, lexem_arr[i].num);
        i += 1;
    }
    Write_File(lexem_arr);
//printf ("%d", *arr_code);
}

char *Read_File() {
    char *code = NULL;
    int flen = 0;
    FILE *fcode = fopen("/home/ksenia/Desktop/Everything for Processor/Compilator.cpp/code.txt", "r");
    if (fcode == NULL) {
        printf("There is error: file cannot be opened.");
        return NULL;
    }
    flen = FLength(fcode);
    //printf ("%d", flen);
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
    printf("%s", ptr_str);
    while (ptr_str) {
        Make_elem(ptr_str, arrcode, nsymbols);
        ptr_str = (char *) strtok(NULL, " \n");
        nsymbols = nsymbols + 2;
        arrcode = (int *) realloc(arrcode, nsymbols * sizeof(int));
    }
    arrcode[nsymbols - 2] = arrcode[nsymbols - 1] = END;
    printf("|%d %d|", nsymbols, arrcode[nsymbols - 1]);
    return arrcode;
}

void Make_elem(char *ptr_str, int *arrcode, int nsymbols) {
    if (!strcmp(ptr_str, "push")) {
        //printf ("push ");
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = PUSH;
        return;
    }
    if (!strcmp(ptr_str, "pop")) {
        //printf ("pop ");
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = POP;
        return;
    }
    if (!strcmp(ptr_str, "add")) {
        //printf ("add ");
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = ADD;

        return;
    }
    if (!strcmp(ptr_str, "sub")) {
        //printf ("sub ");
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = SUB;
        return;
    }
    int number = 0;
    if (atoi(ptr_str)) {
        number = atoi(ptr_str);
        //printf ("%d ", number);
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

void Write_File(struct lexem* arr)
        {
    assert (arr);
    FILE *write_file = fopen("/home/ksenia/Desktop/Everything for Processor/Compilator.cpp/make.txt", "w");
    assert (write_file);
    int nlexem = 0;
            while (arr[nlexem].flagcmd != END) {
                fprintf(write_file, "%d %d %d %d\n", arr[nlexem].flagcmd, arr[nlexem].numcmd, arr[nlexem].flagnum, arr[nlexem].num);
                nlexem += 1;
            }
    return;
}
