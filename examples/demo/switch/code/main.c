/**
  ******************************************************************************
  * @file   :   main.c
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

/* includes ------------------------------------------------------------------*/

#include "bx_kernel.h"
#include "ble_stack.h"
#include "app.h"

#include "bxd_gpio.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/

/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/

/*========================= end of private function ==========================*/


/*============================= exported function ============================*/
#define OUTPUT_PIN_NUM 10
#define INPUT_PIN_NUM 11

#define OUTPUT_PIN GPIO_PIN_10
#define INPUT_PIN GPIO_PIN_11

bool daotong = false;
void set_daotong_false( void * arg )
{
    daotong = false;

}

void set_daotong_true( void * arg )
{
    daotong = true;
    bx_dwork( set_daotong_false, NULL, 100, 1 );
    bxd_gpio_toggle(BX_GPIOA,2);
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
int main( void )
{
    ble_init();
    bx_kernel_init();

    app_init();

    bxd_gpio_open( BX_GPIOA );
    bxd_gpio_set_mode( BX_GPIOA, OUTPUT_PIN_NUM, BX_GPIO_MODE_OUTPUT );
    bxd_gpio_set_mode( BX_GPIOA, 2, BX_GPIO_MODE_OUTPUT );
    bxd_gpio_set_mode( BX_GPIOA, INPUT_PIN_NUM, BX_GPIO_MODE_INPUT );
    bx_dwork( set_daotong_true, NULL, 1000, -1 );


    while( 1 ) {
        ble_schedule();
        bx_kernel_schedule();
        if( daotong ) {
            if( BX_GPIOA->ID & INPUT_PIN ) {
                BX_GPIOA->OD |= OUTPUT_PIN;
            } else {
                BX_GPIOA->OD &= ~OUTPUT_PIN;
            }
        } else {
            BX_GPIOA->OD |= OUTPUT_PIN;
        }

    }
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



