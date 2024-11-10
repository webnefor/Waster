

#include "scan.h"


int main(int argc, char *argv[]) {

    __attribute__((unused)) tArgs get_data = parse_args(argc, argv);

    __attribute__((unused)) intervalRange intRangeSplit = c_split(&get_data);

    logo();

    kernelThread(&intRangeSplit);

    return 0;
}

//"\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x31\xc9\x31\xd2\xb0\x0b\xcd\x80";
