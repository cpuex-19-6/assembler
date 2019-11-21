# assembler

## 対応済

#### 即値補助命令

lui

#### 基本算術論理命令

addi, slli, xori, srli, srai, ori, andi, add, sub, divu, div, remu, rem, sll, xor, srl, sra, or, and

#### 無条件分岐命令

auipc, jalr, jal

#### 条件分岐命令

bltu, bgeu, beq, bne, blt, bge

#### メモリ操作命令

lw, sw

#### 浮動小数点数メモリ操作命令

flw, fsw

#### 浮動小数点数算術命令

fadd, fsub, fmul, fdiv, fsgnjn, fsgnjx, fsgnj, fsqrt, ffloor

#### 浮動小数点数・整数間命令

itof, ftoi, fmvi, imvf, feq, flt, fle

#### 入出力命令

inw, inf, outw, outb, outf

## 使い方

```bash
./asm [src] [target]
./asm  -l [src] [target] # タグファイル用
./asm  -b [src] [target] # bin.coe 用
./asm  -B [src] [target] # バイナリ 用（予定）
./asm  -v [src] [target] # デバッグ用
```

## オプション

| Option   |  Description  |
|:---|:---|
|  -l  |  タグファイルも合わせて生成する。  |
|  -b  |  bin.coe 形式で機械語を出力する。  |
|  -B  |  バイナリを出力する。（予定）  |
|  -v  |  デバッグモード  |