#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


const char CMD = 1;
const char REG = 2;
const char NUM = 3;
const char ZERO = 4;
const char PUSH = 10;
const char POP = 11;
const char ADD = 12;
const char SUB = 13;
const char END = 20;
const int MAXCOUNT = 100;

void Compile ();

char *freading();
int FLength(FILE *fcode);

//struct lexem *Analyse(char *code);
int *Make_arr(char *code);
void Make_elem(char *ptr_str, int *arrcode, int nsymbols);
void Write_File(int *arr_code);
//struct lexem Make_struct(int* arrcode, int *nelem);

struct lexem {
    char flag;
    int value;
};

int main() {
    Compile ();
}

void Compile ()
{
    char * code = freading ();
    int * arr_code = Make_arr (code);
    Write_File (arr_code);
}

char *freading() {
    char *code = NULL;
    int flen = 0;
    int nstr = 0;
    FILE *fcode = fopen("/home/ksenia/Desktop/proga/Processor/Compilator/code.txt", "r");
    if (fcode == NULL) {
        printf("There is error: file cannot be opened.");
        return NULL;
    }
    flen = FLength(fcode);
    //printf ("%d", flen);
    code = (char *) calloc(flen, sizeof(char));
    if (fread(code, sizeof(char), flen, fcode) == 0) {
        printf("There is error: the file is empty.");
        return 0;
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

/*struct lexem *Analyse (char *code) {
    assert(code);
    //printf ("%s", code);
    int i = 0, nelem = 0, nstruct = 0;
    struct lexem *struct_code = (struct lexem*) calloc (1, sizeof(struct lexem));
    int *arrcode = Make_arr(code);
    while (arrcode[nelem] != END)
    {
        struct_code [nstruct - 1] = Make_struct(arrcode, &nelem);
    }
    return struct_code;
}*/

int *Make_arr(char *code) {
    assert(code);
    int nsymbols = 2;
    int *arrcode = (int *) calloc(nsymbols, sizeof(int));
    char *ptr_str = strtok(code, " \n");
    while (ptr_str) {
        Make_elem(ptr_str, arrcode, nsymbols);
        nsymbols += 2;
        arrcode = (int *) realloc(arrcode, nsymbols);
    }
    arrcode[nsymbols - 1] = END;
}

void Make_elem(char *ptr_str, int *arrcode, int nsymbols) {
    if (strcmp(ptr_str, "push")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = PUSH;
        return;
    }
    if (strcmp(ptr_str, "pop")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = POP;
        return;
    }
    if (strcmp(ptr_str, "add")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = ADD;
        return;
    }
    if (strcmp(ptr_str, "sub")) {
        arrcode[nsymbols - 2] = CMD;
        arrcode[nsymbols - 1] = SUB;
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
    exit (0);

}

/*struct lexem Make_struct(int* arrcode, int *nelem) {
    assert (arrcode);
    assert (nelem);
    struct lexem elem;
    if (arrcode[*nelem] = CMD)
        elem.flag =
}*/

void Write_File(int *arr_code)
{
    FILE *write_file = fopen ("/home/ksenia/Desktop/proga/Processor/Compilator.cpp", "w");
    int nsymbol = 1;
    while (arr_code[nsymbol] != END)
    {
        fprintf (write_file,"%d", arr_code[nsymbol]);
        nsymbol += 2;
    }

}
