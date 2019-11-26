/* 擬似命令を実現するためのライブラリ */

long long int upper(long long int n) {
  return ((n >> 12) + (((n & (1 << 11)) == 0) ? 0 : 1)) * 4096;
}

long long int lower(long long int n) {
  return (n << 51) >> 51;
}

unsigned long long int imm_31_12_int(long long int imm) {
  int m = imm / 4096;
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

long long int imm_11_0_int(int imm) {
  int n = (imm < 0) ? ((1 << 12) + imm) : imm;

  long long int binary = 0;
  long long int base = 1;
  
  while (n > 0) {
    binary += (n % 2) * base;
    n /= 2;
    base *= 10;
  }

  return binary;
}