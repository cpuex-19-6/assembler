#ifndef INSTRUCTION_INCLUDE
#define INSTRUCTION_INCLUDE

#define OP_LA	   110011 
#define OP_LAI    10011

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
#define F3_SLL  001
#define F3_XOR  100
#define F3_SRL  101
#define F3_SRA  101
#define F3_OR   110
#define F3_AND  111
#define F3_ADDI 000
#define F3_SLLI 001
#define F3_XORI 100
#define F3_SRLI 101
#define F3_SRAI 101
#define F3_ORI  110
#define F3_ANDI 111

#endif

int reg(char* reg);
int imm_4_0(char* imm);
long long int imm_11_0(char* imm);