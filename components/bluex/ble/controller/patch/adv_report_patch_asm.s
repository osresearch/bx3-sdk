    PRESERVE8
	THUMB
	AREA    |.text|, CODE, READONLY
LLM_ADV_REPORT_SEND_ADV_RX_TIME_GET PROC
    EXPORT LLM_ADV_REPORT_SEND_ADV_RX_TIME_GET
    IMPORT adv_rx_time_get_patch_c
    LDR R1,[sp,#0x14]
    BL adv_rx_time_get_patch_c
    LDR R0,=0x19453
    BX R0
    NOP
    ENDP
    
    END
    