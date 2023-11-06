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

#### 批处理运行nemu

查看sdb的源码可以发现，批处理需要在 nemu 启动时传入 b 参数。修改 platform/nemu.mk 即可。

#### 实现字符串处理函数

注意memset虽然传入了int，但是填充时是按无符号char进行填充的，每个字符都填充。

#### 实现 sprintf



## 最简单的处理器

支持 addi 和 ebreak，参考一生一芯视频课提到的 YPC （第六节）的写法

