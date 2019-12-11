#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


const char CMD = 1;
const char REG = 2;
const char NUM = 3;
const char PUSH = 10;
const char POP = 11;
const char ADD = 12;
const char SUB = 13;
const int MAXCOUNT = 100;

char* freading();
int FLength (FILE *fcode);
int *Analyse(char *code);
int Strtok (char *ptr_str, int *ncode, int *narr);

struct lexem
{
    char flag;
    int value;
};
int main() {
    int nsymbols;
    char *code;
    int *ncode;
    code = freading(nsymbols);
    printf("%s", code);
    printf ("%s", Analyse(code));

    return 0;
}

char* freading ()
{
    char *code = NULL;
    int flen = 0;
    int nstr = 0;
    FILE *fcode = fopen ("/home/ksenia/Desktop/proga/Processor/Compilator/code.txt", "rb");
    if (fcode == NULL) {
        printf("There is error: file cannot be opened.");
        return NULL;
    }
    flen = FLength (fcode);
    //printf ("%d", flen);
    code = (char *) calloc(flen, sizeof(char));
    if (fread (code, sizeof(char), flen, fcode) == 0) {
        printf("There is error: the file is empty.");
        return 0;
    }
    fclose (fcode);
    return code;
}

int *Analyse(char *code)
{
    assert(code);
    //printf ("%s", code);
    int i = 0, narr = 0, nsymbols = 4
            , quantity = 0;
    int *ncode;
    char *ptr_str;
    ncode = (int *) calloc (nsymbols, sizeof(int));
    ptr_str = strtok (code, " ");
    //printf ("%s", strtok(code, " "));
    while (ptr_str != NULL) {
        ncode = (int *) realloc (ncode, (nsymbols)*sizeof(int));
        quantity = Strtok(ptr_str, ncode, &narr);
        ptr_str = strtok(NULL, " ");
        //printf ("%s \n", ptr_str);
        nsymbols = nsymbols + quantity;
       // printf ("%d", ncode[0]);
    }
    return ncode;
}

int Strtok (char *ptr_str, int *ncode, int *narr)
{
    assert (ptr_str);
    assert (ncode);
    char push[] = "push", pop[] = "pop", add[] = "add", sub[] = "sub";
    printf ("%s \n", ptr_str);
    if (!strcmp(ptr_str, push))
    {
        printf ("1");
        ncode[*narr] = CMD;
        ncode[*narr + 1] = PUSH;
        *narr += 2;
        return 2;
    }
    if (!strcmp(ptr_str, pop))
    {
        ncode[*narr] = CMD;
        ncode[*narr + 1] = POP;
        *narr += 2;
        return 2;
    }
    if (!strcmp(ptr_str, add))
    {
        ncode[*narr] = CMD;
        ncode[*narr + 1] = ADD;
        *narr += 2;
        return 2;
    }
    if (!strcmp(ptr_str, sub))
    {
        ncode[*narr] = CMD;
        ncode[*narr + 1] = SUB;
        *narr += 2;
        return 2;
    }
    int number = 0;
    if (atoi(ptr_str))
    {
        number = atoi(ptr_str);
        ncode[*narr] = NUM;
        ncode[*narr + 1] = number;
        *narr += 2;
        return 2;
    }
    printf ("There is syntax error:%ls code can not be compiled.", *(ptr_str));
    //exit (0);

}

int FLength (FILE *fcode)
{
    assert (fcode);
    int length = 0;
    fseek(fcode, 0, SEEK_END);
    length = ftell(fcode);
    fseek(fcode, 0, SEEK_SET);
    return length;
}
