#define RAM_BASE                0x00100000
#define RAM_LIMIT               0x00130000
#define EM_START                0x00128000
#define EM_END                  0x00129dc6
#define ROM_CODE_ZI_BASE        0x0012f5cc
#define ISR_JUMP_TABLE_SIZE     0x100
#define FLASH_MAPPED_ADDR       0x00800000
#define IMAGE_OFFSET_IN_FLASH   0x3000

#define IMAGE_BASE_IN_FLASH     ((FLASH_MAPPED_ADDR)+(IMAGE_OFFSET_IN_FLASH))

ENTRY(Reset_Handler)

MEMORY
{
	RAM(rwx): ORIGIN = RAM_BASE, LENGTH = RAM_LIMIT - RAM_BASE
	EM(rwx): ORIGIN = EM_START, LENGTH = EM_END - EM_START
	ZI(rwx): ORIGIN = ROM_CODE_ZI_BASE, LENGTH = 1024
	FLASH(rx): ORIGIN = FLASH_MAPPED_ADDR + IMAGE_OFFSET_IN_FLASH, LENGTH = 1024K
}


SECTIONS
{
	.isr_vector : {
		. = ALIGN(4);
		*(__Vectors)
		*(jump_table_area)
		*(.kernel_data_section)
	} > FLASH

	.text : {
		. = ALIGN(4);
		*(.text)
		*(.text*)
		KEEP(*(.init))
		KEEP(*(.fini))

		. = ALIGN(4);
		.etext = .;
	} > FLASH

	.rodata : {
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		Image$$BOOT_PARAMS$$Base = .;
		*(boot_tunnel)
		. = ALIGN(4);
	} > FLASH

	.ram : {
		*(kernel_data_section)
		__initial_sp = .;
	} > RAM

	RAM_UNLOADED :
	{
		Image$$RAM_UNLOADED$$Base = .;
	} > RAM
}

/*
LR_FLASH IMAGE_BASE_IN_FLASH{
    RAM_CODE RAM_BASE{
        *(RESET, +First)
        *(jump_table_area)
    }
	RAM_KERNEL +0{
        *(kernel_data_section)
    }
    RAM_CODE_2 +0 {
        *(n_xip_section)
        *(n_xip_variable)
        SEGGER_RTT*(+RO)
        bx_dbg.o(+RO)
		lld_sleep.o(+RO)
        ;*(:gdef:main)
        ;*(+RO)
        *(+RW)
    }


    FLASH_CODE IMAGE_BASE_IN_FLASH + ImageLength(RAM_CODE) + ImageLength(RAM_CODE_2) + ImageLength(RAM_KERNEL) {
        *(InRoot$$Sections)
        *(xip_section)
        *(+RO)

    }
    
    BSS ImageLimit(RAM_CODE_2)
    {
        *(+ZI)
    }
    HEAP_STACK +0 UNINIT
    {
        *(HEAP)
        *(STACK)
    } 
    ScatterAssert(ImageLimit(HEAP_STACK)<=EM_START)
    SECTION_RTT AlignExpr(EM_END,0x4) {
        *(SECTION_RTT, +First)
    }
    RWIP_ENV +0
    {
        rwip.o(+ZI)
    }
    RTOS_ZI_ENV +0
    {
        os_bridge.o(+ZI)
        ble_task.o(+ZI)
        osapp_task.o(+ZI)
        task_init.o(+ZI)
        timers.o(+ZI)
        tasks.o(+ZI)
    }
    DBG_LOG_ZI_ENV +0
    {
        SEGGER_RTT.o(+ZI)
        bx_dbg.o(+ZI)
    }
    BOOT_PARAMS +0 UNINIT{
        *(boot_tunnel)
    }
    RAM_UNLOADED +0 EMPTY 4
    {
    }
    ScatterAssert(ImageLimit(RAM_UNLOADED)<=ROM_CODE_ZI_BASE)
    
}
*/
