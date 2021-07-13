	PRESERVE8
	THUMB
	AREA    |.text|, CODE, READONLY

LLC_VERSION_PATCH PROC
    EXPORT LLC_VERSION_PATCH
    IMPORT llc_llcp_version_ind_pdu_send_patch
    BL       llc_llcp_version_ind_pdu_send_patch
    POP      {r2-r4,pc}
    ENDP
    
    END
    
    
    
    
    
