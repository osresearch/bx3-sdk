all: app.elf

DATE := $(shell date "+%Y%m%d")
TIME := $(shell date "+%H%M%S")
CROSS ?= arm-none-eabi-
CC = $(CROSS)gcc
LD = $(CROSS)ld

CPU_FLAGS += -mcpu=cortex-m0plus -mtune=cortex-m0plus -mthumb
#CFLAGS += -nostdlib
CFLAGS += $(CPU_FLAGS)
#CFLAGS += --include ../../../../platform/bluex/apollo/apollo00/apollo_00_reg.h
#CFLAGS += --include ../../../../platform/cmsis/core_cm0plus.h

ASFLAGS += $(CPU_FLAGS)

INCDIRS = \
../../../../include \
../../../../platform/cmsis \
../../../../platform/bluex/apollo/common \
../../../../platform/bluex/apollo/typedef \
../../../../platform/bluex/apollo/apollo00 \
../../../../platform/bluex/apollo/apollo00/driver_service \
../../../../components/bluex/ble/common \
../../../../components/bluex/ble/dbg \
../../../../components/bluex/bxfs \
../../../../components/bluex/ble/profiles \
../../../../components/bluex/ble/controller \
../../../../components/bluex/ble/controller/patch \
../../../../components/bluex/ble/controller/driver \
../../../../components/bluex/ble/controller/driver/reg \
../../../../components/bluex/fifo \
../code \
../config \
../../../../components/3rdparty/cm_backtrace \
../code/profile \
../../../../components/bluex/ble/controller/driver/rf_setting \

#             <TextAddressRange>0x00000000</TextAddressRange>
#            <DataAddressRange>0x20000000</DataAddressRange>
#            <ScatterFile>../config/user_link.txt</ScatterFile>

BX_CORE_SRC = \
              ../code/main.c \
              ../../../../kernel/bx_kernel.c \
              ../../../../kernel/bx_kernel_timer.c \

BX_CORE_AS = \
              ../code/startup_apollo00_ble.S \

BX_BLE_SRC = \
              ../../../../components/bluex/ble/controller/ble_stack.c \
              ../../../../components/bluex/ble/controller/rwip.c \
              ../../../../components/bluex/ble/controller/rf_apollo.c \
              ../../../../components/bluex/ble/controller/nvds_task.c \
              ../../../../components/bluex/ble/controller/ecc_p256.c \
              ../../../../components/bluex/ble/controller/lld_sleep.c \
              ../../../../components/bluex/ble/controller/nvds_in_ram.c \
              ../../../../components/bluex/ble/controller/rwble.c \
              ../../../../components/bluex/ble/controller/driver/app_dmac.c \
              ../../../../components/bluex/ble/controller/driver/app_dmac_wrapper.c \
              ../../../../components/bluex/ble/controller/driver/app_gpio.c \
              ../../../../components/bluex/ble/controller/driver/app_hwecc.c \
              ../../../../components/bluex/ble/controller/driver/app_hwecc_wrapper.c \
              ../../../../components/bluex/ble/controller/driver/app_qspi.c \
              ../../../../components/bluex/ble/controller/driver/app_qspi_wrapper.c \
              ../../../../components/bluex/ble/controller/driver/arch_init.c \
              ../../../../components/bluex/ble/controller/driver/clk_gate.c \
              ../../../../components/bluex/ble/controller/driver/flash_base.c \
              ../../../../components/bluex/ble/controller/driver/flash_cache.c \
              ../../../../components/bluex/ble/controller/driver/flash_integration.c \
              ../../../../components/bluex/ble/controller/driver/flash_wrapper.c \
              ../../../../components/bluex/ble/controller/driver/io_ctrl.c \
              ../../../../components/bluex/ble/controller/driver/jump_table.c \
              ../../../../components/bluex/ble/controller/driver/modem.c \
              ../../../../components/bluex/ble/controller/driver/patch.c \
              ../../../../components/bluex/ble/controller/driver/periph_lock.c \
              ../../../../components/bluex/ble/controller/driver/periph_mngt.c \
              ../../../../components/bluex/ble/controller/driver/periph_recovery.c \
              ../../../../components/bluex/ble/controller/driver/pshare.c \
              ../../../../components/bluex/ble/controller/driver/rc_calib.c \
              ../../../../components/bluex/ble/controller/driver/rf_reg_settings_apollo_00.c \
              ../../../../components/bluex/ble/controller/driver/rst_gen.c \
              ../../../../components/bluex/ble/controller/driver/sys_sleep.c \
              ../../../../components/bluex/ble/controller/driver/sys_sleep_ram.c \
              ../../../../components/bluex/ble/controller/driver/sysctrl.c \
              ../../../../components/bluex/ble/controller/driver/true_random.c \
              ../../../../components/bluex/ble/controller/patch/adv_int_patch.c \
              ../../../../components/bluex/ble/controller/patch/adv_report_patch.c \
              ../../../../components/bluex/ble/controller/patch/lld_evt_schedule_patch.c \
              ../../../../components/bluex/ble/controller/patch/lld_pdu_tx_flush_list_patch.c \
              ../../../../components/bluex/ble/controller/patch/lld_scan_stop.c \
              ../../../../components/bluex/ble/controller/patch/lld_slave_instant_patch.c \
              ../../../../components/bluex/ble/controller/patch/llm_end_evt_defer_patch.c \
              ../../../../components/bluex/ble/controller/patch/llm_util_chk_tst_mode_patch.c \
              ../../../../components/bluex/ble/controller/patch/llm_util_gen_pattern_tx_patch.c \
              ../../../../components/bluex/ble/controller/patch/prog_latency_patch.c \
              ../../../../components/bluex/ble/controller/patch/rc32k_patch.c \
              ../../../../components/bluex/ble/controller/patch/scan_adv_rx_threshold_patch.c \
              ../../../../components/bluex/ble/controller/patch/scan_timeout_patch.c \
              ../../../../components/bluex/ble/controller/patch/set_adv_payload_31Byte_patch.c \
              ../../../../components/bluex/ble/controller/patch/slave_finetimecnt_patch.c \
              ../../../../components/bluex/ble/controller/patch/slave_latency_patch.c \
              ../../../../components/bluex/ble/controller/patch/smpc_construct_id_addr_type_patch.c \
              ../../../../components/bluex/ble/controller/patch/task_id_patch.c \
              ../../../../components/bluex/bxfs/bxfs.c \
              ../../../../components/bluex/bxfs/bxfs_write_cache.c \
              ../../../../components/bluex/bxfs/static_buffer.c \
              ../../../../components/bluex/ble/controller/patch/llc_version_patch.c \
              ../../../../components/bluex/ble/controller/driver/rf_setting/adc_integration.c \
              ../../../../components/bluex/ble/controller/driver/rf_setting/app_adc.c \
              ../../../../components/bluex/ble/controller/driver/rf_setting/app_adc_utils.c \
              ../../../../components/bluex/ble/controller/driver/rf_setting/refresh_rf_param_with_ro.c \
              ../../../../components/bluex/ble/controller/driver/rf_setting/rf_power_set.c \
              ../../../../components/bluex/ble/controller/driver/rf_setting/rf_temp_adjust.c \
              ../../../../components/bluex/ble/controller/driver/rf_setting/rf_battery_adjust.c \


BX_BLE_AS = \
              ../../../../components/bluex/ble/controller/patch/llc_version_patch_asm.s \
              ../../../../components/bluex/ble/controller/patch/adv_report_patch_asm.s \
              ../../../../components/bluex/ble/controller/patch/lld_pdu_tx_flush_list_patch_asm.s \
              ../../../../components/bluex/ble/controller/patch/lld_scan_stop_patch_asm.s \
              ../../../../components/bluex/ble/controller/patch/lld_slave_instant_patch_asm.s \
              ../../../../components/bluex/ble/controller/patch/rc32k_patch_asm.s \
              ../../../../components/bluex/ble/controller/patch/slave_finetimecnt_patch_asm.s \
              ../../../../components/bluex/ble/controller/patch/smpc_construct_id_addr_type_patch_asm.s \
              ../../../../components/bluex/ble/controller/patch/task_id_patch_asm.s \

BX_LOG_SRC = \
              ../../../../components/bluex/ble/dbg/bx_dbg.c \
              ../../../../components/bluex/ble/dbg/SEGGER_RTT.c \

BX_LOG_AS = \
              ../../../../components/bluex/ble/dbg/bx_dbg_asm.s \

BX_DRIVERS_SRC = \
              ../../../../platform/bluex/apollo/apollo00/driver_service/bx_pm.c \

USER_PROFILES_SRC = \
              ../code/profile/prf.c \
              ../code/profile/prf_utils.c \
              ../code/profile/diss.c \
              ../code/profile/diss_task.c \
              ../code/profile/app_dis.c \

USER_APP_SRC = \
              ../code/app.c \
              ../code/ble.c \
              ../code/bx_apollo00_it.c \

SRCS += $(BX_CORE_SRC)
SRCS += $(BX_BLE_SRC)
SRCS += $(BX_LOG_SRC)
SRCS += $(BX_DRIVERS_SRC)
SRCS += $(USER_PROFILES_SRC)
SRCS += $(USER_APP_SRC)

AS_SRCS += $(BX_CORE_AS)
AS_SRCS += $(BX_BLE_AS)
AS_SRCS += $(BX_LOG_AS)

# Fake the rvds compiler check
CFLAGS += -D__ARMCC_VERSION=1
# Fixup the __weak alias
CFLAGS += -D__weak="__attribute__((__weak__))"
CFLAGS += $(foreach _,$(INCDIRS),-I$_)

OBJS = syms.o lmul.o strlen.o

%.o: %.s
	$(CC) $(ASFLAGS) -c -o $@ $<

linker.lds: ../../../../linker.lds
	$(CC) $(CFLAGS) -E  - < $< | grep -v '^#' > $@

syms.s: ../../../../components/bluex/ble/controller/rom_syms_armcc.txt
	./syms2elf < $< > $@ || $(RM) $@ && exit 1

define make-goal
$2: $1
	$(CC) $(CFLAGS) -c -o $$@ $$<
OBJS+=$2
endef
define make-goal-as
$2: $1
	./arm-as < $$< > $(basename $2).S
	$(CC) $(ASFLAGS) -c -o $$@ $(basename $2).S
OBJS+=$2
endef


$(foreach _,$(SRCS),$(eval $(call make-goal,$_,$(notdir $(basename $_)).o)))
$(foreach _,$(AS_SRCS),$(eval $(call make-goal-as,$_,$(notdir $(basename $_)).o)))

app.elf: linker.lds $(OBJS)
	$(LD) $(LDFLAGS) -o $@ -T $^ 
