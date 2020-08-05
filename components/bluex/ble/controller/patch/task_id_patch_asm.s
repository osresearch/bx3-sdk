    PRESERVE8
	THUMB
	AREA    |.text|, CODE, READONLY

GET_TASK_FROM_ID_PATCH PROC
    EXPORT GET_TASK_FROM_ID_PATCH
    IMPORT gapm_get_task_from_id_patch
    BL gapm_get_task_from_id_patch
    POP      {r4,pc}
    ENDP
    
GET_ID_FROM_TASK_PATCH PROC
    EXPORT GET_ID_FROM_TASK_PATCH
    IMPORT gapm_get_id_from_task_patch
    BL gapm_get_id_from_task_patch
    POP      {r4,pc}
    ENDP
    
    END
    