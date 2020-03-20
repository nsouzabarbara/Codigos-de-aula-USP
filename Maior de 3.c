#include <stdio.h>

int main() {
  int a, b, c, maior;
  printf("Insira tres numeros: ");
  scanf("%d %d %d", &a, &b, &c);
  if(a >= b && a >= c)
    maior = a;
  if(b >= a && b >= c)
    maior = b;
  if(c >= a && c >= b)
    maior = c;
  printf("O maior numero e: %d", maior);
  return 0;
}
