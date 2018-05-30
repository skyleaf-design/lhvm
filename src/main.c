#include <stdio.h>

char buffer[128];

int boing(char *buf, int buflen );

int main(int argc, char *argv[]) {
  if (argc > 1) {
    printf("%s\n", argv[1]);
  }
  else {
    printf( "this is my lexer/parser\n" );
  }

  boing(buffer, 12);
  printf("%s\n", buffer);
}

int boing(char *buf, int str_len ) {
  int index;
  for (index = 0; index < str_len; index += 1) {
    buf[index] = 'X';
  }
  buf[str_len + 1] = '\n';
  buf[str_len + 2] = '\0';
  return str_len;
}