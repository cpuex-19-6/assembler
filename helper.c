#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// アセンブリのカンマ区切りを除去する
char* eliminate_comma(char* line) {
  int n = strlen(line);

  for (int i=0;i<n;++i) {
    if (line[i] == ',') {
      line[i] = ' ';
    }
  }

  return line;
}

// 行頭のPCの数値を除去する
char* eliminate_pc(char* line) {
  int n = strlen(line);

  for (int i=0;i<n;++i) {
    char cur = line[i];

    if (cur == 32) {
      continue;
    } else if (cur == 9) {
      continue;
    } else if (cur >= 48 && cur <= 57) {
      line[i] = ' ';
    } else {
      break;
    }
  }

  return line;
}

//ラベルのスペースをアンダーバーに変換
char* space2_(char* line) {
  int n = strlen(line);

  for (int i=0;i<n;++i) {
    if (line[i] == ' ') {
      line[i] = '_';
    }
  }

  return line;
}

// 0, 1の文字列を4つずつに区切って出力する
void emit_binary(FILE* out, char* line) {
  char tmp = 0;
  // int num = 0;

  for (int i=0;i<32;++i) {
    if ((i > 0) && (i % 8) == 0) {
      fprintf(out, "%c", tmp);
      // printf("%d\n", num);
      tmp = line[i] - '0';
      // num = line[i] - '0';
    } else {
      tmp *= 2;
      tmp += line[i] - '0';
      // num *= 2;
      // num += line[i] - '0';
    }
  }

  fprintf(out, "%c", tmp);
  // printf("%d\n", num);
}

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

// 即値 imm[11:5]
long long int imm_11_5(char* imm) {
  int n = (atoi(imm) < 0) ? ((1 << 12) + atoi(imm)) : atoi(imm);

  long long int binary = 0;
  long long int base = 1;
  
  while (n > 0) {
    binary += (n % 2) * base;
    n /= 2;
    base *= 10;
  }

  return (binary / 100000);
}

// 即値 imm[4:0]
int imm_4_0(char* imm) {
  int n = (atoi(imm) < 0) ? ((1 << 12) + atoi(imm)) : atoi(imm);

  long long int binary = 0;
  long long int base = 1;
  
  while (n > 0) {
    binary += (n % 2) * base;
    n /= 2;
    base *= 10;
  }

  return (binary % 100000);
}

// 即値 imm[12|10:5]
long long int imm_12_10_5(char* imm) {
  int m = atoi(imm) / 2;
  int n = (m < 0) ? ((1 << 12) + m) : m;

  long long int binary = 0;
  
  binary += ((n >> 11) % 2) * 1000 * 1000;
  binary += ((n >> 9) % 2) * 1000 * 100;
  binary += ((n >> 8) % 2) * 1000 * 10;
  binary += ((n >> 7) % 2) * 1000;
  binary += ((n >> 6) % 2) * 100;
  binary += ((n >> 5) % 2) * 10;
  binary += ((n >> 4) % 2);

  return binary;
}

// 即値 imm[4:1|11]
int imm_4_1_11(char* imm) {
  int m = atoi(imm) / 2;
  int n = (m < 0) ? ((1 << 12) + m) : m;

  long long int binary = 0;

  binary += ((n >> 3) % 2) * 10000;
  binary += ((n >> 2) % 2) * 1000;
  binary += ((n >> 1) % 2) * 100;
  binary += (n % 2) * 10;
  binary += ((n >> 10) % 2);
  
  return binary;
}

// 即値 imm[31:12]
// 20桁の整数ですが, unsigned long long でギリギリおさまります（）
unsigned long long int imm_31_12(char* imm) {
  int m = atoi(imm) / 4096;
  unsigned long int n = (m < 0) ? ((1 << 20) + m) : m;

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
  int m = atol(imm) / 2;
  unsigned long int n = (m < 0) ? ((1 << 20) + m) : m;

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
