    PRESERVE8
	THUMB
	AREA    |.text|, CODE, READONLY

H4TL_READ_START_PATCH PROC
    EXPORT H4TL_READ_START_PATCH
    IMPORT h4tl_read_start_patch

    BL h4tl_read_start_patch
    POP      {r4,pc}

	ENDP
    
    END