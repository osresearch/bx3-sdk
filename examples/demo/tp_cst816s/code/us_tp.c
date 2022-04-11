/**
  ******************************************************************************
  * @file   :   .c
  * @version:
  * @author :
  * @brief  :
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) .
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */


#define LOG_LVL 5
#define LOG_TAG "[TP]"

/* includes ------------------------------------------------------------------*/
#include "log.h"
#include "bx_kernel.h"
#include "us_tp.h"
#include "bxd_gpio.h"
#include "bxd_iic.h"
#include "bx_pm.h"
#include "cst816s_comm.h"
/* private define ------------------------------------------------------------*/

/* private typedef -----------------------------------------------------------*/
enum usm_tp_def_ex {
    USM_TP_EX_FIRST = USM_TP_MAX,

    USM_TP_ACT_RESET_STEP1,
    USM_TP_ACT_RESET_STEP2,
    USM_TP_ACT_RESET_STEP3,
};
/* private variables ---------------------------------------------------------*/

/* exported variables --------------------------------------------------------*/
struct us_tp_service tp_svc = {0};
struct us_tp_data    tp_data = {0};
/* private macros ------------------------------------------------------------*/
#define GET_TP_SERVICE_BY_ID( p_svc, svc_id )              \
do{                                                         \
    if( ( svc_id ) == tp_svc.id ) {                        \
        p_svc = &tp_svc;                                   \
    } else {                                                \
        return BX_ERR_NOTSUP;                               \
    }                                                       \
}while(0)

#define CHECK_TP_SVC_PARAM( param )                        \
do{                                                         \
    if( param == NULL ) {                                   \
        return BX_ERR_INVAL;                                \
    }                                                       \
}while(0)

/*============================= private function =============================*/

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
static bx_err_t tp_msg_handle( s32 svc_id, u32 msg, u32 param0, u32 param1 )
{
    switch( msg ) {
        case BXM_OPEN: {
            LOG_D( "BXM_OPEN" );
            if( tp_svc.state != tp_sta_ready &&
                tp_svc.state != tp_sta_busy
              ) {
                tp_svc.state = tp_sta_ready;
            }
            return BX_OK;
        }

        case BXM_CLOSE: {
            LOG_D( "BXM_CLOSE" );
            if( tp_svc.state != tp_sta_closed ) {
                bxd_iic_close( BX_IIC1 );
                tp_svc.state = tp_sta_closed;
            }
            return BX_OK;
        }

            //Split the reset operation into two steps
        {
            case USM_TP_ACT_RESET: {
                LOG_D( "USM_TP_ACT_RESET" );
                if( tp_svc.state == tp_sta_closed ) {
                    return BX_ERR_STA;
                }
                tp_svc.state = tp_sta_busy;
                bx_post( tp_svc.id, USM_TP_ACT_RESET_STEP1, 0, 0 );
                return BX_OK;
            }

            case USM_TP_ACT_RESET_STEP1: {
                LOG_D( "USM_TP_ACT_RESET_STEP1" );
                bxd_gpio_write( BX_GPIOA, 7, 0 );
                bx_defer( tp_svc.id, USM_TP_ACT_RESET_STEP2, 0, 0, 100 );
                return BX_OK;
            }

            case USM_TP_ACT_RESET_STEP2: {
                LOG_D( "USM_TP_ACT_RESET_STEP2" );
                bxd_gpio_write( BX_GPIOA, 7, 1 );
                bx_defer( tp_svc.id, USM_TP_ACT_RESET_STEP3, 0, 0, 100 );
                return BX_OK;
            }

            case USM_TP_ACT_RESET_STEP3: {
                LOG_D( "USM_TP_ACT_RESET_STEP3" );
                tp_svc.state = tp_sta_ready;
            }
        }

        case USM_TP_ACT_GET_ID: {
            LOG_D( "USM_TP_ACT_GET_ID" );
            if( tp_svc.state == tp_sta_busy ) {
                return BX_ERR_BUSY;
            } else if( tp_svc.state == tp_sta_ready ) {
                tp_svc.state = tp_sta_busy;
                u8 whoami = 0;
                bx_err_t err = bxd_iic_read_ex( BX_IIC1, 0x2a, 0xa7, &whoami, 1, 100 );
                tp_svc.state = tp_sta_ready;
                if( err == BX_OK ) {
                    tp_svc.pdata->id = whoami;
                    LOG_D( "whoami = %x ", whoami );
                    return BX_OK;
                } else {
                    return us_tp_err_occurred(msg);
                }
            } else {
                return BX_ERR_STA;
            }
        }

        case USM_TP_ACT_UPDATE_SOFTWARE: {
            LOG_D( "USM_TP_ACT_UPDATE_SOFTWARE" );
            if( tp_svc.state == tp_sta_busy ) {
                return BX_ERR_BUSY;
            } else if( tp_svc.state == tp_sta_ready ) {
                tp_svc.state = tp_sta_busy;
                //cst816s_update();
                tp_svc.state = tp_sta_ready;
                bx_public( tp_svc.id, USM_TP_PBL_SOFTWARE_UPDATED, ( u32 )&tp_data, 0 );
                return BX_OK;
            } else {
                return BX_ERR_STA;
            }
        }

        case USM_TP_ACT_UPDATE_GUESTURE: {
            LOG_D( "USM_TP_ACT_UPDATE_GUESTURE" );
            if( tp_svc.state == tp_sta_busy ) {
                return BX_ERR_BUSY;
            } else if( tp_svc.state == tp_sta_ready ) {
                u8 guestureid = 0;
                tp_svc.state = tp_sta_busy;
                bx_err_t err = bxd_iic_read_ex( BX_IIC1, 0x2a, 0x01, &guestureid, 1, 100 );
                tp_svc.state = tp_sta_ready;
                if( err == BX_OK ) {
                    LOG_D( "guestureid = %x ", guestureid );
                    tp_svc.pdata->guesture = guestureid;
                    bx_public( tp_svc.id, USM_TP_PBL_GUESTURED_UPDATED, ( u32 )&tp_data, 0 );
                    return BX_OK;
                } else {
                    return us_tp_err_occurred(msg);
                }
            } else {
                return BX_ERR_STA;
            }
        }

        case USM_TP_ACT_UPDATE_POSITION: {
            LOG_D( "USM_TP_ACT_UPDATE_POSITION" );
            if( tp_svc.state == tp_sta_busy ) {
                return BX_ERR_BUSY;
            } else if( tp_svc.state == tp_sta_ready ) {
                u8 xypos[4] = {0};
                tp_svc.state = tp_sta_busy;
                bx_err_t err = bxd_iic_read_ex( BX_IIC1, 0x2a, 0x03, xypos, 4, 100 );
                tp_svc.state = tp_sta_ready;
                if( err == BX_OK ) {
                    tp_svc.pdata->pos_x = ( ( short )xypos[1] | ( ( short )( xypos[0] & 0x0F ) << 8 ) ) & 0x7FFF;
                    tp_svc.pdata->pos_y = ( ( short )xypos[3] | ( ( short )( xypos[2] & 0x0F ) << 8 ) ) & 0x7FFF;
                    tp_svc.pdata->pos_sta = ( xypos[0] & 0xF0 );
                    LOG_D( "(x = %d, y=%d) sta = 0x%x\r\n", tp_svc.pdata->pos_x,
                           tp_svc.pdata->pos_y, tp_svc.pdata->pos_sta );

                    bx_public( tp_svc.id, USM_TP_PBL_GUESTURED_UPDATED, ( u32 )&tp_data, 0 );
                    return BX_OK;
                } else {
                    return us_tp_err_occurred(msg);
                }
            } else {
                return BX_ERR_STA;
            }
        }

        case USM_TP_ACT_UPDATA_ALL_DATA: {
            LOG_D( "USM_TP_ACT_UPDATA_ALL_DATA" );
            if( tp_svc.state == tp_sta_busy ) {
                return BX_ERR_BUSY;
            } else if( tp_svc.state == tp_sta_ready ) {
                tp_svc.state = tp_sta_busy;
//                tp_svc.pdata->guesture = 0;
//                tp_svc.pdata->pos_x = 0;
//                tp_svc.pdata->pos_y = 0;
//                tp_svc.pdata->pos_sta = 0;
//                tp_svc.state = tp_sta_ready;
                bx_public( tp_svc.id, USM_TP_PBL_ALL_DATA_UPDATED, ( u32 )&tp_data, 0 );
                return BX_OK;
            } else {
                return BX_ERR_STA;
            }
        }

        case USM_TP_EVT_INTR: {
            if( tp_svc.state == tp_sta_busy ) {
                LOG_D( "busy" );
                return BX_OK;
            }
            LOG_D( "USM_TP_EVT_INTR" );
            bx_post( tp_svc.id, USM_TP_ACT_GET_ID, 0, 0 );
            bx_post( tp_svc.id, USM_TP_ACT_UPDATE_GUESTURE, 0, 0 );
            bx_post( tp_svc.id, USM_TP_ACT_UPDATE_POSITION, 0, 0 );
            return BX_OK;
        }

        default: {
            return BX_ERR_NOTSUP;
        }
    }
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/

__weak bx_err_t us_tp_err_occurred( u32 msg )
{
    LOG_D( "tp err msg = %u",msg );
    //while(1);
    return BX_ERROR;
}
/*========================= end of private function ==========================*/

/*============================= exported function ============================*/
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
void us_tp_init( void )
{
    bxd_gpio_open( BX_GPIOA );
//    //先设置输出电平
//    bxd_gpio_write( BX_GPIOA, TP_RST_PIN, 1 );
//    //再设置output,这样可以避免设置为outpu时短暂的电平变化
//    bxd_gpio_set_mode( BX_GPIOA, TP_RST_PIN, BX_GPIO_MODE_OUTPUT );

    bxd_gpio_set_mode( BX_GPIOA, TP_INT_PIN, BX_GPIO_MODE_INPUT );
    bxd_gpio_set_mode( BX_GPIOA, TP_INT_PIN, BX_GPIO_MODE_EIT_FALLING );
    bxd_gpio_set_pull( BX_GPIOA, TP_INT_PIN, BX_GPIO_PULLUP );

    bxd_gpio_clr_intr( BX_GPIOA );
    bxd_gpio_enable_intr( BX_GPIOA );


    bx_pm_lock( BX_PM_IIC );
    bxd_iic_open( BX_IIC1 );
    bxd_iic_set_scl( BX_IIC1, 3 );
    bxd_iic_set_sda( BX_IIC1, 5 );
    bxd_iic_set_speed( BX_IIC1, BX_IIC_SPEED_STANDARD );
    bxd_iic_set_addr_bit( BX_IIC1, BX_IIC_ADDR_BIT_7B );
    bxd_iic_set_mode( BX_IIC1, BX_IIC_MODE_MASTER );
    tp_svc.state = tp_sta_none;
}

/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
bool us_tp_register( void )
{
    struct bx_service svc;
    svc.name = "tp service";
    svc.msg_handle_func = tp_msg_handle;
    svc.prop_get_func = NULL;
    svc.prop_set_func = NULL;
    tp_svc.id = bx_register( &svc );
    if( tp_svc.id == -1 ) {
        return false;
    }
    tp_svc.pdata = &tp_data;
    return true;
}
/** ---------------------------------------------------------------------------
 * @brief   :
 * @note    :
 * @param   :
 * @retval  :
-----------------------------------------------------------------------------*/
s32 us_tp_id( void )
{
    return tp_svc.id;
}
/*========================= end of exported function =========================*/


/******************** (C) COPYRIGHT ****************************END OF FILE****/



