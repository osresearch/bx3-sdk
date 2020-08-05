    PRESERVE8
    THUMB

    
    AREA    |BX_DELAY_ASM|, CODE, READONLY
    FRAME UNWIND ON
bx_delay_asm PROC
    EXPORT bx_delay_asm
    SUBS R0,R0,#1
    CMP R0,#0
    BNE bx_delay_asm
    BX LR
    ENDP

                

    END
    
