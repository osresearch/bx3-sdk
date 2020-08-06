# BLUEX代码规范 v0.0.0

## 1、基本原则

- linux代码风格
- 代码小写
- 以下划线“_”作为单词分隔符

## 2、类型定义

- 使用后缀区分类型
- 不使用typedef对基础类型重命名

### 2.1 基本类型

- 支持所有C语言标准类型，即char、int、float、double、signed、 unsigned、short、long等
- 使用u8、s8、u16、s16、u32、s32重定义基础类型
- 支持 <stdint.h>、<stdbool.h>中定义的基本类型，即常见的uin8_t、in8_t和bool等，建议使用u8、s8等

### 2.2 struct

保持C语言原有风格，不使用typedef重定义，使用时也是直接写上struct，注意使用小写作为struct的名称

```c
struct name{
	...
};
```

### 2.3 enum

保持C语言原有风格，不使用typedef重定义，使用时也是直接写上enum，注意使用小写作为enum的名称

```c
enum XXX
{
	...
};
```

### 2.4 union

保持C语言原有风格，不使用typedef重定义，使用时也是直接写上union，注意使用小写作为union的名称

```c
union XXX 
{
    ...
};
```

考虑到不同编译器对union的支持不同，而.h文件有可能被客户单独拿走使用，因此在.h文件中不允许使用union定义类型，可在.c文件使用

### 2.5 函数指针类型

以名称+"_func"结尾，建议使用如下风格：

```c
typedef void (*after_done_f)(void *,uint32_t);
```

## 3、命名

### 3.1 文件名(.c .h)

- 以功能模块命名

- 一个功能块对应一个.c文件（或.s文件）和一个.h文件
- 多个功能块不共用同一个.c或.h文件

### 3.2 变量

#### 3.2.1 文件内全局变量

包含局部静态变量

小写 local_

#### 3.2.2 文件外全局变量

小写 global_

.h中声明全局变量，在对应的.c中定义变量，注意不要在.h中定义全局变量

#### 3.2.3 局部变量

- 以实际含义命名，控制字母的数量，用可读性最高的写法  

- 不区分变量类型，即从变量的名称中看不出变量的类型，但能看出含义
- 保留i,j,k作为for循环的变量，除此之外，i,j,k不运行出现在其它地方

#### 3.2.4 数组变量

通用后缀 _ary

常用后缀 _buff、 _hub、 _list

常用的buffer、hub、list等暗含数组类型的命名，可以不用_ary后缀

#### 3.2.5 指针变量

以p_开头，加具体名称

多层指针则多个p，不建议使用超过2层指针

#### 3.2.6 函数指针变量

- pf_ 一般函数指针
- cb_ 特指回调函数

#### 3.2.7 基本实例

```c
//文件内全局变量
static uint8_t local_var_in_file;

//文件外全局变量
uint32_t global_var;

//局部变量(看不出类型，看得出含义)
void func()
{
	uint8_t str_len;
	uint32_t pin_num;
    ...
}

//局部静态变量
void func()
{
    static uint8_t local_var;//local_前缀
    ...
}

//数组变量
uint8_t led_ary[2];
uint8_t led_hub[2];
uint8_t tx_buff[128];

//指针变量
uint8_t * p_data;
uint32_t * p_buff;

//函数指针类型 _func 后缀
//一般函数指针变量 pf_ 前缀
typedef void (*read_func)(void *,uint32_t);
read_func pf_read;
    
//函数指针类型 _func 后缀
//回调函数指针变量 cb_ 前缀
typedef void (*read_done_func)(void *,uint32_t);
read_done_func cb_read_done;

struct xxx {
    ...
    read_func		pf_read;
    read_done_func	cb_read_done;
    ...
};
```

#### 3.2.8 复合实例

```c
//全局指针变量
uint32_t * global_p_rx_buff;

//文件外全局自定义类型变量
struct struct_name{
    ...
    uint8_t 
    uint32_t
    ...
};

struct struct_name global_var;
struct struct_name * global_p_var;

//文件内全局内数组
uint8_t local_var_ary[10];

//文件内指针
uint8_t * local_p_data;
```

#### 3.2.9 不规范命名

```c
//不使用typedef对指针类型重新命名别名，可对uint8_t等类型重命名别名
typedef uint32_t * mytype1_t;
typedef uint32_t ** mytype2_t;
//此时定义一个全局变量
mytype2_t * g_p_var;
//容易让人误认为是一级指针

//不使用SDK2.1中把enum类型当作赋初值的用法
enum SSI_CTRLR0_FIELD
{
    SSI_SPI_FRF_MASK = 0x600000,
    SSI_SPI_FRF_POS = 21,
    SSI_DFS_MASK = 0x1f0000,
    SSI_DFS_POS = 16,
    SSI_CFS_MASK = 0xf000,
    SSI_CFS_POS = 12,
    SSI_SRL_MASK = 0x800,
    SSI_SRL_POS = 11,
    SSI_SLV_OE_MASK = 0x400,
    SSI_SLV_OE_POS = 10,
    SSI_TMOD_MASK = 0x300,
    SSI_TMOD_POS = 8,
    SSI_SCPOL_MASK = 0x80,
    SSI_SCPOL_POS = 7,
    SSI_SCPH_MASK = 0x40,
    SSI_SCPH_POS = 6,
    SSI_FRF_MASK = 0x30,
    SSI_FRF_POS = 4,
};
//正确的做法应该使用define的形式：
#define SSI_SPI_FRF_POS		(21UL)
#define SSI_SPI_FRF_MASK	( 0X3UL << SSI_SPI_FRF_POS )
//0X3<<21 = 0x600000
//其余的同上
//关于#define的命名方式，后面还有讲
```

### 3.3 函数

#### 3.3.1 私有函数

- static 限定文件内使用
- 命名不添加前后缀，直接表达函数含义
- 不区分返回值类型，即从函数名称中看不出返回值的类型，但能看出函数基本含义

#### 3.3.2 导出函数

 以文件名+功能的形式命名，文件名太长的可以使用缩写

#### 3.3.3 中断服务函数

_irq 后缀

#### 3.3.4 预定义函数

- __weak 修饰函数
- _callback为后缀 

预定义函数为定义给用户的重新编写的函数，属于回调函数的另一种写法，多存在于中断函数中，对比如下：

- 使用函数指针：

```c
//在xxx.h中：
...
typedef void (*abc_func)(void);
...
void xxx_set_callback(abc_func pf_abc);
...
    
    
//在xxx.c中
...
static abc_func local_pf_abc;
...
    
void xxx_set_callback(abc_func pf_abc)
{
    ...
	local_pf_abc = pf_abc;
    ...
}
...
...
...
void xxx_irq(void)
{
    ...
    if( local_pf_abc != null )
        local_pf_abc();
    ...
}

//用户在使用时：
#include "xxx.h"

void xxx_callback()
{
    ...
}

void main()
{
    ...
    xxx_set_callback(xxx_callback_func);
    ...
}
```

- 使用预定义函数

```c
//在xxx.h中：
...
void xxx_callback(void);
...
    
    
//在xxx.c中

...    
__weak void xxx_callback(void)
{
    ...
}
...
...
...
void xxx_irq(void)
{
    ...
    xxx_callback();
    ...
}

//用户在使用时：
#include "xxx.h"

void xxx_callback()
{
    ...
}
...
void main()
{
    ...
    ...
}
```

因为使用了 __weak 修饰函数，并不会同时生成两个 xxx_callback 函数。

#### 3.3.3 实例

```c
//私有函数
static void set_value(uint32_t val)
{
    ...
}

static void clear_value(void)
{
    ...
}

//导出函数
bool gpio_init(void)
{
    ...
}

bool gpio_set_input(void)
{
    ...
}

//中断服务函数
void gpio_irq()
{
    ...
}

//预定义函数
__weak void gpio_after_clear_cabllback(void)
{
    ...
}
```

### 3.4 #define

- 注意使用括号包含好宏定义以及宏定义的参数

#### 3.4.1 宏函数

以括号"()"结尾的

- 私有，在.c中专用的，与私有函数命名规则一样
- 公有，在.h中使用，与导出函数命名规则一样
- 参数类型判断

```c
//私有 .c内使用，其它.c不使用
#define power_on()		(REG->BIT |= 1)

//公有 .h中
#define gpio_irq_enable()	...
#define gpio_irq_enable()	\
do{							\
	...						\
}while(0)

//参数类型判断，.c .h中均可使用
#define IS_XXX_TYPE(type)	(type==xxx||type==xxx||...)
```

#### 3.4.2 宏配置

常见配置类型有以下几种：

- 使能类

- 参数型

- 可选项

```c
//其它SDK上常见的配置宏定义：
#define USE_XXX				0
#define CONFIG_XXX			1234
#define configXXX			1234
#define XXX_ENABLE			1
#define INCLUDE_XXX			1
```

NRF的做法：

```c
//使能型 值只有1或者0
#define NFC_T4T_TLV_BLOCK_PARSER_ENABLED 0
#define NRF_XXX_XXX_ENABLED 1

#define SPI1_USE_EASY_DMA 	1
#define XXX_USE_XXX			1

//参数型	注释标明范围
#define SEGGER_RTT_CONFIG_BUFFER_SIZE_UP 512
#define XXX_CONFIG_XXX		512

//可选项	注释标明可选项有哪些
#define SER_HAL_TRANSPORT_CONFIG_INFO_COLOR 0
#define XXX_CONFIG_XXX		0
```

直接使用NRF的命名方式

## 4、代码布局

### 4.1、.c文件

#### 4.1.1 基本模板

```c
/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author :	BLUEX OD Team
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *	This software component is licensed by ...
  *
  ******************************************************************************
  */
/* config --------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/

/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* private function ----------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* import function prototypes ------------------------------------------------*/


/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/


```

#### 4.1.2 相关描述

相关描述在第一部分，具体如下：

```c
/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
```

此部分在初次编写代码时不需要填写任何内容，在代码基本确定无误后才应该填写，其中：

- @brief 		介绍文件基本功能
- @attention 说明文件的注意事项
- 其余版本、作者名称、版权信息待定

#### 4.1.3 配置项

```c
/* config -------------------------------------------------------------------*/

```

此部分主要是限定此文件内的配置，而不影响其它文件的配置，最常见的是debug级别的重新定义：

```c
//debug.h
...
#define DEBUG_LEVEL_P 1
...
#define LOG(levle,...)	if( levle <= DEBUG_LEVEL_P ) printf("")
...


//c_file1.c
...
/* config -------------------------------------------------------------------*/

/* includes ------------------------------------------------------------------*/
#include "debug.h"
...
void func()
{
	...
	LOG(2,"c_file1:hi");
	...
}
...


    
//c_file2.c
...
/* config -------------------------------------------------------------------*/
#define DEBUG_LEVEL_P 2

/* includes ------------------------------------------------------------------*/
#include "debug.h"
...
void func()
{
	...
	LOG(2,"c_file2:hi");
	...
}
...

```

当如上设置时，“c_file2:hi”会输出，而c_file1的不会输出。

#### 4.1.4 包含头文件

```c
/* includes ------------------------------------------------------------------*/

```

#### 4.1.5 仅限文件内使用

```c
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* private macros ------------------------------------------------------------*/

```

#### 4.1.6 全局变量定义

```c
/* exported variables --------------------------------------------------------*/

```

在.h声明的变量，在此处定义

#### 4.1.7 导入函数声明

```c
/* import function prototypes ------------------------------------------------*/

```

此项为可选项，主要是过渡使用，用于目前部分代码在.s文件中实现，但是又没有相对应的.h文件，可以在此处进行声明引入，以后的代码应该一个.c或者.s对应一个.h，使用的时候在include的位置包相关头文件包含进来，不是用这种偷懒的方式。

#### 4.1.8 函数说明

```c
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :	[in]	param1
 * @param   :	[out]	param2
 * @retval  :
-----------------------------------------------------------------------------*/
```

- @brief	   基本功能说明
- @note       注意事项，如调用函数前先调用什么
- @param   参数说明，使用[in]、[out]注明参数方向
- @retval     返回值，以及返回值的含义

- 对于一般函数，都需要添加函数说明
- 对于宏函数，若功能复杂，则应添加函数说明，若功能简单，则可不添加函数说明

#### 4.1.9 私有函数实现

```c
/*============================= private function =============================*/
//此处存放具体代码
/*========================= end of private function ==========================*/

```

对应命名中的[私有函数](####3.3.1 私有函数)

#### 4.1.10 导出函数实现

```c
/*============================= exported function ============================*/
//此处存放具体代码
/*========================= end of exported function =========================*/
```

对应命名中的[导出函数](####3.3.2 导出函数)

#### 4.1.11 导入函数实现

```c
/*============================= import function ==============================*/
//此处存放具体代码
/*=========================== end of import function =========================*/

```

对应命名中的[预定义函数](####3.3.4 预定义函数)，此处编写的代码即为对预定义代码的重新实现

#### 4.1.12 中断函数

```c
/*============================ interrupt function ============================*/
//此处存放具体代码
/*========================= end of interrupt function ========================*/

```

对应命名中的[中断服务函数](####3.3.3 中断服务函数)

#### 4.1.13 文件结束

```c
/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

```

注意多空一行，主要是避免MDK的一个警告

### 4.2 .h文件

#### 4.2.1 基本模板

```C
/**
  ******************************************************************************
  * @file   :   .h
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AB_CD_EF_H__
#define __AB_CD_EF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* includes ------------------------------------------------------------------*/

/* exported config -----------------------------------------------------------*/

/* exported types ------------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/

/* exported constants --------------------------------------------------------*/

/* exported macros -----------------------------------------------------------*/

/* exported functions --------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* __AB_CD_EF_H__ */

/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/

```

#### 4.2.2 相关描述

```c
/**
  ******************************************************************************
  * @file   :   .h
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) . BLUEX Microelectronics.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
```

同.c文件 [4.1.2 相关描述](####4.1.2 相关描述)

#### 4.2.3 预定义

```c
/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __AB_CD_EF_H__
#define __AB_CD_EF_H__

#ifdef __cplusplus
extern "C" {
#endif

...

#ifdef __cplusplus
}
#endif

#endif /* __AB_CD_EF_H__ */

//注意前后都有双下划线 __AB_CD_EF_H__
```

#### 4.2.4 包含头文件

```c
/* includes ------------------------------------------------------------------*/

```

#### 4.2.5 配置项

```c
/* exported config -----------------------------------------------------------*/

```

主要是参数配置，与.c中的配置略有不同，如配置最大值之类的数据，而在定义类型是可能会用到此参数

此项也是过渡使用，某些数值参数可暂时先存放在此处，后期会把该类配置型参数，统一成一个专用的配置文件

#### 4.2.6 导出类型

```c
/* exported types ------------------------------------------------------------*/

```

#### 4.2.7 导出变量声明

```c
/* exported variables --------------------------------------------------------*/

```

注意只是声明，并非定义

#### 4.2.10 常量定义

```c
/* exported macros -----------------------------------------------------------*/

```

#### 4.2.11 宏函数定义

```c
/* exported macros -----------------------------------------------------------*/

```

注意宏函数定义应该按功能是否复杂添加必要的[函数说明](####4.1.8 函数说明)

#### 4.2.12 一般函数定义

```c
/* exported functions --------------------------------------------------------*/

```

- 一般函数定义不需要添加函数说明，因为在.c中添加了
- 可稍微分组，例如读、写操作，稍微分组

#### 4.2.13 文件结束

```c
/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/
```

### 4.3 代码风格

- 对于if、while、switch...case，操作符、等要求，在编写代码时不作要求，但是在代码编写完成后，使用AStyle对代码进行格式化，AStyle参数为“-n !E --style=linux -s4 -S -p -D -m0 -M40 -c -j -k2”

```c
//原始代码:
void func(){uint8_t a,b,c;if(1)c=a+b;else c=a-b;}

//经过Astyle格式化的代码(AStyle参数同上)：
void func()
{
    uint8_t a, b, c;
    if( 1 ) {
        c = a + b;
    } else {
        c = a - b;
    }
}

//更多的AStyle操作请自行查找，推荐 http://www.tzwyx.com/717.html
```

目前Astyle对 .h .s 文件支持并不太好，暂时只使用AStyle对.h .s文件进行格式化，后期会给出相关代码格式化工具，对于目前的.h文件，请手动对齐，注意把Tab换成空格填充

## 5、注释

- 不使用 C++风格的双斜线（//）注释
- 使用 /**/ 注释
- 单行注释原则上不超过80列，特殊情况除外
- 可多行注释
- 尽量捉住关键点，尽量简短
- 函数内不添加过多注释，尽量在函数外添加注释，即在函数说明中写注释

## 6、其它

### 6.1 #if

- 若#endif距离#if较远，在#endif 后面注意添加注释 /*  */，说明是哪一个预编译条件结束

```c
#if A
...
//此处省略代码200行
#if B
...
//此处省略代码100行
#else
...
//此处省略代码100行
#endif /* B */
...
//此处省略代码300行
#if C
...
//此处省略代码500行
#else
...
//此处省略代码500行
#endif /* C */
#endif /* A */
```

