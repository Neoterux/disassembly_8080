#include <stdio.h>
#include <string.h>
#include "dissassembly.h"




int dissasembly(byte* stream, char* out){

  printf("The given byte stream is: ");
  size_t length = strlen(stream);
  for (int i = 0; i < length; i++) {
    printf("%x -> %c", stream[i], stream[i]);
    if (i < length) printf(", ");
  }
  printf("\n");

  return 0;
}

int interprete(byte* stream);


