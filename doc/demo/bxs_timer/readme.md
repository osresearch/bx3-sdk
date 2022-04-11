# 用消息的方式介绍TIME的使用

## 1、概述

本文档使用库函数的方式介绍TIME的使用,单位时间可精确到us，目前最高周期为1s。

## 2、新建工程

1、新建工程，首先复制下图工程：

![](image1.png)

2、粘贴到SDK3\example目录下

3、修改文件名为bxs_timer,将工程名修改为bxs_timer

4、打开工程添加文件

- bxd_tim.c
- bxs_tim.c
- bxd_gpio.c
- bxs_gpio.c

## 3、编写代码

```c
#define LED2 3
#define LED1 2
    s32 us_svc;
    void app_init( void ) {
        s32 user_service_id;
        struct bx_service svc;
        svc.prop_set_func = NULL;
        svc.prop_get_func = NULL;
        svc.msg_handle_func = user_msg_handle_func;
        svc.name = "user service";
        us_svc = bx_register( &svc );

        bxs_tim_register();
        bxs_gpio_register();

        s32 id0 = bxs_tim0_id();
        s32 id1 = bxs_tim1_id();
        s32 id_gpio = bxs_gpio_a_id();

        bx_call( id0, BXM_OPEN, 0, 0 ); //启动TIM0服务
        bx_call( id1, BXM_OPEN, 0, 0 ); //启动TIM1服务
        bx_call( id_gpio, BXM_OPEN, 0, 0 ); //启动GPIO服务

        bx_call( id0, BXM_START, 1000000, 0 ); //每隔1s定时器0工作一次
        bx_call( id1, BXM_START, 500000, 0 ); //每隔0.5s定时器1工作一次

        bx_set( id_gpio, BXP_MODE, LED2, BX_GPIO_MODE_OUTPUT ); //将LED2设置为输出模式
        bx_set( id_gpio, BXP_MODE, LED1, BX_GPIO_MODE_OUTPUT ); //将LED1设置为输出模式

        bx_subscibe( id0, BXM_TIM0_INTR, 0, 0 ); //订阅TIM0中断消息
        bx_subscibe( id1, BXM_TIM1_INTR, 0, 0 ); //订阅TIM1中断消息
    }
```

添加user_msg_handle_func()函数

```c
    bx_err_t user_msg_handle_func( s32 id, u32 msg, u32 param0, u32 param1 ) {
        s32 id_gpio = bxs_gpio_a_id();

        if( ( bx_msg_source() != bxs_tim0_id() ) && ( bx_msg_source() != bxs_tim1_id() ) )
//判断消息是否来自tim0服务或者tim1服务
        {
            return 0;
        }
        switch( msg ) {
            case BXM_TIM0_INTR:     //消息为BXM_TIM0_INTR翻转LED1
                bx_call( id_gpio, BXM_TOGGLE, LED1, 0 );
                break;

            case BXM_TIM1_INTR:     //消息为BXM_TIM1_INTR翻转LED2
                bx_call( id_gpio, BXM_TOGGLE, LED2, 0 );
                break;
        }
        return BX_OK;
    }
```

## 4、功能演示

定时翻转LED1和LED2

- 按照第三章3.1、3.2代码实现
- 编译文件，然后烧录文件
- 演示结果

RF01板子上的LED1每隔0.5s翻转一次，LED2每隔1s翻转一次