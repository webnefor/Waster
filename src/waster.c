
#include "scan.h"


char * takestr(int number) {
    int i = 0;
    int isNegative = 0;
    char arr[255];
    char *str = malloc(255);

    if (number < 0) {
        isNegative = 1;
        number = -number;
    }

    do {
        str[i++] = (number % 10) + '0';
        number /= 10;
    } while (number != 0);

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for (int j = 0; j < i / 2; ++j) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }


    return str;
}



int main(int argc, char *argv[]) {

    __attribute__((unused)) tArgs get_data = parse_args(argc, argv);

    __attribute__((unused)) intervalRange intRangeSplit = c_split(&get_data);

    logo();

    kernelThread(&intRangeSplit);

    return 0;
}
