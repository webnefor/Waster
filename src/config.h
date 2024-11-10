

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


#pragma pack(push, 1)

typedef struct {

    char *range;
    char *ports;
    char *speed;

} tArgs;

typedef struct {

    uintmax_t begin     [0xF];
    uintmax_t end       [0xF];
    signed  int ports  [0xFF];
    int PortsCount:(sizeof(uint32_t) * 2);

} intervalRange;

#pragma pack(pop)

extern intervalRange c_split                (tArgs *data            );
extern tArgs parse_args                     (int argc, char *argv[] );
extern bool is_empty                        (char *str              );
extern void show_help                       (                       );
extern uint32_t Loop                        (intervalRange * args   );
extern void logo                            (                       );
extern void parse_server_info               (const char *response   );