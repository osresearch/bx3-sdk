    PRESERVE8
	THUMB
    AREA    |.text|, CODE, READONLY
SMPC_CONSTRUCT_ID_ADDR_TYPE_PATCH PROC
    EXPORT SMPC_CONSTRUCT_ID_ADDR_TYPE_PATCH
    IMPORT smpc_construct_id_addr_type_patch_c
    PUSH {LR}
    MOV R4,R0
    BL smpc_construct_id_addr_type_patch_c
    POP {PC}
    
    ENDP
    
    END
    