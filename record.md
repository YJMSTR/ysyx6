
# 第六期一生一芯实验记录

之前做过第四期一生一芯，完成到 PA2.3 和数电实验，单周期刚开始写。

第六期预学习的流程发生了一些变化，重走一遍流程

## PA0

安装了一个全新的 Ubuntu 22.04.3, 不过太新了，装 PA0 里那些软件包的时候满足不了依赖关系，通过 aptitude 降级了一些软件才解决。

Ubuntu 22.04.3 刚装好时不能关机和重启，会卡在 logo，STFW 得知是 NVIDIA 显卡驱动问题，装完驱动解决。

之前做 ysyx 的时候只把 pa2 分支传到了自己的 GitHub 上，这次把所有分支都传上去了，方便恢复。

在 NEMU 里键入 q 退出时报错：`make: *** [/home/yjmstr/ysyx-workbench/nemu/scripts/native.mk:38: run] Error 1, 原因不明`。

## 复习 C 语言

预学习答辩需要完成 C 语言入门必做题。大部分内容之前都学过了，这里仅记录新学到的东西

### ex4

Valgrind 第一次用

### ex16

strdup 返回指向参数字符串副本的指针，它的行为类似 malloc ，但会复制字符串到新创建的内存

附加题：将程序改成不用指针和 malloc 的版本。

```c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person Person_create(char *name, int age, int height, int weight)
{
	struct Person who;

	who.name = strdup(name);
	who.age = age;
	who.height = height;
	who.weight = weight;

	return who;
}



void Person_print(struct Person who)
{
	printf("Name: %s\n", who.name);
	printf("\tAge: %d\n", who.age);
	printf("\tHeight: %d\n", who.height);
	printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
	struct Person joe = Person_create(
			"Joe Alex", 32, 64, 140);

	struct Person frank = Person_create(
			"Frank Blank", 20, 72, 180);

	printf("Joe is at memory location %p:\n", &joe);
	Person_print(joe);

	printf("Frank is at memory location %p:\n", &frank);
	Person_print(frank);


	joe.age += 20;
	joe.height -= 2;
	joe.weight += 40;
       	Person_print(joe);
	frank.age += 20;
	frank.weight += 20;
	Person_print(frank);
	// destroy them both so we clean up
        free(joe.name);
	free(frank.name);
	return 0;
}
```

不想显示释放内存的话，可以使用 libGC 库中的 GC_malloc，然后把所有的 free 删掉

### ex17

strncpy 的缺陷：n 大于源串长度时，遇到 '\0' 结束，但小于源串长度时到第n个字符结束，不会在末尾补'\0'

附加题2：把结构体里的定长数组改成指针，读入参数后用 malloc 进行分配。
Database_load 与 Database_store 函数也要进行对应的修改，原先 load 函数从文件中读入 Database 结构体到 conn->db 当中，现在要在读入时分配内存。

附加题3：strcmp

附加题4：可以用 sizeof 来计算结构体的大小，结构体包含多种类型成员时，会进行对齐，最终的大小和对齐规则有关。成员变量需要满足 `offset mod size == 0`;

附加题6：编写 shell 脚本如下：

```shell
#!/bin/bash
set -e
make ex17
./ex17 db.dat 512 100 c
./ex17 db.dat 512 100 s 1 zed zed@zed.com
./ex17 db.dat 512 100 s 2 frank frank@frank.com
./ex17 db.dat 512 100 s 3 joe joe@joe.com

./ex17 db.dat 512 100 l
./ex17 db.dat 512 100 d 3 

./ex17 db.dat 512 100 l
./ex17 db.dat 512 100 g 2

```

### ex20

C 语言使用错误码或 errno 来处理错误。本教程提供了调试宏

### ex28

后面的实验要用到代码框架，ex28-ex31 会逐步构建出这个框架

此外 ex28 用到了 ex20 的 dbg.h

第三行 PREFIX?= xxx 在没有 PREFIX 设置的平台上运行 Makefile 时有效

Makefile 规则中通配符会自动展开，但在定义变量和函数引用时通配符会失效，这种时候需要使用 wildcard 来让通配符有效。

patsubst 是模式串替换函数，例如可以用于替换 .c 后缀为 .o 后缀

### ex29

修改 Makefile 和 ex29_tests.c ，把 argv 去掉，并修改路径即可。

### ex32

实验时出现了找不到函数定义的问题，看预学习微信群得知是动态链接的问题, 但我用他提供的 Makefile 加载静态库也有问题。

ex29 提到了 ubuntu 下动态链接需要注意 -ldl 参数的顺序，不然会导致找不到函数。

静态库使用 ar 进行打包，r 选项用于将后面的文件列表添加到文件包。r 选项改成 rs 表示生成静态库，为静态库创建索引。也可以直接 ar r 然后 ranlib 来为静态库创建索引。但教程中不仅 ar rcs 还 ranlib 了，意义不明

编译时用 -Lxx 选项告诉编译器去 xx 目录下找库，-lxx 告诉编译器要链接什么库，-Ixx 告诉编译器去 xx 目录下找头文件。

区别于静态库，共享库在运行时才会真正被链接。

一般的目标文件称为 Relocatable，在链接时可以把目标文件中各段的地址做重定位，重定位时需要修改指令。

list_tests.c 找不到 list.c 中定义的函数。list.c -> list.o -> liblcthw.a，随后 liblcthw.a 提供给 list_tests.c 来生成 list_tests

手动加载静态库可以成功通过测试，所使用的命令如下：

```sh
mkdir -p build
ar rs build/liblcthw.a src/lcthw/list.o
ranlib build/liblcthw.a
cc $CFLAGS tests/list_tests.c build/liblcthw.a -o tests/list_tests
sh tests/runtests.sh
```

手动加载动态库也可以成功编译通过测试，所使用的命令如下：

```sh
mkdir -p build
ar rs build/liblcthw.a src/lcthw/list.o
ranlib build/liblcthw.a 
cc -shared -o build/liblcthw.so src/lcthw/list.o
cc $CFLAGS tests/list_tests.c build/liblcthw.so -o tests/list_tests
sh tests/runtests.sh
```

说明是 Makefile 写得有问题

注意到 Makefile 中每一个目标的规则中都没有编译命令，那终端中出现的 cc 命令是哪来的呢？原来这是 Makefile 的隐藏规则，如果一个目标在 Makefile 中的所有规则都没有命令列表，make 会尝试在内建的隐含规则数据库中查找适用的规则。make 的隐含规则数据库可以用 make -p 打印。

我们可以改成使用上面能够成功编译的规则，向 Makefile 中添加一个目标 `$TESTS` 及其对应的规则如下，并对 tests 进行修改，去掉其对 CFLAGS 的修改：

```Makefile

$(TESTS): $(TARGET) $(SO_TARGET)
	@echo building TESTS, TEST_SRC=:$(TEST_SRC)

	$(CC) $(CFLAGS) $(TEST_SRC) $(TARGET) -o $@

.PHONY: tests 
tests: $(TESTS)
	@echo TARGET=$(TARGET)
	sh ./tests/runtests.sh

```

如果要用动态库，就把 `$TARGET` 改为 `$SO_TARGET` 即可。

附加题：咕咕咕

### ex33

从测例可以看出要实现的函数为 `int List_bubble_sort()` 和 `List* List_merge_sort()`

写完以后 make 的时候出错了，报错 main 和 all_tests 多次定义。查看 Makefile 的输出发现在编译 list_algos_tests 时把 list.c 也给输入进来了。修改 Makefile, 用 for 循环遍历 tests 目录下的 c 文件，依次编译出对应的文件。

附加题让 man 3 time 查询基本的时间函数，但 man 3 time 提示不存在该条目，应该 man 2 time。

原始数据就 5 个字符串，太小了，测时间的时候两个排序各跑了 5000000 次，冒泡 1s，归并跑了 7s. 可能是因为归并排序每次划分 left 和 right 时需要从链表头部遍历一次链表导致的，如果用数组的话直接按下标划分即可。

### ex42

Makefile 里 TESTS 目标漏了 `TEST_SRC` 依赖，补上以后 ok

本题化身宏孩儿就行

附加题提到了 DArray，没听说过这是什么，往前翻 ex34 找到了相关的内容，原来是指动态数组。

### ex44

要用到 ex36 的 bstrlib 库，按照 ex36 的文档获取源文件后还没有编写 bstring 的单元测试

附加题给的 wiki 链接点开没有 POSIX 的优化实现，切换到中文页面的话只有代码没有解释。英文页面的解释大意如下：

> 可以把缓冲区映射到虚拟内存中的两块连续区域上（底层缓冲区的长度必须等于系统页面大小的倍数），对环形缓冲区的读写可以通过内存访问变得更加高效。

大致思想是断环成链

mkstemp() 用于生成独特的临时文件名，传入的参数是文件名的模板，末6个字符必须是 XXXXXX，然后他们会被替换为一个独特的字符串。

unlink() 移除指定的文件

ftruncate() 会将指定文件扩大/裁减到指定大小。扩大时用 '\0' 填充

mmap() 在虚拟内存中创建映射, 新映射的起始地址为 addr，映射的长度由 length 参数指定。当 addr 为 NULL，内核会选取页面对齐地址来创建映射，否则 addr 会作为内核选择映射起始地址的依据（但可能不是最终的起始地址）。

## 搭建 Verilator 仿真环境

verilog 的第四期搭过了，这次搭 chisel 的。对照 npc 目录下的 readme 进行配置。

前面双控开关啥的直接参考上次的实验报告即可。

make 时报错找不到 type Tests，看微信群和 mill 的 changelog 得知是 Tests 这个 trait 要被弃用了，应该改用 ScalaTests 作为替代。

### 一键仿真

按照模板用 chisel 实现了双控开关，并用 verilator 进行仿真。makefile 中代码如下：

```makefile
sim: verilog
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator --cc --exe --trace --build sim_main.cpp build/TOP.v
```

去掉了 -Wall 选项，因为生成的 verilog 代码的 clock 和 reset 置空了，会报错，之后看情况加回来。

playground/src 目录下包含 Elaborate.scala 和 TOP.scala 两个文件，平常改 TOP 和外面的 sim_main 就行，Elaborate 不用动。test 目录目前清空了，之后深入学习 chisel 之后再补上。

### 接入 nvboard

对着 example 的 makefile 改了改，现在 make run 即可自动 make verilog 随后 make sim，然后执行编译出的可执行文件。

todo：在 makefile 里控制是否生成波形图

```makefile
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
NXDC_FILES = constr/top.nxdc
TOPNAME = Top

export PATH := $(PATH):$(abspath ./utils)

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
VSRCS = $(shell find $(BUILD_DIR) -name "*.v")
CSRCS = $(shell find $(abspath ./) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

test:
	mill -i __.test

verilog:
	$(call git_commit, "generate verilog")
	mill -i __.test.runMain Elaborate -td $(BUILD_DIR)

help:
	mill -i __.test.runMain Elaborate --help

compile:
	mill -i __.compile

bsp:
	mill -i mill.bsp.BSP/install

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

clean:
	-rm -rf $(BUILD_DIR)

.PHONY: test verilog help compile bsp reformat checkformat clean

sim: $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE) verilog
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	$(VERILATOR) $(VERILATOR_CFLAGS) \
	--top-module $(TOPNAME) $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE) \
	$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
	--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

run: sim
	@$(BIN)

-include ../Makefile
```

但目前有个问题，如果先 make verilog 再 make run 会报错。

### 流水灯

继承自 Module 类的模块会获得隐式的全局时钟和同步复位信号，如果继承自 RawModule，就不会有这两个信号。也可以用 withClock 等对象创建单独的时钟域和复位域。

使用 RegInit，即可在每次 reset 时初始化寄存器，无需显式判断 reset 的值。

```scala
import chisel3._
import chisel3.util._

class Top extends Module {
  val io = IO(new Bundle {
    // val clk = Input(Clock())
    // val rst = Input(Bool())
    val led  = Output(UInt(16.W))
  })
  val count = RegInit(0.U(32.W))
  val led = RegInit(1.U(16.W))

  when(count === 0.U) {
    led := Cat(led(14, 0), led(15))
  }
  count := Mux(count >= 5000000.U, 0.U, count+1.U)

  io.led := led
}
```

流水灯接入nvboard 改引脚绑定就行，然后make run

## 数电实验

### 7. ps2键盘

键盘和第四期中数电实验有所不同，新加入了 FIFO 队列，需要处理一下 ready和nextdata_n 信号。

只有当 ready 信号为 1 时（队列非空），接收模块才能从键盘控制器读取数据。每当读取完毕一次数据，就要将 nextdata_n 置 0 一个周期，

已有的键盘模块verilog代码可以通过chisel的blackbox连进chisel。编译的时候chisel生成的 verilog代码中会多出来一行黑盒连接的verilog的文件名，很奇怪。

还是用第四期做键盘的方法，在键盘控制器模块添加一个 kbd_clk 时钟，当键盘每次收到一个帧就将其置为高电平，否则为低电平。在 chisel 顶层模块使用 withClock(kbd_clk) 将 keycount 和 lastdata 包进去，lastdata 记录最近收到的 3 帧的内容，keycount 记录按键数。ascii 的转换偷懒只写了数字键的，其它建直接输出键码。nextdata 每个周期和自己取反。

## PA1

配置 ccache：`export PATH=/usr/lib/ccache:$PATH`

### RTFSC

#### 谁来指示程序的结束?

> 在main()函数退出之后，一般不会有语句继续执行，但是如果我们使用atexit()函数，事先注册一个无返回值、无参数的函数，就可以在main()函数退出之后，继续执行我们注册的函数中的任务，用来保证一些资源的使用或清理等操作，就类似C++中的析构函数一般，不一样的是atexit()是在程序结束后，进行执行的。
>
> 1、**函数执行的顺序与注册的顺序相反**
> 2、**使用atexit()注册的函数必须是无参数、无返回值的，否则注册不成功**
> 3、**如果函数注册成功，则atexit()函数会返回0，否则返回其他值**

#### 有始有终

GNU/Linux 上的程序开始：创建进程，加载相关资源，开始执行主函数

结束：主函数执行结束，或 exit，或发生错误

NEMU 中的程序开始：RESET_VECTOR 处的第一条指令

结束：nemu_trap 或者最后一条指令 或者出错

#### 优美地退出

> 为了测试大家是否已经理解框架代码, 我们给大家设置一个练习: 如果在运行NEMU之后直接键入 `q`退出, 你会发现终端输出了一些错误信息. 请分析这个错误信息是什么原因造成的, 然后尝试在NEMU中修复它.

错误信息如下：

```sh
make: *** [/home/yjmstr/ysyx-workbench/nemu/scripts/native.mk:38: run] Error 1
```

在 gdb 中运行编译出的 build/riscv64-nemu-interpreter，观察到 main 的返回值不为 0,这是因为 cmd_q 没有正确设置 nemu_state.state 的值。

### 基础设施：简易调试器

这部分和 ISA 关系不大，可以直接复用第四期完成的 NEMU 代码。之前将参数字符串转为数字都是手动转的，现在知道了可以用 atoi 函数，可以优化代码。此外可以用 sscanf 从字符串中读入格式化输入。

内置客户程序在 `nemu/src/isa/$ISA/init.c` 中定义，可以用这个和扫描内存的结果进行对比。

### 表达式求值

自从上一次做 PA 之后我几乎没有再用到过正则表达式相关的概念，正好复习一下。

之前实现表达式求值时没有注意处理 token 缓冲区溢出的问题，这次直接在长度超过 32 时返回 false。

注意正则表达式规则的优先顺序，hex要放在dec前面，不然匹配不到

### 监视点

每个监视点存一个长度至多为 1024 的表达式。

free_wp  的参数改成 int，只删除指定编号的监视点，没有释放空间。

#### 温故而知新

static 的作用是

- 对其它文件隐藏含有该前缀的变量和函数
- 并且将变量存储在静态存储区，仅初始化一次
- 并且初始化为 0

### 如何阅读手册

#### 学会使用目录

https://nju-projectn.github.io/i386-manual/s02_05.htm

#### 必答题

##### 程序是个状态机

状态为(PC，r1，r2)，x表示未初始化

```
0:mov r1, 0
1:mov r2, 0
2:add r1 r2
3:add r2 1
4:jmp 2
```

(0,x,x)->(1,0,x)->(2,0,0)->(3,0,0)->(4,0,1)->(5,1,1)->(6,1,2)->(7,3,2)->...(201, 4950, 99)->(202, 4950, 100)->(203, 5050, 100)->(203, 5050, 101)

##### 理解基础设施

$4500\times30\times20s$

$4500\times(30-10)\times20s$

##### RTFM

riscv32指令集有很多模块，其中基础整数指令集模块有 R I S U 四种格式，此外还有两种类型 B 和 J 用于编码立即数

LUI: 将立即数放到 rd 的高二十位

mstatus：priv spec 3.1.6 节

##### shell 命令

```makefile
count:
	@find . -name "*.h" -or -name "*.c" |xargs wc -l
```

pa0 23775

pa1 24197

##### RTFM

-Wall

`This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros`

-Werror

`Make all warnings into errors.`

开启这两个选项能够使我们的代码规避大部分可能引起bug的行为。

## PA2

### 不停计算的机器

#### 理解 YEMU 如何执行程序

1. YEMU 上执行的加法程序的状态机

   (0, x, x)->(1, x, M[y])->(2, M[y], M[y])->(3, M[y], M[x])->(4, M[y]+M[x], M[x])
2. 通过 RTFSC 理解 YEMU 如何执行一条指令

   通过 exec_once 函数，先从 M[pc] 处取出指令，然后进行译码，根据译码结果执行对应的操作，然后更新 pc。

执行指令->在状态机上转移一步

#### RTFSC理解指令执行的过程

执行 isa_exec_once 函数，首先通过 inst_fetch 函数取指，随后调用 decode_exec 函数译码并执行。decode_exec 中调用 decode_operand 函数进行指令的译码和执行。执行过程中通过 INSTPAT 对指令字符串进行模式匹配，转为函数所需的参数。

### 运行更多的程序

mul-longlong 测例过不去，等接入 difftest 再调一下

## 程序、运行时环境和AM

### RTFSC（3）

#### 阅读makefile

am的makefile只有如下短短几行

```makefile
NAME     := am
SRCS      = $(addprefix src/, $(AM_SRCS))
INC_PATH += $(AM_HOME)/am/src

include $(AM_HOME)/Makefile

```

第一行 `NAME	:= am` 用 `:=`运算符避免了多次展开，但也因此必须提前声明。

第二行声明一个 SRCS 变量， 值为 `src/$(AM_SRCS)`

第三行通过 `+=`运算符给 INC_PATH变量追加一个值，为am/src的绝对路径。

最后一行导入上一级目录的Makefile，这个Makefile比较有含金量，可以通过make html获得一个html版本以便阅读，各个步骤在html里都有说明

#### 批处理运行 nemu

查看sdb的源码可以发现，批处理需要在 nemu 启动时传入 b 参数。修改 platform/nemu.mk 即可。

#### 实现字符串处理函数

注意memset虽然传入了int，但是填充时是按无符号char进行填充的，每个字符都填充。

#### 实现 sprintf

可变参数列表需要使用 stdarg.h 中的 va_xxx 系列宏

sprintf 末尾需要加上 `'\0'`

### 基础设施（2）

#### trace

Kconfig 里已经定义了 ITRACE. 其它 trace 的开关与否可以用类似的方法定义。

环形缓冲区在 cpu_exec 末尾检测 cpu 状态为 abort 或 stop 后进行输出。

mtrace 略

#### 消失的符号

https://blog.csdn.net/helowken2/article/details/113782851

> elf 的符号包括一个 Symbol Table，其中包含一组 Symbol。这些 Symbol 在程序中要么表示定义，要么表示引用，它们的作用是在编译和链接的过程中进行定位和重定位。

https://blog.csdn.net/helowken2/article/details/113792555

> 从链接器的角度看，Symbol 可以分为3类（这里的类别不同于 Symbol Type）
>
> Global Symbol Def：定义在当前对象文件中，可以被其他对象文件引用。例如定义在当前对象文件中的非 static 的函数或者全局变量。
>
> Global Symbol Ref：定义在其他对象文件中，被当前对象文件所引用。又被称作 externals，例如定义在其他对象文件中的非 static 的函数或者全局变量。
>
> Local Symbol：定义和引用都在当前对象文件中。例如 static 函数和 static 全局变量。这些 Symbol 对当前对象文件的任何地方都可见，但是不能被其他对象文件引用。
>
> Local Symbol 并不是指局部变量
>
> 1. .symtab 不会包含任何局部变量。
> 2. 局部变量是运行期间在 Stack 上进行分配
> 3. static 变量不会在 Stack 上进行分配，而是在编译期间，由编译器在 ".data" 或 ".bss"  Section 上分配空间，然后在 ".symtab" 段中创建 Symbol，这些 Symbol 名字都是唯一的。

NR_DATA 宏会在预处理阶段被展开

#### 寻找 Hello World

```
  [29] .strtab           STRTAB           0000000000000000  000033a0
       00000000000001e2  0000000000000000           0     0     1

```

33a0 旁边是

```
000033a0  00 53 63 72 74 31 2e 6f  00 5f 5f 61 62 69 5f 74  |.Scrt1.o.__abi_t|
000033b0  61 67 00 63 72 74 73 74  75 66 66 2e 63 00 64 65  |ag.crtstuff.c.de|
000033c0  72 65 67 69 73 74 65 72  5f 74 6d 5f 63 6c 6f 6e  |register_tm_clon|
000033d0  65 73 00 5f 5f 64 6f 5f  67 6c 6f 62 61 6c 5f 64  |es.__do_global_d|
000033e0  74 6f 72 73 5f 61 75 78  00 63 6f 6d 70 6c 65 74  |tors_aux.complet|
000033f0  65 64 2e 30 00 5f 5f 64  6f 5f 67 6c 6f 62 61 6c  |ed.0.__do_global|
00003400  5f 64 74 6f 72 73 5f 61  75 78 5f 66 69 6e 69 5f  |_dtors_aux_fini_|
00003410  61 72 72 61 79 5f 65 6e  74 72 79 00 66 72 61 6d  |array_entry.fram|
00003420  65 5f 64 75 6d 6d 79 00  5f 5f 66 72 61 6d 65 5f  |e_dummy.__frame_|
00003430  64 75 6d 6d 79 5f 69 6e  69 74 5f 61 72 72 61 79  |dummy_init_array|
00003440  5f 65 6e 74 72 79 00 68  65 6c 6c 6f 77 6f 72 6c  |_entry.helloworl|
00003450  64 2e 63 00 5f 5f 46 52  41 4d 45 5f 45 4e 44 5f  |d.c.__FRAME_END_|
00003460  5f 00 5f 44 59 4e 41 4d  49 43 00 5f 5f 47 4e 55  |_._DYNAMIC.__GNU|
00003470  5f 45 48 5f 46 52 41 4d  45 5f 48 44 52 00 5f 47  |_EH_FRAME_HDR._G|
00003480  4c 4f 42 41 4c 5f 4f 46  46 53 45 54 5f 54 41 42  |LOBAL_OFFSET_TAB|
00003490  4c 45 5f 00 5f 5f 6c 69  62 63 5f 73 74 61 72 74  |LE_.__libc_start|
000034a0  5f 6d 61 69 6e 40 47 4c  49 42 43 5f 32 2e 33 34  |_main@GLIBC_2.34|
000034b0  00 5f 49 54 4d 5f 64 65  72 65 67 69 73 74 65 72  |._ITM_deregister|
000034c0  54 4d 43 6c 6f 6e 65 54  61 62 6c 65 00 5f 65 64  |TMCloneTable._ed|
000034d0  61 74 61 00 5f 66 69 6e  69 00 70 72 69 6e 74 66  |ata._fini.printf|
000034e0  40 47 4c 49 42 43 5f 32  2e 32 2e 35 00 5f 5f 64  |@GLIBC_2.2.5.__d|
000034f0  61 74 61 5f 73 74 61 72  74 00 5f 5f 67 6d 6f 6e  |ata_start.__gmon|
00003500  5f 73 74 61 72 74 5f 5f  00 5f 5f 64 73 6f 5f 68  |_start__.__dso_h|
00003510  61 6e 64 6c 65 00 5f 49  4f 5f 73 74 64 69 6e 5f  |andle._IO_stdin_|
00003520  75 73 65 64 00 5f 65 6e  64 00 5f 5f 62 73 73 5f  |used._end.__bss_|
00003530  73 74 61 72 74 00 6d 61  69 6e 00 5f 5f 54 4d 43  |start.main.__TMC|
00003540  5f 45 4e 44 5f 5f 00 5f  49 54 4d 5f 72 65 67 69  |_END__._ITM_regi|
00003550  73 74 65 72 54 4d 43 6c  6f 6e 65 54 61 62 6c 65  |sterTMCloneTable|
00003560  00 5f 5f 63 78 61 5f 66  69 6e 61 6c 69 7a 65 40  |.__cxa_finalize@|
00003570  47 4c 49 42 43 5f 32 2e  32 2e 35 00 5f 69 6e 69  |GLIBC_2.2.5._ini|
00003580  74 00 00 2e 73 79 6d 74  61 62 00 2e 73 74 72 74  |t...symtab..strt|
00003590  61 62 00 2e 73 68 73 74  72 74 61 62 00 2e 69 6e  |ab..shstrtab..in|
000035a0  74 65 72 70 00 2e 6e 6f  74 65 2e 67 6e 75 2e 70  |terp..note.gnu.p|
000035b0  72 6f 70 65 72 74 79 00  2e 6e 6f 74 65 2e 67 6e  |roperty..note.gn|
000035c0  75 2e 62 75 69 6c 64 2d  69 64 00 2e 6e 6f 74 65  |u.build-id..note|
000035d0  2e 41 42 49 2d 74 61 67  00 2e 67 6e 75 2e 68 61  |.ABI-tag..gnu.ha|
000035e0  73 68 00 2e 64 79 6e 73  79 6d 00 2e 64 79 6e 73  |sh..dynsym..dyns|
000035f0  74 72 00 2e 67 6e 75 2e  76 65 72 73 69 6f 6e 00  |tr..gnu.version.|
00003600  2e 67 6e 75 2e 76 65 72  73 69 6f 6e 5f 72 00 2e  |.gnu.version_r..|
00003610  72 65 6c 61 2e 64 79 6e  00 2e 72 65 6c 61 2e 70  |rela.dyn..rela.p|
00003620  6c 74 00 2e 69 6e 69 74  00 2e 70 6c 74 2e 67 6f  |lt..init..plt.go|
00003630  74 00 2e 70 6c 74 2e 73  65 63 00 2e 74 65 78 74  |t..plt.sec..text|
00003640  00 2e 66 69 6e 69 00 2e  72 6f 64 61 74 61 00 2e  |..fini..rodata..|
00003650  65 68 5f 66 72 61 6d 65  5f 68 64 72 00 2e 65 68  |eh_frame_hdr..eh|
00003660  5f 66 72 61 6d 65 00 2e  69 6e 69 74 5f 61 72 72  |_frame..init_arr|
00003670  61 79 00 2e 66 69 6e 69  5f 61 72 72 61 79 00 2e  |ay..fini_array..|
00003680  64 79 6e 61 6d 69 63 00  2e 64 61 74 61 00 2e 62  |dynamic..data..b|
00003690  73 73 00 2e 63 6f 6d 6d  65 6e 74 00 00 00 00 00  |ss..comment.....|
000036a0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
```

hd 的输出中 helloworld 位置如下

```
00002000  01 00 02 00 68 65 6c 6c  6f 20 77 6f 72 6c 64 00  |....hello world.|
```

2000 对应的是 rodata，而不是字符串表

#### 实现 ftrace

在 parse_args 里加入了 r 参数，对应读取 elf. 用此方式读取 elf 时自动启用 ftrace。需要注意的是 ftrace 读取 elf 与当前架构的位宽有关，后续将 32 位 NEMU 改为 64 位时需要修改 ftrace。

下面直接把做第四期 ftrace 时候的笔记复制过来：

> 如果每执行一条指令就去 func 里查找对应的函数显然不太合理，只需要关心函数调用和返回的指令即可
>
> 可以关注所有的跳转指令的目的寄存器，判断是否是函数（有哪些指令可以调用函数？）
>
> 先考虑实现对 jal 的支持。
>
> 可以向 ftrace 函数传入 dnpc，判断跳转到的地方是不是函数。而返回指令可以分析指令中跳转地址-4 的地方是不是函数。（nemu 中实现的 jal 是将 pc+4 存入 rd）。
>
> 实现时发现 存在 iringbuf 中的 instval 与 si 的输出不太对，永远只有低 5 位，是环形缓冲区对于指令值的解码有问题。已修复
>
> 通过向 ftrace 函数传入 ra 的值，当跳转的目的地和 ra 的值一样时鉴定为退出函数。
>
> 对于不使用跳转语句退出函数的情况，比如 ebreak，按照实际情况直接不输出 ret。

修改 /platform/nemu.mk，其中 $(IMAGE).elf 是 elf 的位置

#### 不匹配的函数调用和返回

反汇编结果中 f2 和 f3 的末尾都有两个 ret，f1 和 f0 的末尾仅有一个 ret。每一次函数调用并没有开辟新的栈空间，而是复用了之前开辟的栈空间。

> **Tail recursion** *is defined as a recursive function in which the recursive call is the last statement that is executed by the function. So basically nothing is left to execute after the recursion call.*

ftrace  的输出如下：

```
Welcome to riscv32-NEMU!
For help, type "help"
#1: call: _start at 80000000
#2: call: _trm_init at 80000254
#3: call: main at 800001c8
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f3 at 80000108
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#3: call: f2 at 800000a4
#3: call: f1 at 8000005c
#3: call: f0 at 80000010
#4: call: check at 800001b0
#4: ret:  check at 800001b4 to 80000204
#4: call: check at 800001b0
#4: ret:  check at 800001b4 to 8000021c
#4: call: check at 800001b0
#4: ret:  check at 800001b4 to 80000234
#3: ret:  main at 80000244 to 80000268
```

#### 冗余的符号表

去掉可执行文件中的符号表后， `readelf -s` 仅输出 `.dynsym`，可以执行

去掉目标文件中的符号表后，无法链接。

这是因为

> elf 的符号包括一个 Symbol Table，其中包含一组 Symbol。这些 Symbol 在程序中要么表示定义，要么表示引用，它们的作用是在编译和链接的过程中进行定位和重定位。

#### 如何生成 native 的可执行文件

支持的 ARCH 在 `$(AM_HOME)/scripts/*.mk` 列出，其中包含 native。该 Makefile 包含如下代码

`@g++ -pie -o $(IMAGE) -Wl,--whole-archive $(LINKAGE) -Wl,-no-whole-archive $(LDFLAGS_CXX) -lSDL2 -ldl`

#### 奇怪的错误码

https://www.gnu.org/software/make/manual/html_node/Running.html

> The exit status of `make` is always one of three values:
>
> - `0`
>
>   The exit status is zero if `make` is successful.
> - `2`
>
>   The exit status is two if `make` encounters any errors. It will print messages describing the particular errors.
> - `1`
>
>   The exit status is one if you use the ‘-q’ flag and `make` determines that some target is not already up to date. See [Instead of Executing Recipes](https://www.gnu.org/software/make/manual/html_node/Instead-of-Execution.html).

#### 这是如何实现的

> 框架代码编译到 `native`的时候默认链接到glibc, 我们需要把这些库函数的调用链接到我们编写的klib来进行测试. 我们可以通过在 `abstract-machine/klib/include/klib.h` 中通过定义宏 `__NATIVE_USE_KLIB__`来把库函数链接到klib. 如果不定义这个宏, 库函数将会链接到glibc, 可以作为正确的参考实现来进行对比.

klib 文件的代码中会判断是否定义了这个宏，并用 `#if` 把 klib 的实现代码包起来。

系统的 `/usr/include` 目录下包含了 glibc 的头文件

klib 的 build 目录下包含生成的静态库文件 `xxx.a`，

#### 测试你的klib

使用时应该先用 glibc 测试我的测试代码，再用测试代码测试 klib。printf 暂未实现，因此目前用测试代码测 klib 会因为 main 中调用了 printf 而报错。目前相当于是搭了一个测试框架，写了两个测例在 klib-tests 目录下，以后有需要再来补充。

#### DiffTest

需要在 nemu 中实现 difftest 比较寄存器的函数。

实现之后运行之前未通过的 mul-longlong 测例，在 `800000ac:	02fc97b3          	mulh	a5,s9,a5` 出错。

尝试了在 src1 和 src2 前面加上（long long）进行乘法运算，以及在乘法中乘上 1ll，均没效果，最后将 src1 和 src2 符号位扩展到 64 位进行乘法，结果正确。

#### Spike 不支持不对齐的访存

待填坑

> RISC-V作为一个RISC架构, 通常是不支持不对齐访存的, 在Spike中执行一条地址不对齐的访存指令将会抛出异常, 让PC跳转到 `0`. 但NEMU为了简化, 没有实现这样的功能, 因此如果让NEMU和Spike同时执行这样的指令, DiffTest将会报错. 不过这很可能是你的软件实现(例如klib)有问题, 请检查并修改相关代码.

2024.01.10：

感觉这段话有语病阿，看不懂“不过”这个词的上下文到底有没有关系

开启 difftest spike，为 NEMU 增加对齐访存之后跑 unalign 的测例会在 `80000078:	00544783          	lbu	a5,5(s0)` 处 abort，并且此时 s0 为 `s0: 80000134`

#### 一键回归测试

全部通过

### 输入输出

#### 运行Hello World

关了trace，直接运行就可以看见Hello, AbstractMachine!

需要注意：

> 设备和DiffTest
>
> 在状态机视角下, 执行一条输入指令会让状态机的状态转移变得不唯一, 新状态取决于设备的状态. 由于NEMU中设备的行为是我们自定义的, 与REF中的标准设备的行为不完全一样 (例如NEMU中的串口总是就绪的, 但QEMU中的串口也许并不是这样), 这导致**在NEMU中执行输入指令的结果会和REF有所不同**. 为了使得DiffTest可以正常工作, 框架代码在访问设备的过程中调用了 `difftest_skip_ref()`函数 (见 `nemu/include/device/map.h`中定义的 `find_mapid_by_addr()`函数)来跳过与REF的检查.

#### 实现 printf

实现 vsprintf，然后

```c
int printf(const char *fmt, ...) {
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  int ret = vsprintf(buf, fmt, args);
  va_end(args);
  for (int i = 0; i < ret; i++) {
    putch(buf[i]);
  }
  return ret;
  panic("Not implemented");
}
```

buf 开的 1024，

怎么测试呢？后面实现IOE时会用到printf，到时候就知道实现有没有问题了。实现 IOE 的 uptime 之后发现，`printf("%d-%d-%d %02d:%02d:%02d GMT (", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second);` 的输出是形如 1900-- 02d:02d:02d GMT (1 second). 的，在解析了第一个 %d 之后后面的 %d 都没有正确解析。这说明 printf 的实现有问题。经检查发现 printf 在 %d 对应的值为 0 时没有输出，加一个判断即可。目前还没有实现对 %02d 的支持

此外，讲义中提到不要在 native 链接到 klib 的时候运行 IOE 相关的测试，因此我们还需要将 native 链接到 glibc

> 我们可以通过在 `abstract-machine/klib/include/klib.h` 中通过定义宏 `__NATIVE_USE_KLIB__`来把库函数链接到klib. 如果不定义这个宏, 库函数将会链接到glibc

#### 实现 IOE

```c
void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uptime->us = inl(RTC_ADDR) + (inl(RTC_ADDR+4) << 32);
}
```

#### 看看 NEMU 跑多快

ftrace 被我设置为了如果开启 ITRACE 就自动开启 FTRACE

跑 dhrystone 的时候报了浮点异常，去nemu的menuconfig里开启 rv32e support，还是这样。开着这个选项时无法difftest，将其关闭随后用 difftest 进行 debug，difftest 没有报错，Dhrystone 会在输出一行 Finished in 0ms 后报浮点异常.

检查发现，这几个 benchmark 从 uptime 中读出的时间始终为 0，但 am test 里的 rtc 又没有问题。

经检查，下面这种写法就不会出现问题

```c
  // uint64_t clk = 0;
  // clk = (((uint64_t)inl(RTC_ADDR + 4)) << 32ull) + inl(RTC_ADDR);
  // uptime->us = clk;
```

而下面的写法会有错：

```c
uptime->us = (uint64_t)inl(RTC_ADDR) + (((uint64_t)inl(RTC_ADDR+4)) << 32ull);
```

经过尝试发现，必须先读取高 32 位的值，否则运行 benchmark 时 end time 读出来时钟为0,从而会导致 总时间为 0-0=0,发生除0异常

coremark 得分：

> CoreMark PASS       416 Marks
> vs. 100000 Marks (i7-7700K @ 4.20GHz)

#### RTFSC 了解一切细节

做第四期的时候我没有发现这个问题，但刚才上面读取寄存器的顺序可能就是这个坑，第四期时我是先读取的高位，这次一开始我写的先读低32位就挂了.

RTFSC，在调用 inl 时，模拟器会通过 map_read 访问设备，会触发相应的回调函数。时钟对应的回调函数是

```c
static void rtc_io_handler(uint32_t offset, int len, bool is_write) {
  assert(offset == 0 || offset == 4);
  if (!is_write && offset == 4) {
    uint64_t us = get_time();
    rtc_port_base[0] = (uint32_t)us;
    rtc_port_base[1] = us >> 32;
  }
}
```

根据这个函数，当读取了 RTC_ADDR + 4 处后，会调用 get_time 来为下一次读取准备好数据。

这些函数的调用关系是 uptime_ms->ioe_read ->__am_timer_uptime-> inl(RTC_ADDR) && inl(RTC_ADDR+4)

```c
static inline uint32_t inl(uintptr_t addr) { return *(volatile uint32_t *)addr; }
```

这个 inl 直接访问 addr 处并取回数据。

开启 ftrace，先读低32位在读高32位运行dhrystone 能够正常运行且没有报错？？？

ftrace 显示的调用过程是

```c
#6: call: ioe_read at 80000cc8
#6: call: __am_timer_uptime at 80000ce8
#6: ret:  ioe_read at 80000cfc to 80000524
```

```c
void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  //uptime->us = (((uint64_t)inl(RTC_ADDR+4)) << 32ull) + inl(RTC_ADDR);
  uptime->us = inl(RTC_ADDR); //+ (((uint64_t)inl(RTC_ADDR+4)) << 32ull);
  uptime->us += (uint64_t)((uint64_t)inl(RTC_ADDR+4) << 32ull);
}
```

改成先读高位再试一次，即改成注释那样，再跑一次没有问题，改成下面这样再跑一次：

```c
uptime->us = (uint64_t)inl(RTC_ADDR) + (((uint64_t)inl(RTC_ADDR+4)) << 32ull);
```

又能跑了

关闭 ftrace 再跑，爆了，说明这个 bug 还和 trace 有关。

如果同时开启 mtrace，在跑了一段时间以后终端就会卡住。上面的“打开ftrace”都是关闭 mtrace 跑的。

对比了一下第四期时的 benchmark 得分，dhrystone 的分很低只有16分，但 microbench 和 coremark 都小幅提高（25%）

```
Dhrystone PASS         16 Marks
                   vs. 100000 Marks (i7-7700K @ 4.20GHz)
```

第四期时 dhrystone 能跑到 130 分.

换成 native 跑的得分是正常的 125842 分，复用第四期代码跑仍然只有25分。

修改代码，让读取低 4 位时也能触发回调函数，得分仍然是 25 分。

#### dtrace

略

#### 实现IOE（2）键盘

review: 按下是通码，松开是断

> \#键盘#
>
> 键盘中含有名为键盘编码器的芯片（如 i8048），用于检测按键的按下与释放，并向键盘控制器发送扫描码。
>
> 每个键被按下时对应的扫描码被称为通码（make code），弹起时的扫描码是断码（break code）。每个键都有唯一的通码和断码。
>
> 现行的扫描码有三种，所有现代键盘默认使用第二种扫描码。在第二套扫描码中，断码是在通码前多发送一帧 0xF0，共两帧进行传输，例如 `W` 键的通码为 0x1D，则其断码为 0xF0 0x1D。
>
> 键盘控制器（如 i8042）位于南桥芯片上，不在键盘内部。它接收键盘编码器发送来的第二种扫描码，将其解码为第一套扫描码后保存到自己的寄存器中。
>
> i8042 有 4 个 8 bits 寄存器，其中输入缓冲器和输出缓冲器共用 0x60 端口，状态寄存器和控制寄存器共用 0x64 处的端口。在 CPU 从 i8042 读入数据时，这两个端口分别对应输出缓冲区和状态寄存器；而在 CPU 向 i8042 写入数据时，这两个端口对应输入缓冲区和控制寄存器。
>
> 第一种扫描码中大部分通码和断码都是 1 字节，长度超过 1 字节的扫描码都是以 0xE0 开头，Pause Brk 键例外，它以 0xE1 开头。在第一种扫描码中，断码等于通码在数值上加上 0x80，并且通码的最低字节的最高位均为 0。因此，我们可以通过该位的值来判断按键的按下和释放

AM 中读取的 keycode  是按照 amdev.h 中的映射来的。直接通过 inb 从 KBD_ADDR 读入 kbd->keycode。但如何判断断码和通码？讲义里说 keycode 是断码，但按下和释放的时候都有 keycode。

讲义里说注册了 4 字节的端口，但只有最低字节是按键对应的扫描码。判断读入的4字节数据与 KEYDOWN_MASK 的与值是否为 0 以判断键盘按下与释放

#### 实现IOE3 VGA

nemu/src/device/vga.c 在 NEMU 层面定义了显示器的大小。vgactl 的高 2 个字节是 width，低 2 个字节是 height。用 inw 从 VGACTL_ADDR 读出数据即可。

还有一个用于同步的 sync，对应 SYNC_ADDR=VGACTL_ADDR+4 处的 MMIO，即 vgactl_port_base[1]

#### 实现IOE(4)

修改 fbdraw，把 pixels 中的东西画到 framebuffer 上，在 (x,y) 处画一个 wxh 的矩形

```c
for (int i = 0; i < ctl->h /*&& i + ctl->y < h*/; i++) {
  for (int j = 0; j < ctl->w /*&& j + ctl->x < w*/; j++) {
    int t = (i + ctl->y) * w + j + ctl->x;
    fb[t] = *(pixels + i * ctl->w + j);
  }
}
```

### 冯诺依曼计算机系统

#### 游戏是如何运行的

> 请你以打字小游戏为例, 结合"程序在计算机上运行"的两个视角, 来剖析打字小游戏究竟是如何在计算机上运行的. 具体地, 当你按下一个字母并命中的时候, 整个计算机系统(NEMU, ISA, AM, 运行时环境, 程序) 是如何协同工作, 从而让打字小游戏实现出"命中"的游戏效果?
>
> 打字小游戏只有不到200行的简单代码, 非常适合大家RTFSC. 如果你发现自己难以理解打字小游戏的具体行为, 你需要给自己敲响警钟了: 你在做PA的时候很有可能只关注怎么把必做内容的代码写对, 而不去思考这些代码和计算机系统的关系. 从ICS和PA的角度来说, 这种做法是不及格的, 而且很快你就会吃苦头了.

main 函数中有一个主循环不断检测按下的键，调用 io_read 读取 am 键盘获取按键信息。

程序通过 check_hit 函数检查范围内的字符是否有与按下的字符一致的，并执行对应操作（例如 miss++）。game_logic_update 函数负责刷新字符及其位置，render 负责向 FB 写入数据，以及让字符拥有对应的颜色。这个过程中 NEMU 会模拟指令的执行以及模拟时钟、画布等设备

#### 必答题

编译与链接：

> 在 `nemu/include/cpu/ifetch.h`中, 你会看到由 `static inline`开头定义的 `inst_fetch()`函数. 分别尝试去掉 `static`, 去掉 `inline`或去掉两者, 然后重新进行编译, 你可能会看到发生错误. 请分别解释为什么这些错误会发生/不发生? 你有办法证明你的想法吗?

去掉 static 没有报错，去掉 inline 也没有报错，去掉二者则会报错：

```
 /usr/bin/ld: /home/yjmstr/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/engine/interpreter/hostcall.o: in function `inst_fetch':
hostcall.c:(.text+0x0): multiple definition of `inst_fetch'; /home/yjmstr/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/isa/riscv32/inst.o:inst.c:(.text+0xeb0): first defined here
collect2: error: ld returned 1 exit status
```

static 关键字可以使函数变为静态函数，仅声明该函数的文件可以访问静态函数，因此不同文件中可以存在同名的 static 函数。inline 是建议编译器将函数内联，编译器最终不一定会这么做。注意到这个函数是定义在头文件里的，多处引用该头文件的话如果没加 static 的话 inline 不内联就会重复定义。对于头文件中定义的函数，其要被外部使用则不会内联，得加 static inline 才能成功内联。

去掉 static 不会报错，可能是因为编译器将其内联了。去掉 inline 不报错是因为引用该头文件的 c 文件都创建了该函数的 static 副本，static 允许不同文件中的同名函数。

> 在 `nemu/include/common.h`中添加一行 `volatile static int dummy;` 然后重新编译NEMU. 请问重新编译后的NEMU含有多少个 `dummy`变量的实体? 你是如何得到这个结果的?

`nm build/riscv32-nemu-interpreter | grep dummy` ，34 个。nm 可以从对象文件中读取符号

> 添加上题中的代码后, 再在 `nemu/include/debug.h`中添加一行 `volatile static int dummy;` 然后重新编译NEMU. 请问此时的NEMU含有多少个 `dummy`变量的实体? 与上题中 `dummy`变量实体数目进行比较, 并解释本题的结果.

还是 34 个。去掉 debug.h 中添加的代码并把 common.h 中的 volatile 去掉，则会报错 定义了未使用的变量。y

> 修改添加的代码, 为两处 `dummy`变量进行初始化:`volatile static int dummy = 0;` 然后重新编译NEMU. 你发现了什么问题? 为什么之前没有出现这样的问题? (回答完本题后可以删除添加的代码.)

此时会报错 `error: redefinition of ‘dummy’` 。STFW，C 语言的 static 变量在编译时初始化，C++ 的 static 变量在运行时初始化，如果在头文件中定义 static 变量，其会在所有包括该头文件的源文件中都进行一次初始化。如果仅在 common.h 中进行初始化则不会报错。这涉及到 C 语言的链接决议规则：

链接器的工作分为两个阶段：符号解析和重定位。对于编译器来说，函数名和变量名都可以称为符号。符号可以分为强符号和弱符号，对于 C/C++，函数名称和初始化了的变量的名称为强符号，未初始化的变量名为弱符号。

- 链接器不允许强符号被多次定义
- 链接器选择符号时，一强多弱的同名符号选择强的那个
- 全是同名弱符号选择占空间最大的那个

上述例子中，如果同时在两个头文件中进行初始化，就会有两个名为dummy的强符号，这是链接器不允许的。之前没有出现这个问题是因为之前dummy都是弱符号，链接器只会选取占空间最大的那个。

> **了解Makefile**
>
> 请描述你在 `am-kernels/kernels/hello/`目录下敲入 `make ARCH=$ISA-nemu` 后, `make`程序如何组织.c和.h文件, 最终生成可执行文件 `am-kernels/kernels/hello/build/hello-$ISA-nemu.elf`. (这个问题包括两个方面:`Makefile`的工作方式和编译链接的过程.) 关于 `Makefile`工作方式的提示:
>
> - `Makefile`中使用了变量, 包含文件等特性
> - `Makefile`运用并重写了一些implicit rules
> - 在 `man make`中搜索 `-n`选项, 也许会对你有帮助
> - RTFM

hello 文件夹中的 makefile 包含了 AM_HOME 目录下的 makefile，后者定义了 `INC_PATH += $(WORK_DIR)/include $(addsuffix /include/, $(addprefix $(AM_HOME)/, $(LIBS)))`，编译器在编译时将会在 INC_PATH 下寻找头文件，包括 am 和 klib 的头文件（由 LIBS 指定）。

此外还定义了 ARCH_H 变量来指定 am 的 `arch/$(ARCH).h`

第二点，隐含规则例如 AS、CC 等对应的规则在 AMHOME 下的 makefile 中进行了重写，将其改为使用对应架构的交叉编译工具链。

第三点，在 man 中可以通过 `/` 进行查找，`/` 后面可以跟正则表达式。查找到 -n 选项为：

> -n, --just-print, --dry-run, --recon
> Print the commands that would be executed, but do not execute them
> (except in certain circumstances).

可以用来看变量展开以后的命令

得到的输出如下：

```
# Building hello-image [riscv32e-nemu]
make -s -C /home/yjmstr/ysyx-workbench/abstract-machine/am archive
# Building am-archive [riscv32e-nemu]
mkdir -p /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/ && echo + CC src/platform/nemu/trm.c
riscv64-linux-gnu-gcc -std=gnu11 -O2 -MMD -Wall -Werror -I/home/yjmstr/ysyx-workbench/abstract-machine/am/src -I/home/yjmstr/ysyx-workbench/abstract-machine/am/include -I/home/yjmstr/ysyx-workbench/abstract-machine/am/include/ -I/home/yjmstr/ysyx-workbench/abstract-machine/klib/include/ -D__ISA__=\"riscv32e\" -D__ISA_RISCV32E__ -D__ARCH__=riscv32e-nemu -D__ARCH_RISCV32E_NEMU -D__PLATFORM__=nemu -D__PLATFORM_NEMU -DARCH_H=\"arch/riscv.h\" -fno-asynchronous-unwind-tables -fno-builtin -fno-stack-protector -Wno-main -U_FORTIFY_SOURCE -fno-pic -march=rv64g -mcmodel=medany -mstrict-align -march=rv32em_zicsr -mabi=ilp32e   -static -fdata-sections -ffunction-sections -DMAINARGS=\"\" -I/home/yjmstr/ysyx-workbench/abstract-machine/am/src/platform/nemu/include -DISA_H=\"riscv/riscv.h\" -c -o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/trm.o /home/yjmstr/ysyx-workbench/abstract-machine/am/src/platform/nemu/trm.c
echo + AR "->" build/am-riscv32e-nemu.a
riscv64-linux-gnu-ar rcs /home/yjmstr/ysyx-workbench/abstract-machine/am/build/am-riscv32e-nemu.a /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/trm.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/ioe/ioe.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/ioe/timer.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/ioe/input.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/ioe/gpu.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/ioe/audio.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/ioe/disk.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/platform/nemu/mpe.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/riscv/nemu/start.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/riscv/nemu/cte.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/riscv/nemu/trap.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/riscv32e-nemu/src/riscv/nemu/vme.o
make -s -C /home/yjmstr/ysyx-workbench/abstract-machine/klib archive
# Building klib-archive [riscv32e-nemu]
echo + LD "->" build/hello-riscv32e-nemu.elf
riscv64-linux-gnu-ld -z noexecstack -melf64lriscv -T /home/yjmstr/ysyx-workbench/abstract-machine/scripts/linker.ld --defsym=_pmem_start=0x80000000 --defsym=_entry_offset=0x0 --gc-sections -e _start -melf32lriscv                      -o /home/yjmstr/ysyx-workbench/am-kernels/kernels/hello/build/hello-riscv32e-nemu.elf --start-group /home/yjmstr/ysyx-workbench/am-kernels/kernels/hello/build/riscv32e-nemu/hello.o /home/yjmstr/ysyx-workbench/abstract-machine/am/build/am-riscv32e-nemu.a /home/yjmstr/ysyx-workbench/abstract-machine/klib/build/klib-riscv32e-nemu.a --end-group
echo \# Creating image [riscv32e-nemu]
riscv64-linux-gnu-objdump -d /home/yjmstr/ysyx-workbench/am-kernels/kernels/hello/build/hello-riscv32e-nemu.elf > /home/yjmstr/ysyx-workbench/am-kernels/kernels/hello/build/hello-riscv32e-nemu.txt
echo + OBJCOPY "->" build/hello-riscv32e-nemu.bin
riscv64-linux-gnu-objcopy -S --set-section-flags .bss=alloc,contents -O binary /home/yjmstr/ysyx-workbench/am-kernels/kernels/hello/build/hello-riscv32e-nemu.elf /home/yjmstr/ysyx-workbench/am-kernels/kernels/hello/build/hello-riscv32e-nemu.bin
```

am 和 klib 作为静态库被链接进最终的文件

编译出的 elf 文件通过 objdump -d 去掉符号表之类的得到 bin 文件，并输出到 txt 中

## 最简单的处理器

支持 addi 和 ebreak，参考一生一芯视频课提到的 YPC （第六节）的写法

## RV32E NPC

### 搭建面向riscv32e-npc的运行时环境

#### 从命令行中读入NPC需要执行的程序

在 verilator 外层的 C++ 文件中实现 load_img 函数即可，读入指定位置的 img 到 mem 数组中。

#### 一键编译并在 NPC 上运行 AM 程序

修改 verilator 外层的 C++ 文件，令其从 argv[1] 读入文件名，然后在 riscv64-npc.mk 中添加 run 目标。

要实现一键编译，首先要解决 firtool 在 chisel 使用了 blackbox 后会在 top.v 中生成导致编译失败的 blackbox 文件名的问题。ysyx 助教给出的方案是为 firtool 添加 `--split-verilog` 参数，但我目前还不知道应该在哪添加。

firtool 位于 `$NPC_HOME/utils`，将其加入 PATH 后可以在命令行中直接 firtool --help 查看使用说明。查看目录下的 makefile，没有发现哪个地方调用了 firtool

上网搜了下 mill 的用法，在 makefile 里执行 make help 看见了 `--split-verilog` 选项，直接加在 makefile  的 verilog 目标后面就行。但这样除了 dpi-c，生成的都是 sv 文件，make sim 会报错找不到 top，需要对 makefile 中的 VSRCS 变量进行修改，令其包含 .sv 后缀的文件。

关于修改 makefile 来生成所需的 bin 文件并一键仿真，参考第四期的实验记录。不过当时我修改的是 riscv64-npc.mk，这次直接对 npc.mk 进行修改，方便跨架构运行。

目前 npc.mk 中部分代码如下：

```makefile
IMAGE_SPLIT = $(subst -, ,$(basename $(notdir $(IMAGE))))
BINNAME		= $(word 1,$(IMAGE_SPLIT))

run: 
	$(MAKE) -C /home/yjmstr/ysyx-workbench/am-kernels/tests/cpu-tests ARCH=$(ARCH) ALL=$(BINNAME)
	$(MAKE) -C $(NPC_HOME) ISA=$(ISA) run IMG=$(IMAGE).bin
```

$NPC_HOME 下的 makefile 中 相关的目标如下：

```makefile
verilog: clean
	@echo make verilog
	$(call git_commit, "generate verilog")
	mill -i __.test.runMain Elaborate -td $(BUILD_DIR) --split-verilog 

$(VSRCS): $(CSRCS) verilog

sim: $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE) 
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	$(VERILATOR) $(VERILATOR_CFLAGS) \
	--top-module $(TOPNAME) $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE) \
	$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
	--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

run: sim
	@$(BIN) $(IMG)

```

现在能够稳定一键仿真了。

#### 在 NPC 上运行 dummy 程序

auipc，lui，jal，jalr，sw（可选）

现在使用 ListLookup 的方式来方便地添加指令

为了方便迁移到 64 位，可以创建 chisel 的全局配置文件 Configs.scala ，在其中定义处理器的位宽等。目前仅在其中定义 XLEN 和 RESET_VECTOR。

ALU 参与运算的两个数据进行选择时，JALR 指令比较复杂

dummy 会在 addr = 0x8000002c 处无限循环，这是因为 npc 的 halt 函数被实现为了死循环，需要查看波形来确定 npc 是否进入了 halt 函数。

现在在 cpu-tests 目录下编译 npc 时加入 vcd=1 即可生成波形

#### 实现riscv32e-npc中的halt()函数

用 asm("ebreak") 加入指令后再次编译，发现不生成 .bin 文件了，只生成 dummy.d 和 dummy.o，查看 npc.mk 发现之前把 image 相关的给注释掉了，不清楚之前为什么能跑起来。

修改后成功 halt

#### 为NPC实现HIT GOOD/BAD TRAP

先看看 nemu 是怎么实现的，nemu/src/cpu/cpu-exec.c 中会在 NEMU_END 和 NEMU_ABORT 时检查 halt_ret 是否为 0，若不为 0 即 HIT BAD TRAP

nemu 的 trm.c 中通过 NEMU_TRAP

```c
asm volatile("mv a0, %0; ebreak" : :"r"(code))
```

来传递参数给 a0 寄存器

后面一行的 while 不能删，不然会报错 void 函数有返回值。

原先 npc 的 ebreak 的实现方式是通过 dpi-c 直接执行 exit(0)，这样会导致进程直接退出，无法进入 GOOD/BAD TRAP 的判断，应该在 npc 的 sim_main.cpp 中加入 npc_state 变量进行判断，类似 nemu 那样在执行每一条指令之前判断处理器的状态。

### 为 npc 搭建基础设施

#### 为 npc 搭建 sdb

把 Log 系统迁移过来了，但目前还没为 npc 搭建 kconfig

#### 为 npc 搭建 trace

在 makefile 里链接了 llvm 之后，提示 init_disasm 和 disassemble 函数未定义，暂时先注释掉相关代码，之后来修。

> 2023.12.17 update: llvm 的函数是用 gcc 编译的 c 语言实现的，仿真文件是 cpp，用的是 g++ 生成的 .o 文件，其和 gcc 生成的 .o 文件不能同时链接，要在 cpp 文件里声明时加上 extern "C"

我实现的 ftrace 要用到 dnpc， 把 dnpc 信号拉到顶。注意这里指的并不是 ALU 算出来的 dnpc，而是下一个 pc 的值（不管是 snpc 还是 dnpc，都输出。而 alu 在 使用 snpc 时输出的 dnpc 为 0）

实际上可以利用 verilator 读两次 pc，第一次在上升沿电路状态更新之前读取，此时读出的即为 pc，第二次在上升沿电路状态更新之后读取，此时读出的即为下一个周期的pc。instval也类似，应该和 pc 同时读取。而寄存器值应该在当前周期结束后读取，即上升沿电路状态更新之后再读取寄存器。这样 ftrace 的输出结果就和 nemu 一致了。

#### 为 npc 搭建 difftest

> 为了方便实现DiffTest, 我们在DUT和REF之间定义了如下的一组API:
>
> ```c
> // 在DUT host memory的`buf`和REF guest memory的`addr`之间拷贝`n`字节,
> // `direction`指定拷贝的方向, `DIFFTEST_TO_DUT`表示往DUT拷贝, `DIFFTEST_TO_REF`表示往REF拷贝
> void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction);
> // `direction`为`DIFFTEST_TO_DUT`时, 获取REF的寄存器状态到`dut`;
> // `direction`为`DIFFTEST_TO_REF`时, 设置REF的寄存器状态为`dut`;
> void difftest_regcpy(void *dut, bool direction);
> // 让REF执行`n`条指令
> void difftest_exec(uint64_t n);
> // 初始化REF的DiffTest功能
> void difftest_init();
> ```
>
> 其中寄存器状态 `dut`要求寄存器的成员按照某种顺序排列, 若未按要求顺序排列, `difftest_regcpy()`的行为是未定义的(这样就把锅甩给你们了^_^). REF需要实现这些API, DUT会使用这些API来进行DiffTest. 在这里, DUT和REF分别是NEMU和其它模拟器.

在实现了相关 API 之后修改 NEMU 的 menuconfig，重新编译时报错：` src/cpu/cpu-exec.c:33:13: error: ‘CONFIG_ITRACE_RINGBUFFER_SIZE’ undeclared here (not in a function)`，此时注意到 menuconfig 中相关的配置选项都消失了。涉及到的代码是iringbuffer 的结构体定义，在定义的两头加上 ifdef CONFIG_ITRACE 即可。

按照nemu中的dut写法会报错，`invalid conversion from ‘void*’ to ‘void (*)(uint64_t)’ {aka ‘void (*)(long unsigned int)’} [-fpermissive]`，这是因为g++不支持隐式转换具有不同参数的 void 类型函数指针，而gcc可以。

动态链接 nemu 时报错：`==14526==ASan runtime does not come first in initial library list; you should either link runtime to your application or manually preload it with LD_PRELOAD.` 临时的解决方案是编译 nemu 时取消选中 asan 选项

现在 difftest 的开关是用一个全局变量定义的。且目前 nemu 没有实现对齐访存，如果 npc 实现了 4 字节对齐会导致 difftest 不一致。

### 实现RV32E指令集

在 instr.scala 里把指令的模式串先敲进去

#### **硬件如何区分有符号数和无符号数**?

```
test.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <fun1>:
   0:	00b50533          	add	a0,a0,a1
   4:	00008067          	ret

00000008 <fun2>:
   8:	00b50533          	add	a0,a0,a1
   c:	00008067          	ret
```

没有区别

#### 实现访存

实现访存指令时，按照讲义上的 verilog 代码实现 DPI-C MEM 编译时会报错：Procedural assignment to wire, perhaps intended var (IEEE 1800-2017 6.5)，STFW 得知 wire 类型的变量不能放在 always 语句块中赋值，改成 reg 可以修复这一问题，但不知道有没有其它影响，目前改成了 reg。

上面的问题改好以后重新跑仿真会段错误，用 Log 调试发现在第一个周期（属于 reset 期间）的第一个 eval() 出现了段错误

```c++
static void single_cycle() {
  if (npc_state != NPC_RUN) return;
  char *p = logbuf;
	contextp->timeInc(1);
  topp->clock = 0;
  Log("我没问题");
  topp->eval();
  Log("我没问题"); //-> 段错误
  ...
}
```

尝试在 chisel 中进行输出调试，首先看取指令，现在取指令是由 IFU 调用 pmem_read 函数实现的，

```verilog
module DPIC_IFU(valid, pc, inst);
  input valid;
  input [31:0] pc;
  output reg [31:0] inst;
  import "DPI-C" function void pmem_read(
    input int raddr, output int rdata);
  always @(*) begin
    if (valid) begin 
      pmem_read(pc, inst);
    end else begin
      inst = 0;
    end
  end
endmodule
```

reset 期间 IFU 收到的 addr 为 0，在取指时减去基地址会导致数组越界。为访存的 C 函数添加 assert 解决，并为 reset 期间的行为增加特判：

```
wireinst := Mux(reset, 0.U, InstFetcher.io.inst)
```

此外还要为 IFU 添加 valid 信号，在 reset 期间 valid 信号始终为 0,

在 listlookup 的 List 中加入了 MEM_SEXT 系列信号，该信号用于表示 ALU 的计算结果要保留几位，以及要对几位数据进行符号位扩展。

目前支持的访存指令要么是读指令，要么是写指令，因此可以对讲义中给出的访存部分 verilog 进行修改，当 wen 为 0 且 valid 为 1 即为 读，否则 valid 为 1 为写

在Chisel中，如果Fill函数的第一个参数为0，它将返回一个全为0的硬件节点，其位宽由第二个参数指定。例如，Fill(0, myUInt)将返回一个与myUInt具有相同位宽的全为0的硬件节点。这种用法通常用于在Chisel中创建一个全为0的硬件节点，而不是进行符号位扩展。

跑测例 sum 的时候发现 bne 在该跳转的时候没有跳转 ，经检查发现是参与比较的两个数错了，比较的是 rs1v 和 rs2v 两个寄存器值，修改后 HIT GOOD TRAP。

**注意：目前访存相关函数没有进行地址对齐（NEMU也没有），如果进行地址对齐，unalign 测例会无法通过**。如果要地址对齐，那么 NEMU 的相应实现也该进行地址对齐

#### 修改 makefile 以修复文件名错误

一键仿真跑 bubble-sort 时会有问题，`make[2]: *** No rule to make target 'Makefile.bubble', needed by 'all'.  Stop.`，但是将 run 目标的两条 make 命令手动分开执行没有问题，推测是因为文件名中带有 `-` 导致的。一键仿真的相关代码如下所示：

```makefile
run: image
	$(MAKE) -C /home/yjmstr/ysyx-workbench/am-kernels/tests/cpu-tests ARCH=$(ARCH) ALL="$(BINNAME)"
	$(MAKE) -C $(NPC_HOME) ISA=$(ISA) run IMG=$(IMAGE).bin
```

```sh
# 运行仿真的命令（在 cpu-tests 目录下）
make ARCH=riscv32e-npc ALL=bubble-sort run
```

经检查发现这个问题在 add-longlong 也存在，不过 add-longlong 会直接用 Makefile.add，因此没有报错

对 npc.mk 进行修改，修改后如下：

```makefile
IMAGE_NAME = $(basename $(notdir $(IMAGE)))
BINNAME		= $(word 1,$(IMAGE_NAME))
```

但这样生成的 Makefile 文件名会变为 Makefile.bubble-sort-riscv32e-npc，与所需的 Makefile.bubble-sort 不符

可以用 patsubst 函数去掉指定后缀

`$(patsubst pattern,replacement,text)`，例如，如果想去掉文件名中的 .txt 后缀，可以这样：

```makefile
FILE = example.txt
FILE_WITHOUT_SUFFIX = $(patsubst %.txt,%,$(FILE))
```

那么修改之后的语句是

```makefile
BINNAME = $(patsubst %-$(ARCH), %, $(IMAGE_NAME))
```

#### 用 Valgrind 修复段错误

在跑 load-store 测例时 npc 的 ftrace 报错，找不到 elf 文件，但是 build 目录下有该文件，bin、elf、txt 都在，查看 strerror(errno) 得到的结果是文件或目录不存在, matrix-mul，quick-sort 也存在这个问题

**如果不用 make 一键仿真，而是先用 Verilator 编译出可执行文件，再通过参数传递 img 的路径，就不会报错**

把 ftrace 关了（在 npc 的 init_monitor 函数里不调用 set_ftrace_enable），报错信息就变成了段错误

```shell
Top: malloc.c:2617: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
make[2]: *** [Makefile:82: run] Aborted (core dumped)
make[1]: *** [/home/yjmstr/ysyx-workbench/abstract-machine/scripts/platform/npc.mk:30: run] Error 2
 load-store
```

用 Valgrind 进行检查，首先在 strcat 检测到了 `Conditional jump or move depends on uninitialised value(s)`，STFW 得知可能是有内存未初始化。检查以后发现下面这段代码有问题：

```c
	// img_file 和 elf_file 一开始都是 static char * img_file = NULL 这样的 
	img_file = argv[1];
  	elf_file = (char *)malloc(strlen(img_file));
  	memcpy(elf_file, img_file, strlen(img_file)-3);
  	strcat(elf_file, "elf");
```

给elf_file 分配的内存是 strlen(img_file)，这会导致最后一个 '\0' 存到不应该存的地方去。如果分配 strlen(img_file)+1 再进行一键仿真就不会报错了，但是这解释不了为什么之前手动输入参数运行不会报错，而一键仿真时会报错。用 Valgrind 跑测例也是手动传入参数再运行。

修改之后 strcat 处仍然报相同的错误，用 memset 对分配的内存进行初始化后仍报同样的错误

```c
  img_file = argv[1];
  elf_file = (char *)malloc(strlen(img_file)+1);
  memset(elf_file, 0, sizeof(elf_file));
  memcpy(elf_file, img_file, strlen(img_file)-3);
  strcat(elf_file, "elf");
```

```sh
==64032== Memcheck, a memory error detector
==64032== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==64032== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==64032== Command: /home/yjmstr/ysyx-workbench/npc/build/Top build/load-store-riscv32e-npc.bin
==64032== 
==64032== Conditional jump or move depends on uninitialised value(s)
==64032==    at 0x8D58947: strcat (vg_replace_strmem.c:333)
==64032==    by 0x114574: sim_main(int, char**) (in /home/yjmstr/ysyx-workbench/npc/build/Top)
==64032==    by 0x111EA2: main (in /home/yjmstr/ysyx-workbench/npc/build/Top)
==64032== 
```

#### 用 yosys-sta 综合

样例包含一个 sdc 文件和 verilog 文件，STFW 得知 SDC 文件为设计约束文件，我的 npc 目前没有 sdc 文件，

### 设备和输入输出

#### 在NPC中运行超级玛丽（为NPC添加串口和时钟）

首先是时钟，修改 npc 的 pmem_read 函数之后还要在 am 一侧添加相应的代码。在 platform 文件夹中新建一个 npc 文件夹，并添加 npc.h，在其中定义 RTC_ADDR 等宏并修改 npc.mk 将其添加到 include path 中。此外，还需要 `CFLAGS  += -DISA_H=\"riscv/riscv.h\"`，这个可以放在 scripts 文件夹下 riscv32e-npc 的脚本。

都改完以后发现 sim_main.cpp 里还是要重新定义一下 RTC_ADDR 在哪，am 定义的那个头文件只能在 am 里用..

跑 rtc test 的时候发现 pc 跑飞了

```
[/home/yjmstr/ysyx-workbench/npc/sim_main.cpp:222 pmem_write] dtrace: pc = 0x80001090 serial wdata = 111, wmask = 1
difftest: reg #2 = sp err at pc: 0x80200634
difftest: ref_r->gpr[2] == 0x8009cfb0
$0: 0
ra: 8000106c
sp: 8009cfe8
```

反汇编出来的文件里根本没有 0x80200634 这个地址的指令，看波形图也没有这个 pc，经检查发现是 j-type 立即数的符号位扩展写错了。修复后发现 difftest 涉及设备的部分也需要修改，在访问设备地址时应该跳过 diff。但后面发现区别还是有点大，暂时把 diff 关了

串口同样要看看 am， 串口在 trm.c 里，只是实现 putch 函数的话每个字符会被输出三遍。如果给 sim_main 中的 pmem_read 函数加上地址对齐，putch 的输出不仅会重复超过3次还会乱码。在 DPIC 的 verilog 代码中添加输出，发现执行一条指令时会取指三次，且有访存指令时一条指令会访存三次

目前把取指和访存都放在时钟上升沿了，但这样运行时会出现 lbu 指令越界访存，访问 0x00000008 这样的地址

且看 log 时发现 取出的指令 pc 和 inst 对不上，第一条指令会是 unimp（这个已修复）

给 NEMU 加了对齐访存之后运行 dummy，difftest 直接在 第一条指令处报错，单独运行NEMU 并没有问题。去掉对齐之后 difftest 会在 80000004 报错，此时 npc sp寄存器的值最后4位是0x4

检查后发现，虽然目前 log 的输出正确了，但 log 中 pc 为 x 时，pc = x 的那一条指令实际上在下一周期才会被执行。因此仿真环境 pc 的获取还要再提前，放在第一次 eval 之前。此外 NPC 内部的取值改成上升沿取指后，取出的指令会在下一个周期才被执行（什么流水线，，）。例如 0x80000004 处是 auipc sp, 9，其执行结果应该是 80009004，但目前 NPC 的执行结果是 80009008，并且 sp 在第三次 si 时才会改变

把取指模块的时钟信号去掉以后，将仿真环境改为在每个周期第一次 eval 之后获取指令的值，此时可以正确读出指令值并进入后续译码执行等环节，但取指会在一个周期内重复好几次 ，暂时搁置可以通过 difftest 和测例。

给 nemu 也加上地址对齐后，NEMU 取指令取出的指令会不正确，经检查发现是 difftest nemu 作为 ref 时使用了 paddr_write 来拷贝 img 数据，将其改为地址对齐后便出现了错误。给 NEMU 新增一个 unalign_paddr_write 用作 difftest 即可。

改完以后开着 difftest 跑 unalign 测例，NEMU Hit Bad trap 了但是 NPC hit good trap 了..

再一想，NEMU 的访存函数会被很多东西用到，不应该直接改访存函数，而应该在 NEMU 模拟指令的部分进行修改，这样才能和 NPC 对齐。于是在 inst.c 里进行修改，为访存函数添加地址对齐（改 Mr 和 Mw 这两个宏）。改完以后发现 单独运行 NEMU 的 unalign 测试还是 HIT BAD TRAP，这说明：

- 要么我的 NPC 的 HIT GOOD/BAD TRAP 实现有问题
- 要么 NEMU 的实现有问题

检查以后发现，NEMU 运行 unalign 时，a0 寄存器最终的值为 1，但我的 NPC 判断 GOOD/BAD TRAP 时没有用到 a0 寄存器，而是执行到 ebreak 即让 NPC_RET = 0 并返回 HIT GOOD TRAP，因此 NPC 的判断不准确。应该将 a0 的值赋值给 NPC_RET 才对。

修复以后 crc32、hello-str、unalign 等测例爆了 bad trap，但把 NEMU 和 NPC 都改成支持非对齐访存以后就可以通过测试了。并且 am-test 中的 hello test 也正常了。但 rtc-test 不太正常，时间非常快。检查以后发现是没有计算 boot_time，加入之后就正常了。

运行字符版超级玛丽：一堆字符，fps 为 0, 完全不能玩，跑的时候还有申必报错 `ROM 'mario' not found, using default ROM 'mario'`，启动以后 129 s 才能出现依稀可辨的界面。

#### 修改 NEMU ，使其支持设备 difftest

用 difftest_skip_ref 函数可以将当前指令 dut 的状态强行拷贝给 ref，使其不进行状态检测，但实际上 NEMU 作为 ref 时还是向下执行了一条指令，因此访问设备地址时还是会报越界

NEMU 默认在编译为 TARGET_SHARE 时不开启 DEVICE 支持，暂时注释掉这行试试，重新编译并运行 hello 测例，得到如下结果：

`Top: src/device/io/map.c:37: check_bound: Assertion 'map != ((void *)0)' failed`

对应下列函数的第三行：

```c
static void check_bound(IOMap *map, paddr_t addr) {
  if (map == NULL) {
    Assert(map != NULL, "address (" FMT_PADDR ") is out of bound at pc = " FMT_WORD, addr, cpu.pc);
  } else {
    Assert(addr <= map->high && addr >= map->low,
        "address (" FMT_PADDR ") is out of bound {%s} [" FMT_PADDR ", " FMT_PADDR "] at pc = " FMT_WORD,
        addr, map->name, map->low, map->high, cpu.pc);
  }
}
```

说明读取串口和 RTC 时，还没有对应的 IOMap。在 init_map 函数中添加一行输出，发现并没有对应的输出，检查发现 init_device 函数也没有被调用。这些函数是在 init_monitor 函数中被调用的，由于将 NEMU 编译为 .SO 时没有 monitor，因此没有进行对应的初始化。解决方案是加一个 ifdef CONFIG_TARGET_SHARE 进行判断。

但我实际上不需要让 NEMU 执行这些指令，只要让 NEMU 跳过这些比对即可。但这样需要修改 NEMU 的 pc 值。留个坑之后再实现

## RV64IM NPC

先迁移 ISA 到 RV64IM，按照讲义中从 RV64IM 迁移到 RV32E 的部分进行反向操作.

首先是 NEMU，注意指令实现时的 shamt 要多一位，还有转换符号数时改用 longlong。ftrace 要把 Elf32 等数据结构改回 Elf64

然后重新 clone abstract-machine ？我的 init.sh 并没有把 ics2023 改成 ysyx2204

dhrystone 跑了几次，最高分只有 20 分，但第四期的时候虚拟机里跑都有 130 分，用 native 跑分数是正常的。coremark 430 分也挺正常(第四期 coremark 是 200多分)

然后是改 RTL，除修改一些位置的位数以外还要添加新指令，例如字版本的加减法指令 addw、addiw、subw 指令还要增加额外的符号扩展处理，要和 ADDI 等指令进行区分

字版本的指令有大约十几条，可以加个译码信号来表示

原先一些 U 后缀的命令我是单独加了 ALU 控制信号来控制的，现在 U 后缀的指令多了，可能可以用额外的译码信号来表示。不过目前先不进行优化，怎么简单怎么写，先给加 ALU 控制信号

SRAW 这样的指令的结果不仅仅是 SRA 的低 32 位进行符号位扩展，其行为与 SRA 不同，不仅仅要加 isword 信号进行字指令的判断，还要给 ALU 加新的 op SRAW，SRLW 也类似，

注意 RTL 代码中移位量要同时在 EXU 和 IDU 进行修改

### 修改 am 里的编译脚本

加完 RTL 指令准备跑个 ARCH=riscv64-npc 的 dummy 进行测试，结果发现 scripts 目录下没有 riscv64-npc.mk。。，得对着第四期的 am 写一下

第四期 isa 目录下有 riscv32.mk 和 riscv64.mk 两个脚本，到了第六期全部合为 riscv.mk 了，riscv.mk 中 march 参数为 rv64g，riscv32e-npc.mk 中会用 `march=rv32e_zicsr  mabi=ilp32e` 覆盖掉这些。现在我们要新建一个 riscv64-npc.mk。

其中的 AM_SRCS 也要进行修改，在没有实现 M 扩展时要把 riscv/npc 这个目录下 libgcc 文件夹内的文件加到 AM_SRCS 变量里，libgcc 文件夹外的文件是在 platform/npc.mk 里加进来的

写掩码的宽度也要改为 8，并且在原来 0b1, 0b11, 0xF 的基础上加入 0xFF

之前仿真环境访存模拟的是 32 位总线，现在也改 64 的。但 RV32 和 RV64 的指令长度都是 32 位，pmem_write 函数改成 64 位

### 修复 NPC 的基础设施

npc 的 difftest 之前加载 so 文件的位置是被我写死的，直接用绝对路径找 rv32 的 NEMU 的 so 文件，现在要把相应的字符串改成 riscv64

目前能够成功用 difftest 比对 RV64NPC 和 64位 NEMU 的 dummy

看 log 发现一些指令的反汇编消失了，发现是 init_disasm 时传入的参数不对，应该改成 RV64

给 NPC 加了批处理和一键回归测试，现在 RV64 NPC 可以过所有测例了。

### 流水化

首先对单周期进行流水化，在每一级之间加入级间寄存器【理想流水线，不存在冒险和跳转指令】

#### chisel 复习 & 优化 NPC 代码

参考：

- [dinocpu/assignments/assignment-3.md at main · jlpteaching/dinocpu (github.com)](https://github.com/jlpteaching/dinocpu/blob/main/assignments/assignment-3.md#updating-the-dino-cpu-code)

按照 dinocpu 的写法，每一个流水级间寄存器可以用 chisel 中的 Bundle 来表示，在一个 Bundle 中定义若干个 val 来表示该流水级间寄存器所包含的数据内容

dinocpu 利用了一些 scala/chisel 语法，诸如用 Bundle 打包流水级间寄存器的数据内容，之前我写单周期的时候没有用到 Bundle 来打包 IO，于是要手动连一堆控制信号，写流水段寄存器把它们断开以后又要重新连一遍，非常丑陋。可以先参考https://blog.csdn.net/weixin_43681766/article/details/125573400复习一下 chisel，对着目前写好的单周期 NPC 练练手，再动手流水化；

Bundle 类似结构体，可以打包一堆变量

```scala
class Channel() extends Bundle {
    val data = UInt(32.W)
    val valid = Bool()
}
```

用 Bundle 打包连线的时候，可以创建一个 Wire 变量，将 Bundle 包在里面，然后就可以像结构体访问成员一样对 Bundle 中的信号进行访问了

```scala
val ch = Wire(new Channel())

ch.data := xxx
ch.valid := xxx

val xxx = ch.xxx
```

还有一个是 Vec 类型，类似数组，可以打包一堆同类型变量，用来写寄存器组之类的

```scala
val regfile = Reg(Vec(32, UInt(XLEN.W)))
```

可以通过下标访问，注意下标用的是圆括号：

```scala
regfile(rd) := rdv
```

类似于 C 语言可以开一个结构体作为元素的数组，Chisel 也可以用 Bundle 作为 Vec 的元素，同样地 Bundle 里也可以包括 Vec

```scala
val VecBundle = Wire(Vec(8, new Channel()))
```

用 Bundle + Wire 可以实现带有复位值的寄存器，可用于写流水级间寄存器，但是需要先声明一个该 Bundle 对象的 Wire，给 Wire 赋值后作为 init 值传给 RegInit

```
val initVal = Wire(new Channel())

initVal.data := XXX
initVal.valid := XXX

val channelReg = RegInit(init)
```

chisel 中不能进行局部赋值（chisel2 可以），但可以借助 Bundle 实现局部赋值。Bundle 可以通过 asUInt 或类似方法转为可直接赋值的类型，先对 Bundle 中的每个字段进行赋值，再这样转换后赋给目标值即可：

```scala
val assignWord = Wire(UInt(16.W))

class Split extends Bundle {
    val high = UInt(8.W)
    val low = UInt(8.W)
}

val split = Wire(new Split()) 
split.low := lowByte
split.high := highByte

assignWord := split.asUInt
```

需要注意 Bundle 里的字段合并成位向量以后的顺序。

一根一根线连信号非常麻烦，chisel 提供了整体连接运算符 `<>` 来连接多端口的模块，可以将 Bundle 部分双向连接。但是 chisel3 中 `<>` 的用法发生了变化，现在如果 `<>` 的两边端口不一致会报错，而不是仅连接同名端口。

使用例：流水线级间寄存器可以用 Bundle 中定义普通变量的方式定义，参考 riscv-mini

```scala
class FetchExecutePipelineRegister(xlen: Int) extends Bundle {
  val inst = chiselTypeOf(Instructions.NOP)
  val pc = UInt(xlen.W)
}

...
// IF/ID reg
val fe_reg = RegInit(
    // 此处 .Lit 需要 import chisel3.experimental.BundleLiterals._
    // 其可以
	(new FetchExecutePipelineRegister(conf.xlen)).Lit(
      _.inst -> Instructions.NOP,
      _.pc -> 0.U
    )
)
```

`.Lit` 用法参考 https://www.chisel-lang.org/docs/appendix/experimental-features#bundle-literals- ，其可以用于为 Bundle 中的成员进行赋值，并且可以仅对某些成员赋值。这样我们定义级间寄存器的 Bundle 时就不用指定方向，也不用搞 Wire 来给 RegInit 了，直接在 RegInit 传初值的时候传一个 (new mybundle).Lit(_.a->xxx, _.b->xxx) 即可。结合“可以仅对部分成员赋值”这一特性，.Lit 可以和 RegInit 结合使用来构造一个“部分初始化寄存器”

### 添加级间寄存器

RV 中的访存指令地址总是在 rs2v，addr 总是在指令中（可以直接走 ALU->res 这个数据通路）

每一级级间寄存器都加 inst 和 pc，方便 debug，目前不考虑冒险，所有的 en 信号都初始化为 1 且保持为 1

目前不考虑跳转和分支指令，因此 isdnpc 时钟为 0, pc 直接取 snpc 作为 nextpc

测例：

```c
static uint8_t mem[MEM_SIZE] = {
  0x93, 0x02, 0x00, 0x08, //addi	t0, zero, 128
  0x13, 0x03, 0x10, 0x08, //addi	t1, zero, 129
  0x13, 0x05, 0x10, 0x00, //li a0, 1
  0x13, 0x07, 0xb0, 0x00, //li a4, 11 
  0x13, 0x06, 0x10, 0x3a, //li a2, 929
  0x93, 0x05, 0x10, 0x3a, //li a1, 929
  0x73, 0x00, 0x10, 0x00  //ebreak
}; 
```

ebreak 在 EX 阶段检测到当前指令为 ebreak 则直接退出程序（即，上一个译码阶段结束后直接退出）。因此正确的五级流水应当成功写入a0，a4, 但没有写回 a2, a1

### 实现考虑跳转指令的流水线

原先 dnpc 的计算是放在 ALU 里算的，现在要提前到译码级算出要不要跳转，由于需要访问寄存器，跳转地址计算模块应当单独作为一个模块放在顶层模块中。当一条跳转指令到达译码阶段时，另一条指令正在取指，计算出的 dnpc 要直接取代正在取指的指令原先的 PC 值，这里要是组合逻辑，马上更新。

```c
static uint8_t mem[MEM_SIZE] = {
  0x93, 0x02, 0x00, 0x08, //addi	t0, zero, 128
  0xef, 0x00, 0xc0, 0x00, //jal ra, 80000010
  0x13, 0x03, 0x10, 0x08, //addi	t1, zero, 129
  0x13, 0x05, 0x10, 0x00, //li a0, 1
  0x13, 0x07, 0xb0, 0x00, //li a4, 11 
  0x13, 0x06, 0x10, 0x3a, //li a2, 929
  0x93, 0x05, 0x10, 0x3a, //li a1, 929
  0x73, 0x00, 0x10, 0x00  //ebreak
}; 
```

测例如上，Top 从 InstFetcher 模块读取 pc 和 inst 即可。

### 解决指令相关性冲突

采用计分板检测 RAW 冒险

在每种级间寄存器里添加 valid 信号，用于表示该寄存器这一周期的输出是否有效。再为每种级间寄存器定义一个 Wire 类型的 en 变量，用于表示当前这一级寄存器是否可以写入。

在流水线中，若上一级级间寄存器的 valid 信号为 0，则本级按照空指令对各个信号进行处理，并将下一级的 valid 信号也置为 0。

假如要阻塞执行级，即将 IDReg，EXReg 的写使能 en 设为 0，LSReg 和 WBReg 的写使能设为 1。并将 LSReg 的 valid 置为 0，其它的 valid 设为上一级的输入。这样的话，译码阶段的输入和执行阶段的输入就会停住，而访存阶段和写回阶段仍会有新数据写入（当前位于访存阶段的指令及其之后的指令还会继续，而执行阶段及其之前的阶段就会停住）

当执行级停止阻塞（对于顺序五级流水来说，即 WB 阶段完成了 RD 寄存器的写入），此时 IDReg，EXReg 的 en 重新设为 1，LSReg 的 valid 重新置为 1

输入 InstFetcher 的 PC 在流水线停顿期间不应该发生变化

实现步骤：

- 在每一个流水线寄存器输入时判断 EN 信号
- 在每一个流水线寄存器输出时判断 valid 信号
- 上一级的某输出信号可能是这一级的某输入信号，这种情况要同时对当前级 en 和上一级 valid 进行判断

现在把级间寄存器的输入和输出都加上了 valid 条件和 en 条件进行判断，除了 LSReg 的 valid 没有直接将 EXReg 的 valid 作为输入。

接下来用计分板实现判断冒险的逻辑：当一条指令进入译码阶段，我们可以得到这条指令是否包含 rs1, rs2，是否要对 rd 进行写入。如果其要对 rd 进行写入，那么 scoreboard(rd) 就在当前周期结束后记为 1（所以 scoreboard 用多端口的 Reg（即 chisel 的 Mem）实现）。如果其要读取的 rs1，rs2 对应的 scoreboard 已经为 1，那么就进行阻塞，将 EXReg.valid 置为 0，IDReg 和 EXReg 的 en 置为 0。

注意特判 rd 为 0 或 rs1,rs2 为 0 的情况，这种情况下不会冒险。

如何处理同一条指令中 rd == rs1 或 rs2 的情况？

- 这种指令不应阻塞

流水线要怎么开 difftest？在 difftest 函数里判断 pc 是否小于 RESET_VECTOR，是的话 ref 就不执行指令。

debug：原先没有阻塞流水线时，译码阶段发现当前指令需要跳转就直接计算出跳转地址，并写入

debug：运行 add 和 add-longlong 时

```c
0x80000098 : 00 15 35 13             sltiu	a0, a0, 1
0x8000009c : f7 5f f0 ef             jal	ra, 0x80000010
0x80000010 : 00 05 04 63             beq	a0, zero, 0x80000018
0x80000018 : ff 01 01 13             addi	sp, sp, -16
```

sltiu 和 beq 之间应当多停顿一个周期的，sltiu 还没有写回，beq 就进行跳转了。查看波形图发现 0x80000010 处的指令进入译码阶段时本应检测到 hazard，但是没有检测到，此时 sltiu 指令并未完成写入

如果在同一个周期内要对 scoreboard 的同一个寄存器同时写入 0 和 1（例如，处于译码阶段的指令要向 scoreboard(a0) 写入 1，但目前处于写回阶段的指令要向 scoreboard(a0) 写入 0）应该怎么办？不如一起阻塞了，当当前指令未来要写入某个目前 scoreboard 为 1 的寄存器，阻塞，直到其 scoreboard 为 0。即，译码阶段对 rd，rs1，rs2 都进行检测

改完以后运行 add-longlong，会无限阻塞下去。 经检查发现是在下一条指令卡死：挨着的两条指令第一条将 s0 作为 rd，第二条也是。当第一条指令处于执行阶段时，scoreboard(rd) 为 1，此时第二条指令处于译码阶段，检测到了 scoreboard(rd) 为 1，于是将 hazard 设为 1 进行阻塞。当第一条指令执行完成时，需要写入 rd 并清空对应的 scoreboard(rd)。如果此时处于译码阶段的指令马上又写入了 scoreboard(rd) = 1，就会导致一直卡死，应当在**清除 scoreboard 后再停一个周期再让流水线动起来**。

现在流水线动不动是根据 hazard 变量进行判断的，目前这是一个 Wire，其输入是若干 Reg，将其改成 Reg 类型，这样 scoreboard 清除后的下一个周期才会检测是否阻塞已经消失。但这样如果当前译码阶段的指令和当前执行阶段的指令有冒险会无法检测到。

问题：

- case1：rd == rs1 或 rd == rs2
- case2：要写回的 rd 等于当前译码阶段的 rd，因此目前的写法同一个周期内要对 scoreboard(rd) 进行两次写入一次读出，需要保证顺序
  - sol：仅当要写入的 rd 对应的 scoreboard 不为 1 时才进行写入，但这样写入还是会一直阻塞
  - sol2：检测到这种情况以后将 IDRegen 设为 false，检测条件为 IDReg.rd == WBReg.rd
  - 太蠢了，把计分板删了就行。

删除计分板，直接用组合逻辑进行判断，当前指令如果包含 rd，rs1，rs2，就在译码阶段检查流水线中更前面阶段（执行、访存、写回）是否包含非0目的寄存器并且是否和当前译码的指令的 rs1，rs2，rd 相关。

1. 当前的 rs1/rs2 等于 EX 的 rd
2. 当前的 rs1/rs2 等于 LS 的 rd
3. 当前的 rs1/rs2 等于 WB 的 rd

bug 找到了，beq 的 alu_sel 并不是 rs1 和 rs2，但这类指令还是读取了 rs1 和 rs2，需要特殊判断。即：(decoder.io.isdnpc && inst != JAL) 则有读取 rs1，额外加上 inst != JALR 则有读取 rs2，这样判断容易漏，直接给每条指令标记是否用了 rs1, rs2, 即可通过所有测例

### 输入输出

跑 am-test 跑不起来

bug：译码阶段计算 JALR 等跳转指令的地址的时候要访问 rs1、rs2 等寄存器，但此时可能流水线已经阻塞，寄存器有未完成的写入，此时读取会读到错误的值。因此计算跳转地址之前要先判断当前指令是否已被阻塞，若是则不计算跳转地址

已修复，并添加了相关 am 文件，现在可以跑 Bad-apple 了。

### 总线

先不改整体连线了，就直接把 IFU 改成延迟 1 周期。不应该一次重构太多代码，应该改一点测一点。

#### IFU 重构

加入 DecoupledIO，然后手动让输出比输入慢一个周期即可。这样从取指模块输入 dnpc 到 IDReg 输出对应的 pc 和 inst 需要两个周期，在此期间流水线中要出现一个气泡？

需要两个气泡，pc的输入输出差了一个周期，pc的输出即ifu的输入和输出又差一个周期，ifu的输入即IDReg的输入和IDReg的输出又差一个周期，IDReg的输出为跳转指令时，dnpc只能赋值给pc的输入，其如果要成为下一条指令，需要把当前处于pc中的指令和处于ifu中的指令都吃了。

如果阻塞了，需要把 PC，IFU，IDReg 的全部锁住，即 stall 期间让它们保持当前的状态。

这么改完以后可以运行 bad apple

2024.2.22: 在使用状态机模型改写 IFU 后，sim_main.cpp 中获取 PC 的逻辑也需要修改：

- IFU 上升沿时取出下一个 pc，在 clk = 0 时是当前指令对应的 pc，clk = 1 时已经取出了下一条指令对应的 pc。
- 当 single_cycle 函数中第二次执行 eval() 时，clk 进入高电位，此时 pc 已经变为了 dnpc，并且寄存器的状态已经发生了变化。因此，difftest 应该在此之前比较 ref 和 dut 的状态
- sim_main 中需要 pc 和 nextpc，而 nextpc 被读出时其对应的指令不应该执行完毕，即应该在写回之前读出 nextpc。因此可以添加一个 npc ，从 LSReg 读出。此外 PC 从 WBReg 读出
- 改完之后发现，IFU 会在不该跳转的时候（例如 add 测例第一次执行 80000018 处的 beqz 指令）跳转，导致 difftest 报错并 hit bad trap。注意到 Decoder 的 isdnpc 信号仅仅用于标识当前指令是否为跳转指令，并不一定真的会跳转，至于是否跳转是需要再额外判断的。原先的逻辑是：如果不跳转，就把跳转地址设置为 snpc。但 snpc 的计算随着每次重构都要重写一遍，不如把 isdnpc 信号改一下，改成真要跳转时才为真

#### LSU 重构

给 Mem 加上一周期延迟后，如果当前指令要访问 Mem，需要等待 mem 取回数据之后再进入下一个阶段，此时需要阻塞访存级（？），即把 LSU 的 valid 信号置为 0，ready 信号也置为 0，

如果某个模块没有和下游模块握手，该模块中现有的数据会怎么样呢？由于处理器是一个状态机，当 valid 无效时，我们可以将后续模块的写使能置 0，使后续模块保持当前状态。但目前我的处理器在 valid 为 0 时会往后输出无效数据 nop。valid & !ready 时，master 要暂存消息避免丢失

目前我实现的五级流水是由一个全局的 stall 信号来检测是否阻塞的，它会和各个模块之间的分布式控制有冲突吗？

```scala
  when (stall) {
    IDRegen := 0.B
    EXReg.valid := 0.B
    ifu_dnpc := "x114514".U
  } .otherwise { 
    IDRegen := 1.B
    EXReg.valid := 1.B
    ifu_dnpc := MuxCase(0.U, Array(
    (Decoder.io.inst === JALR)  -> (rs1v + Decoder.io.imm),
    (Decoder.io.inst === JAL)   -> (pc_plus_imm),
    (Decoder.io.inst === BEQ)   -> Mux(rs1v === rs2v, pc_plus_imm, snpc),
    (Decoder.io.inst === BNE)   -> Mux(rs1v === rs2v, snpc, pc_plus_imm),
    (Decoder.io.inst === BGE)   -> Mux(rs1v.asSInt >= rs2v.asSInt, pc_plus_imm, snpc),
    (Decoder.io.inst === BGEU)  -> Mux(rs1v >= rs2v, pc_plus_imm, snpc),
    (Decoder.io.inst === BLT)   -> Mux(rs1v.asSInt < rs2v.asSInt, pc_plus_imm, snpc),
    (Decoder.io.inst === BLTU)  -> Mux(rs1v < rs2v, pc_plus_imm, snpc)
  ))
 }
```

IDRegen 和 EXReg.valid 的结果是根据 stall 来修改的，此外 PC 和 InstFetcher 也受 stall 的影响。

todo：

1. 检查当 valid 为 0 时，后续模块的时序元件是不是保持了当前的状态，但后续模块的组合元件怎么处理？
2. valid & !ready 时，master 要暂存消息，避免丢失。master 在暂存信号时，master 输入端的 ready 信号又该是什么呢？
3. 改位宽，现在我的地址位宽和数据位宽都是 64 位，但按照第五期讲义的话，地址位宽应该是 32，数据位宽是 64 才对。(已经改成 32)
4. 为访存部分加入 1 周期的读取延迟后，原先读取结果放入 LS/WBReg 改为直接放到一个 Wire 中，直通到 WB 阶段，这样一个周期之后的 WB 阶段正好能够得到上一个周期访存时对应的结果。



#### AXI4-Lite

master 读取 slave 的数据时，首先要由 master 向 slave 传输读地址，这个过程需要进行一次握手，通过信号 `arvalid` 和 `arready` 实现。随后 slave 向 master 传回读到的数据也要进行一次握手，通过 `rvalid` 和 `rready` 实现。

写事务也要握手，写地址和写数据分开，通过 `wvalid` 和 `wready` 信号实现写数据的握手，`awvalid` 和 `awready` 信号实现写地址的握手。

AXI4-Lite 按功能可以分为五个信道，分别是读地址(AR), 读数据(R), 写地址(AW), 写数据(W)和写回复(B), 它们的工作状态只取决与各自的握手信号, 因此它们可以独立工作, 例如读请求和写请求可以在同一个周期中同时发送.于是可以设置五个独立的状态机实现这一点。

现在为 IFU 实现了 AXI4-Lite，但目前完成一次取指需要好多个周期，这会影响到流水线的正常运行，使得流水线每一级需要多个周期才能完成。并且跳转指令也出了问题：如果当前处于译码阶段的指令是跳转指令，那么 dnpc 会被放入 PC 寄存器，到下一条指令被读出后才会被读进 IDReg，这太迟了，应该冲刷掉 IDReg 里的指令，即判断当前是否有指令跳转。

如果向 IFU 的 SRAM 传入 isdnpc 信号来实现冲刷数据是不合适的，因为最终 IFU 和 LSU 要用同一个存储器，不会接受 isdnpc 信号，只能对 IDReg 进行操作来实现冲刷。实现：当译码阶段的 isdnpc == 1，将 IFU out 的 valid 置为 false，直到 IDReg === dnpc

访存部分：执行 lw 之类的指令时，要等待存储器读出数据再进行寄存器写回。

AXI 总线支持 Outstanding，即 AXI 允许数据返回之前又发起一次新的读请求

#### 避免握手的死锁和活锁

> 在实际使用中, 我们还需要避免和握手信号相关的两种情况:
>
> * master和slave互相都在等待对方先将握手信号置1: master在等slave将 `ready`置1后, 才将 `valid`置1; 而slave则在等master将 `valid`置1后, 才将 `ready`置1. 结果就是双方无限制地等待, 造成[死锁(dead lock)在新窗口中打开](https://en.wikipedia.org/wiki/Deadlock).
> * master和slave都在试探性地握手, 但试探失败后又都取消握手:
>   * 在第1周期, master将 `valid`置1, 但此时 `ready`置0, 握手失败
>   * 在第2周期, slave发现上一个周期master将 `valid`置1, 因此这个周期将 `ready`置1; 但因为上一个周期握手失败, master在这个周期将 `valid`置0, 于是这个周期握手仍然失败
>   * 在第3周期, master发现上一个周期slave将 `ready`置1, 因此这个周期将 `valid`置1; 但因为上一个周期握手失败, slave在这个周期将 `ready`置0, 于是这个周期握手仍然失败
>   * 结果双方仍然无限制地等待, 造成[活锁(live lock)在新窗口中打开](https://en.wikipedia.org/wiki/Deadlock#Livelock).

1. 避免死锁：数据源端必须等待自身的 valid 有效后，再对接收方的 ready 信号进行等待。一旦 valid 有效，源端就得保证 valid 信号不变并保持数据，直到握手成功。但接收端可以在 ready 信号无效时等待源端的 valid 信号有效，并且在 valid 有效前，ready 可以在有效和无效之间切换。为了避免死锁，发送方的 valid 信号不能依赖于接收方的 ready 信号，接收方的 ready 信号有效前可以等待 valid 信号。
2. 避免活锁：为了避免试探性握手带来的活锁，valid 置为 1 后应当保持 valid 不变直到握手成功。

可以新建一个 fake_sram 模块，并用 AXI4-Lite 接口包装，该模块内调用 DPIC 访问内存。

AMBA 手册里有 AXI4 各握手信号的依赖关系图，可以按照那个进行。需要注意图中单箭头和双箭头含义不同

### 流水线（接 AXI-4 lite 总线）

2024.2.23

写这段的时候总线并没有调通，之前是先实现的组合逻辑存储器+没有实现总线协议的裸五级流水，再接的AXI4-Lite。接总线过程中把流水线改成了 IF ID EX LS 四级，目前 IFU 已经是 AXI4-lite 了，LSU 还没改，应该先改回五级流水

2024.2.25

目前 FAKE_SRAM 的写通道还未实现，因此测例还不能通过。

2024.2.26

加上写通道了，但是看 log 发现运行 add 测例跑到 80000118 处跳转指令时，IF ID EX 会有跳转指令，但是 LSReg 没有读入跳转指令（流水线没往下传）因此最终 log 在 IS 阶段输出时无法输出跳转指令。这是因为上一条指令是访存指令，其访存时改变了 LSU 的状态机，使其 ready 信号为低。

将各流水级寄存器的 en 信号 & 上下一集的 en 信号后，跳转指令没有正确执行，而是直接在 80000114 之后直接执行了 8000011c。

fix：让流水线寄存器的 en 充当 ready，重新运行之后 80000118 的指令还是被吞了

2024.2.28

看波形发现 IFU 执行 add 测例 80000114 处跳转指令时，out.valid 为 1 的瞬间 out.ready 被拉低了。

STFW 发现当某一级流水线的 valid 为 0 时可以让该级接收数据，即将该级的 ready =1。这样改了之后 0x80000084 处的访存指令结果不正确。

给 WBReg.valid 加上一个条件：`WBReg.valid := LSReg.valid & NPC_Mem.io.out.valid`

上一个条件太迟生效了，在 WBReg 和 LSReg 握手时就可以把这个条件加进去进行判断。

直接把 LSReg 里的所有信号传给 NPC_Mem，让 LSReg 和 NPC_Mem 握手，和 WBReg 握手（进行中），以避免 LSReg 和 NPC_Mem 握手成功但 Mem 和 WBReg 握手失败的情况（NPC_Mem.valid = 0）。于是 Top 里变成了 6 个模块依次握手

2024.2.29

LSU 里传入 PC 和 INST 时要分情况讨论，如果当前不是访存指令，可以直接把 PC 和 INST 传给下一级，否则应该等待读/写操作完成后一起输出。

目前的实现是用一个寄存器标识当前是否正在执行访存指令。需要注意将 LSReg 和 LSU 连接后，由于 LSU 不是纯组合逻辑了，需要提取其中的 rd 信息判断是否存在数据冒险

现在处理器按照时间走，一条指令执行经过这些时序逻辑部件：IF->IDReg->EXReg->LSReg->LSU->WBReg->ISReg。（其实 LSReg 可以删了）

发现写指令（例如 sd） 全都没有生效，检查后发现是调用 DPIC_MEM 使能其 valid 信号时只根据读取相关的信号进行使能了，没有根据写相关的信号进行使能。改完以后运行 add 可以 hit good trap

运行 quicksort 如果不开 difftest 会直接卡死，经检查发现本该执行跳转的 bge 指令没有成功跳转。bge 0 0 两边相等，本该跳转。

检查后发现当跳转地址正准备输入 IFU 时流水线发生了全局 stall，stall 时会把 IDRegen 和 EXReg.valid 置为 0,

IFU 的 in.valid 应该是什么？直接改成全 1

然后执行到 80000298 处，开始无限爆 nop。看波形发现是 FAKE_SRAM 的 ar_state 卡在 ar_wait_ready，一直在等待 rready，而 IFU rready 的条件是 state === s_wait_rvalid & io.out.ready，IFU 的读状态机一直卡在 wait_arready 的状态，导致死锁

看波形发现 state 从 10(wait_rvalid) 变成 00(idle) 的一瞬间 io.out.ready 变为 1 了， 需要 state 迟一个周期发生变化，或者 ready 早一个周期发生变化才能避免死锁。但 io.out.ready 实际上是 IDRegen，它随着 stall 的变化而变化，要动只能动 state 或者动 rready 的判断条件了。IFU 什么时候能接收 MEM 发来的 rdata，即什么时候可以把 rready 置为 1？当 IFU 的下游可以接收数据时（out.ready，即 IDRegen），即可接收 rdata，或是 IFU 当前的 output.valid 无效（说明存放 rdata 的寄存器中的数据无效）

现在 master 和 slave 都是拉高自己的 valid/ready 信号然后去判断对方的对应信号是否为 1。

2024.3.1

将 rready 的条件改为 state === s_wait_rvalid 后，即去掉对 io.out.ready 的依赖后，解决了死锁问题，但是运行到 800002a8 处 difftest 报错。检查 log 和寄存器发现是 800002a4 处的 blt 指令本该跳转但是没有正确跳转导致的。检查后发现当 dnpc 输入到 IFU 后，IFU 要经过 1 个周期的延迟才能反应过来。解决方法是：isdnpc 也只持续一个周期，可以把 isdnpc 加入 out.valid 的判断条件中，若 isdnpc = 1 则无效。

把 io.out.ready 加到 io.in.ready 的判断条件中，即现在 io.in.ready = io.out.ready & arready（但好像根本没用上 io.in.ready）

能过 quicksort 等测例了，但是跑 hello-str 时发现不该跳转的指令也跳转了，检查发现当遇到数据冒险需要全局阻塞之前，dnpc 会被读入 ifu 并且判断 isdnpc 时用的是导致冒险的寄存器写回之前的旧值，从而导致了错误的跳转。解决方案是在 stall 时将 IFU 的 in.valid 拉低[没用]

把每个流水线寄存器的波形拉出来看，发现当 NPC_Mem 里的 rd 等于 IDU 的 rs1 时本应 stall 但实际上没有 stall，

```scala
val MEM_RS1_Hazard = Decoder.io.rs1 === Mux(NPC_Mem.io.out.valid, NPC_Mem.io.out.bits.rd, 0.U) && NPC_Mem.io.out.bits.rden
```

此时 Decoder.io.rs1 和 NPC_Mem.rd 相等，但 NPC_Mem.io.out.valid 为 0，导致没有标出发生了冒险。应该修改 NPC_Mem 相关冒险的检测方式，当一条指令进入 MEM 一直到离开 MEM 的期间都需要对其进行检测。RTFSC 后发现不需要判断 io.out.valid，

现在能过这个测例了，但是 movsx 报错，addi 指令似乎读不到寄存器的原值。检查发现 80000060 执行完成之后漏掉了中间的 80000064 auipc 指令，直接跳到了 80000068，导致这个错。发现是 LSU 的 io.in.ready 变成 0 了，并且在 io.in.ready 为 0 时发送方没有保存数据导致的。当 valid = 1，ready = 0 时，发送方应该保持 valid = 1 并保持要发送的数据不变，直到 ready = 1。但是代码里 `LSRegen := NPC_Mem.io.in.ready | !LSReg.valid`，当 NPC_Mem.io.in.ready 为 0 时 LSReg.valid 并不为 0，此时 LSRegen 为 0 正在保持数据才对，但是 LSReg.pc 还是发生了变化。发现是给 LSReg 在 EXReg.valid = 0 时赋值时漏判了 LSRegen

修正以后再次运行 movsx 会在 80000070 处指令访存时越界，`80000070:	1af72423          	sw	a5,424(a4) # 80000214 <b>` 在 log 里报的是访问了 000001a8 的地址，（0x1a8 就是 424），由于这条指令还没进入提交阶段，它和它的上一条指令都还没有 difftest. 看 cpu-tests 的反汇编结果发现上一条指令是 `auipc a4, 0`，和这一条访存指令存在数据冒险，从结果来看上一条指令还没写回，当前这条指令就进行访存了，导致了这个错误。 

查看波形发现并不是因为数据冒险了没有停顿，而是 8000006c 处的指令根本没有执行，直接被跳过了。原因：当 IDRegen 为 false 时，IFU 没有保持数据。修改后此处运行正确了，但随后 80000080 处的指令也被跳过了，查看波形发现是访存部分丢指令了。检查后发现 LSReg 没有在 valid = 1 且下游 ready = 0 时保存数据，即使 LSRegen = 0 传进去的 pc 还是变成 0 了，发现是 MEM 的 in.ready  设置有问题，改成 io.in.ready := r_state === r_idle && w_state === w_idle 后又把 8000008c 丢了

----------------------------------------------------此处 commit---------------------------------

看波形推了一下，由于 Chisel 用 Mem 实现的寄存器具有先写后读的特性，当 EXRegen 变为 1 的那一瞬间，新的 PC 值将会先写入 EXReg，随后 LSReg 才会从 EXReg 中读出新的 PC 值，这就导致旧 PC 值丢失了。

8000008c 为什么被吞：当 EXReg.pc 变成 8000008c 的那一瞬间，LSU 正好在执行一条访存指令，此时 LSU 的 in.ready 即 LSReg 的写使能正好变成 0 了，于是 EXReg 会保持 8000008c 这个数据，直到 LSU 的 io.in.ready 变为 1。从 io.in.ready 变为 1 到 EXReg.pc 变成下一条指令之间还需要有一个周期

2024.3.2

在 EXReg.pc === 8000008c 的期间，Mem 由于访存指令的原因阻塞了，而 IDReg 也因为 stall 的原因阻塞了。访存导致的阻塞先消失-》导致了 EXReg 发生更新，LSReg 此时理应更新但是没有更新

*流水线阻塞会导致  EXReg.valid 被拉低，但其实拉低后 EXReg 中保存的仍然是有效数据，不应该冲刷掉*。原先 EXRegen = LSRegen | !EXReg.valid，就会导致 EXReg 被冲刷，其它流水线寄存器同理。修改各个流水线寄存器的 en 信号后通过了这一测例。

通过全部测例，能够运行 bad apple！

2024.3.4

### 测试总线的实现

把 IFU 的 SRAM 延迟调成 5，可以通过测试。

保留上面的修改，将 LSU 的 SRAM 延迟也改成 5，可以通过测试

将 IFU 的 SRAM 延迟改为由 4 位 LFSR 决定，运行测例时第一条指令都跑不通，一开始就直接对 0 地址进行访问了。如果只是单纯把 LSU 的 SRAM 改成 LFSR 延迟，并不会有这个问题。给 IFU 的 SRAM 里加入一个判断，当 reset == 0 时访存的 valid 信号为 0，即解决。

### 总线仲裁

多周期处理器的 IFU 和 LSU 不会同时访问 SRAM，但目前我写的流水线会，因此需要合适的总线仲裁调度策略

多个 master 发送请求时，需要由仲裁器 Arbiter 来决定对哪一个提供服务。而 slave 也可能不止一个，Arbiter 仲裁出的请求会发送给 Xbar，由 Xbar 转发给特定的设备。

Arbiter 和 Xbar 合在一起可以组成多进多出的 Xbar（也叫 Interconnect，总线桥等）

可以给 IFU 和 LSU 增加总线请求线 bus_req 和总线授权线 bus_ac，当 bus_ac 才能和 slave  通信。通信完成的标志是 r 通道握手或 b 通道握手

目前实现了简单的优先级仲裁，IFU 的优先级高于 LSU。运行时会卡死，检查波形发现是因为在 ifu 发起一次请求后，请求结束 req 信号还没归 0 时 Arbiter 已经回到了 idle 状态开始检测请求，于是又开启了新一次 IFU 的事务。并且 ac 信号用的是 wire，而 req 信号用的是 reg. 修改成 reg 之后 add 测例能跑通了

### 多个设备的系统

0x80000000 是负的，没法直接加 .U 转为 UInt，需要在 Configs 里把它们定义为 BigInt（也不行

在 Configs 里加 L 后缀 ok.

写好 UART 后发现，当 awaddr 为 SERIAL_PORT 时，还是访问了 SRAM 而没有访问 UART。检查发现 XBar 里只用了 araddr 没用 awaddr.

跑 demo 里的 ant demo 有问题，输出两个 c 字符之后就卡死了，检查后发现 这个测例访问了 RTC 寄存器的地址，但 NPC 目前实现的 RTC 是交给 SRAM 的。Bad Apple 测例也在尝试访问 a000004c。在 XBar 里将对 RTC 的访问转发给 SRAM 后，能够运行 Bad Apple，但性能比之前的低。

实现 mtime 寄存器后，将 IOE 里 uptime 函数读出的时间乘以 0.25 的系数，让其接近真实时间

#### alu-test 有问题

为了测试串口，跑 alu-tests 挂了一堆 unsigned int 的边界测试点。用 NEMU 跑挂的测试点少一些，但还是挂了 4 个。native 跑没有问题，说明我的 NEMU 和 NPC 的实现有问题

下面是 NEMU 挂的点：

```shell
                                                                         
line 14532: unsigned int: -214748364(  /  1  ==  -214748364( =>  FAIL (-214748364()                            
line 14567: unsigned int: -2147483647  /  1  ==  -2147483647 =>  FAIL (-2147483647)                            
line 14597: unsigned int: -2  /  1  ==  -2 =>  FAIL (-2)                              
line 14622: unsigned int: -1  /  1  ==  -1 =>  FAIL (-1)          
```

输出里面的括号估计是 Klib 实现有问题，但这报错的点结果和答案一样啊，不懂咋挂的。NPC 也有类似的输出，但是结果和答案不一样

```
line 14537: unsigned int: -214748364(  /  2  ==  1073741824 =>  FAIL (-1073741824)                                                                                                                                                
line 14542: unsigned int: -214748364(  /  2147483646  ==  1 =>  FAIL (7)                                                                                                                                                          
line 14547: unsigned int: -214748364(  /  2147483647  ==  1 =>  FAIL (3)                                       
line 14572: unsigned int: -2147483647  /  2  ==  1073741824 =>  FAIL (-1073741824)                             
line 14577: unsigned int: -2147483647  /  2147483646  ==  1 =>  FAIL (7)                                       
line 14582: unsigned int: -2147483647  /  2147483647  ==  1 =>  FAIL (3)                                       
line 14602: unsigned int: -2  /  2  ==  2147483647 =>  FAIL (-1)                                               
line 14607: unsigned int: -2  /  2147483646  ==  2 =>  FAIL (8)                                                
line 14612: unsigned int: -2  /  2147483647  ==  2 =>  FAIL (4)                                                
line 14627: unsigned int: -1  /  2  ==  2147483647 =>  FAIL (-1)                                               
line 14632: unsigned int: -1  /  2147483646  ==  2 =>  FAIL (8)                                                
line 14637: unsigned int: -1  /  2147483647  ==  2 =>  FAIL (4)
```

查看 alu_test.c 的源码，发现字符 8 变成了 '('，



