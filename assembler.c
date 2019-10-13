#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./helper.h"
#define BUFSIZE 100

int main(int argc, char *argv[]) {
  FILE *in, *out;
  int verbose = 0;

  if (argc < 3) {
    perror("Usage: ./assembler [source] [target] (-v)\n");
    exit(1);
  }

  if ((in = fopen(argv[1], "r")) == NULL) {
    perror("Failed to open file.\n");
    exit(1);
  }
  if ((out = fopen(argv[2], "w")) == NULL) {
    perror("Failed to open file.\n");
    exit(1);
  }
  if ((argc >= 4) && strncmp(argv[3], "-v", 2) == 0) {
    verbose = 1;
  }


  char line[BUFSIZE];

  while (fgets(line, BUFSIZE, in) != NULL) {
    // コメントはスキップ
    if (strncmp(line, "#", 1) == 0) {
      continue;
    }

    int pc;
    char opecode[10];
    char r0[5];
    char r1[5];
    char r2[5];

    sscanf(line, "%d%s%s%s%s", &pc, opecode, r0, r1, r2);

    
    if (strncmp(opecode, "addi", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      long long int imm = imm_11_0(r2);
      if (verbose)
        fprintf(out, "%012lld %05d %03d %05d 0110011 // %s", imm, rs1, F3_ADDI, rd, line);
      else
        fprintf(out, "%012lld%05d%03d%05d0110011\n", imm, rs1, F3_ADDI, rd);
    }
    else if (strncmp(opecode, "add", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d 0110011 // %s", F7_ADD, rs2, rs1, F3_ADD, rd, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d0110011\n", F7_ADD, rs2, rs1, F3_ADD, rd);
    }
  }

  fprintf(out, "00000000000000000000000000000000");

  fclose(in);
  fclose(out);
}