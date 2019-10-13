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

    
    // 基本算術命令
    if (strncmp(opecode, "addi", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      long long int imm = imm_11_0(r2);
      if (verbose)
        fprintf(out, "%012lld %05d %03d %05d %07d // %s", imm, rs1, F3_ADDI, rd, OP_LAI, line);
      else
        fprintf(out, "%012lld%05d%03d%05d%07d\n", imm, rs1, F3_ADDI, rd, OP_LAI);
    }
    else if (strncmp(opecode, "slli", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int imm = imm_4_0(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_SLLI, imm, rs1, F3_SLLI, rd, OP_LAI, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_SLLI, imm, rs1, F3_SLLI, rd, OP_LAI);
    }
    else if (strncmp(opecode, "xori", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      long long int imm = imm_11_0(r2);
      if (verbose)
        fprintf(out, "%012lld %05d %03d %05d %07d // %s", imm, rs1, F3_XORI, rd, OP_LAI, line);
      else
        fprintf(out, "%012lld%05d%03d%05d%07d\n", imm, rs1, F3_XORI, rd, OP_LAI);
    }
    else if (strncmp(opecode, "srli", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int imm = imm_4_0(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_SRLI, imm, rs1, F3_SRLI, rd, OP_LAI, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_SRLI, imm, rs1, F3_SRLI, rd, OP_LAI);
    }
    else if (strncmp(opecode, "srai", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int imm = imm_4_0(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_SRAI, imm, rs1, F3_SRAI, rd, OP_LAI, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_SRAI, imm, rs1, F3_SRAI, rd, OP_LAI);
    }
    else if (strncmp(opecode, "ori", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      long long int imm = imm_11_0(r2);
      if (verbose)
        fprintf(out, "%012lld %05d %03d %05d %07d // %s", imm, rs1, F3_ORI, rd, OP_LAI, line);
      else
        fprintf(out, "%012lld%05d%03d%05d%07d\n", imm, rs1, F3_ORI, rd, OP_LAI);
    }
    else if (strncmp(opecode, "andi", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      long long int imm = imm_11_0(r2);
      if (verbose)
        fprintf(out, "%012lld %05d %03d %05d %07d // %s", imm, rs1, F3_ANDI, rd, OP_LAI, line);
      else
        fprintf(out, "%012lld%05d%03d%05d%07d\n", imm, rs1, F3_ANDI, rd, OP_LAI);
    }
    else if (strncmp(opecode, "add", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_ADD, rs2, rs1, F3_ADD, rd, OP_LA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_ADD, rs2, rs1, F3_ADD, rd, OP_LA);
    }
    else if (strncmp(opecode, "sub", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_SUB, rs2, rs1, F3_SUB, rd, OP_LA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_SUB, rs2, rs1, F3_SUB, rd, OP_LA);
    }
    else if (strncmp(opecode, "sll", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_SLL, rs2, rs1, F3_SLL, rd, OP_LA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_SLL, rs2, rs1, F3_SLL, rd, OP_LA);
    }
    else if (strncmp(opecode, "xor", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_XOR, rs2, rs1, F3_XOR, rd, OP_LA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_XOR, rs2, rs1, F3_XOR, rd, OP_LA);
    }
    else if (strncmp(opecode, "srl", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_SRL, rs2, rs1, F3_SRL, rd, OP_LA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_SRL, rs2, rs1, F3_SRL, rd, OP_LA);
    }
    else if (strncmp(opecode, "sra", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_SRA, rs2, rs1, F3_SRA, rd, OP_LA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_SRA, rs2, rs1, F3_SRA, rd, OP_LA);
    }
    else if (strncmp(opecode, "or", 2) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_OR, rs2, rs1, F3_OR, rd, OP_LA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_OR, rs2, rs1, F3_OR, rd, OP_LA);
    }
    else if (strncmp(opecode, "and", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_AND, rs2, rs1, F3_AND, rd, OP_LA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_AND, rs2, rs1, F3_AND, rd, OP_LA);
    }


    // 無条件分岐命令
    else if (strncmp(opecode, "auipc", 5) == 0) {
      int rd = reg(r0);
      unsigned long long int imm = imm_31_12(r1);
      if (verbose)
        fprintf(out, "%020llu %05d %07d // %s", imm, rd, OP_AUIPC, line);
      else 
        fprintf(out, "%020llu%05d%07d\n", imm, rd, OP_AUIPC);
    }
    else if (strncmp(opecode, "jalr", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      long long int imm = imm_11_0(r2);
      if (verbose)
        fprintf(out, "%012lld %05d %03d %05d %07d // %s", imm, rs1, F3_JALR, rd, OP_JALR, line);
      else
        fprintf(out, "%012lld%05d%03d%05d%07d\n", imm, rs1, F3_JALR, rd, OP_JALR);
    }
    else if (strncmp(opecode, "jal", 3) == 0) {
      int rd = reg(r0);
      unsigned long long int imm = imm_20_10_1_11_19_12(r1);
      if (verbose)
        fprintf(out, "%020llu %05d %07d // %s", imm, rd, OP_JAL, line);
      else 
        fprintf(out, "%020llu%05d%07d\n", imm, rd, OP_JAL);  
    }
  }

  fprintf(out, "00000000000000000000000000000000");

  fclose(in);
  fclose(out);
}