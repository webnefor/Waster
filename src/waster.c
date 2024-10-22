
#include "scan.h"

int main(int argc, char *argv[]) {

    __attribute__((unused)) tArgs get_data = parse_args(argc, argv);

    __attribute__((unused)) intervalRange intRangeSplit = c_split(&get_data);

    logo();

    kernelThread(&intRangeSplit);

    return 0;
}
