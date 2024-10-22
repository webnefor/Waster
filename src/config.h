

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define RANGE ("-r")
#define PORTS ("-p")
#define SPEED ("-s")
#define HELP  ("-h")

#define MAX_NUMBERS 254


#define RED "\033[31m"
#define DEFAULT "\033[0m"

typedef struct {

    char *range;
    char *ports;
    char *speed;

} tArgs;

typedef struct {

    unsigned int begin[8];
    unsigned int end  [8];
    signed   int ports [254];
    int PortsCount;

} intervalRange;

extern intervalRange c_split                (tArgs *data            );
extern tArgs parse_args                     (int argc, char *argv[] );
extern bool is_empty                        (char *str              );
extern void show_help                       (                       );
extern void logo();