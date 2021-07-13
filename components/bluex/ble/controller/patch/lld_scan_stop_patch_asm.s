    PRESERVE8
	THUMB
	AREA    |.text|, CODE, READONLY

LLD_SCAN_STOP_PATCH_ASM PROC
    EXPORT LLD_SCAN_STOP_PATCH_ASM
    IMPORT lld_scan_stop_patch
    BL       lld_scan_stop_patch
    POP      {r4,pc}
    ENDP
    
    END
    
    
    
    
    
