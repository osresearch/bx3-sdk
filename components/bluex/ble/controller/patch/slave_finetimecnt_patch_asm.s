    PRESERVE8
	THUMB
	AREA    |n_xip_section|, CODE, READONLY
SLAVE_FINETIMECNT_PATCH PROC
    EXPORT SLAVE_FINETIMECNT_PATCH
    IMPORT finetimecnt_recalculate
    MRS r1,MSP
    BL finetimecnt_recalculate
    LDR r2,=0x17677
    BX r2
    
    ENDP
    
    END
    