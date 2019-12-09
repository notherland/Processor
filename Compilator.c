#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


const char CMD = 1;
const char REG = 2;
const char NUM = 3;
const int MAXCOUNT = 100;

char* freading();
int FLength (FILE *fcode);

int main() {
    printf("%s", freading());
    return 0;
}

char* freading ()
{
    char *code = NULL;
    FILE *fcode;
    int flen = 0;
    if (fcode = fopen ("/home/ksenia/Desktop/proga/Processor/Compilator/code.txt", "rb") == NULL) {
        printf("There is error: file cannot be opened.");
        return NULL;
    }
    printf ("%d", fcode);
    flen = FLength (fcode);
    code = (char *) calloc(MAXCOUNT, sizeof(char));
    if (fread (code, sizeof(char), flen, fcode) == 0) {
        printf("There is error: the file is empty.");
        return 0;
    }
    fclose (fcode);
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
