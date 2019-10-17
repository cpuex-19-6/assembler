#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./helper.h"
#define BUFSIZE 100

int main(int argc, char *argv[]) {
  FILE *in, *out;
  int verbose = 0;
  int bincoeMode = 0;

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
  if ((argc >= 4) && strncmp(argv[3], "-b", 2) == 0) {
    bincoeMode = 1;
  }

  if (bincoeMode) {
    fprintf(out, "memory_initialization_radix=2;\n");
    fprintf(out, "memory_initialization_vector=\n");
  }


  char line[BUFSIZE];

  while (fgets(line, BUFSIZE, in) != NULL) {
    // コメントはスキップ
    if (strncmp(line, "#", 1) == 0) {
      continue;
    }

    int pc;
    char opecode[10];
    char r0[10];
    char r1[10];
    char r2[10];

    char* inst = eliminate_comma(line);

    int res = sscanf(inst, "%d%s%s%s%s", &pc, opecode, r0, r1, r2);
    if ((res == 0) || (res == EOF)) {
      printf("cannot assemble: %s", line);
      continue;
    }


    // 即値補助命令
    if (strncmp(opecode, "lui", 3) == 0) {
      int rd = reg(r0);
      unsigned long long int imm = imm_31_12(r1);
      if (verbose)
        fprintf(out, "%020llu %05d %07d // %s", imm, rd, OP_LUI, line);
      else 
        fprintf(out, "%020llu%05d%07d\n", imm, rd, OP_LUI);
    }

    
    // 基本算術命令
    else if (strncmp(opecode, "addi", 4) == 0) {
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


    // メモリ操作命令
    else if (strncmp(opecode, "lw", 2) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      long long int imm = imm_11_0(r2);
      if (verbose)
        fprintf(out, "%012lld %05d %03d %05d %07d // %s", imm, rs1, F3_LW, rd, OP_LD, line);
      else
        fprintf(out, "%012lld%05d%03d%05d%07d\n", imm, rs1, F3_LW, rd, OP_LD);
    }
    else if (strncmp(opecode, "sw", 2) == 0) {
      int rs1 = reg(r0);
      int rs2 = reg(r1);
      long long int imm1 = imm_11_5(r2);
      int imm2 = imm_4_0(r2);
      if (verbose)
        fprintf(out, "%07lld %05d %05d %03d %05d %07d // %s", imm1, rs2, rs1, F3_SW, imm2, OP_ST, line);
      else
        fprintf(out, "%07lld%05d%05d%03d%05d%07d\n", imm1, rs2, rs1, F3_SW, imm2, OP_ST);
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


    // 条件分岐命令
    else if (strncmp(opecode, "bltu", 4) == 0) {
      int rs1 = reg(r0);
      int rs2 = reg(r1);
      long long int imm1 = imm_12_10_5(r2);
      int imm2 = imm_4_1_11(r2);
      if (verbose)
        fprintf(out, "%07lld %05d %05d %03d %05d %07d // %s", imm1, rs2, rs1, F3_BLTU, imm2, OP_CB, line);
      else 
        fprintf(out, "%07lld%05d%05d%03d%05d%07d\n", imm1, rs2, rs1, F3_BLTU, imm2, OP_CB);
    }
    else if (strncmp(opecode, "bgeu", 4) == 0) {
      int rs1 = reg(r0);
      int rs2 = reg(r1);
      long long int imm1 = imm_12_10_5(r2);
      int imm2 = imm_4_1_11(r2);
      if (verbose)
        fprintf(out, "%07lld %05d %05d %03d %05d %07d // %s", imm1, rs2, rs1, F3_BGEU, imm2, OP_CB, line);
      else 
        fprintf(out, "%07lld%05d%05d%03d%05d%07d\n", imm1, rs2, rs1, F3_BGEU, imm2, OP_CB);
    }
    else if (strncmp(opecode, "beq", 3) == 0) {
      int rs1 = reg(r0);
      int rs2 = reg(r1);
      long long int imm1 = imm_12_10_5(r2);
      int imm2 = imm_4_1_11(r2);
      if (verbose)
        fprintf(out, "%07lld %05d %05d %03d %05d %07d // %s", imm1, rs2, rs1, F3_BEQ, imm2, OP_CB, line);
      else 
        fprintf(out, "%07lld%05d%05d%03d%05d%07d\n", imm1, rs2, rs1, F3_BEQ, imm2, OP_CB);
    }
    else if (strncmp(opecode, "bne", 3) == 0) {
      int rs1 = reg(r0);
      int rs2 = reg(r1);
      long long int imm1 = imm_12_10_5(r2);
      int imm2 = imm_4_1_11(r2);
      if (verbose)
        fprintf(out, "%07lld %05d %05d %03d %05d %07d // %s", imm1, rs2, rs1, F3_BNE, imm2, OP_CB, line);
      else 
        fprintf(out, "%07lld%05d%05d%03d%05d%07d\n", imm1, rs2, rs1, F3_BNE, imm2, OP_CB);
    }
    else if (strncmp(opecode, "blt", 3) == 0) {
      int rs1 = reg(r0);
      int rs2 = reg(r1);
      long long int imm1 = imm_12_10_5(r2);
      int imm2 = imm_4_1_11(r2);
      if (verbose)
        fprintf(out, "%07lld %05d %05d %03d %05d %07d // %s", imm1, rs2, rs1, F3_BLT, imm2, OP_CB, line);
      else 
        fprintf(out, "%07lld%05d%05d%03d%05d%07d\n", imm1, rs2, rs1, F3_BLT, imm2, OP_CB);
    }
    else if (strncmp(opecode, "bge", 3) == 0) {
      int rs1 = reg(r0);
      int rs2 = reg(r1);
      long long int imm1 = imm_12_10_5(r2);
      int imm2 = imm_4_1_11(r2);
      if (verbose)
        fprintf(out, "%07lld %05d %05d %03d %05d %07d // %s", imm1, rs2, rs1, F3_BGE, imm2, OP_CB, line);
      else 
        fprintf(out, "%07lld%05d%05d%03d%05d%07d\n", imm1, rs2, rs1, F3_BGE, imm2, OP_CB);
    }
    

    // 浮動小数点数メモリ操作命令
    else if (strncmp(opecode, "flw", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      long long int imm = imm_11_0(r2);
      if (verbose)
        fprintf(out, "%012lld %05d %03d %05d %07d // %s", imm, rs1, F3_FLW, rd, OP_FLW, line);
      else
        fprintf(out, "%012lld%05d%03d%05d%07d\n", imm, rs1, F3_FLW, rd, OP_FLW);
    }
    else if (strncmp(opecode, "fsw", 3) == 0) {
      int rs1 = reg(r0);
      int rs2 = reg(r1);
      long long int imm1 = imm_11_5(r2);
      int imm2 = imm_4_0(r2);
      if (verbose)
        fprintf(out, "%07lld %05d %05d %03d %05d %07d // %s", imm1, rs2, rs1, F3_FSW, imm2, OP_FSW, line);
      else
        fprintf(out, "%07lld%05d%05d%03d%05d%07d\n", imm1, rs2, rs1, F3_FSW, imm2, OP_FSW);
    }


    // 浮動小数点数算術命令
    else if (strncmp(opecode, "fadd", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FADD, rs2, rs1, F3_FADD, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FADD, rs2, rs1, F3_FADD, rd, OP_FLA);
    }
    else if (strncmp(opecode, "fsub", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FSUB, rs2, rs1, F3_FSUB, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FSUB, rs2, rs1, F3_FSUB, rd, OP_FLA);
    }
    else if (strncmp(opecode, "fmul", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FMUL, rs2, rs1, F3_FMUL, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FMUL, rs2, rs1, F3_FMUL, rd, OP_FLA);
    }
    else if (strncmp(opecode, "fdiv", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FDIV, rs2, rs1, F3_FDIV, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FDIV, rs2, rs1, F3_FDIV, rd, OP_FLA);
    }
    else if (strncmp(opecode, "fsgnjn", 6) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FSGNJN, rs2, rs1, F3_FSGNJN, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FSGNJN, rs2, rs1, F3_FSGNJN, rd, OP_FLA);
    }
    else if (strncmp(opecode, "fsgnjx", 6) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FSGNJX, rs2, rs1, F3_FSGNJX, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FSGNJX, rs2, rs1, F3_FSGNJX, rd, OP_FLA);
    }
    else if (strncmp(opecode, "fsgnj", 5) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FSGNJ, rs2, rs1, F3_FSGNJ, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FSGNJ, rs2, rs1, F3_FSGNJ, rd, OP_FLA);
    }
    else if (strncmp(opecode, "feq", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FEQ, rs2, rs1, F3_FEQ, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FEQ, rs2, rs1, F3_FEQ, rd, OP_FLA);
    }
    else if (strncmp(opecode, "flt", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FLT, rs2, rs1, F3_FLT, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FLT, rs2, rs1, F3_FLT, rd, OP_FLA);
    }
    else if (strncmp(opecode, "fle", 3) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      int rs2 = reg(r2);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FLE, rs2, rs1, F3_FLE, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FLE, rs2, rs1, F3_FLE, rd, OP_FLA);
    }
    else if (strncmp(opecode, "fsqrt", 5) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FSQRT, RS2_FSQRT, rs1, F3_FSQRT, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FSQRT, RS2_FSQRT, rs1, F3_FSQRT, rd, OP_FLA);
    }
    else if (strncmp(opecode, "itof", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_ITOF, RS2_ITOF, rs1, F3_ITOF, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_ITOF, RS2_ITOF, rs1, F3_ITOF, rd, OP_FLA);
    }
    else if (strncmp(opecode, "ftoi", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FTOI, RS2_FTOI, rs1, F3_FTOI, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FTOI, RS2_FTOI, rs1, F3_FTOI, rd, OP_FLA);
    }
    else if (strncmp(opecode, "fmvi", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_FMVI, RS2_FMVI, rs1, F3_FMVI, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_FMVI, RS2_FMVI, rs1, F3_FMVI, rd, OP_FLA);
    }
    else if (strncmp(opecode, "imvf", 4) == 0) {
      int rd = reg(r0);
      int rs1 = reg(r1);
      if (verbose)
        fprintf(out, "%07d %05d %05d %03d %05d %07d // %s", F7_IMVF, RS2_IMVF, rs1, F3_IMVF, rd, OP_FLA, line);
      else
        fprintf(out, "%07d%05d%05d%03d%05d%07d\n", F7_IMVF, RS2_IMVF, rs1, F3_IMVF, rd, OP_FLA);
    }


    else {
      printf("cannot assemble: %s", line);
    }
  }

  fprintf(out, "00000000000000000000000000000000");
  if (bincoeMode) {
    fprintf(out, ";");
  }

  fclose(in);
  fclose(out);
}