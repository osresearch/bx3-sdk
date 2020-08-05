    PRESERVE8
	THUMB
	AREA    |.text|, CODE, READONLY
LLD_PDU_TX_FLUSH_LIST_PATCH PROC
    EXPORT LLD_PDU_TX_FLUSH_LIST_PATCH
    IMPORT lld_pdu_tx_flush_patch_c
    MOV R1,R4
    BL lld_pdu_tx_flush_patch_c
    MOV R4,R0
    LDR R0,=0x18641
    BX R0
    
    ENDP
    
    END
    