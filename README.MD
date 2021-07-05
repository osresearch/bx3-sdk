# 版本更新

当前SDK3最新版本为：SDK3.3

[SDK3.3发行版下载](https://gitee.com/BXMicro/SDK3/releases)



相较SDK3.2版本，SDK3.3有以下更新：

- rf01、rf03、rf04 3款芯片在保证连接稳定性的前提下，支持去除32768晶振（去除后部分应用功耗会有所增加）
- rf参数版本更新为18.7，更优异的rf特性
- 低温、低压环境自动调整rf参数，更稳定的连接
- 新增QSPI 4线驱动API，最高可达48M，更快的刷屏速度
- 解决flash在某些条件下读写错误的bug，引进优质第三方代码，数据存储更可靠、安全

- 优化log文件组织结构，分文件、模块开关log，程序调试更方便
- 将bx_service_xxx的命名方式修改为bxs_xxx，将bx_drv_xxx的命名方式修改为bxd_xxx，更简洁的命名方式
- 外设驱动新增更多的API，编程控制更灵活
- 大量例程代码和文档（视频部分正在规划），掌握SDK和芯片掌握速度更快
- 新增应用基础模板，新项目代码启动速度更快



# 文档中心

[SDK3.3说明文档](https://gitee.com/BXMicro/SDK3_DOC)

[SDK3.3例程代码](https://gitee.com/BXMicro/SDK3_Demo)



| 例程                       | 概述                                                         |
| -------------------------- | ------------------------------------------------------------ |
| base                       | 一个包含BLE协议栈的基础模板，无其它任何功能                  |
| ble_base                   | 一个BLE基础功能的模板，包含一个dis服务，可广播，连接，收发数据 |
| app_base                   | 一个BLE产品所需要的基础从机模板，包括一个dis服务,OTA服务，键值对存储，异常查错，调试输出，所有功能均可按需配置 |
| base_sram_io_max           | 代码运行在sram，同时把所有pin引脚都配置为普通的输入输出      |
|                            |                                                              |
| bxd_adc                    | 使用库函数的方式介绍adc的使用步骤和功能                      |
| bxd_spi                    | 使用库函数的方式介绍spi的使用步骤和功能                      |
| bxd_iic                    | 使用库函数的方式介绍iic的使用步骤和功能                      |
| bxd_gpio                   | 使用库函数的方式介绍gpio的使用步骤和功能                     |
| bxd_timer                  | 使用库函数的方式介绍timer的使用步骤和功能                    |
| bxd_pwm                    | 使用库函数的方式介绍pwm的使用步骤和功能                      |
| bxd_uart                   | 使用库函数的方式介绍uart的使用步骤和功能                     |
| bxd_flash                  | 使用库函数的方式介绍flash的使用步骤和功能                    |
| bxd_sleep                  | 介绍BX设备如何进入休眠，以及唤醒后外设使用的注意事项         |
| bxd_sys_tick               | 使用库函数的方式介绍sys_tick的使用步骤和功能                 |
|                            |                                                              |
| bxs_adc                    | 使用消息的方式介绍adc的使用步骤和功能                        |
| bxs_spi                    | 使用消息的方式介绍spi的使用步骤和功能                        |
| bxs_iic                    | 使用消息的方式介绍iic的使用步骤和功能                        |
| bxs_gpio                   | 使用消息的方式介绍gpio的使用步骤和功能                       |
| bxs_timer                  | 使用消息的方式介绍timer的使用步骤和功能                      |
| bxs_pwm                    | 使用消息的方式介绍pwm的使用步骤和功能                        |
| bxs_uart                   | 使用消息的方式介绍uart的使用步骤和功能                       |
| bxs_sleep                  | 以消息的方式介绍BX设备如何进入休眠，以及唤醒后外设使用的注意事项 |
|                            |                                                              |
| ble_adv_cnt                | 可连接广播例程                                               |
| ble_anps                   | 以添加一个anps服务作为一个例子，介绍如何添加一个标准profile  |
| ble_custom_profile         | 介绍如何添加一个自定义profile                                |
| ble_report                 | 以一个自定义profile来介绍notify、indicate的使用              |
| ble_bond                   | 从机绑定配对例程                                             |
| ble_scan                   | 主机扫描从机                                                 |
| ble_connect                | 主机连接从机                                                 |
| ble_mlt_cnt                | 多连接                                                       |
| ble_all                    | 主从一体                                                     |
|                            |                                                              |
| bx_service                 | 如何新建一个service                                          |
| bx_api                     | 对常用api的介绍bx_register、bx_post、bx_repeat、bx_defe、bx_dwork等 |
| bx_ota                     | 介绍OTA的使用，包括配套的APP操作流程                         |
| bx_log                     | 介绍uart和rtt的方式使用log                                   |
|                            |                                                              |
| bxe_cmd_parser             | 一个简单的嵌入式命令解释                                     |
| bxe_easylogger             | 轻量级高性能日志库                                           |
| bxe_matrix_keyboard_wakeup | 可唤醒的矩阵键盘                                             |
| bxe_flashdb                | 介绍flashdb的移植和使用(键值对存储)                          |
| bxe_mpu9250                | mpu9250的使用，姿态角的获取                                  |
| bxe_led                    | 通过手机控制一些列灯的开关                                   |
| bxe_pwm                    | 通过手机控制PWM的输出                                        |
| bxe_qspi_lcd               | qspi屏幕                                                     |
|                            |                                                              |
| bxa_tt                     | 透传（transparent_transmission）应用，支持UART透传、IIC透传、SPI透传 |
| bxa_hid                    | hid应用(鼠标、键盘等)                                        |
|                            |                                                              |
| ble_speed_test             | 速度测试                                                     |



# How to

[如何将SDK3.3中修复的bug合并到SDK3.2?](https://gitee.com/BXMicro/SDK3_DOC/blob/master/%E5%A6%82%E4%BD%95%E5%B0%86SDK3.3%E4%B8%AD%E4%BF%AE%E5%A4%8D%E7%9A%84bug%E5%90%88%E5%B9%B6%E5%88%B0SDK3.2.md)

[如何将SDK3.2的项目移植到SDK3.3?](https://gitee.com/BXMicro/SDK3_DOC/blob/master/%E5%A6%82%E4%BD%95%E5%B0%86SDK3.2%E7%9A%84%E9%A1%B9%E7%9B%AE%E7%A7%BB%E6%A4%8D%E5%88%B0SDK3.3.md)

