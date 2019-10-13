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
  int n = (atoi(imm) < 0) ? ((1 << 12) + atoi(imm)) : atoi(imm);

  long long int binary = 0;
  long long int base = 1;
  
  while (n > 0) {
    binary += (n % 2) * base;
    n /= 2;
    base *= 10;
  }

  return binary;
}

// 即値 imm[4:0]
int imm_4_0(char* imm) {
  int n = atoi(imm) % 32;

  int binary = 0;
  int base = 1;
  
  while (n > 0) {
    binary += (n % 2) * base;
    n /= 2;
    base *= 10;
  }

  return binary;
}

// 即値 imm[31:12]
// 20桁の整数ですが, unsigned long long でギリギリおさまります（）
unsigned long long int imm_31_12(char* imm) {
  unsigned long int n = (atol(imm) < 0) ? ((1 << 20) + atol(imm)) : atol(imm);

  unsigned long long int binary = 0;
  unsigned long long int base = 1;
  
  while (n > 0) {
    binary += (n % 2) * base;
    n /= 2;
    base *= 10;
  }

  return binary;
}

// 即値 imm[20|10:1|11|19:12]
unsigned long long int imm_20_10_1_11_19_12(char* imm) {
  unsigned long int n = (atol(imm) < 0) ? ((1 << 20) + atol(imm)) : atol(imm);

  unsigned long long int binary = 0;

  // もっと良い方法はあるはず....
  binary += ((n >> 19) % 2) * 10000 * 10000 * 10000 * 10000 * 1000;  
  binary += ((n >> 9) % 2) * 10000 * 10000 * 10000 * 10000 * 100;
  binary += ((n >> 8) % 2) * 10000 * 10000 * 10000 * 10000 * 10; 
  binary += ((n >> 7) % 2) * 10000 * 10000 * 10000 * 10000;
  binary += ((n >> 6) % 2) * 10000 * 10000 * 10000 * 1000;    
  binary += ((n >> 5) % 2) * 10000 * 10000 * 10000 * 100; 
  binary += ((n >> 4) % 2) * 10000 * 10000 * 10000 * 10; 
  binary += ((n >> 3) % 2) * 10000 * 10000 * 10000; 
  binary += ((n >> 2) % 2) * 10000 * 10000 * 1000; 
  binary += ((n >> 1) % 2) * 10000 * 10000 * 100; 
  binary += (n % 2) * 10000 * 10000 * 10; 
  binary += ((n >> 10) % 2) * 10000 * 10000;
  binary += ((n >> 18) % 2) * 10000 * 1000;
  binary += ((n >> 17) % 2) * 10000 * 100;
  binary += ((n >> 16) % 2) * 10000 * 10;
  binary += ((n >> 15) % 2) * 10000;
  binary += ((n >> 14) % 2) * 1000;
  binary += ((n >> 13) % 2) * 100;
  binary += ((n >> 12) % 2) * 10;
  binary += ((n >> 11) % 2);

  return binary;
}