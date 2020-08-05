    PRESERVE8
	THUMB
	AREA    |n_xip_section|, CODE, READONLY

SLAVE_EVT_COUNT_JUST_BEFORE_INSTANT PROC
    EXPORT SLAVE_EVT_COUNT_JUST_BEFORE_INSTANT
    IMPORT slave_event_count_just_before_instant_c
    MOV r1,r6
    BL slave_event_count_just_before_instant_c
    BX r0
    ENDP
    
    END
    