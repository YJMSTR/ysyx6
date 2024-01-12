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

> 为了测试大家是否已经理解框架代码, 我们给大家设置一个练习: 如果在运行NEMU之后直接键入`q`退出, 你会发现终端输出了一些错误信息. 请分析这个错误信息是什么原因造成的, 然后尝试在NEMU中修复它.

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

第一行`NAME	:= am` 用`:=`运算符避免了多次展开，但也因此必须提前声明。

第二行声明一个 SRCS 变量， 值为`src/$(AM_SRCS)` 

第三行通过`+=`运算符给 INC_PATH变量追加一个值，为am/src的绝对路径。

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

>  elf 的符号包括一个 Symbol Table，其中包含一组 Symbol。这些 Symbol 在程序中要么表示定义，要么表示引用，它们的作用是在编译和链接的过程中进行定位和重定位。

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
>
> - `2`
>
>   The exit status is two if `make` encounters any errors. It will print messages describing the particular errors.
>
> - `1`
>
>   The exit status is one if you use the ‘-q’ flag and `make` determines that some target is not already up to date. See [Instead of Executing Recipes](https://www.gnu.org/software/make/manual/html_node/Instead-of-Execution.html).

#### 这是如何实现的

> 框架代码编译到`native`的时候默认链接到glibc, 我们需要把这些库函数的调用链接到我们编写的klib来进行测试. 我们可以通过在`abstract-machine/klib/include/klib.h` 中通过定义宏`__NATIVE_USE_KLIB__`来把库函数链接到klib. 如果不定义这个宏, 库函数将会链接到glibc, 可以作为正确的参考实现来进行对比.

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

> RISC-V作为一个RISC架构, 通常是不支持不对齐访存的, 在Spike中执行一条地址不对齐的访存指令将会抛出异常, 让PC跳转到`0`. 但NEMU为了简化, 没有实现这样的功能, 因此如果让NEMU和Spike同时执行这样的指令, DiffTest将会报错. 不过这很可能是你的软件实现(例如klib)有问题, 请检查并修改相关代码.

#### 一键回归测试

全部通过

### 输入输出

####  运行Hello World

关了trace，直接运行就可以看见Hello, AbstractMachine!

需要注意：

>  设备和DiffTest
>
> 在状态机视角下, 执行一条输入指令会让状态机的状态转移变得不唯一, 新状态取决于设备的状态. 由于NEMU中设备的行为是我们自定义的, 与REF中的标准设备的行为不完全一样 (例如NEMU中的串口总是就绪的, 但QEMU中的串口也许并不是这样), 这导致**在NEMU中执行输入指令的结果会和REF有所不同**. 为了使得DiffTest可以正常工作, 框架代码在访问设备的过程中调用了`difftest_skip_ref()`函数 (见`nemu/include/device/map.h`中定义的`find_mapid_by_addr()`函数)来跳过与REF的检查.

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

> 我们可以通过在`abstract-machine/klib/include/klib.h` 中通过定义宏`__NATIVE_USE_KLIB__`来把库函数链接到klib. 如果不定义这个宏, 库函数将会链接到glibc

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
>                 vs. 100000 Marks (i7-7700K @ 4.20GHz)

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

####  实现IOE(4)

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

> 在`nemu/include/cpu/ifetch.h`中, 你会看到由`static inline`开头定义的`inst_fetch()`函数. 分别尝试去掉`static`, 去掉`inline`或去掉两者, 然后重新进行编译, 你可能会看到发生错误. 请分别解释为什么这些错误会发生/不发生? 你有办法证明你的想法吗?

去掉 static 没有报错，去掉 inline 也没有报错，去掉二者则会报错：

```
 /usr/bin/ld: /home/yjmstr/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/engine/interpreter/hostcall.o: in function `inst_fetch':
hostcall.c:(.text+0x0): multiple definition of `inst_fetch'; /home/yjmstr/ysyx-workbench/nemu/build/obj-riscv32-nemu-interpreter/src/isa/riscv32/inst.o:inst.c:(.text+0xeb0): first defined here
collect2: error: ld returned 1 exit status
```

static 关键字可以使函数变为静态函数，仅声明该函数的文件可以访问静态函数，因此不同文件中可以存在同名的 static 函数。inline 是建议编译器将函数内联，编译器最终不一定会这么做。注意到这个函数是定义在头文件里的，多处引用该头文件的话如果没加 static 的话 inline 不内联就会重复定义。对于头文件中定义的函数，其要被外部使用则不会内联，得加 static inline 才能成功内联。

去掉 static 不会报错，可能是因为编译器将其内联了。去掉 inline 不报错是因为引用该头文件的 c 文件都创建了该函数的 static 副本，static 允许不同文件中的同名函数。

> 在`nemu/include/common.h`中添加一行`volatile static int dummy;` 然后重新编译NEMU. 请问重新编译后的NEMU含有多少个`dummy`变量的实体? 你是如何得到这个结果的?

`nm build/riscv32-nemu-interpreter | grep dummy` ，34 个。nm 可以从对象文件中读取符号

> 添加上题中的代码后, 再在`nemu/include/debug.h`中添加一行`volatile static int dummy;` 然后重新编译NEMU. 请问此时的NEMU含有多少个`dummy`变量的实体? 与上题中`dummy`变量实体数目进行比较, 并解释本题的结果.

还是 34 个。去掉 debug.h 中添加的代码并把 common.h 中的 volatile 去掉，则会报错 定义了未使用的变量。y

> 修改添加的代码, 为两处`dummy`变量进行初始化:`volatile static int dummy = 0;` 然后重新编译NEMU. 你发现了什么问题? 为什么之前没有出现这样的问题? (回答完本题后可以删除添加的代码.)

此时会报错 `error: redefinition of ‘dummy’` 。STFW，C 语言的 static 变量在编译时初始化，C++ 的 static 变量在运行时初始化，如果在头文件中定义 static 变量，其会在所有包括该头文件的源文件中都进行一次初始化。如果仅在 common.h 中进行初始化则不会报错。这涉及到 C 语言的链接决议规则：

链接器的工作分为两个阶段：符号解析和重定位。对于编译器来说，函数名和变量名都可以称为符号。符号可以分为强符号和弱符号，对于 C/C++，函数名称和初始化了的变量的名称为强符号，未初始化的变量名为弱符号。

- 链接器不允许强符号被多次定义
- 链接器选择符号时，一强多弱的同名符号选择强的那个
- 全是同名弱符号选择占空间最大的那个

上述例子中，如果同时在两个头文件中进行初始化，就会有两个名为dummy的强符号，这是链接器不允许的。之前没有出现这个问题是因为之前dummy都是弱符号，链接器只会选取占空间最大的那个。

> **了解Makefile**
>
> 请描述你在`am-kernels/kernels/hello/`目录下敲入`make ARCH=$ISA-nemu` 后, `make`程序如何组织.c和.h文件, 最终生成可执行文件`am-kernels/kernels/hello/build/hello-$ISA-nemu.elf`. (这个问题包括两个方面:`Makefile`的工作方式和编译链接的过程.) 关于`Makefile`工作方式的提示:
>
> - `Makefile`中使用了变量, 包含文件等特性
> - `Makefile`运用并重写了一些implicit rules
> - 在`man make`中搜索`-n`选项, 也许会对你有帮助
> - RTFM

hello 文件夹中的 makefile 包含了 AM_HOME 目录下的 makefile，后者定义了 `INC_PATH += $(WORK_DIR)/include $(addsuffix /include/, $(addprefix $(AM_HOME)/, $(LIBS)))`，编译器在编译时将会在 INC_PATH 下寻找头文件，包括 am 和 klib 的头文件（由 LIBS 指定）。

此外还定义了 ARCH_H 变量来指定 am 的 `arch/$(ARCH).h`

第二点，隐含规则例如 AS、CC 等对应的规则在 AMHOME 下的 makefile 中进行了重写，将其改为使用对应架构的交叉编译工具链。

第三点，在 man 中可以通过 `/` 进行查找，`/` 后面可以跟正则表达式。查找到 -n 选项为：

>  -n, --just-print, --dry-run, --recon
>             Print the commands that would be executed, but do not execute them
>             (except in certain circumstances).

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
> 其中寄存器状态`dut`要求寄存器的成员按照某种顺序排列, 若未按要求顺序排列, `difftest_regcpy()`的行为是未定义的(这样就把锅甩给你们了^_^). REF需要实现这些API, DUT会使用这些API来进行DiffTest. 在这里, DUT和REF分别是NEMU和其它模拟器.

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
