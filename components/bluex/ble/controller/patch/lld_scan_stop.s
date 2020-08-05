    PRESERVE8
	THUMB
	AREA    |.text|, CODE, READONLY

LLD_SCAN_STOP_PATCH PROC
    EXPORT LLD_SCAN_STOP_PATCH
    IMPORT lld_scan_stop_patch
    BL       lld_scan_stop_patch
    POP      {r4,pc}
    ENDP
    
    END
    
    
    
    
    
