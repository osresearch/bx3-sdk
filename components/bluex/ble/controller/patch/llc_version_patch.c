#define LOG_TAG  "LLC_VERSION_PATCH"

#include "rwip_config.h"

#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "compiler.h"
#include "co_error.h"
#include "co_endian.h"
#include "co_bt.h"
#include "co_llcp.h"
#include "em_buf.h"
#include "ke_task.h"
#include "ke_timer.h"
#include "reg_ble_em_tx_desc.h"
#include "reg_ble_em_rx_desc.h"
#include "reg_ble_em_cs.h"
#include "llm.h"
#include "llm_util.h"
#include "co_version.h"
#include "llc_task.h"
#include "llc_util.h"
#include "llc.h"
#include "llc_llcp.h"
#include "lld_pdu.h"
#include "lld_util.h"
#include "lld.h"
#include "patch.h"
#define LLC_VERSION_PATCH_ADDR 0x00012f24

void LLC_VERSION_PATCH(void);

static void llc_llcp_send(uint8_t conhdl, void *param, uint8_t opcode)
{

    uint8_t llcp_length = sizeof(union llcp_pdu);
    // LLCP can be received, so allocate a message structure
    void *llcp_ptr= ke_malloc(llcp_length, KE_MEM_KE_MSG);

    struct llcp_pdu_tag *llcp_elt = (struct llcp_pdu_tag*)ke_malloc(sizeof(struct llcp_pdu_tag), KE_MEM_ENV);

    if(llcp_ptr && llcp_elt)
    {
        // Get associated BLE event environment
        struct lld_evt_tag *evt = LLD_EVT_ENV_ADDR_GET(llc_env[conhdl]->elt);
        // Get list of data packets ready for programming
        struct co_list *list = &evt->tx_llcp_pdu_rdy;

        // Copy the llcp pdu in a heap
        memcpy(llcp_ptr, param,llcp_length);
        // Fill the element before pushing in the list
        llcp_elt->ptr = llcp_ptr;
        llcp_elt->idx = conhdl;
        llcp_elt->opcode = opcode;

        GLOBAL_INT_DISABLE();
        // Push the llcp pdu allocated at the end of the TX llcp pending list
        co_list_push_back(list, &llcp_elt->hdr);
        GLOBAL_INT_RESTORE();

        #if(BLE_PERIPHERAL)
        // Schedule the next event as soon as possible
        lld_evt_schedule_next( llc_env[conhdl]->elt);
        #endif //(BLE_PERIPHERAL)
    }
    else
    {
        ASSERT_INFO(0, (llcp_ptr && llcp_elt), llcp_length);
    }
}

void llc_llcp_version_ind_pdu_send_patch(uint16_t conhdl)
{
	struct llcp_vers_ind pdu;

    pdu.opcode = LLCP_VERSION_IND_OPCODE;
    pdu.vers = 9;
    pdu.compid = co_htobs(RW_COMP_ID);
    pdu.subvers = co_htobs(CO_SUBVERSION_BUILD(RWBT_SW_VERSION_MINOR, RWBT_SW_VERSION_BUILD));

    llc_llcp_send(conhdl, &pdu, pdu.opcode);
}

void llc_llcp_version_ind_pdu_send_patch_creat(void)
{
    uint8_t patch_no;
    if(patch_alloc(&patch_no)==false)
    {
        BX_ASSERT(0);
    }
    uint32_t code = cal_patch_bl(LLC_VERSION_PATCH_ADDR, (uint32_t)LLC_VERSION_PATCH -1);
    patch_entrance_exit_addr(patch_no,LLC_VERSION_PATCH_ADDR,code);
    PATCH_ENABLE(patch_no);
}


