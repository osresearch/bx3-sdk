# 用库函数的方式介绍TIME的使用

## 1、概述

本文档使用库函数的方式介绍TIME的使用,单位时间可精确到us，目前最高周期为1s。

## 2、新建工程

1、新建工程，首先复制下图工程：

![](image3.png)

2、粘贴到SDK3\example目录下

3、修改文件名为bxd_timer,将工程名修改为bxd_timer

4、打开工程添加文件

- bxd_tim.c
- bxd_gpio.c
- bx_pm.h

## 3、编写代码

在app_init()函数添加以下代码

```c
void app_init(void)
{
		bx_pm_lock(BX_PM_TIM);
		bxd_timer_open(BX_TIM0);		//打开定时器0的驱动
		bxd_timer_open(BX_TIM1);		//打开定时器1的驱动
		bx_pm_lock(BX_PM_GPIO);
		bxd_gpio_open(BX_GPIOA);		//打开gpio驱动
		bxd_timer_start(BX_TIM0,1000000);	//每1s定时器0工作一次
		bxd_timer_start(BX_TIM1,500000);		//每0.5s定时器1工作一次
		bxd_gpio_set_mode(BX_GPIOA,2,BX_GPIO_MODE_OUTPUT);
    //设置2号引脚为输出模式
		bxd_gpio_set_mode(BX_GPIOA,3,BX_GPIO_MODE_OUTPUT);
    //设置3号引脚为输出模式
}
```

添加定时器中断函数TIMER_IRQHandler函数

```c
void TIMER_IRQHandler(void)
{
		uint32_t timer_isr_status0,timer_isr_status1;
		timer_isr_status0 = BX_TIM0->IS & 0x01;
		timer_isr_status1 = BX_TIM1->IS & 0x01;
		if(timer_isr_status0)
		{
			BX_READ_REG(BX_TIM0->EOI);
			bxd_gpio_toggle(BX_GPIOA,2);	//翻转2号引脚
		}
		if(timer_isr_status1)
		{
			BX_READ_REG(BX_TIM1->EOI);
			bxd_gpio_toggle(BX_GPIOA,3);	//翻转3号引脚
		}
}
```



## 4、功能演示

定时翻转LED1和LED2

- 按照第三章3.1、3.2代码实现
- 编译文件，然后烧录文件
- 演示结果

RF01板子上的LED1每隔0.5s翻转一次，LED2每隔1s翻转一次