
#include "config.h"
#include <netinet/in.h>

intervalRange c_split(tArgs *data) {

    intervalRange this_data = {0, 0};

    const char *input = data->ports;
    int count = 0;
    char inputCopy[100];
    strncpy(inputCopy, input, 100);

    char *began = strtok(data->range, "-");
    char *ended = strtok(NULL, "-");

    sscanf(
            began, "%d.%d.%d.%d",
            &this_data.begin[0],
            &this_data.begin[1],
            &this_data.begin[2],
            &this_data.begin[3]
            );

    sscanf(
            ended, "%d.%d.%d.%d",
            &this_data.end[0],
            &this_data.end[1],
            &this_data.end[2],
            &this_data.end[3]
           );

    char *token = strtok(inputCopy, ", ");


    while (token != NULL && count < MAX_NUMBERS)
    {
        this_data.ports[count] = atoi(token);
        count++;
        token = strtok(NULL, ", ");    // Get the next token
    }

    this_data.PortsCount = count;

    return this_data;
}

tArgs parse_args(int argc, char *argv[]) {
    tArgs temp_data;
    signed char _data[64];
    int rcode; // result code

    for (int i = 0; i < argc; i++)
    {

        if (argc < 2)
        {
            puts(
                    "waster: cannot find any params\n"
                    "\t-h\tto show help"
            );
            exit(-1);
        }

        if (strcmp(argv[i], HELP) == 0)
        {
            show_help();
            exit(0);
        }

        if (strcmp(argv[i], RANGE) == 0) {
            if ((rcode = !is_empty(argv[i+1])))
                temp_data.range = argv[i + 1];
        }

        if (strcmp(argv[i], PORTS) == 0) {
            if ((rcode = !is_empty(argv[i+1])))
            temp_data.ports = argv[i + 1];
        }

        if (strcmp(argv[i], SPEED) == 0) {
            if ((rcode = !is_empty(argv[i+1])));
                temp_data.speed = argv[i+1];
            // in developing
        }
    }

    if (temp_data.range == NULL || temp_data.speed == NULL || temp_data.ports == NULL) {
        puts("waster: missing required arguments");
        exit(-1);
    }

    return temp_data;
}

bool is_empty(char *str) {

    /*
     * Checks if a given string is empty or NULL.
     * @return Returns 1 (true) if the string is NULL or empty, otherwise returns 0 (false).
     */

    if (str == NULL || *str == '\0')
        return 0;

    char *reserved[] = {RANGE, SPEED, PORTS};

    for (int i = 0; i < (sizeof(reserved) / 8); i++) {
        if (strcmp(str, reserved[i]) == 0)
        {
            printf(RED "[-]" " " DEFAULT "Using a reserved value\n");
            return -1;
        }
    }
}

void logo() {
    printf( "\033[032m_____________________________________\n"       );
    printf( "\033[033m /    / //\\\\  |_--| =====  //\\ |\\\\ |\n"    );
    printf( "\033[033m/_/\\_/ //--\\\\|___|  ||\\\\ //--\\| \\\\|\n" );
    printf( "\033[032m-------------------------------------\n"       );
}

void show_help() {

    printf  (   "\n");
    printf  (   "Options:\n"                                                    );
    printf  (   "\t-r\tRange\n"                                                 );
    printf  (   "\t-s\tSpeed mode\n"                                            );
    printf  (   "\t-p\tports\n"                                                 );
    printf  (   "\n"                                                            );
    printf  (    "\n"                                                           );
    // see ya
}

char * intToStr(int number) {
    int i = 0;
    int isNegative = 0;
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