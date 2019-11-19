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

inw, inf, outw, outb

## 使い方

```bash
./asm [src] [target]
./asm [src] [target] -l # タグファイル用
./asm [src] [target] -b # bin.coe 用
./asm [src] [target] -v # デバッグ用
```

実行時に引数のオプションで `-v` を付けると

```
000000011110 00000 000 00100 0110011 // 12 addi x4 x0 30  ! 4
000000000000 00001 000 11111 0110011 // 16 addi x31 x1 0  ! 4
```

このように多少読みやすい形式で出力します。

また、実行時に引数のオプションで`-l`を付けると、[src].tag というタグファイルも生成します。ただし、`-v`や、`-b`がある場合には、`-l`は付けるとするならそれらの後である必要があります。

実行時に引数のオプションで `-b` を付けると bin.coe の形式で出力します。
