#ifndef H4TL_CUSTOM_H_
#define H4TL_CUSTOM_H_
#include "ahi.h"
#include "rwip.h"

#define RX_TMP_BUFF_SIZE     AHI_RESET_MSG_LEN

///H4TL RX states
enum H4TL_STATE_RX
{
    ///H4TL RX Start State - receive message type
    H4TL_STATE_RX_START,
    ///H4TL RX Header State - receive message header
    H4TL_STATE_RX_HDR,
    ///H4TL RX Header State - receive (rest of) message payload
    H4TL_STATE_RX_PAYL,
    ///H4TL RX Out Of Sync state - receive message type
    H4TL_STATE_RX_OUT_OF_SYNC
};

/// H4TL Environment context structure
struct h4tl_env_tag
{
    /// pointer to External interface api
    const struct rwip_eif_api* ext_if;
    ///Pointer to space reserved for received payload.
    uint8_t *curr_payl_buff;
    ///TX callback for indicating the end of transfer
    void (*tx_callback)(void);
    /// Ensure that array is 32bits alligned
    /// Latest received message header, or used to receive a message alowing to exit from out of sync
    uint8_t rx_buf[RX_TMP_BUFF_SIZE];

    ///Rx state - can be receiving message type, header, payload or error
    uint8_t rx_state;
    ///Tx state - either transmitting, done or error.
    uint8_t tx_state;
    ///Latest received message type: CMD/EVT/ACL.
    uint8_t rx_type;
    /// Transport layer type
    uint8_t tl_type;
};

void h4tl_read_start_2(void);


#endif

