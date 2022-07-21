#include <stdio.h>

struct Book {
  char name[10];
  double price;

} b1;

int main(int argc, char const *argv[]) {
  /* code */

  struct Book b1 = {"c语言", 3.12};

  printf("bookName: %s \n", b1.name);

  return 0;
}
