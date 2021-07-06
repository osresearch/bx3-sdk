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

/* includes ------------------------------------------------------------------*/
#include "bxd_pwm.h"
#include "bxd_io_mux.h"

#include "bxd_gpio.h"

/* includes ------------------------------------------------------------------*/
#define PWM_MAX_FREQUENCY_HZ                    16000000

/* private define ------------------------------------------------------------*/
#define CHECK_DIV(hdl)                                   \
do{                                                         \
    if( (hdl) < 2 ){                                \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)


#define CHECK_HANDLE(hdl)                                   \
do{                                                         \
    if( (hdl) != BX_PWM0 &&                                 \
        (hdl) != BX_PWM1 &&                                 \
        (hdl) != BX_PWM2 &&                                 \
        (hdl) != BX_PWM3 &&                                 \
        (hdl) != BX_PWM4 ) {                                \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_PIN_NUM(pin_num)                              \
do{                                                         \
    if( (pin_num) < 2 || (pin_num) > 23 ){                  \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_POINTER(p)                                    \
do{                                                         \
    if( (p) == NULL ) {                                     \
        return BX_ERR_POINTER_EMPTY;                        \
    }                                                       \
}while(0)

#define CHECK_FREQUENCY( freq )                             \
do{                                                         \
    if( (freq) > PWM_MAX_FREQUENCY_HZ && (freq) != 0 ) {    \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

#define CHECK_DUTY( duty )                                  \
do{                                                         \
    if( (duty) > 100 ) {                                    \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

/* private typedef -----------------------------------------------------------*/
struct bx_pwm_drv {
    void * handle;

    u8 pin_num;
    u8 pin_type;
};

/* private variables ---------------------------------------------------------*/
static struct bx_pwm_drv pwm_drv[5] = { 0 };
static u8 pwm_div = 0;
/* exported variables --------------------------------------------------------*/


/*============================= private function =============================*/


/*========================= end of private function ==========================*/


/*============================= exported function ============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_pwm_set_pin( void * hdl, u8 pin_num )
{
    CHECK_HANDLE( hdl );
    CHECK_PIN_NUM( pin_num );
    reg_pwm_t * BX_PWMx = ( reg_pwm_t * )hdl;

    if( BX_PWMx == BX_PWM0 ) {
        pwm_drv[0].handle = BX_PWMx;
        pwm_drv[0].pin_num = pin_num;
        pwm_drv[0].pin_type = BX_PIN_TYPE_PWM0;
        return bxd_iomux_set_pin_type( pin_num, BX_PIN_TYPE_PWM0 );
    } else if ( BX_PWMx == BX_PWM1 ) {
        pwm_drv[1].handle = BX_PWMx;
        pwm_drv[1].pin_num = pin_num;
        pwm_drv[1].pin_type = BX_PIN_TYPE_PWM1;
        return bxd_iomux_set_pin_type( pin_num, BX_PIN_TYPE_PWM1 );
    } else if ( BX_PWMx == BX_PWM2 ) {
        pwm_drv[2].handle = BX_PWMx;
        pwm_drv[2].pin_num = pin_num;
        pwm_drv[2].pin_type = BX_PIN_TYPE_PWM2;
        return bxd_iomux_set_pin_type( pin_num, BX_PIN_TYPE_PWM2 );
    } else if ( BX_PWMx == BX_PWM3 ) {
        pwm_drv[3].handle = BX_PWMx;
        pwm_drv[3].pin_num = pin_num;
        pwm_drv[3].pin_type = BX_PIN_TYPE_PWM3;
        return bxd_iomux_set_pin_type( pin_num, BX_PIN_TYPE_PWM3 );
    } else if ( BX_PWMx == BX_PWM4 ) {
        pwm_drv[4].handle = BX_PWMx;
        pwm_drv[4].pin_num = pin_num;
        pwm_drv[4].pin_type = BX_PIN_TYPE_PWM4;
        return bxd_iomux_set_pin_type( pin_num, BX_PIN_TYPE_PWM4 );
    } else {
        return BX_ERR_INVAL;
    }

//    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_pwm_open( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_pwm_t * BX_PWMx = ( reg_pwm_t * )hdl;

    /* close clock gate */
    if( BX_PWMx == BX_PWM0 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM0;
    } else if ( BX_PWMx == BX_PWM1 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM1;
    } else if ( BX_PWMx == BX_PWM2 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM2;
    } else if ( BX_PWMx == BX_PWM3 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM3;
    } else if ( BX_PWMx == BX_PWM4 ) {
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM4;
    } else {
        return BX_ERR_INVAL;
    }

    /* clk div config */
    BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM_DIV;
    uint8_t div = 1;/* PWM tick clock = 32MHz/(div+1) zero means divide by 2 */
    BX_PER->CDP0 |= ( uint32_t )div << PER_CDP0_PWM_POS;
    BX_PER->CLKG1 |= PER_CLKG1_SET_PWM_DIV;

    /* open clock gate */
    if( BX_PWMx == BX_PWM0 ) {
        BX_PER->CLKG1 |= PER_CLKG1_SET_PWM0;;
    } else if ( BX_PWMx == BX_PWM1 ) {
        BX_PER->CLKG1 |= PER_CLKG1_SET_PWM1;
    } else if ( BX_PWMx == BX_PWM2 ) {
        BX_PER->CLKG1 |= PER_CLKG1_SET_PWM2;
    } else if ( BX_PWMx == BX_PWM3 ) {
        BX_PER->CLKG1 |= PER_CLKG1_SET_PWM3;
    } else if ( BX_PWMx == BX_PWM4 ) {
        BX_PER->CLKG1 |= PER_CLKG1_SET_PWM4;
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :Note that the clocks for all channels will be modified
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_pwm_set_clock_div( u8 div )
{
	/* div minimum value is 2 */
	CHECK_DIV(div);
	/* PWM tick clock = 32MHz/div */
    BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM_DIV;
    BX_PER->CDP0 = ( uint32_t )(div - 1) << PER_CDP0_PWM_POS;
    BX_PER->CLKG1 |= PER_CLKG1_SET_PWM_DIV;
	pwm_div = div;
    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_pwm_close( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_pwm_t * BX_PWMx = ( reg_pwm_t * )hdl;

    /* close clock gate */
    if( BX_PWMx == BX_PWM0 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM0;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM0;
    } else if ( BX_PWMx == BX_PWM1 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM1;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM1;
    } else if ( BX_PWMx == BX_PWM2 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM2;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM2;
    } else if ( BX_PWMx == BX_PWM3 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM3;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM3;
    } else if ( BX_PWMx == BX_PWM4 ) {
        BX_PER->CLKG1 &= ~PER_CLKG1_SET_PWM4;
        BX_PER->CLKG1 |= PER_CLKG1_CLR_PWM4;
    } else {
        return BX_ERR_INVAL;
    }

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_pwm_start( void * hdl, u32 freq, u8 duty )
{
    CHECK_HANDLE( hdl );
    CHECK_FREQUENCY( freq );
    CHECK_DUTY( duty );
    reg_pwm_t * BX_PWMx = ( reg_pwm_t * )hdl;


    uint32_t high_time;
    uint32_t low_time;
    u32 pin_mask ;
    static bool is_set_funcio = false;
    if( duty == 0 ) {
        for( u8 i = 0; i < 5; i++ ) {
            if( pwm_drv[i].handle == BX_PWMx ) {
                BX_PWMx->EN = 0;
                bxd_iomux_set_pin_type( pwm_drv[i].pin_num, BX_PIN_TYPE_GENERAL_IO );

                BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
                pin_mask =  0x01UL << pwm_drv[i].pin_num;
                BX_GPIOA->DIR |= ( pin_mask );
                BX_GPIOA->OD &= ~( 0x01UL << pwm_drv[i].pin_num );
                break;
            }
        }
        is_set_funcio = true;
    } else if( duty == 100 ) {
        for( u8 i = 0; i < 5; i++ ) {
            if( pwm_drv[i].handle == BX_PWMx ) {
                BX_PWMx->EN = 0;
                bxd_iomux_set_pin_type( pwm_drv[i].pin_num, BX_PIN_TYPE_GENERAL_IO );

                BX_PER->CLKG1 |= PER_CLKG1_SET_GPIO;
                pin_mask =  0x01UL << pwm_drv[i].pin_num;
                BX_GPIOA->DIR |= ( pin_mask );
                BX_GPIOA->OD |= ( 0x01UL << pwm_drv[i].pin_num );
                break;
            }
        }
        is_set_funcio = true;
    } else {
		high_time = ( ( 320000 / ( pwm_div) ) * duty ) / ( freq );
        low_time  = ( ( 320000 / ( pwm_div) ) * ( 100 - duty ) ) / ( freq );
        if( high_time > 0xFFFF || low_time > 0xFFFF ) {
            return BX_ERR_INVAL;
        }
        for( u8 i = 0; i < 5 && is_set_funcio ; i++ ) {
            if( pwm_drv[i].handle == BX_PWMx ) {
                bxd_iomux_set_pin_type( pwm_drv[i].pin_num,pwm_drv[i].pin_type);
                break;
            }
        }

        BX_PWMx->EN = 0;
        BX_PWMx->PS = ( ( uint32_t )high_time << 16 ) | low_time;
        BX_PWMx->EN = 1;
        is_set_funcio = false;
    }

    return BX_OK;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bx_err_t bxd_pwm_stop( void * hdl )
{
    CHECK_HANDLE( hdl );
    reg_pwm_t * BX_PWMx = ( reg_pwm_t * )hdl;
    BX_PWMx->EN = 0;
    return BX_OK;
}
/*========================= end of exported function =========================*/


/*============================= import function ==============================*/

/*=========================== end of import function =========================*/


/*============================ interrupt function ============================*/

/*========================= end of interrupt function ========================*/


/******************** (C) COPYRIGHT BLUEX **********************END OF FILE****/



