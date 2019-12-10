include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


const char CMD = 1;
const char REG = 2;
const char NUM = 3;
const int MAXCOUNT = 100;

char* freading();
int FLength (FILE *fcode, int *nstr);

struct lexem
{
    char flag;
    int value;
};
int main() {
    printf("%s", freading);
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
    flen = FLength (fcode, &nstr);
    code = (char *) calloc(MAXCOUNT, sizeof(char));
    if (fread (code, sizeof(char), flen, fcode) == 0) {
        printf("There is error: the file is empty.");
        return 0;
    }
    fclose (fcode);
    return code;
}

char *Analyse(char *code, int nstr)
{
    assert(code);
    int i = 0;
    

}

struct lexem Makestruct ()
{

}

char *Strtok (char *code, int len, int *nstr)
{
    assert (code);
    int i = 0;
    for (i = 0; i < len; i++) {
        if ((code[i] == "\n") || (code[i] == " "))
        {
            code[i] = "\0";
            *nstr = *nstr + 1;
        }

    }
     return code;
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
