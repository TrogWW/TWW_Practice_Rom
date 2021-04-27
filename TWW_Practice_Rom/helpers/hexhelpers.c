#include "hexhelpers.h"

byte nthByte(int number, int n){
    return (number >> (8*n)) & 0xff;
}
