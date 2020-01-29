#include <stdio.h>
#include "Header.h"

int main() {
   printf (ANSI_COLOR_GREEN "Wellcome to Processor!\n" ANSI_COLOR_WHITE);
   Processing();
   printf (ANSI_COLOR_GREEN"Your programm completed succesfully." ANSI_COLOR_WHITE);
}