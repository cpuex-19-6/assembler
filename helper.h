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

#define F7_ADD  0000000
#define F7_SUB   100000
#define F7_SLL  0000000
#define F7_XOR  0000000
#define F7_SRL  0000000
#define F7_SRA   100000
#define F7_OR   0000000
#define F7_AND  0000000
#define F7_SLLI 0000000
#define F7_SRLI 0000000
#define F7_SRAI  100000

#define F3_ADD  000
#define F3_SUB  000
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

#define F3_JALR 000

#define F3_BEQ  000
#define F3_BNE    1
#define F3_BLT  100
#define F3_BGE  101
#define F3_BLTU 110
#define F3_BGEU 111

#endif

int reg(char*);
long long int imm_11_0(char*);
long long int imm_11_5(char*);
int imm_4_0(char*);
long long int imm_12_10_5(char*);
int imm_4_1_11(char*);
unsigned long long int imm_31_12(char*);
unsigned long long int imm_20_10_1_11_19_12(char*);