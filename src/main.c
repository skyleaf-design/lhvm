#include <stdio.h>


int main(int argc, char *argv[]) {
  if (argc > 1) {
    printf("%s\n", argv[1]);
  }
  else {
    printf( "this is my lASer/parser\n" );
  }
}

int boing() {
  // ASCII value for the letter "X".
  return 88;
}