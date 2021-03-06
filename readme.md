# 字符串表达式求值 C++版

> 问题要求：给你一个**字符串**，这个字符串表示一个**表达式**，这个表达式可能有整数/小数，加减乘除符号和小括号，求这个**表达式的值**。

## 运行截图

![](截图.png)

## 三种算术表达式

算术表达式中最常见的表示法形式有 **中缀**、**前缀**和 **后缀**表示法。中缀表示法是书写表达式的常见方式，而前缀和后缀表示法主要用于计算机科学领域。

### 中缀表示法 
中缀表示法是算术表达式的常规表示法。称它为 *中缀*表示法是因为每个操作符都位于其操作数的中间，这种表示法只适用于操作符恰好对应两个操作数的时候（在操作符是二元操作符如加、减、乘、除以及取模的情况下）。对以中缀表示法书写的表达式进行语法分析时，需要用括号和优先规则排除多义性。

```c++
(A+B)*C-D/(E+F)
```

### 前缀表示法
前缀表示法中，操作符写在操作数的前面。这种表示法经常用于计算机科学，特别是编译器设计方面。为纪念其发明家 ― Jan Lukasiewicz（请参阅[参考资料](<https://zh.wikipedia.org/wiki/%E6%B3%A2%E5%85%B0%E8%A1%A8%E7%A4%BA%E6%B3%95>)，这种表示法也称 **波兰表示法**。

```c++
-*+ABC/D+EF
```

### 后缀表示法 
在后缀表示法中，操作符位于操作数后面。后缀表示法也称 ***逆波兰表示法***（reverse Polish notation，RPN），因其使表达式求值变得轻松，所以被普遍使用。

```c++
AB+C*DEF+/-
```

## 中缀表达式到后缀表达式的转换

要把表达式从中缀表达式的形式转换成用后缀表示法表示的等价表达式，必须了解操作符的优先级和结合性。 *优先级*或者说操作符的强度决定求值顺序；优先级高的操作符比优先级低的操作符先求值。 如果所有操作符优先级一样，那么求值顺序就取决于它们的 *结合性*。操作符的结合性定义了相同优先级操作符组合的顺序（从右至左或从左至右）。

```
Left associativity  : A+B+C = (A+B)+C
Right associativity : A^B^C = A^(B^C)
```

转换过程包括用下面的算法读入中缀表达式的操作数、操作符和括号：

1. 初始化一个空堆栈，将结果字符串变量置空。
2. 从左到右读入中缀表达式，每次一个字符。
3. 如果字符是操作数，将它添加到结果字符串。
4. 如果字符是个操作符，弹出（pop）操作符，直至遇见开括号（opening parenthesis）、优先级较低的操作符或者同一优先级的右结合符号。把这个操作符压入（push）堆栈。
5. 如果字符是个开括号，把它压入堆栈。
6. 如果字符是个闭括号（closing parenthesis），在遇见开括号前，弹出所有操作符，然后把它们添加到结果字符串。
7. 如果到达输入字符串的末尾，弹出所有操作符并添加到结果字符串。

## 后缀表达式求值

对后缀表达式求值比直接对中缀表达式求值简单。在后缀表达式中，不需要括号，而且操作符的优先级也不再起作用了。您可以用如下算法对后缀表达式求值：

1. 初始化一个空堆栈
2. 从左到右读入后缀表达式
3. 如果字符是一个操作数，把它压入堆栈。
4. 如果字符是个操作符，弹出两个操作数，执行恰当操作，然后把结果压入堆栈。如果您不能够弹出两个操作数，后缀表达式的语法就不正确。
5. 到后缀表达式末尾，从堆栈中弹出结果。若后缀表达式格式正确，那么堆栈应该为空。


