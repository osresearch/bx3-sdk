    PRESERVE8
	THUMB
	AREA    |.text|, CODE, READONLY

H4TL_PATCH PROC
    EXPORT H4TL_PATCH
    IMPORT h4tl_patch_c
    MOV r0,r4
    MOV r1,lr
    BL h4tl_patch_c
    MOV r1,r0
    LDRB r0,[r4,#0x16]
    BX r1
    ENDP
    
    END
    
    
    
    
    
