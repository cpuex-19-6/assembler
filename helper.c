#include <stdio.h>
#include <stdlib.h>

// レジスタを5bitのバイナリ（の10進数表記）に変換する
int reg(char* reg) {
  int n = atoi(++reg);
  int binary = 0;
  int base = 1;
  
  while (n > 0) {
    binary += (n % 2) * base;
    n /= 2;
    base *= 10;
  }

  return binary;
}

// 即値 imm[11:0]
long long int imm_11_0(char* imm) {
  int n = (atoi(imm) < 0) ? (4096 + atoi(imm)) : atoi(imm);

  long long int binary = 0;
  long long int base = 1;
  
  while (n > 0) {
    binary += (n % 2) * base;
    n /= 2;
    base *= 10;
  }

  return binary;
}