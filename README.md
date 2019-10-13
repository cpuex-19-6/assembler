# assembler

## 使い方

```
./assembler [source] [target] (-v)
```

アセンブラの形式は

```
# jump to main entry point
0 	jalr	x0 x1 12
# fib.5:
4	addi	x4 x4 7		! 3
8	jalr	x0 x1 0		! 3
# main program starts
12 	addi	x4 x0 30		! 4
16	addi	x31 x1 0		! 4
20	sw	x2 x31 4		! 4
24	addi	x2 x2 8		! 4
28	jal	x1 -24		! 4
32	addi	x2 x2 -8		! 4
36	lw	x31 x2 4		! 4
40	addi	x1 x31 0		! 4
# main program ends
```

例えば上記のような、

- `rd`, `rs1`, `rs2` が空白区切り
- レジスタには `x` が先頭に付いていて即値には付いていない
- load 命令や store 命令でも、例えば `sw	x31 4(x2)` ではなく `sw	x2 x31 4` と表記されている

このような形式を一応想定しています。

実行時に引数のオプションで `-v` を付けると

```
000000011110 00000 000 00100 0110011 // 12 addi x4 x0 30  ! 4
000000000000 00001 000 11111 0110011 // 16 addi x31 x1 0  ! 4
```

このように多少読みやすい形式で出力します。
