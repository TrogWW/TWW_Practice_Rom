#ifndef HEXHELPERS_C_INCLUDED
#define HEXHELPERS_C_INCLUDED

#include "hexhelpers.h"

byte nthByte(int number, int n){
    return (number >> (8*n)) & 0xff;
}
bool isNthBitSet(int i, int n){
    return i & (1 << (n - 1));
}
void *memset(void *b, int c, int len){
  int           i;
  unsigned char *p = b;
  i = 0;
  while(len > 0)
    {
      *p = c;
      p++;
      len--;
    }
  return(b);
}

#endif