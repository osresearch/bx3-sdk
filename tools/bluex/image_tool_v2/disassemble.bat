@%~dp0\boot_ram_config.exe %~dp0\config.ini %~dp0\boot_ram.bin
@%~dp0\srec_cat.exe .\Objects\%1.hex -Intel .\boot_ram.hex -Intel -o %1_with_bootloader.hex -Intel
@echo %1_with_bootloader.hex generated
@fromelf --bincombined --output=%1_ota.bin .\Objects\%1.axf
@echo %1_ota.bin generated
@fromelf -c -a -d -e -v -o %1.asm .\Objects\%1.axf
@echo %1.asm generated
@echo LOAD .\Objects\%1.axf NOCODE > debug_flash.ini