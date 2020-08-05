    PRESERVE8
	THUMB
	AREA    |.text|, CODE, READONLY
LLD_EVT_DRIFT_COMPUTE_PATCH PROC
    EXPORT LLD_EVT_DRIFT_COMPUTE_PATCH
    IMPORT lld_evt_drift_compute_patch
    BL lld_evt_drift_compute_patch
    LDR r2,[sp,#4]
    ADD sp,sp,#8
    BX r2
    
    ENDP
    
    END

