#include <stdio.h>

#ifndef INSTRUCTION_INCLUDE
#define INSTRUCTION_INCLUDE

#define OP_LUI    110111
#define OP_LA     110011 
#define OP_LAI     10011
#define OP_AUIPC   10111
#define OP_JAL   1101111
#define OP_JALR  1100111
#define OP_LD         11
#define OP_ST     100011
#define OP_CB    1100011

#define OP_FLW       111
#define OP_FSW    100111
#define OP_FLA   1010011

#define OP_IN       1011
#define OP_OUT    101011

#define F7_ADD  0000000
#define F7_SUB   100000
#define F7_DIV        1
#define F7_DIVU       1
#define F7_REM        1
#define F7_REMU       1
#define F7_SLL  0000000
#define F7_XOR  0000000
#define F7_SRL  0000000
#define F7_SRA   100000
#define F7_OR   0000000
#define F7_AND  0000000
#define F7_SLLI 0000000
#define F7_SRLI 0000000
#define F7_SRAI  100000

#define F7_FADD   0000000
#define F7_FSUB       100
#define F7_FMUL      1000
#define F7_FDIV      1100
#define F7_FSGNJ    10000
#define F7_FSGNJN   10000
#define F7_FSGNJX   10000
#define F7_FEQ    1010000
#define F7_FLT    1010000
#define F7_FLE    1010000
#define F7_FSQRT   101100
#define F7_FFLOOR  100000
#define F7_ITOF   1100000
#define F7_FTOI   1101000
#define F7_FMVI   1110000
#define F7_IMVF   1111000

#define F7_INW    0000000
#define F7_INF     100000
#define F7_OUTW   0000000
#define F7_OUTB   0000000
#define F7_OUTF    100000

#define F3_ADD  000
#define F3_SUB  000
#define F3_DIV  100
#define F3_DIVU 101
#define F3_REM  110
#define F3_REMU 111
#define F3_SLL    1
#define F3_XOR  100
#define F3_SRL  101
#define F3_SRA  101
#define F3_OR   110
#define F3_AND  111
#define F3_ADDI 000
#define F3_SLLI   1
#define F3_XORI 100
#define F3_SRLI 101
#define F3_SRAI 101
#define F3_ORI  110
#define F3_ANDI 111

#define F3_LW    10
#define F3_SW    10

#define F3_FLW   10
#define F3_FSW   10

#define F3_JALR 000

#define F3_BEQ  000
#define F3_BNE    1
#define F3_BLT  100
#define F3_BGE  101
#define F3_BLTU 110
#define F3_BGEU 111

#define F3_FADD   000
#define F3_FSUB   000
#define F3_FMUL   000
#define F3_FDIV   000
#define F3_FSGNJ  000
#define F3_FSGNJN   1
#define F3_FSGNJX  10
#define F3_FEQ     10
#define F3_FLT      1
#define F3_FLE    000
#define F3_FSQRT  000
#define F3_FFLOOR  10
#define F3_ITOF   000
#define F3_FTOI   000
#define F3_FMVI   000
#define F3_IMVF   000

#define F3_INW     10
#define F3_INF     10
#define F3_OUTB   000
#define F3_OUTW    10
#define F3_OUTF    10

#define RS2_FSQRT  00000
#define RS2_FFLOOR 00000
#define RS2_ITOF   00000
#define RS2_IMVF   00000
#define RS2_FTOI   00000
#define RS2_FMVI   00000

#define RS2_IN    00000
#define RS2_OUT   00000
#define RS1_IN    00000
#define RD_OUT    00000

#endif

char* eliminate_comma(char*);
char* eliminate_pc(char*);
char* space2_(char*);
void emit_binary(FILE*, char*);

int reg(char*);
long long int imm_11_0(char*);
long long int imm_11_5(char*);
int imm_4_0(char*);
long long int imm_12_10_5(char*);
int imm_4_1_11(char*);
unsigned long long int imm_31_12(char*);
unsigned long long int imm_20_10_1_11_19_12(char*);
