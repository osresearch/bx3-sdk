
========================================================================

** ELF Header Information

    File Name: boot_ram.elf

    Machine class: ELFCLASS32 (32-bit)
    Data encoding: ELFDATA2LSB (Little endian)
    Header version: EV_CURRENT (Current version)
    Operating System ABI: none
    ABI Version: 0
    File Type: ET_EXEC (Executable) (2)
    Machine: EM_ARM (ARM)

    Image Entry point: 0x00128219
    Flags: EF_ARM_ABI_FLOAT_SOFT (0x05000200)

    ARM ELF revision: 5 (ABI version 2)

    Conforms to Soft float procedure-call standard

    Header size: 52 bytes (0x34)
    Program header entry size: 32 bytes (0x20)
    Section header entry size: 40 bytes (0x28)

    Program header entries: 1
    Section header entries: 18

    Program header offset: 52 (0x00000034)
    Section header offset: 290796 (0x00046fec)

    Section header string table index: 17

========================================================================

** Program header #0

    Type          : PT_LOAD (1)
    File Offset   : 0 (0x0)
    Virtual Addr  : 0x00120000
    Physical Addr : 0x00120000
    Size in file  : 37900 bytes (0x940c)
    Size in memory: 39338 bytes (0x99aa)
    Flags         : PF_X + PF_W + PF_R (0x7)
    Alignment     : 65536


========================================================================

** Section #1

    Name        : boot_ram
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : SHF_ALLOC + SHF_WRITE + SHF_EXECINSTR (0x00000007)
    Addr        : 0x00127ff0
    File Offset : 32752 (0x7ff0)
    Size        : 5140 bytes (0x1414)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0

    [Anonymous symbol #1]
    $d
    boot_ram_head
        0x00127ff0:    34325842    BX24    DCD    875714626
        0x00127ff4:    00128000    ....    DCD    1212416
        0x00127ff8:    ffffffff    ....    DCD    4294967295
        0x00127ffc:    00128219    ....    DCD    1212953
        0x00128000:    00000000    ....    DCD    0
        0x00128004:    00000000    ....    DCD    0
        0x00128008:    00000000    ....    DCD    0
        0x0012800c:    00000000    ....    DCD    0
    $t
    quad_enable_read
        0x00128010:    b5b0        ..      PUSH     {r4,r5,r7,lr}
        0x00128012:    4669        iF      MOV      r1,sp
        0x00128014:    7842        Bx      LDRB     r2,[r0,#1]
        0x00128016:    af00        ..      ADD      r7,sp,#0
        0x00128018:    0692        ..      LSLS     r2,r2,#26
        0x0012801a:    0f92        ..      LSRS     r2,r2,#30
        0x0012801c:    1dd3        ..      ADDS     r3,r2,#7
        0x0012801e:    08db        ..      LSRS     r3,r3,#3
        0x00128020:    00db        ..      LSLS     r3,r3,#3
        0x00128022:    1acb        ..      SUBS     r3,r1,r3
        0x00128024:    469d        .F      MOV      sp,r3
        0x00128026:    0005        ..      MOVS     r5,r0
        0x00128028:    4669        iF      MOV      r1,sp
        0x0012802a:    7800        .x      LDRB     r0,[r0,#0]
        0x0012802c:    f001f98e    ....    BL       flash_read_status_reg ; 0x12934c
        0x00128030:    2107        .!      MOVS     r1,#7
        0x00128032:    2001        .       MOVS     r0,#1
        0x00128034:    786b        kx      LDRB     r3,[r5,#1]
        0x00128036:    466c        lF      MOV      r4,sp
        0x00128038:    071b        ..      LSLS     r3,r3,#28
        0x0012803a:    0f1b        ..      LSRS     r3,r3,#28
        0x0012803c:    10da        ..      ASRS     r2,r3,#3
        0x0012803e:    400b        .@      ANDS     r3,r3,r1
        0x00128040:    4098        .@      LSLS     r0,r0,r3
        0x00128042:    5ca2        .\      LDRB     r2,[r4,r2]
        0x00128044:    46bd        .F      MOV      sp,r7
        0x00128046:    4010        .@      ANDS     r0,r0,r2
        0x00128048:    1e43        C.      SUBS     r3,r0,#1
        0x0012804a:    4198        .A      SBCS     r0,r0,r3
        0x0012804c:    b2c0        ..      UXTB     r0,r0
        0x0012804e:    bdb0        ..      POP      {r4,r5,r7,pc}
    $t
    quad_enable_write
        0x00128050:    b5f8        ..      PUSH     {r3-r7,lr}
        0x00128052:    466a        jF      MOV      r2,sp
        0x00128054:    7844        Dx      LDRB     r4,[r0,#1]
        0x00128056:    af00        ..      ADD      r7,sp,#0
        0x00128058:    06a4        ..      LSLS     r4,r4,#26
        0x0012805a:    0fa4        ..      LSRS     r4,r4,#30
        0x0012805c:    1de3        ..      ADDS     r3,r4,#7
        0x0012805e:    08db        ..      LSRS     r3,r3,#3
        0x00128060:    00db        ..      LSLS     r3,r3,#3
        0x00128062:    1ad3        ..      SUBS     r3,r2,r3
        0x00128064:    469d        .F      MOV      sp,r3
        0x00128066:    0005        ..      MOVS     r5,r0
        0x00128068:    0022        ".      MOVS     r2,r4
        0x0012806a:    2100        .!      MOVS     r1,#0
        0x0012806c:    4668        hF      MOV      r0,sp
        0x0012806e:    f6d9fd4e    ..N.    BL       0x1b0e ; 0x1b0e
        0x00128072:    2207        ."      MOVS     r2,#7
        0x00128074:    786b        kx      LDRB     r3,[r5,#1]
        0x00128076:    466e        nF      MOV      r6,sp
        0x00128078:    071b        ..      LSLS     r3,r3,#28
        0x0012807a:    0f1b        ..      LSRS     r3,r3,#28
        0x0012807c:    10d9        ..      ASRS     r1,r3,#3
        0x0012807e:    4013        .@      ANDS     r3,r3,r2
        0x00128080:    3a06        .:      SUBS     r2,#6
        0x00128082:    409a        .@      LSLS     r2,r2,r3
        0x00128084:    7828        (x      LDRB     r0,[r5,#0]
        0x00128086:    5472        rT      STRB     r2,[r6,r1]
        0x00128088:    4669        iF      MOV      r1,sp
        0x0012808a:    0022        ".      MOVS     r2,r4
        0x0012808c:    f001f969    ..i.    BL       flash_write_status_reg ; 0x129362
        0x00128090:    46bd        .F      MOV      sp,r7
        0x00128092:    bdf8        ..      POP      {r3-r7,pc}
    $t
    zero_init
        0x00128094:    b510        ..      PUSH     {r4,lr}
        0x00128096:    4c06        .L      LDR      r4,[pc,#24] ; [0x1280b0] = 0x129404
        0x00128098:    4b06        .K      LDR      r3,[pc,#24] ; [0x1280b4] = 0x12940c
        0x0012809a:    429c        .B      CMP      r4,r3
        0x0012809c:    d300        ..      BCC      0x1280a0 ; zero_init + 12
        0x0012809e:    bd10        ..      POP      {r4,pc}
        0x001280a0:    6862        bh      LDR      r2,[r4,#4]
        0x001280a2:    6820         h      LDR      r0,[r4,#0]
        0x001280a4:    2100        .!      MOVS     r1,#0
        0x001280a6:    f6d9fd32    ..2.    BL       0x1b0e ; 0x1b0e
        0x001280aa:    3408        .4      ADDS     r4,r4,#8
        0x001280ac:    e7f4        ..      B        0x128098 ; zero_init + 4
        0x001280ae:    46c0        .F      MOV      r8,r8
    $d
        0x001280b0:    00129404    ....    DCD    1217540
        0x001280b4:    0012940c    ....    DCD    1217548
    $t
    ota_image1_verify_success
        0x001280b8:    b570        p.      PUSH     {r4-r6,lr}
        0x001280ba:    0005        ..      MOVS     r5,r0
        0x001280bc:    4807        .H      LDR      r0,[pc,#28] ; [0x1280dc] = 0x4c11db7
        0x001280be:    000e        ..      MOVS     r6,r1
        0x001280c0:    0014        ..      MOVS     r4,r2
        0x001280c2:    f000f8f3    ....    BL       crc32_init ; 0x1282ac
        0x001280c6:    2001        .       MOVS     r0,#1
        0x001280c8:    0032        2.      MOVS     r2,r6
        0x001280ca:    0029        ).      MOVS     r1,r5
        0x001280cc:    4240        @B      RSBS     r0,r0,#0
        0x001280ce:    f000f911    ....    BL       crc32_calc ; 0x1282f4
        0x001280d2:    1b00        ..      SUBS     r0,r0,r4
        0x001280d4:    4243        CB      RSBS     r3,r0,#0
        0x001280d6:    4158        XA      ADCS     r0,r0,r3
        0x001280d8:    b2c0        ..      UXTB     r0,r0
        0x001280da:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x001280dc:    04c11db7    ....    DCD    79764919
    $t
    ota_process
        0x001280e0:    2180        .!      MOVS     r1,#0x80
        0x001280e2:    b5f0        ..      PUSH     {r4-r7,lr}
        0x001280e4:    4b3f        ?K      LDR      r3,[pc,#252] ; [0x1281e4] = 0x127ff0
        0x001280e6:    4c40        @L      LDR      r4,[pc,#256] ; [0x1281e8] = 0x129814
        0x001280e8:    691b        .i      LDR      r3,[r3,#0x10]
        0x001280ea:    b085        ..      SUB      sp,sp,#0x14
        0x001280ec:    0022        ".      MOVS     r2,r4
        0x001280ee:    0018        ..      MOVS     r0,r3
        0x001280f0:    0049        I.      LSLS     r1,r1,#1
        0x001280f2:    9300        ..      STR      r3,[sp,#0]
        0x001280f4:    f001f884    ....    BL       flash_multi_read ; 0x129200
        0x001280f8:    4b3c        <K      LDR      r3,[pc,#240] ; [0x1281ec] = 0x1001
        0x001280fa:    4d3d        =M      LDR      r5,[pc,#244] ; [0x1281f0] = 0x12940c
        0x001280fc:    6822        "h      LDR      r2,[r4,#0]
        0x001280fe:    602b        +`      STR      r3,[r5,#0]
        0x00128100:    4b3c        <K      LDR      r3,[pc,#240] ; [0x1281f4] = 0x12345678
        0x00128102:    429a        .B      CMP      r2,r3
        0x00128104:    d14c        L.      BNE      0x1281a0 ; ota_process + 192
        0x00128106:    4b3c        <K      LDR      r3,[pc,#240] ; [0x1281f8] = 0x1002
        0x00128108:    483c        <H      LDR      r0,[pc,#240] ; [0x1281fc] = 0x800100
        0x0012810a:    602b        +`      STR      r3,[r5,#0]
        0x0012810c:    9b00        ..      LDR      r3,[sp,#0]
        0x0012810e:    6862        bh      LDR      r2,[r4,#4]
        0x00128110:    68a1        .h      LDR      r1,[r4,#8]
        0x00128112:    1818        ..      ADDS     r0,r3,r0
        0x00128114:    f7ffffd0    ....    BL       ota_image1_verify_success ; 0x1280b8
        0x00128118:    2800        .(      CMP      r0,#0
        0x0012811a:    d05e        ^.      BEQ      0x1281da ; ota_process + 250
        0x0012811c:    2280        ."      MOVS     r2,#0x80
        0x0012811e:    4b38        8K      LDR      r3,[pc,#224] ; [0x128200] = 0x1003
        0x00128120:    0152        R.      LSLS     r2,r2,#5
        0x00128122:    602b        +`      STR      r3,[r5,#0]
        0x00128124:    4b37        7K      LDR      r3,[pc,#220] ; [0x128204] = 0x1293c0
        0x00128126:    2100        .!      MOVS     r1,#0
        0x00128128:    6818        .h      LDR      r0,[r3,#0]
        0x0012812a:    f6d9fcf0    ....    BL       0x1b0e ; 0x1b0e
        0x0012812e:    68a3        .h      LDR      r3,[r4,#8]
        0x00128130:    2600        .&      MOVS     r6,#0
        0x00128132:    0b1c        ..      LSRS     r4,r3,#12
        0x00128134:    051a        ..      LSLS     r2,r3,#20
        0x00128136:    3301        .3      ADDS     r3,#1
        0x00128138:    0d12        ..      LSRS     r2,r2,#20
        0x0012813a:    33ff        .3      ADDS     r3,r3,#0xff
        0x0012813c:    9202        ..      STR      r2,[sp,#8]
        0x0012813e:    051a        ..      LSLS     r2,r3,#20
        0x00128140:    1e51        Q.      SUBS     r1,r2,#1
        0x00128142:    418a        .A      SBCS     r2,r2,r1
        0x00128144:    0b1b        ..      LSRS     r3,r3,#12
        0x00128146:    18d3        ..      ADDS     r3,r2,r3
        0x00128148:    9303        ..      STR      r3,[sp,#0xc]
        0x0012814a:    b2a3        ..      UXTH     r3,r4
        0x0012814c:    9301        ..      STR      r3,[sp,#4]
        0x0012814e:    4a2e        .J      LDR      r2,[pc,#184] ; [0x128208] = 0xffffd000
        0x00128150:    1cf5        ..      ADDS     r5,r6,#3
        0x00128152:    9b00        ..      LDR      r3,[sp,#0]
        0x00128154:    032d        -.      LSLS     r5,r5,#12
        0x00128156:    18af        ..      ADDS     r7,r5,r2
        0x00128158:    3301        .3      ADDS     r3,#1
        0x0012815a:    9a01        ..      LDR      r2,[sp,#4]
        0x0012815c:    33ff        .3      ADDS     r3,r3,#0xff
        0x0012815e:    18ff        ..      ADDS     r7,r7,r3
        0x00128160:    4296        .B      CMP      r6,r2
        0x00128162:    d31f        ..      BCC      0x1281a4 ; ota_process + 196
        0x00128164:    1cd5        ..      ADDS     r5,r2,#3
        0x00128166:    0314        ..      LSLS     r4,r2,#12
        0x00128168:    18e4        ..      ADDS     r4,r4,r3
        0x0012816a:    4e21        !N      LDR      r6,[pc,#132] ; [0x1281f0] = 0x12940c
        0x0012816c:    4b27        'K      LDR      r3,[pc,#156] ; [0x12820c] = 0x1004
        0x0012816e:    032d        -.      LSLS     r5,r5,#12
        0x00128170:    2101        .!      MOVS     r1,#1
        0x00128172:    0028        (.      MOVS     r0,r5
        0x00128174:    6033        3`      STR      r3,[r6,#0]
        0x00128176:    f001f8cf    ....    BL       flash_erase ; 0x129318
        0x0012817a:    0020         .      MOVS     r0,r4
        0x0012817c:    2400        .$      MOVS     r4,#0
        0x0012817e:    4f21        !O      LDR      r7,[pc,#132] ; [0x128204] = 0x1293c0
        0x00128180:    9902        ..      LDR      r1,[sp,#8]
        0x00128182:    683a        :h      LDR      r2,[r7,#0]
        0x00128184:    f001f83c    ..<.    BL       flash_multi_read ; 0x129200
        0x00128188:    683a        :h      LDR      r2,[r7,#0]
        0x0012818a:    9902        ..      LDR      r1,[sp,#8]
        0x0012818c:    0028        (.      MOVS     r0,r5
        0x0012818e:    f001f886    ....    BL       flash_program ; 0x12929e
        0x00128192:    4b1f        .K      LDR      r3,[pc,#124] ; [0x128210] = 0x1005
        0x00128194:    6033        3`      STR      r3,[r6,#0]
        0x00128196:    9b03        ..      LDR      r3,[sp,#0xc]
        0x00128198:    429c        .B      CMP      r4,r3
        0x0012819a:    d116        ..      BNE      0x1281ca ; ota_process + 234
        0x0012819c:    4b1d        .K      LDR      r3,[pc,#116] ; [0x128214] = 0x1006
        0x0012819e:    6033        3`      STR      r3,[r6,#0]
        0x001281a0:    b005        ..      ADD      sp,sp,#0x14
        0x001281a2:    bdf0        ..      POP      {r4-r7,pc}
        0x001281a4:    2101        .!      MOVS     r1,#1
        0x001281a6:    0028        (.      MOVS     r0,r5
        0x001281a8:    f001f8b6    ....    BL       flash_erase ; 0x129318
        0x001281ac:    2180        .!      MOVS     r1,#0x80
        0x001281ae:    4c15        .L      LDR      r4,[pc,#84] ; [0x128204] = 0x1293c0
        0x001281b0:    0149        I.      LSLS     r1,r1,#5
        0x001281b2:    6822        "h      LDR      r2,[r4,#0]
        0x001281b4:    0038        8.      MOVS     r0,r7
        0x001281b6:    f001f823    ..#.    BL       flash_multi_read ; 0x129200
        0x001281ba:    2180        .!      MOVS     r1,#0x80
        0x001281bc:    6822        "h      LDR      r2,[r4,#0]
        0x001281be:    0149        I.      LSLS     r1,r1,#5
        0x001281c0:    0028        (.      MOVS     r0,r5
        0x001281c2:    f001f86c    ..l.    BL       flash_program ; 0x12929e
        0x001281c6:    3601        .6      ADDS     r6,#1
        0x001281c8:    e7c1        ..      B        0x12814e ; ota_process + 110
        0x001281ca:    9b00        ..      LDR      r3,[sp,#0]
        0x001281cc:    0320         .      LSLS     r0,r4,#12
        0x001281ce:    18c0        ..      ADDS     r0,r0,r3
        0x001281d0:    2101        .!      MOVS     r1,#1
        0x001281d2:    f001f8a1    ....    BL       flash_erase ; 0x129318
        0x001281d6:    3401        .4      ADDS     r4,#1
        0x001281d8:    e7dd        ..      B        0x128196 ; ota_process + 182
        0x001281da:    2380        .#      MOVS     r3,#0x80
        0x001281dc:    019b        ..      LSLS     r3,r3,#6
        0x001281de:    602b        +`      STR      r3,[r5,#0]
        0x001281e0:    e7de        ..      B        0x1281a0 ; ota_process + 192
        0x001281e2:    46c0        .F      MOV      r8,r8
    $d
        0x001281e4:    00127ff0    ....    DCD    1212400
        0x001281e8:    00129814    ....    DCD    1218580
        0x001281ec:    00001001    ....    DCD    4097
        0x001281f0:    0012940c    ....    DCD    1217548
        0x001281f4:    12345678    xV4.    DCD    305419896
        0x001281f8:    00001002    ....    DCD    4098
        0x001281fc:    00800100    ....    DCD    8388864
        0x00128200:    00001003    ....    DCD    4099
        0x00128204:    001293c0    ....    DCD    1217472
        0x00128208:    ffffd000    ....    DCD    4294955008
        0x0012820c:    00001004    ....    DCD    4100
        0x00128210:    00001005    ....    DCD    4101
        0x00128214:    00001006    ....    DCD    4102
    $t
    main
        0x00128218:    b5b0        ..      PUSH     {r4,r5,r7,lr}
        0x0012821a:    af00        ..      ADD      r7,sp,#0
        0x0012821c:    b672        r.      CPSID    i
        0x0012821e:    2280        ."      MOVS     r2,#0x80
        0x00128220:    4b1d        .K      LDR      r3,[pc,#116] ; [0x128298] = 0xe000e104
        0x00128222:    0112        ..      LSLS     r2,r2,#4
        0x00128224:    67da        .g      STR      r2,[r3,#0x7c]
        0x00128226:    2020                MOVS     r0,#0x20
        0x00128228:    f000fa14    ....    BL       srst_per ; 0x128654
        0x0012822c:    f7ffff32    ..2.    BL       zero_init ; 0x128094
        0x00128230:    f000fa56    ..V.    BL       sysctrl_io_init ; 0x1286e0
        0x00128234:    f000f9d0    ....    BL       clk_gate_clr_all_clk ; 0x1285d8
        0x00128238:    f000f9fa    ....    BL       pshare_reset_to_gpio ; 0x128630
        0x0012823c:    f000ff24    ..$.    BL       app_dmac_init_wrapper ; 0x129088
        0x00128240:    4c16        .L      LDR      r4,[pc,#88] ; [0x12829c] = 0x127ff0
        0x00128242:    0020         .      MOVS     r0,r4
        0x00128244:    301a        .0      ADDS     r0,r0,#0x1a
        0x00128246:    f000fd31    ..1.    BL       app_qspi_param_init_wrapper ; 0x128cac
        0x0012824a:    f000fd49    ..I.    BL       app_qspi_init_wrapper ; 0x128ce0
        0x0012824e:    f000f877    ..w.    BL       cache_config ; 0x128340
        0x00128252:    223f        ?"      MOVS     r2,#0x3f
        0x00128254:    7ee3        .~      LDRB     r3,[r4,#0x1b]
        0x00128256:    4393        .C      BICS     r3,r3,r2
        0x00128258:    2b80        .+      CMP      r3,#0x80
        0x0012825a:    d109        ..      BNE      0x128270 ; main + 88
        0x0012825c:    0020         .      MOVS     r0,r4
        0x0012825e:    301c        .0      ADDS     r0,r0,#0x1c
        0x00128260:    f7fffed6    ....    BL       quad_enable_read ; 0x128010
        0x00128264:    2800        .(      CMP      r0,#0
        0x00128266:    d103        ..      BNE      0x128270 ; main + 88
        0x00128268:    0020         .      MOVS     r0,r4
        0x0012826a:    301e        .0      ADDS     r0,r0,#0x1e
        0x0012826c:    f7fffef0    ....    BL       quad_enable_write ; 0x128050
        0x00128270:    f000f86c    ..l.    BL       cache_enable ; 0x12834c
        0x00128274:    f7ffff34    ..4.    BL       ota_process ; 0x1280e0
        0x00128278:    4b09        .K      LDR      r3,[pc,#36] ; [0x1282a0] = 0x803000
        0x0012827a:    681b        .h      LDR      r3,[r3,#0]
        0x0012827c:    f3838808    ....    MSR      MSP,r3
        0x00128280:    0021        !.      MOVS     r1,r4
        0x00128282:    0020         .      MOVS     r0,r4
        0x00128284:    4b07        .K      LDR      r3,[pc,#28] ; [0x1282a4] = 0x803004
        0x00128286:    3118        .1      ADDS     r1,r1,#0x18
        0x00128288:    681c        .h      LDR      r4,[r3,#0]
        0x0012828a:    3010        .0      ADDS     r0,r0,#0x10
        0x0012828c:    4b06        .K      LDR      r3,[pc,#24] ; [0x1282a8] = 0x3399
        0x0012828e:    2200        ."      MOVS     r2,#0
        0x00128290:    47a0        .G      BLX      r4
        0x00128292:    46bd        .F      MOV      sp,r7
        0x00128294:    bdb0        ..      POP      {r4,r5,r7,pc}
        0x00128296:    46c0        .F      MOV      r8,r8
    $d
        0x00128298:    e000e104    ....    DCD    3758153988
        0x0012829c:    00127ff0    ....    DCD    1212400
        0x001282a0:    00803000    .0..    DCD    8400896
        0x001282a4:    00803004    .0..    DCD    8400900
        0x001282a8:    00003399    .3..    DCD    13209
    $t
    crc32_init
        0x001282ac:    231f        .#      MOVS     r3,#0x1f
        0x001282ae:    2100        .!      MOVS     r1,#0
        0x001282b0:    2201        ."      MOVS     r2,#1
        0x001282b2:    b5f0        ..      PUSH     {r4-r7,lr}
        0x001282b4:    4210        .B      TST      r0,r2
        0x001282b6:    d002        ..      BEQ      0x1282be ; crc32_init + 18
        0x001282b8:    0014        ..      MOVS     r4,r2
        0x001282ba:    409c        .@      LSLS     r4,r4,r3
        0x001282bc:    4321        !C      ORRS     r1,r1,r4
        0x001282be:    0840        @.      LSRS     r0,r0,#1
        0x001282c0:    3b01        .;      SUBS     r3,#1
        0x001282c2:    d2f7        ..      BCS      0x1282b4 ; crc32_init + 8
        0x001282c4:    2480        .$      MOVS     r4,#0x80
        0x001282c6:    2200        ."      MOVS     r2,#0
        0x001282c8:    2601        .&      MOVS     r6,#1
        0x001282ca:    4d09        .M      LDR      r5,[pc,#36] ; [0x1282f0] = 0x129410
        0x001282cc:    0064        d.      LSLS     r4,r4,#1
        0x001282ce:    0013        ..      MOVS     r3,r2
        0x001282d0:    2008        .       MOVS     r0,#8
        0x001282d2:    001f        ..      MOVS     r7,r3
        0x001282d4:    085b        [.      LSRS     r3,r3,#1
        0x001282d6:    4037        7@      ANDS     r7,r7,r6
        0x001282d8:    d000        ..      BEQ      0x1282dc ; crc32_init + 48
        0x001282da:    404b        K@      EORS     r3,r3,r1
        0x001282dc:    3801        .8      SUBS     r0,#1
        0x001282de:    2800        .(      CMP      r0,#0
        0x001282e0:    d1f7        ..      BNE      0x1282d2 ; crc32_init + 38
        0x001282e2:    0090        ..      LSLS     r0,r2,#2
        0x001282e4:    3201        .2      ADDS     r2,#1
        0x001282e6:    502b        +P      STR      r3,[r5,r0]
        0x001282e8:    42a2        .B      CMP      r2,r4
        0x001282ea:    d1f0        ..      BNE      0x1282ce ; crc32_init + 34
        0x001282ec:    bdf0        ..      POP      {r4-r7,pc}
        0x001282ee:    46c0        .F      MOV      r8,r8
    $d
        0x001282f0:    00129410    ....    DCD    1217552
    $t
    crc32_calc
        0x001282f4:    b530        0.      PUSH     {r4,r5,lr}
        0x001282f6:    25ff        .%      MOVS     r5,#0xff
        0x001282f8:    4c07        .L      LDR      r4,[pc,#28] ; [0x128318] = 0x129410
        0x001282fa:    188a        ..      ADDS     r2,r1,r2
        0x001282fc:    4291        .B      CMP      r1,r2
        0x001282fe:    d101        ..      BNE      0x128304 ; crc32_calc + 16
        0x00128300:    43c0        .C      MVNS     r0,r0
        0x00128302:    bd30        0.      POP      {r4,r5,pc}
        0x00128304:    780b        .x      LDRB     r3,[r1,#0]
        0x00128306:    3101        .1      ADDS     r1,#1
        0x00128308:    4043        C@      EORS     r3,r3,r0
        0x0012830a:    402b        +@      ANDS     r3,r3,r5
        0x0012830c:    009b        ..      LSLS     r3,r3,#2
        0x0012830e:    591b        .Y      LDR      r3,[r3,r4]
        0x00128310:    0a00        ..      LSRS     r0,r0,#8
        0x00128312:    4058        X@      EORS     r0,r0,r3
        0x00128314:    e7f2        ..      B        0x1282fc ; crc32_calc + 8
        0x00128316:    46c0        .F      MOV      r8,r8
    $d
        0x00128318:    00129410    ....    DCD    1217552
    $t
    mpu_enable_for_xip_region
        0x0012831c:    2207        ."      MOVS     r2,#7
        0x0012831e:    4b06        .K      LDR      r3,[pc,#24] ; [0x128338] = 0xe000ed90
        0x00128320:    609a        .`      STR      r2,[r3,#8]
        0x00128322:    2280        ."      MOVS     r2,#0x80
        0x00128324:    0412        ..      LSLS     r2,r2,#16
        0x00128326:    60da        .`      STR      r2,[r3,#0xc]
        0x00128328:    4a04        .J      LDR      r2,[pc,#16] ; [0x12833c] = 0x1002002d
        0x0012832a:    611a        .a      STR      r2,[r3,#0x10]
        0x0012832c:    2205        ."      MOVS     r2,#5
        0x0012832e:    605a        Z`      STR      r2,[r3,#4]
        0x00128330:    f3bf8f4f    ..O.    DSB      
        0x00128334:    4770        pG      BX       lr
        0x00128336:    46c0        .F      MOV      r8,r8
    $d
        0x00128338:    e000ed90    ....    DCD    3758157200
        0x0012833c:    1002002d    -...    DCD    268566573
    $t
    cache_config
        0x00128340:    b510        ..      PUSH     {r4,lr}
        0x00128342:    2000        .       MOVS     r0,#0
        0x00128344:    f000f9e0    ....    BL       flash_cache_config ; 0x128708
        0x00128348:    bd10        ..      POP      {r4,pc}
        0x0012834a:    0000        ..      MOVS     r0,r0
    $t
    cache_enable
        0x0012834c:    b510        ..      PUSH     {r4,lr}
        0x0012834e:    f000f9f9    ....    BL       flash_cache_enable ; 0x128744
        0x00128352:    2200        ."      MOVS     r2,#0
        0x00128354:    4b01        .K      LDR      r3,[pc,#4] ; [0x12835c] = 0xe000ed90
        0x00128356:    605a        Z`      STR      r2,[r3,#4]
        0x00128358:    bd10        ..      POP      {r4,pc}
        0x0012835a:    46c0        .F      MOV      r8,r8
    $d
        0x0012835c:    e000ed90    ....    DCD    3758157200
    $t
    cache_disable
        0x00128360:    b510        ..      PUSH     {r4,lr}
        0x00128362:    f7ffffdb    ....    BL       mpu_enable_for_xip_region ; 0x12831c
        0x00128366:    f000fa07    ....    BL       flash_cache_disable ; 0x128778
        0x0012836a:    bd10        ..      POP      {r4,pc}
    $t
    dmac_clk_gate
        0x0012836c:    b510        ..      PUSH     {r4,lr}
        0x0012836e:    2040        @       MOVS     r0,#0x40
        0x00128370:    2900        .)      CMP      r1,#0
        0x00128372:    d000        ..      BEQ      0x128376 ; dmac_clk_gate + 10
        0x00128374:    2080        .       MOVS     r0,#0x80
        0x00128376:    f000f93d    ..=.    BL       clk_gate_cpu_g1 ; 0x1285f4
        0x0012837a:    bd10        ..      POP      {r4,pc}
    $t
    dmac_sw_rst
        0x0012837c:    b510        ..      PUSH     {r4,lr}
        0x0012837e:    2020                MOVS     r0,#0x20
        0x00128380:    f000f960    ..`.    BL       srst_cpu ; 0x128644
        0x00128384:    bd10        ..      POP      {r4,pc}
        0x00128386:    0000        ..      MOVS     r0,r0
    $t
    dmac_intr_op
        0x00128388:    2900        .)      CMP      r1,#0
        0x0012838a:    d105        ..      BNE      0x128398 ; dmac_intr_op + 16
        0x0012838c:    2240        @"      MOVS     r2,#0x40
        0x0012838e:    4b09        .K      LDR      r3,[pc,#36] ; [0x1283b4] = 0x129810
        0x00128390:    6018        .`      STR      r0,[r3,#0]
        0x00128392:    4b09        .K      LDR      r3,[pc,#36] ; [0x1283b8] = 0xe000e100
        0x00128394:    601a        .`      STR      r2,[r3,#0]
        0x00128396:    4770        pG      BX       lr
        0x00128398:    2901        .)      CMP      r1,#1
        0x0012839a:    d103        ..      BNE      0x1283a4 ; dmac_intr_op + 28
        0x0012839c:    2240        @"      MOVS     r2,#0x40
        0x0012839e:    4b07        .K      LDR      r3,[pc,#28] ; [0x1283bc] = 0xe000e104
        0x001283a0:    67da        .g      STR      r2,[r3,#0x7c]
        0x001283a2:    e7f8        ..      B        0x128396 ; dmac_intr_op + 14
        0x001283a4:    2902        .)      CMP      r1,#2
        0x001283a6:    d1f6        ..      BNE      0x128396 ; dmac_intr_op + 14
        0x001283a8:    23c0        .#      MOVS     r3,#0xc0
        0x001283aa:    4a03        .J      LDR      r2,[pc,#12] ; [0x1283b8] = 0xe000e100
        0x001283ac:    005b        [.      LSLS     r3,r3,#1
        0x001283ae:    313e        >1      ADDS     r1,r1,#0x3e
        0x001283b0:    50d1        .P      STR      r1,[r2,r3]
        0x001283b2:    e7f0        ..      B        0x128396 ; dmac_intr_op + 14
    $d
        0x001283b4:    00129810    ....    DCD    1218576
        0x001283b8:    e000e100    ....    DCD    3758153984
        0x001283bc:    e000e104    ....    DCD    3758153988
    $t
    dmac_sys_stat
        0x001283c0:    b510        ..      PUSH     {r4,lr}
        0x001283c2:    0002        ..      MOVS     r2,r0
        0x001283c4:    2903        .)      CMP      r1,#3
        0x001283c6:    d808        ..      BHI      0x1283da ; dmac_sys_stat + 26
        0x001283c8:    0008        ..      MOVS     r0,r1
        0x001283ca:    f000ffcf    ....    BL       __gnu_thumb1_case_uqi ; 0x12936c
    $d
        0x001283ce:    0702        ..      DCW    1794
        0x001283d0:    100c        ..      DCW    4108
    $t
        0x001283d2:    2100        .!      MOVS     r1,#0
        0x001283d4:    4807        .H      LDR      r0,[pc,#28] ; [0x1283f4] = 0x129988
        0x001283d6:    f000fe71    ..q.    BL       recovery_list_add ; 0x1290bc
        0x001283da:    bd10        ..      POP      {r4,pc}
        0x001283dc:    2100        .!      MOVS     r1,#0
        0x001283de:    4805        .H      LDR      r0,[pc,#20] ; [0x1283f4] = 0x129988
        0x001283e0:    f000fe6f    ..o.    BL       recovery_list_remove ; 0x1290c2
        0x001283e4:    e7f9        ..      B        0x1283da ; dmac_sys_stat + 26
        0x001283e6:    2201        ."      MOVS     r2,#1
        0x001283e8:    4b03        .K      LDR      r3,[pc,#12] ; [0x1283f8] = 0x129980
        0x001283ea:    701a        .p      STRB     r2,[r3,#0]
        0x001283ec:    e7f5        ..      B        0x1283da ; dmac_sys_stat + 26
        0x001283ee:    4b02        .K      LDR      r3,[pc,#8] ; [0x1283f8] = 0x129980
        0x001283f0:    2200        ."      MOVS     r2,#0
        0x001283f2:    e7fa        ..      B        0x1283ea ; dmac_sys_stat + 42
    $d
        0x001283f4:    00129988    ....    DCD    1218952
        0x001283f8:    00129980    ....    DCD    1218944
    $t
    qspi_sys_stat
        0x001283fc:    4770        pG      BX       lr
    $t
    qspi_clk_gate
        0x001283fe:    b510        ..      PUSH     {r4,lr}
        0x00128400:    2080        .       MOVS     r0,#0x80
        0x00128402:    2900        .)      CMP      r1,#0
        0x00128404:    d103        ..      BNE      0x12840e ; qspi_clk_gate + 16
        0x00128406:    00c0        ..      LSLS     r0,r0,#3
        0x00128408:    f000f8f4    ....    BL       clk_gate_cpu_g1 ; 0x1285f4
        0x0012840c:    bd10        ..      POP      {r4,pc}
        0x0012840e:    0100        ..      LSLS     r0,r0,#4
        0x00128410:    e7fa        ..      B        0x128408 ; qspi_clk_gate + 10
    $t
    qspi_sw_rst
        0x00128412:    2080        .       MOVS     r0,#0x80
        0x00128414:    b510        ..      PUSH     {r4,lr}
        0x00128416:    0180        ..      LSLS     r0,r0,#6
        0x00128418:    f000f914    ....    BL       srst_cpu ; 0x128644
        0x0012841c:    bd10        ..      POP      {r4,pc}
        0x0012841e:    0000        ..      MOVS     r0,r0
    $t
    qspi_pin_cfg
        0x00128420:    b510        ..      PUSH     {r4,lr}
        0x00128422:    2a05        .*      CMP      r2,#5
        0x00128424:    d811        ..      BHI      0x12844a ; qspi_pin_cfg + 42
        0x00128426:    0010        ..      MOVS     r0,r2
        0x00128428:    f000ffa0    ....    BL       __gnu_thumb1_case_uqi ; 0x12936c
    $d
        0x0012842c:    16131003    ....    DCD    370348035
        0x00128430:    211e        .!      DCW    8478
    $t
        0x00128432:    220f        ."      MOVS     r2,#0xf
        0x00128434:    490f        .I      LDR      r1,[pc,#60] ; [0x128474] = 0x20132000
        0x00128436:    2019        .       MOVS     r0,#0x19
        0x00128438:    6a0b        .j      LDR      r3,[r1,#0x20]
        0x0012843a:    4393        .C      BICS     r3,r3,r2
        0x0012843c:    001a        ..      MOVS     r2,r3
        0x0012843e:    2303        .#      MOVS     r3,#3
        0x00128440:    4313        .C      ORRS     r3,r3,r2
        0x00128442:    620b        .b      STR      r3,[r1,#0x20]
        0x00128444:    210c        .!      MOVS     r1,#0xc
        0x00128446:    f000f943    ..C.    BL       sysctrl_io_config ; 0x1286d0
        0x0012844a:    bd10        ..      POP      {r4,pc}
        0x0012844c:    210d        .!      MOVS     r1,#0xd
        0x0012844e:    201a        .       MOVS     r0,#0x1a
        0x00128450:    e7f9        ..      B        0x128446 ; qspi_pin_cfg + 38
        0x00128452:    210d        .!      MOVS     r1,#0xd
        0x00128454:    201b        .       MOVS     r0,#0x1b
        0x00128456:    e7f6        ..      B        0x128446 ; qspi_pin_cfg + 38
        0x00128458:    230f        .#      MOVS     r3,#0xf
        0x0012845a:    4a06        .J      LDR      r2,[pc,#24] ; [0x128474] = 0x20132000
        0x0012845c:    201c        .       MOVS     r0,#0x1c
        0x0012845e:    6a11        .j      LDR      r1,[r2,#0x20]
        0x00128460:    430b        .C      ORRS     r3,r3,r1
        0x00128462:    6213        .b      STR      r3,[r2,#0x20]
        0x00128464:    210d        .!      MOVS     r1,#0xd
        0x00128466:    e7ee        ..      B        0x128446 ; qspi_pin_cfg + 38
        0x00128468:    2105        .!      MOVS     r1,#5
        0x0012846a:    201d        .       MOVS     r0,#0x1d
        0x0012846c:    e7eb        ..      B        0x128446 ; qspi_pin_cfg + 38
        0x0012846e:    211c        .!      MOVS     r1,#0x1c
        0x00128470:    2018        .       MOVS     r0,#0x18
        0x00128472:    e7e8        ..      B        0x128446 ; qspi_pin_cfg + 38
    $d
        0x00128474:    20132000    . .     DCD    538124288
    $t
    qspi_get_fifo_depth
        0x00128478:    2040        @       MOVS     r0,#0x40
        0x0012847a:    4770        pG      BX       lr
    $t
    cache_sys_stat
        0x0012847c:    b510        ..      PUSH     {r4,lr}
        0x0012847e:    2401        .$      MOVS     r4,#1
        0x00128480:    4804        .H      LDR      r0,[pc,#16] ; [0x128494] = 0x20132000
        0x00128482:    000a        ..      MOVS     r2,r1
        0x00128484:    6c03        .l      LDR      r3,[r0,#0x40]
        0x00128486:    4022        "@      ANDS     r2,r2,r4
        0x00128488:    43a3        .C      BICS     r3,r3,r4
        0x0012848a:    0019        ..      MOVS     r1,r3
        0x0012848c:    4311        .C      ORRS     r1,r1,r2
        0x0012848e:    6401        .d      STR      r1,[r0,#0x40]
        0x00128490:    bd10        ..      POP      {r4,pc}
        0x00128492:    46c0        .F      MOV      r8,r8
    $d
        0x00128494:    20132000    . .     DCD    538124288
    $t
    cache_clk_gate
        0x00128498:    b510        ..      PUSH     {r4,lr}
        0x0012849a:    2080        .       MOVS     r0,#0x80
        0x0012849c:    2900        .)      CMP      r1,#0
        0x0012849e:    d103        ..      BNE      0x1284a8 ; cache_clk_gate + 16
        0x001284a0:    0040        @.      LSLS     r0,r0,#1
        0x001284a2:    f000f8a7    ....    BL       clk_gate_cpu_g1 ; 0x1285f4
        0x001284a6:    bd10        ..      POP      {r4,pc}
        0x001284a8:    0080        ..      LSLS     r0,r0,#2
        0x001284aa:    e7fa        ..      B        0x1284a2 ; cache_clk_gate + 10
    $t
    flash_program_svcall
        0x001284ac:    df00        ..      SVC      #0x0 ; formerly SWI
        0x001284ae:    4770        pG      BX       lr
    $t
    flash_erase_svcall
        0x001284b0:    df01        ..      SVC      #0x1 ; formerly SWI
        0x001284b2:    4770        pG      BX       lr
    $t
    flash_read_svcall
        0x001284b4:    df02        ..      SVC      #0x2 ; formerly SWI
        0x001284b6:    4770        pG      BX       lr
    $t
    flash_multi_read_32bits_svcall
        0x001284b8:    df03        ..      SVC      #0x3 ; formerly SWI
        0x001284ba:    4770        pG      BX       lr
    $t
    flash_write_status_reg_svcall
        0x001284bc:    df04        ..      SVC      #0x4 ; formerly SWI
        0x001284be:    4770        pG      BX       lr
    $t
    flash_program_execution
        0x001284c0:    b5f8        ..      PUSH     {r3-r7,lr}
        0x001284c2:    000d        ..      MOVS     r5,r1
        0x001284c4:    0016        ..      MOVS     r6,r2
        0x001284c6:    001f        ..      MOVS     r7,r3
        0x001284c8:    0004        ..      MOVS     r4,r0
        0x001284ca:    f7ffff49    ..I.    BL       cache_disable ; 0x128360
        0x001284ce:    003b        ;.      MOVS     r3,r7
        0x001284d0:    0032        2.      MOVS     r2,r6
        0x001284d2:    0029        ).      MOVS     r1,r5
        0x001284d4:    0020         .      MOVS     r0,r4
        0x001284d6:    f000fe32    ..2.    BL       flash_program_operation_start ; 0x12913e
        0x001284da:    0004        ..      MOVS     r4,r0
        0x001284dc:    f7ffff36    ..6.    BL       cache_enable ; 0x12834c
        0x001284e0:    0020         .      MOVS     r0,r4
        0x001284e2:    bdf8        ..      POP      {r3-r7,pc}
    $t
    flash_program_operation
        0x001284e4:    b510        ..      PUSH     {r4,lr}
        0x001284e6:    f3ef8410    ....    MRS      r4,PRIMASK
        0x001284ea:    2c00        .,      CMP      r4,#0
        0x001284ec:    d002        ..      BEQ      0x1284f4 ; flash_program_operation + 16
        0x001284ee:    f7ffffe7    ....    BL       flash_program_execution ; 0x1284c0
        0x001284f2:    bd10        ..      POP      {r4,pc}
        0x001284f4:    f7ffffda    ....    BL       flash_program_svcall ; 0x1284ac
        0x001284f8:    e7fb        ..      B        0x1284f2 ; flash_program_operation + 14
    $t
    flash_erase_execution
        0x001284fa:    b570        p.      PUSH     {r4-r6,lr}
        0x001284fc:    000d        ..      MOVS     r5,r1
        0x001284fe:    0016        ..      MOVS     r6,r2
        0x00128500:    0004        ..      MOVS     r4,r0
        0x00128502:    f7ffff2d    ..-.    BL       cache_disable ; 0x128360
        0x00128506:    0032        2.      MOVS     r2,r6
        0x00128508:    0029        ).      MOVS     r1,r5
        0x0012850a:    0020         .      MOVS     r0,r4
        0x0012850c:    f000fe2b    ..+.    BL       flash_erase_operation_start ; 0x129166
        0x00128510:    0004        ..      MOVS     r4,r0
        0x00128512:    f7ffff1b    ....    BL       cache_enable ; 0x12834c
        0x00128516:    0020         .      MOVS     r0,r4
        0x00128518:    bd70        p.      POP      {r4-r6,pc}
    $t
    flash_erase_operation
        0x0012851a:    b510        ..      PUSH     {r4,lr}
        0x0012851c:    f3ef8310    ....    MRS      r3,PRIMASK
        0x00128520:    2b00        .+      CMP      r3,#0
        0x00128522:    d002        ..      BEQ      0x12852a ; flash_erase_operation + 16
        0x00128524:    f7ffffe9    ....    BL       flash_erase_execution ; 0x1284fa
        0x00128528:    bd10        ..      POP      {r4,pc}
        0x0012852a:    f7ffffc1    ....    BL       flash_erase_svcall ; 0x1284b0
        0x0012852e:    e7fb        ..      B        0x128528 ; flash_erase_operation + 14
    $t
    flash_read_execution
        0x00128530:    b5f8        ..      PUSH     {r3-r7,lr}
        0x00128532:    000d        ..      MOVS     r5,r1
        0x00128534:    0016        ..      MOVS     r6,r2
        0x00128536:    001f        ..      MOVS     r7,r3
        0x00128538:    0004        ..      MOVS     r4,r0
        0x0012853a:    f7ffff11    ....    BL       cache_disable ; 0x128360
        0x0012853e:    003b        ;.      MOVS     r3,r7
        0x00128540:    0032        2.      MOVS     r2,r6
        0x00128542:    0029        ).      MOVS     r1,r5
        0x00128544:    0020         .      MOVS     r0,r4
        0x00128546:    f000fe33    ..3.    BL       flash_read_operation_start ; 0x1291b0
        0x0012854a:    0004        ..      MOVS     r4,r0
        0x0012854c:    f7fffefe    ....    BL       cache_enable ; 0x12834c
        0x00128550:    0020         .      MOVS     r0,r4
        0x00128552:    bdf8        ..      POP      {r3-r7,pc}
    $t
    flash_read_operation
        0x00128554:    b510        ..      PUSH     {r4,lr}
        0x00128556:    f3ef8410    ....    MRS      r4,PRIMASK
        0x0012855a:    2c00        .,      CMP      r4,#0
        0x0012855c:    d002        ..      BEQ      0x128564 ; flash_read_operation + 16
        0x0012855e:    f7ffffe7    ....    BL       flash_read_execution ; 0x128530
        0x00128562:    bd10        ..      POP      {r4,pc}
        0x00128564:    f7ffffa6    ....    BL       flash_read_svcall ; 0x1284b4
        0x00128568:    e7fb        ..      B        0x128562 ; flash_read_operation + 14
    $t
    flash_multi_read_32bits_execution
        0x0012856a:    b570        p.      PUSH     {r4-r6,lr}
        0x0012856c:    000d        ..      MOVS     r5,r1
        0x0012856e:    0016        ..      MOVS     r6,r2
        0x00128570:    0004        ..      MOVS     r4,r0
        0x00128572:    f7fffef5    ....    BL       cache_disable ; 0x128360
        0x00128576:    0032        2.      MOVS     r2,r6
        0x00128578:    0029        ).      MOVS     r1,r5
        0x0012857a:    0020         .      MOVS     r0,r4
        0x0012857c:    f000fe13    ....    BL       flash_multi_read_32bits_operation_start ; 0x1291a6
        0x00128580:    0004        ..      MOVS     r4,r0
        0x00128582:    f7fffee3    ....    BL       cache_enable ; 0x12834c
        0x00128586:    0020         .      MOVS     r0,r4
        0x00128588:    bd70        p.      POP      {r4-r6,pc}
    $t
    flash_multi_read_32bits_operation
        0x0012858a:    b510        ..      PUSH     {r4,lr}
        0x0012858c:    f3ef8310    ....    MRS      r3,PRIMASK
        0x00128590:    2b00        .+      CMP      r3,#0
        0x00128592:    d002        ..      BEQ      0x12859a ; flash_multi_read_32bits_operation + 16
        0x00128594:    f7ffffe9    ....    BL       flash_multi_read_32bits_execution ; 0x12856a
        0x00128598:    bd10        ..      POP      {r4,pc}
        0x0012859a:    f7ffff8d    ....    BL       flash_multi_read_32bits_svcall ; 0x1284b8
        0x0012859e:    e7fb        ..      B        0x128598 ; flash_multi_read_32bits_operation + 14
    $t
    flash_write_status_reg_execution
        0x001285a0:    b570        p.      PUSH     {r4-r6,lr}
        0x001285a2:    000d        ..      MOVS     r5,r1
        0x001285a4:    0016        ..      MOVS     r6,r2
        0x001285a6:    0004        ..      MOVS     r4,r0
        0x001285a8:    f7fffeda    ....    BL       cache_disable ; 0x128360
        0x001285ac:    0032        2.      MOVS     r2,r6
        0x001285ae:    0029        ).      MOVS     r1,r5
        0x001285b0:    0020         .      MOVS     r0,r4
        0x001285b2:    f000fe01    ....    BL       flash_write_status_reg_start ; 0x1291b8
        0x001285b6:    0004        ..      MOVS     r4,r0
        0x001285b8:    f7fffec8    ....    BL       cache_enable ; 0x12834c
        0x001285bc:    0020         .      MOVS     r0,r4
        0x001285be:    bd70        p.      POP      {r4-r6,pc}
    $t
    flash_write_status_reg_operation
        0x001285c0:    b510        ..      PUSH     {r4,lr}
        0x001285c2:    f3ef8310    ....    MRS      r3,PRIMASK
        0x001285c6:    2b00        .+      CMP      r3,#0
        0x001285c8:    d002        ..      BEQ      0x1285d0 ; flash_write_status_reg_operation + 16
        0x001285ca:    f7ffffe9    ....    BL       flash_write_status_reg_execution ; 0x1285a0
        0x001285ce:    bd10        ..      POP      {r4,pc}
        0x001285d0:    f7ffff74    ..t.    BL       flash_write_status_reg_svcall ; 0x1284bc
        0x001285d4:    e7fb        ..      B        0x1285ce ; flash_write_status_reg_operation + 14
        0x001285d6:    0000        ..      MOVS     r0,r0
    $t
    clk_gate_clr_all_clk
        0x001285d8:    4b03        .K      LDR      r3,[pc,#12] ; [0x1285e8] = 0xaaaaaaaa
        0x001285da:    4a04        .J      LDR      r2,[pc,#16] ; [0x1285ec] = 0x20132000
        0x001285dc:    6113        .a      STR      r3,[r2,#0x10]
        0x001285de:    6153        Sa      STR      r3,[r2,#0x14]
        0x001285e0:    4a03        .J      LDR      r2,[pc,#12] ; [0x1285f0] = 0x20149000
        0x001285e2:    6113        .a      STR      r3,[r2,#0x10]
        0x001285e4:    6153        Sa      STR      r3,[r2,#0x14]
        0x001285e6:    4770        pG      BX       lr
    $d
        0x001285e8:    aaaaaaaa    ....    DCD    2863311530
        0x001285ec:    20132000    . .     DCD    538124288
        0x001285f0:    20149000    ...     DCD    538218496
    $t
    clk_gate_cpu_g1
        0x001285f4:    b510        ..      PUSH     {r4,lr}
        0x001285f6:    f3ef8210    ....    MRS      r2,PRIMASK
        0x001285fa:    b672        r.      CPSID    i
        0x001285fc:    4b09        .K      LDR      r3,[pc,#36] ; [0x128624] = 0x20132000
        0x001285fe:    490a        .I      LDR      r1,[pc,#40] ; [0x128628] = 0xaaaaaaaa
        0x00128600:    6158        Xa      STR      r0,[r3,#0x14]
        0x00128602:    4208        .B      TST      r0,r1
        0x00128604:    d006        ..      BEQ      0x128614 ; clk_gate_cpu_g1 + 32
        0x00128606:    6959        Yi      LDR      r1,[r3,#0x14]
        0x00128608:    4201        .B      TST      r1,r0
        0x0012860a:    d1fc        ..      BNE      0x128606 ; clk_gate_cpu_g1 + 18
        0x0012860c:    2a00        .*      CMP      r2,#0
        0x0012860e:    d100        ..      BNE      0x128612 ; clk_gate_cpu_g1 + 30
        0x00128610:    b662        b.      CPSIE    i
        0x00128612:    bd10        ..      POP      {r4,pc}
        0x00128614:    4905        .I      LDR      r1,[pc,#20] ; [0x12862c] = 0x55555555
        0x00128616:    4208        .B      TST      r0,r1
        0x00128618:    d0f8        ..      BEQ      0x12860c ; clk_gate_cpu_g1 + 24
        0x0012861a:    0004        ..      MOVS     r4,r0
        0x0012861c:    6959        Yi      LDR      r1,[r3,#0x14]
        0x0012861e:    438c        .C      BICS     r4,r4,r1
        0x00128620:    d1fb        ..      BNE      0x12861a ; clk_gate_cpu_g1 + 38
        0x00128622:    e7f3        ..      B        0x12860c ; clk_gate_cpu_g1 + 24
    $d
        0x00128624:    20132000    . .     DCD    538124288
        0x00128628:    aaaaaaaa    ....    DCD    2863311530
        0x0012862c:    55555555    UUUU    DCD    1431655765
    $t
    pshare_reset_to_gpio
        0x00128630:    2200        ."      MOVS     r2,#0
        0x00128632:    4b03        .K      LDR      r3,[pc,#12] ; [0x128640] = 0x20132000
        0x00128634:    625a        Zb      STR      r2,[r3,#0x24]
        0x00128636:    22c0        ."      MOVS     r2,#0xc0
        0x00128638:    0152        R.      LSLS     r2,r2,#5
        0x0012863a:    621a        .b      STR      r2,[r3,#0x20]
        0x0012863c:    4770        pG      BX       lr
        0x0012863e:    46c0        .F      MOV      r8,r8
    $d
        0x00128640:    20132000    . .     DCD    538124288
    $t
    srst_cpu
        0x00128644:    4b02        .K      LDR      r3,[pc,#8] ; [0x128650] = 0x20132000
        0x00128646:    6198        .a      STR      r0,[r3,#0x18]
        0x00128648:    0840        @.      LSRS     r0,r0,#1
        0x0012864a:    6198        .a      STR      r0,[r3,#0x18]
        0x0012864c:    4770        pG      BX       lr
        0x0012864e:    46c0        .F      MOV      r8,r8
    $d
        0x00128650:    20132000    . .     DCD    538124288
    $t
    srst_per
        0x00128654:    4b02        .K      LDR      r3,[pc,#8] ; [0x128660] = 0x20149000
        0x00128656:    6198        .a      STR      r0,[r3,#0x18]
        0x00128658:    0840        @.      LSRS     r0,r0,#1
        0x0012865a:    6198        .a      STR      r0,[r3,#0x18]
        0x0012865c:    4770        pG      BX       lr
        0x0012865e:    46c0        .F      MOV      r8,r8
    $d
        0x00128660:    20149000    ...     DCD    538218496
    $t
    sysctrl_io_config_mask
        0x00128664:    b530        0.      PUSH     {r4,r5,lr}
        0x00128666:    f3ef8410    ....    MRS      r4,PRIMASK
        0x0012866a:    b672        r.      CPSID    i
        0x0012866c:    4b16        .K      LDR      r3,[pc,#88] ; [0x1286c8] = 0x1293c4
        0x0012866e:    07ca        ..      LSLS     r2,r1,#31
        0x00128670:    d51d        ..      BPL      0x1286ae ; sysctrl_io_config_mask + 74
        0x00128672:    681a        .h      LDR      r2,[r3,#0]
        0x00128674:    4302        .C      ORRS     r2,r2,r0
        0x00128676:    601a        .`      STR      r2,[r3,#0]
        0x00128678:    685a        Zh      LDR      r2,[r3,#4]
        0x0012867a:    078d        ..      LSLS     r5,r1,#30
        0x0012867c:    d51a        ..      BPL      0x1286b4 ; sysctrl_io_config_mask + 80
        0x0012867e:    4302        .C      ORRS     r2,r2,r0
        0x00128680:    605a        Z`      STR      r2,[r3,#4]
        0x00128682:    689a        .h      LDR      r2,[r3,#8]
        0x00128684:    074d        M.      LSLS     r5,r1,#29
        0x00128686:    d517        ..      BPL      0x1286b8 ; sysctrl_io_config_mask + 84
        0x00128688:    4302        .C      ORRS     r2,r2,r0
        0x0012868a:    609a        .`      STR      r2,[r3,#8]
        0x0012868c:    68da        .h      LDR      r2,[r3,#0xc]
        0x0012868e:    070d        ..      LSLS     r5,r1,#28
        0x00128690:    d514        ..      BPL      0x1286bc ; sysctrl_io_config_mask + 88
        0x00128692:    4302        .C      ORRS     r2,r2,r0
        0x00128694:    60da        .`      STR      r2,[r3,#0xc]
        0x00128696:    691a        .i      LDR      r2,[r3,#0x10]
        0x00128698:    06c9        ..      LSLS     r1,r1,#27
        0x0012869a:    d511        ..      BPL      0x1286c0 ; sysctrl_io_config_mask + 92
        0x0012869c:    4310        .C      ORRS     r0,r0,r2
        0x0012869e:    6118        .a      STR      r0,[r3,#0x10]
        0x001286a0:    681a        .h      LDR      r2,[r3,#0]
        0x001286a2:    4b0a        .K      LDR      r3,[pc,#40] ; [0x1286cc] = 0x20201000
        0x001286a4:    655a        Ze      STR      r2,[r3,#0x54]
        0x001286a6:    2c00        .,      CMP      r4,#0
        0x001286a8:    d100        ..      BNE      0x1286ac ; sysctrl_io_config_mask + 72
        0x001286aa:    b662        b.      CPSIE    i
        0x001286ac:    bd30        0.      POP      {r4,r5,pc}
        0x001286ae:    681a        .h      LDR      r2,[r3,#0]
        0x001286b0:    4382        .C      BICS     r2,r2,r0
        0x001286b2:    e7e0        ..      B        0x128676 ; sysctrl_io_config_mask + 18
        0x001286b4:    4382        .C      BICS     r2,r2,r0
        0x001286b6:    e7e3        ..      B        0x128680 ; sysctrl_io_config_mask + 28
        0x001286b8:    4382        .C      BICS     r2,r2,r0
        0x001286ba:    e7e6        ..      B        0x12868a ; sysctrl_io_config_mask + 38
        0x001286bc:    4382        .C      BICS     r2,r2,r0
        0x001286be:    e7e9        ..      B        0x128694 ; sysctrl_io_config_mask + 48
        0x001286c0:    4382        .C      BICS     r2,r2,r0
        0x001286c2:    611a        .a      STR      r2,[r3,#0x10]
        0x001286c4:    e7ec        ..      B        0x1286a0 ; sysctrl_io_config_mask + 60
        0x001286c6:    46c0        .F      MOV      r8,r8
    $d
        0x001286c8:    001293c4    ....    DCD    1217476
        0x001286cc:    20201000    ..      DCD    538972160
    $t
    sysctrl_io_config
        0x001286d0:    2301        .#      MOVS     r3,#1
        0x001286d2:    4083        .@      LSLS     r3,r3,r0
        0x001286d4:    b510        ..      PUSH     {r4,lr}
        0x001286d6:    0018        ..      MOVS     r0,r3
        0x001286d8:    f7ffffc4    ....    BL       sysctrl_io_config_mask ; 0x128664
        0x001286dc:    bd10        ..      POP      {r4,pc}
        0x001286de:    0000        ..      MOVS     r0,r0
    $t
    sysctrl_io_init
        0x001286e0:    2200        ."      MOVS     r2,#0
        0x001286e2:    4b03        .K      LDR      r3,[pc,#12] ; [0x1286f0] = 0x20201000
        0x001286e4:    661a        .f      STR      r2,[r3,#0x60]
        0x001286e6:    3203        .2      ADDS     r2,#3
        0x001286e8:    65da        .e      STR      r2,[r3,#0x5c]
        0x001286ea:    655a        Ze      STR      r2,[r3,#0x54]
        0x001286ec:    4770        pG      BX       lr
        0x001286ee:    46c0        .F      MOV      r8,r8
    $d
        0x001286f0:    20201000    ..      DCD    538972160
    $t
    flash_cache_flush_all
        0x001286f4:    2201        ."      MOVS     r2,#1
        0x001286f6:    4b03        .K      LDR      r3,[pc,#12] ; [0x128704] = 0x20121000
        0x001286f8:    619a        .a      STR      r2,[r3,#0x18]
        0x001286fa:    61da        .a      STR      r2,[r3,#0x1c]
        0x001286fc:    69da        .i      LDR      r2,[r3,#0x1c]
        0x001286fe:    2a00        .*      CMP      r2,#0
        0x00128700:    d1fc        ..      BNE      0x1286fc ; flash_cache_flush_all + 8
        0x00128702:    4770        pG      BX       lr
    $d
        0x00128704:    20121000    ...     DCD    538054656
    $t
    flash_cache_config
        0x00128708:    4b0b        .K      LDR      r3,[pc,#44] ; [0x128738] = 0x1293bc
        0x0012870a:    b570        p.      PUSH     {r4-r6,lr}
        0x0012870c:    681b        .h      LDR      r3,[r3,#0]
        0x0012870e:    0005        ..      MOVS     r5,r0
        0x00128710:    2101        .!      MOVS     r1,#1
        0x00128712:    2000        .       MOVS     r0,#0
        0x00128714:    4798        .G      BLX      r3
        0x00128716:    2100        .!      MOVS     r1,#0
        0x00128718:    4b08        .K      LDR      r3,[pc,#32] ; [0x12873c] = 0x1293b8
        0x0012871a:    4c09        .L      LDR      r4,[pc,#36] ; [0x128740] = 0x20121000
        0x0012871c:    681b        .h      LDR      r3,[r3,#0]
        0x0012871e:    0008        ..      MOVS     r0,r1
        0x00128720:    4798        .G      BLX      r3
        0x00128722:    f7ffffe7    ....    BL       flash_cache_flush_all ; 0x1286f4
        0x00128726:    6065        e`      STR      r5,[r4,#4]
        0x00128728:    f000fb2c    ..,.    BL       app_qspi_dr_reg_addr_for_cache_wrapper ; 0x128d84
        0x0012872c:    239c        .#      MOVS     r3,#0x9c
        0x0012872e:    055b        [.      LSLS     r3,r3,#21
        0x00128730:    60a0        .`      STR      r0,[r4,#8]
        0x00128732:    60e3        .`      STR      r3,[r4,#0xc]
        0x00128734:    bd70        p.      POP      {r4-r6,pc}
        0x00128736:    46c0        .F      MOV      r8,r8
    $d
        0x00128738:    001293bc    ....    DCD    1217468
        0x0012873c:    001293b8    ....    DCD    1217464
        0x00128740:    20121000    ...     DCD    538054656
    $t
    flash_cache_enable
        0x00128744:    b570        p.      PUSH     {r4-r6,lr}
        0x00128746:    2020                MOVS     r0,#0x20
        0x00128748:    f000fb0a    ....    BL       app_qspi_config_for_cache_wrapper ; 0x128d60
        0x0012874c:    1e05        ..      SUBS     r5,r0,#0
        0x0012874e:    d10d        ..      BNE      0x12876c ; flash_cache_enable + 40
        0x00128750:    4b07        .K      LDR      r3,[pc,#28] ; [0x128770] = 0x1293b8
        0x00128752:    4e08        .N      LDR      r6,[pc,#32] ; [0x128774] = 0x20121000
        0x00128754:    681b        .h      LDR      r3,[r3,#0]
        0x00128756:    0001        ..      MOVS     r1,r0
        0x00128758:    4798        .G      BLX      r3
        0x0012875a:    68f4        .h      LDR      r4,[r6,#0xc]
        0x0012875c:    f000fb0a    ....    BL       app_qspi_multi_read_cmd_get_wrapper ; 0x128d74
        0x00128760:    23ff        .#      MOVS     r3,#0xff
        0x00128762:    439c        .C      BICS     r4,r4,r3
        0x00128764:    4320         C      ORRS     r0,r0,r4
        0x00128766:    3bfe        .;      SUBS     r3,r3,#0xfe
        0x00128768:    60f0        .`      STR      r0,[r6,#0xc]
        0x0012876a:    6033        3`      STR      r3,[r6,#0]
        0x0012876c:    0028        (.      MOVS     r0,r5
        0x0012876e:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x00128770:    001293b8    ....    DCD    1217464
        0x00128774:    20121000    ...     DCD    538054656
    $t
    flash_cache_disable
        0x00128778:    b510        ..      PUSH     {r4,lr}
        0x0012877a:    f000fb0b    ....    BL       app_qspi_disable_for_cache_wrapper ; 0x128d94
        0x0012877e:    1e04        ..      SUBS     r4,r0,#0
        0x00128780:    d105        ..      BNE      0x12878e ; flash_cache_disable + 22
        0x00128782:    4b04        .K      LDR      r3,[pc,#16] ; [0x128794] = 0x20121000
        0x00128784:    2101        .!      MOVS     r1,#1
        0x00128786:    6018        .`      STR      r0,[r3,#0]
        0x00128788:    4b03        .K      LDR      r3,[pc,#12] ; [0x128798] = 0x1293b8
        0x0012878a:    681b        .h      LDR      r3,[r3,#0]
        0x0012878c:    4798        .G      BLX      r3
        0x0012878e:    0020         .      MOVS     r0,r4
        0x00128790:    bd10        ..      POP      {r4,pc}
        0x00128792:    46c0        .F      MOV      r8,r8
    $d
        0x00128794:    20121000    ...     DCD    538054656
        0x00128798:    001293b8    ....    DCD    1217464
    $t
    qspi_std_byte_write_dma_start
        0x0012879c:    b570        p.      PUSH     {r4-r6,lr}
        0x0012879e:    b088        ..      SUB      sp,sp,#0x20
        0x001287a0:    0004        ..      MOVS     r4,r0
        0x001287a2:    a802        ..      ADD      r0,sp,#8
        0x001287a4:    6103        .a      STR      r3,[r0,#0x10]
        0x001287a6:    4b0f        .K      LDR      r3,[pc,#60] ; [0x1287e4] = 0xffff9240
        0x001287a8:    6082        .`      STR      r2,[r0,#8]
        0x001287aa:    8283        ..      STRH     r3,[r0,#0x14]
        0x001287ac:    2300        .#      MOVS     r3,#0
        0x001287ae:    7583        .u      STRB     r3,[r0,#0x16]
        0x001287b0:    466b        kF      MOV      r3,sp
        0x001287b2:    0022        ".      MOVS     r2,r4
        0x001287b4:    000e        ..      MOVS     r6,r1
        0x001287b6:    1ddd        ..      ADDS     r5,r3,#7
        0x001287b8:    3260        `2      ADDS     r2,r2,#0x60
        0x001287ba:    0029        ).      MOVS     r1,r5
        0x001287bc:    60c2        .`      STR      r2,[r0,#0xc]
        0x001287be:    f000fc6b    ..k.    BL       app_dmac_start_wrapper ; 0x129098
        0x001287c2:    6126        &a      STR      r6,[r4,#0x10]
        0x001287c4:    7828        (x      LDRB     r0,[r5,#0]
        0x001287c6:    f000fc71    ..q.    BL       app_dmac_transfer_wait_wrapper ; 0x1290ac
        0x001287ca:    2304        .#      MOVS     r3,#4
        0x001287cc:    6aa2        .j      LDR      r2,[r4,#0x28]
        0x001287ce:    421a        .B      TST      r2,r3
        0x001287d0:    d0fc        ..      BEQ      0x1287cc ; qspi_std_byte_write_dma_start + 48
        0x001287d2:    2201        ."      MOVS     r2,#1
        0x001287d4:    6aa3        .j      LDR      r3,[r4,#0x28]
        0x001287d6:    4013        .@      ANDS     r3,r3,r2
        0x001287d8:    d1fc        ..      BNE      0x1287d4 ; qspi_std_byte_write_dma_start + 56
        0x001287da:    60a3        .`      STR      r3,[r4,#8]
        0x001287dc:    6123        #a      STR      r3,[r4,#0x10]
        0x001287de:    b008        ..      ADD      sp,sp,#0x20
        0x001287e0:    bd70        p.      POP      {r4-r6,pc}
        0x001287e2:    46c0        .F      MOV      r8,r8
    $d
        0x001287e4:    ffff9240    @...    DCD    4294939200
    $t
    app_qspi_init
        0x001287e8:    b570        p.      PUSH     {r4-r6,lr}
        0x001287ea:    0004        ..      MOVS     r4,r0
        0x001287ec:    4d20         M      LDR      r5,[pc,#128] ; [0x128870] = 0x1293a0
        0x001287ee:    686b        kh      LDR      r3,[r5,#4]
        0x001287f0:    4798        .G      BLX      r3
        0x001287f2:    2100        .!      MOVS     r1,#0
        0x001287f4:    0020         .      MOVS     r0,r4
        0x001287f6:    68eb        .h      LDR      r3,[r5,#0xc]
        0x001287f8:    4798        .G      BLX      r3
        0x001287fa:    2301        .#      MOVS     r3,#1
        0x001287fc:    2200        ."      MOVS     r2,#0
        0x001287fe:    7a61        az      LDRB     r1,[r4,#9]
        0x00128800:    0020         .      MOVS     r0,r4
        0x00128802:    692e        .i      LDR      r6,[r5,#0x10]
        0x00128804:    47b0        .G      BLX      r6
        0x00128806:    223f        ?"      MOVS     r2,#0x3f
        0x00128808:    7a23        #z      LDRB     r3,[r4,#8]
        0x0012880a:    4393        .C      BICS     r3,r3,r2
        0x0012880c:    2b80        .+      CMP      r3,#0x80
        0x0012880e:    d10b        ..      BNE      0x128828 ; app_qspi_init + 64
        0x00128810:    7b61        a{      LDRB     r1,[r4,#0xd]
        0x00128812:    3b7f        .;      SUBS     r3,r3,#0x7f
        0x00128814:    3a3b        ;:      SUBS     r2,r2,#0x3b
        0x00128816:    0020         .      MOVS     r0,r4
        0x00128818:    692e        .i      LDR      r6,[r5,#0x10]
        0x0012881a:    47b0        .G      BLX      r6
        0x0012881c:    7b21        !{      LDRB     r1,[r4,#0xc]
        0x0012881e:    2301        .#      MOVS     r3,#1
        0x00128820:    2203        ."      MOVS     r2,#3
        0x00128822:    0020         .      MOVS     r0,r4
        0x00128824:    692e        .i      LDR      r6,[r5,#0x10]
        0x00128826:    47b0        .G      BLX      r6
        0x00128828:    2301        .#      MOVS     r3,#1
        0x0012882a:    692e        .i      LDR      r6,[r5,#0x10]
        0x0012882c:    7aa1        .z      LDRB     r1,[r4,#0xa]
        0x0012882e:    001a        ..      MOVS     r2,r3
        0x00128830:    0020         .      MOVS     r0,r4
        0x00128832:    47b0        .G      BLX      r6
        0x00128834:    692e        .i      LDR      r6,[r5,#0x10]
        0x00128836:    7ae1        .z      LDRB     r1,[r4,#0xb]
        0x00128838:    0020         .      MOVS     r0,r4
        0x0012883a:    2301        .#      MOVS     r3,#1
        0x0012883c:    2202        ."      MOVS     r2,#2
        0x0012883e:    47b0        .G      BLX      r6
        0x00128840:    692e        .i      LDR      r6,[r5,#0x10]
        0x00128842:    7ba1        .{      LDRB     r1,[r4,#0xe]
        0x00128844:    0020         .      MOVS     r0,r4
        0x00128846:    2301        .#      MOVS     r3,#1
        0x00128848:    2205        ."      MOVS     r2,#5
        0x0012884a:    47b0        .G      BLX      r6
        0x0012884c:    2600        .&      MOVS     r6,#0
        0x0012884e:    6923        #i      LDR      r3,[r4,#0x10]
        0x00128850:    0020         .      MOVS     r0,r4
        0x00128852:    609e        .`      STR      r6,[r3,#8]
        0x00128854:    88a2        ..      LDRH     r2,[r4,#4]
        0x00128856:    2101        .!      MOVS     r1,#1
        0x00128858:    615a        Za      STR      r2,[r3,#0x14]
        0x0012885a:    79a2        .y      LDRB     r2,[r4,#6]
        0x0012885c:    33f0        .3      ADDS     r3,r3,#0xf0
        0x0012885e:    601a        .`      STR      r2,[r3,#0]
        0x00128860:    68eb        .h      LDR      r3,[r5,#0xc]
        0x00128862:    4798        .G      BLX      r3
        0x00128864:    696b        ki      LDR      r3,[r5,#0x14]
        0x00128866:    0031        1.      MOVS     r1,r6
        0x00128868:    0020         .      MOVS     r0,r4
        0x0012886a:    4798        .G      BLX      r3
        0x0012886c:    0030        0.      MOVS     r0,r6
        0x0012886e:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x00128870:    001293a0    ....    DCD    1217440
    $t
    app_qspi_std_write
        0x00128874:    b5f0        ..      PUSH     {r4-r7,lr}
        0x00128876:    0004        ..      MOVS     r4,r0
        0x00128878:    b085        ..      SUB      sp,sp,#0x14
        0x0012887a:    9101        ..      STR      r1,[sp,#4]
        0x0012887c:    9202        ..      STR      r2,[sp,#8]
        0x0012887e:    9303        ..      STR      r3,[sp,#0xc]
        0x00128880:    f7fffdfa    ....    BL       qspi_get_fifo_depth ; 0x128478
        0x00128884:    0023        #.      MOVS     r3,r4
        0x00128886:    3314        .3      ADDS     r3,r3,#0x14
        0x00128888:    0007        ..      MOVS     r7,r0
        0x0012888a:    0018        ..      MOVS     r0,r3
        0x0012888c:    9300        ..      STR      r3,[sp,#0]
        0x0012888e:    6925        %i      LDR      r5,[r4,#0x10]
        0x00128890:    f000fc1b    ....    BL       periph_lock ; 0x1290ca
        0x00128894:    0003        ..      MOVS     r3,r0
        0x00128896:    2002        .       MOVS     r0,#2
        0x00128898:    2b00        .+      CMP      r3,#0
        0x0012889a:    d024        $.      BEQ      0x1288e6 ; app_qspi_std_write + 114
        0x0012889c:    4e13        .N      LDR      r6,[pc,#76] ; [0x1288ec] = 0x1293a0
        0x0012889e:    2100        .!      MOVS     r1,#0
        0x001288a0:    0020         .      MOVS     r0,r4
        0x001288a2:    68f3        .h      LDR      r3,[r6,#0xc]
        0x001288a4:    4798        .G      BLX      r3
        0x001288a6:    2102        .!      MOVS     r1,#2
        0x001288a8:    0020         .      MOVS     r0,r4
        0x001288aa:    6973        si      LDR      r3,[r6,#0x14]
        0x001288ac:    4798        .G      BLX      r3
        0x001288ae:    4b10        .K      LDR      r3,[pc,#64] ; [0x1288f0] = 0x70100
        0x001288b0:    3f04        .?      SUBS     r7,#4
        0x001288b2:    602b        +`      STR      r3,[r5,#0]
        0x001288b4:    2300        .#      MOVS     r3,#0
        0x001288b6:    652f        /e      STR      r7,[r5,#0x50]
        0x001288b8:    2701        .'      MOVS     r7,#1
        0x001288ba:    64eb        .d      STR      r3,[r5,#0x4c]
        0x001288bc:    3302        .3      ADDS     r3,#2
        0x001288be:    9a02        ..      LDR      r2,[sp,#8]
        0x001288c0:    64eb        .d      STR      r3,[r5,#0x4c]
        0x001288c2:    9901        ..      LDR      r1,[sp,#4]
        0x001288c4:    9b03        ..      LDR      r3,[sp,#0xc]
        0x001288c6:    0028        (.      MOVS     r0,r5
        0x001288c8:    60af        .`      STR      r7,[r5,#8]
        0x001288ca:    f7ffff67    ..g.    BL       qspi_std_byte_write_dma_start ; 0x12879c
        0x001288ce:    2103        .!      MOVS     r1,#3
        0x001288d0:    0020         .      MOVS     r0,r4
        0x001288d2:    6973        si      LDR      r3,[r6,#0x14]
        0x001288d4:    4798        .G      BLX      r3
        0x001288d6:    68f3        .h      LDR      r3,[r6,#0xc]
        0x001288d8:    0039        9.      MOVS     r1,r7
        0x001288da:    0020         .      MOVS     r0,r4
        0x001288dc:    4798        .G      BLX      r3
        0x001288de:    9800        ..      LDR      r0,[sp,#0]
        0x001288e0:    f000fc01    ....    BL       periph_unlock ; 0x1290e6
        0x001288e4:    2000        .       MOVS     r0,#0
        0x001288e6:    b005        ..      ADD      sp,sp,#0x14
        0x001288e8:    bdf0        ..      POP      {r4-r7,pc}
        0x001288ea:    46c0        .F      MOV      r8,r8
    $d
        0x001288ec:    001293a0    ....    DCD    1217440
        0x001288f0:    00070100    ....    DCD    459008
    $t
    app_qspi_std_write_no_dma
        0x001288f4:    b5f0        ..      PUSH     {r4-r7,lr}
        0x001288f6:    0006        ..      MOVS     r6,r0
        0x001288f8:    b085        ..      SUB      sp,sp,#0x14
        0x001288fa:    000c        ..      MOVS     r4,r1
        0x001288fc:    9202        ..      STR      r2,[sp,#8]
        0x001288fe:    9303        ..      STR      r3,[sp,#0xc]
        0x00128900:    f7fffdba    ....    BL       qspi_get_fifo_depth ; 0x128478
        0x00128904:    0033        3.      MOVS     r3,r6
        0x00128906:    3314        .3      ADDS     r3,r3,#0x14
        0x00128908:    0018        ..      MOVS     r0,r3
        0x0012890a:    9301        ..      STR      r3,[sp,#4]
        0x0012890c:    6935        5i      LDR      r5,[r6,#0x10]
        0x0012890e:    f000fbdc    ....    BL       periph_lock ; 0x1290ca
        0x00128912:    0003        ..      MOVS     r3,r0
        0x00128914:    2002        .       MOVS     r0,#2
        0x00128916:    2b00        .+      CMP      r3,#0
        0x00128918:    d028        (.      BEQ      0x12896c ; app_qspi_std_write_no_dma + 120
        0x0012891a:    4f18        .O      LDR      r7,[pc,#96] ; [0x12897c] = 0x1293a0
        0x0012891c:    2100        .!      MOVS     r1,#0
        0x0012891e:    0030        0.      MOVS     r0,r6
        0x00128920:    68fb        .h      LDR      r3,[r7,#0xc]
        0x00128922:    4798        .G      BLX      r3
        0x00128924:    697b        {i      LDR      r3,[r7,#0x14]
        0x00128926:    2102        .!      MOVS     r1,#2
        0x00128928:    0030        0.      MOVS     r0,r6
        0x0012892a:    4798        .G      BLX      r3
        0x0012892c:    4b14        .K      LDR      r3,[pc,#80] ; [0x128980] = 0x70100
        0x0012892e:    602b        +`      STR      r3,[r5,#0]
        0x00128930:    2301        .#      MOVS     r3,#1
        0x00128932:    60ab        .`      STR      r3,[r5,#8]
        0x00128934:    2300        .#      MOVS     r3,#0
        0x00128936:    9903        ..      LDR      r1,[sp,#0xc]
        0x00128938:    b29a        ..      UXTH     r2,r3
        0x0012893a:    4291        .B      CMP      r1,r2
        0x0012893c:    d818        ..      BHI      0x128970 ; app_qspi_std_write_no_dma + 124
        0x0012893e:    2304        .#      MOVS     r3,#4
        0x00128940:    612c        ,a      STR      r4,[r5,#0x10]
        0x00128942:    6aaa        .j      LDR      r2,[r5,#0x28]
        0x00128944:    421a        .B      TST      r2,r3
        0x00128946:    d0fc        ..      BEQ      0x128942 ; app_qspi_std_write_no_dma + 78
        0x00128948:    2301        .#      MOVS     r3,#1
        0x0012894a:    6aac        .j      LDR      r4,[r5,#0x28]
        0x0012894c:    401c        .@      ANDS     r4,r4,r3
        0x0012894e:    d1fc        ..      BNE      0x12894a ; app_qspi_std_write_no_dma + 86
        0x00128950:    60ac        .`      STR      r4,[r5,#8]
        0x00128952:    2103        .!      MOVS     r1,#3
        0x00128954:    0030        0.      MOVS     r0,r6
        0x00128956:    697b        {i      LDR      r3,[r7,#0x14]
        0x00128958:    612c        ,a      STR      r4,[r5,#0x10]
        0x0012895a:    4798        .G      BLX      r3
        0x0012895c:    68fb        .h      LDR      r3,[r7,#0xc]
        0x0012895e:    2101        .!      MOVS     r1,#1
        0x00128960:    0030        0.      MOVS     r0,r6
        0x00128962:    4798        .G      BLX      r3
        0x00128964:    9801        ..      LDR      r0,[sp,#4]
        0x00128966:    f000fbbe    ....    BL       periph_unlock ; 0x1290e6
        0x0012896a:    0020         .      MOVS     r0,r4
        0x0012896c:    b005        ..      ADD      sp,sp,#0x14
        0x0012896e:    bdf0        ..      POP      {r4-r7,pc}
        0x00128970:    9a02        ..      LDR      r2,[sp,#8]
        0x00128972:    5cd2        .\      LDRB     r2,[r2,r3]
        0x00128974:    3301        .3      ADDS     r3,#1
        0x00128976:    662a        *f      STR      r2,[r5,#0x60]
        0x00128978:    e7dd        ..      B        0x128936 ; app_qspi_std_write_no_dma + 66
        0x0012897a:    46c0        .F      MOV      r8,r8
    $d
        0x0012897c:    001293a0    ....    DCD    1217440
        0x00128980:    00070100    ....    DCD    459008
    $t
    app_qspi_flash_program
        0x00128984:    b5f0        ..      PUSH     {r4-r7,lr}
        0x00128986:    0005        ..      MOVS     r5,r0
        0x00128988:    b085        ..      SUB      sp,sp,#0x14
        0x0012898a:    9102        ..      STR      r1,[sp,#8]
        0x0012898c:    9203        ..      STR      r2,[sp,#0xc]
        0x0012898e:    9300        ..      STR      r3,[sp,#0]
        0x00128990:    f7fffd72    ..r.    BL       qspi_get_fifo_depth ; 0x128478
        0x00128994:    002b        +.      MOVS     r3,r5
        0x00128996:    3314        .3      ADDS     r3,r3,#0x14
        0x00128998:    0007        ..      MOVS     r7,r0
        0x0012899a:    0018        ..      MOVS     r0,r3
        0x0012899c:    9301        ..      STR      r3,[sp,#4]
        0x0012899e:    f000fb94    ....    BL       periph_lock ; 0x1290ca
        0x001289a2:    0003        ..      MOVS     r3,r0
        0x001289a4:    2002        .       MOVS     r0,#2
        0x001289a6:    2b00        .+      CMP      r3,#0
        0x001289a8:    d033        3.      BEQ      0x128a12 ; app_qspi_flash_program + 142
        0x001289aa:    4e1b        .N      LDR      r6,[pc,#108] ; [0x128a18] = 0x1293a0
        0x001289ac:    2100        .!      MOVS     r1,#0
        0x001289ae:    0028        (.      MOVS     r0,r5
        0x001289b0:    68f3        .h      LDR      r3,[r6,#0xc]
        0x001289b2:    692c        ,i      LDR      r4,[r5,#0x10]
        0x001289b4:    4798        .G      BLX      r3
        0x001289b6:    2102        .!      MOVS     r1,#2
        0x001289b8:    0028        (.      MOVS     r0,r5
        0x001289ba:    6973        si      LDR      r3,[r6,#0x14]
        0x001289bc:    4798        .G      BLX      r3
        0x001289be:    4b17        .K      LDR      r3,[pc,#92] ; [0x128a1c] = 0x70100
        0x001289c0:    3f04        .?      SUBS     r7,#4
        0x001289c2:    6023        #`      STR      r3,[r4,#0]
        0x001289c4:    2300        .#      MOVS     r3,#0
        0x001289c6:    6527        'e      STR      r7,[r4,#0x50]
        0x001289c8:    2701        .'      MOVS     r7,#1
        0x001289ca:    64e3        .d      STR      r3,[r4,#0x4c]
        0x001289cc:    3302        .3      ADDS     r3,#2
        0x001289ce:    64e3        .d      STR      r3,[r4,#0x4c]
        0x001289d0:    9b03        ..      LDR      r3,[sp,#0xc]
        0x001289d2:    60a7        .`      STR      r7,[r4,#8]
        0x001289d4:    6623        #f      STR      r3,[r4,#0x60]
        0x001289d6:    9b00        ..      LDR      r3,[sp,#0]
        0x001289d8:    9902        ..      LDR      r1,[sp,#8]
        0x001289da:    0c1a        ..      LSRS     r2,r3,#16
        0x001289dc:    23ff        .#      MOVS     r3,#0xff
        0x001289de:    401a        .@      ANDS     r2,r2,r3
        0x001289e0:    6622        "f      STR      r2,[r4,#0x60]
        0x001289e2:    9a00        ..      LDR      r2,[sp,#0]
        0x001289e4:    0020         .      MOVS     r0,r4
        0x001289e6:    0a12        ..      LSRS     r2,r2,#8
        0x001289e8:    401a        .@      ANDS     r2,r2,r3
        0x001289ea:    6622        "f      STR      r2,[r4,#0x60]
        0x001289ec:    9a00        ..      LDR      r2,[sp,#0]
        0x001289ee:    4013        .@      ANDS     r3,r3,r2
        0x001289f0:    6623        #f      STR      r3,[r4,#0x60]
        0x001289f2:    9a0a        ..      LDR      r2,[sp,#0x28]
        0x001289f4:    9b0b        ..      LDR      r3,[sp,#0x2c]
        0x001289f6:    f7fffed1    ....    BL       qspi_std_byte_write_dma_start ; 0x12879c
        0x001289fa:    2103        .!      MOVS     r1,#3
        0x001289fc:    0028        (.      MOVS     r0,r5
        0x001289fe:    6973        si      LDR      r3,[r6,#0x14]
        0x00128a00:    4798        .G      BLX      r3
        0x00128a02:    68f3        .h      LDR      r3,[r6,#0xc]
        0x00128a04:    0039        9.      MOVS     r1,r7
        0x00128a06:    0028        (.      MOVS     r0,r5
        0x00128a08:    4798        .G      BLX      r3
        0x00128a0a:    9801        ..      LDR      r0,[sp,#4]
        0x00128a0c:    f000fb6b    ..k.    BL       periph_unlock ; 0x1290e6
        0x00128a10:    2000        .       MOVS     r0,#0
        0x00128a12:    b005        ..      ADD      sp,sp,#0x14
        0x00128a14:    bdf0        ..      POP      {r4-r7,pc}
        0x00128a16:    46c0        .F      MOV      r8,r8
    $d
        0x00128a18:    001293a0    ....    DCD    1217440
        0x00128a1c:    00070100    ....    DCD    459008
    $t
    app_qspi_std_read
        0x00128a20:    b5f0        ..      PUSH     {r4-r7,lr}
        0x00128a22:    b08f        ..      SUB      sp,sp,#0x3c
        0x00128a24:    9304        ..      STR      r3,[sp,#0x10]
        0x00128a26:    ab14        ..      ADD      r3,sp,#0x50
        0x00128a28:    0015        ..      MOVS     r5,r2
        0x00128a2a:    cb04        ..      LDM      r3!,{r2}
        0x00128a2c:    0007        ..      MOVS     r7,r0
        0x00128a2e:    881b        ..      LDRH     r3,[r3,#0]
        0x00128a30:    9103        ..      STR      r1,[sp,#0xc]
        0x00128a32:    9302        ..      STR      r3,[sp,#8]
        0x00128a34:    0003        ..      MOVS     r3,r0
        0x00128a36:    3314        .3      ADDS     r3,r3,#0x14
        0x00128a38:    0018        ..      MOVS     r0,r3
        0x00128a3a:    9301        ..      STR      r3,[sp,#4]
        0x00128a3c:    9205        ..      STR      r2,[sp,#0x14]
        0x00128a3e:    f000fb44    ..D.    BL       periph_lock ; 0x1290ca
        0x00128a42:    0003        ..      MOVS     r3,r0
        0x00128a44:    2002        .       MOVS     r0,#2
        0x00128a46:    2b00        .+      CMP      r3,#0
        0x00128a48:    d03d        =.      BEQ      0x128ac6 ; app_qspi_std_read + 166
        0x00128a4a:    4e22        "N      LDR      r6,[pc,#136] ; [0x128ad4] = 0x1293a0
        0x00128a4c:    2100        .!      MOVS     r1,#0
        0x00128a4e:    0038        8.      MOVS     r0,r7
        0x00128a50:    68f3        .h      LDR      r3,[r6,#0xc]
        0x00128a52:    693c        <i      LDR      r4,[r7,#0x10]
        0x00128a54:    4798        .G      BLX      r3
        0x00128a56:    6973        si      LDR      r3,[r6,#0x14]
        0x00128a58:    2102        .!      MOVS     r1,#2
        0x00128a5a:    0038        8.      MOVS     r0,r7
        0x00128a5c:    4798        .G      BLX      r3
        0x00128a5e:    4b1e        .K      LDR      r3,[pc,#120] ; [0x128ad8] = 0x70300
        0x00128a60:    6023        #`      STR      r3,[r4,#0]
        0x00128a62:    9b02        ..      LDR      r3,[sp,#8]
        0x00128a64:    3b01        .;      SUBS     r3,#1
        0x00128a66:    6063        c`      STR      r3,[r4,#4]
        0x00128a68:    2307        .#      MOVS     r3,#7
        0x00128a6a:    6563        ce      STR      r3,[r4,#0x54]
        0x00128a6c:    2300        .#      MOVS     r3,#0
        0x00128a6e:    64e3        .d      STR      r3,[r4,#0x4c]
        0x00128a70:    3301        .3      ADDS     r3,#1
        0x00128a72:    64e3        .d      STR      r3,[r4,#0x4c]
        0x00128a74:    60a3        .`      STR      r3,[r4,#8]
        0x00128a76:    9b04        ..      LDR      r3,[sp,#0x10]
        0x00128a78:    18eb        ..      ADDS     r3,r5,r3
        0x00128a7a:    429d        .B      CMP      r5,r3
        0x00128a7c:    d125        %.      BNE      0x128aca ; app_qspi_std_read + 170
        0x00128a7e:    0023        #.      MOVS     r3,r4
        0x00128a80:    2500        .%      MOVS     r5,#0
        0x00128a82:    a808        ..      ADD      r0,sp,#0x20
        0x00128a84:    3360        `3      ADDS     r3,r3,#0x60
        0x00128a86:    6083        .`      STR      r3,[r0,#8]
        0x00128a88:    9b05        ..      LDR      r3,[sp,#0x14]
        0x00128a8a:    7585        .u      STRB     r5,[r0,#0x16]
        0x00128a8c:    60c3        .`      STR      r3,[r0,#0xc]
        0x00128a8e:    9b02        ..      LDR      r3,[sp,#8]
        0x00128a90:    6103        .a      STR      r3,[r0,#0x10]
        0x00128a92:    4b12        .K      LDR      r3,[pc,#72] ; [0x128adc] = 0xffffa480
        0x00128a94:    8283        ..      STRH     r3,[r0,#0x14]
        0x00128a96:    ab06        ..      ADD      r3,sp,#0x18
        0x00128a98:    1dd9        ..      ADDS     r1,r3,#7
        0x00128a9a:    f000fafd    ....    BL       app_dmac_start_wrapper ; 0x129098
        0x00128a9e:    9b03        ..      LDR      r3,[sp,#0xc]
        0x00128aa0:    6123        #a      STR      r3,[r4,#0x10]
        0x00128aa2:    ab06        ..      ADD      r3,sp,#0x18
        0x00128aa4:    79d8        .y      LDRB     r0,[r3,#7]
        0x00128aa6:    f000fb01    ....    BL       app_dmac_transfer_wait_wrapper ; 0x1290ac
        0x00128aaa:    60a5        .`      STR      r5,[r4,#8]
        0x00128aac:    2103        .!      MOVS     r1,#3
        0x00128aae:    0038        8.      MOVS     r0,r7
        0x00128ab0:    6973        si      LDR      r3,[r6,#0x14]
        0x00128ab2:    6125        %a      STR      r5,[r4,#0x10]
        0x00128ab4:    4798        .G      BLX      r3
        0x00128ab6:    68f3        .h      LDR      r3,[r6,#0xc]
        0x00128ab8:    2101        .!      MOVS     r1,#1
        0x00128aba:    0038        8.      MOVS     r0,r7
        0x00128abc:    4798        .G      BLX      r3
        0x00128abe:    9801        ..      LDR      r0,[sp,#4]
        0x00128ac0:    f000fb11    ....    BL       periph_unlock ; 0x1290e6
        0x00128ac4:    0028        (.      MOVS     r0,r5
        0x00128ac6:    b00f        ..      ADD      sp,sp,#0x3c
        0x00128ac8:    bdf0        ..      POP      {r4-r7,pc}
        0x00128aca:    782a        *x      LDRB     r2,[r5,#0]
        0x00128acc:    3501        .5      ADDS     r5,#1
        0x00128ace:    6622        "f      STR      r2,[r4,#0x60]
        0x00128ad0:    e7d3        ..      B        0x128a7a ; app_qspi_std_read + 90
        0x00128ad2:    46c0        .F      MOV      r8,r8
    $d
        0x00128ad4:    001293a0    ....    DCD    1217440
        0x00128ad8:    00070300    ....    DCD    459520
        0x00128adc:    ffffa480    ....    DCD    4294943872
    $t
    app_qspi_multi_read_32bits
        0x00128ae0:    b5f0        ..      PUSH     {r4-r7,lr}
        0x00128ae2:    001f        ..      MOVS     r7,r3
        0x00128ae4:    0003        ..      MOVS     r3,r0
        0x00128ae6:    3314        .3      ADDS     r3,r3,#0x14
        0x00128ae8:    b08d        ..      SUB      sp,sp,#0x34
        0x00128aea:    0005        ..      MOVS     r5,r0
        0x00128aec:    0018        ..      MOVS     r0,r3
        0x00128aee:    9102        ..      STR      r1,[sp,#8]
        0x00128af0:    9203        ..      STR      r2,[sp,#0xc]
        0x00128af2:    9301        ..      STR      r3,[sp,#4]
        0x00128af4:    f000fae9    ....    BL       periph_lock ; 0x1290ca
        0x00128af8:    2602        .&      MOVS     r6,#2
        0x00128afa:    2800        .(      CMP      r0,#0
        0x00128afc:    d059        Y.      BEQ      0x128bb2 ; app_qspi_multi_read_32bits + 210
        0x00128afe:    4c3e        >L      LDR      r4,[pc,#248] ; [0x128bf8] = 0x1293a0
        0x00128b00:    0031        1.      MOVS     r1,r6
        0x00128b02:    6963        ci      LDR      r3,[r4,#0x14]
        0x00128b04:    0028        (.      MOVS     r0,r5
        0x00128b06:    4798        .G      BLX      r3
        0x00128b08:    68e3        .h      LDR      r3,[r4,#0xc]
        0x00128b0a:    2100        .!      MOVS     r1,#0
        0x00128b0c:    0028        (.      MOVS     r0,r5
        0x00128b0e:    4798        .G      BLX      r3
        0x00128b10:    7a29        )z      LDRB     r1,[r5,#8]
        0x00128b12:    692c        ,i      LDR      r4,[r5,#0x10]
        0x00128b14:    068b        ..      LSLS     r3,r1,#26
        0x00128b16:    078a        ..      LSLS     r2,r1,#30
        0x00128b18:    d14e        N.      BNE      0x128bb8 ; app_qspi_multi_read_32bits + 216
        0x00128b1a:    0f1b        ..      LSRS     r3,r3,#28
        0x00128b1c:    3b08        .;      SUBS     r3,r3,#8
        0x00128b1e:    b2db        ..      UXTB     r3,r3
        0x00128b20:    22f0        ."      MOVS     r2,#0xf0
        0x00128b22:    02db        ..      LSLS     r3,r3,#11
        0x00128b24:    01d2        ..      LSLS     r2,r2,#7
        0x00128b26:    4013        .@      ANDS     r3,r3,r2
        0x00128b28:    2288        ."      MOVS     r2,#0x88
        0x00128b2a:    0789        ..      LSLS     r1,r1,#30
        0x00128b2c:    0092        ..      LSLS     r2,r2,#2
        0x00128b2e:    0f89        ..      LSRS     r1,r1,#30
        0x00128b30:    4311        .C      ORRS     r1,r1,r2
        0x00128b32:    0022        ".      MOVS     r2,r4
        0x00128b34:    430b        .C      ORRS     r3,r3,r1
        0x00128b36:    32f4        .2      ADDS     r2,r2,#0xf4
        0x00128b38:    6013        .`      STR      r3,[r2,#0]
        0x00128b3a:    7a2b        +z      LDRB     r3,[r5,#8]
        0x00128b3c:    4a2f        /J      LDR      r2,[pc,#188] ; [0x128bfc] = 0x1f0200
        0x00128b3e:    099b        ..      LSRS     r3,r3,#6
        0x00128b40:    055b        [.      LSLS     r3,r3,#21
        0x00128b42:    4313        .C      ORRS     r3,r3,r2
        0x00128b44:    6023        #`      STR      r3,[r4,#0]
        0x00128b46:    1e7b        {.      SUBS     r3,r7,#1
        0x00128b48:    6063        c`      STR      r3,[r4,#4]
        0x00128b4a:    2600        .&      MOVS     r6,#0
        0x00128b4c:    2301        .#      MOVS     r3,#1
        0x00128b4e:    64e6        .d      STR      r6,[r4,#0x4c]
        0x00128b50:    60a3        .`      STR      r3,[r4,#8]
        0x00128b52:    79eb        .y      LDRB     r3,[r5,#7]
        0x00128b54:    0028        (.      MOVS     r0,r5
        0x00128b56:    6623        #f      STR      r3,[r4,#0x60]
        0x00128b58:    9b12        ..      LDR      r3,[sp,#0x48]
        0x00128b5a:    6623        #f      STR      r3,[r4,#0x60]
        0x00128b5c:    f7fffc8c    ....    BL       qspi_get_fifo_depth ; 0x128478
        0x00128b60:    4287        .B      CMP      r7,r0
        0x00128b62:    d934        4.      BLS      0x128bce ; app_qspi_multi_read_32bits + 238
        0x00128b64:    2307        .#      MOVS     r3,#7
        0x00128b66:    6563        ce      STR      r3,[r4,#0x54]
        0x00128b68:    3b06        .;      SUBS     r3,#6
        0x00128b6a:    64e3        .d      STR      r3,[r4,#0x4c]
        0x00128b6c:    0023        #.      MOVS     r3,r4
        0x00128b6e:    a806        ..      ADD      r0,sp,#0x18
        0x00128b70:    33ec        .3      ADDS     r3,r3,#0xec
        0x00128b72:    6083        .`      STR      r3,[r0,#8]
        0x00128b74:    9b03        ..      LDR      r3,[sp,#0xc]
        0x00128b76:    7586        .u      STRB     r6,[r0,#0x16]
        0x00128b78:    60c3        .`      STR      r3,[r0,#0xc]
        0x00128b7a:    4b21        !K      LDR      r3,[pc,#132] ; [0x128c00] = 0xffffa492
        0x00128b7c:    6107        .a      STR      r7,[r0,#0x10]
        0x00128b7e:    8283        ..      STRH     r3,[r0,#0x14]
        0x00128b80:    ab04        ..      ADD      r3,sp,#0x10
        0x00128b82:    1dde        ..      ADDS     r6,r3,#7
        0x00128b84:    0031        1.      MOVS     r1,r6
        0x00128b86:    f000fa87    ....    BL       app_dmac_start_wrapper ; 0x129098
        0x00128b8a:    9b02        ..      LDR      r3,[sp,#8]
        0x00128b8c:    7830        0x      LDRB     r0,[r6,#0]
        0x00128b8e:    6123        #a      STR      r3,[r4,#0x10]
        0x00128b90:    f000fa8c    ....    BL       app_dmac_transfer_wait_wrapper ; 0x1290ac
        0x00128b94:    2600        .&      MOVS     r6,#0
        0x00128b96:    60a6        .`      STR      r6,[r4,#8]
        0x00128b98:    6126        &a      STR      r6,[r4,#0x10]
        0x00128b9a:    4c17        .L      LDR      r4,[pc,#92] ; [0x128bf8] = 0x1293a0
        0x00128b9c:    2101        .!      MOVS     r1,#1
        0x00128b9e:    0028        (.      MOVS     r0,r5
        0x00128ba0:    68e3        .h      LDR      r3,[r4,#0xc]
        0x00128ba2:    4798        .G      BLX      r3
        0x00128ba4:    0028        (.      MOVS     r0,r5
        0x00128ba6:    6963        ci      LDR      r3,[r4,#0x14]
        0x00128ba8:    2103        .!      MOVS     r1,#3
        0x00128baa:    4798        .G      BLX      r3
        0x00128bac:    9801        ..      LDR      r0,[sp,#4]
        0x00128bae:    f000fa9a    ....    BL       periph_unlock ; 0x1290e6
        0x00128bb2:    0030        0.      MOVS     r0,r6
        0x00128bb4:    b00d        ..      ADD      sp,sp,#0x34
        0x00128bb6:    bdf0        ..      POP      {r4-r7,pc}
        0x00128bb8:    0f18        ..      LSRS     r0,r3,#28
        0x00128bba:    000e        ..      MOVS     r6,r1
        0x00128bbc:    233f        ?#      MOVS     r3,#0x3f
        0x00128bbe:    439e        .C      BICS     r6,r6,r3
        0x00128bc0:    1f03        ..      SUBS     r3,r0,#4
        0x00128bc2:    b2db        ..      UXTB     r3,r3
        0x00128bc4:    2e80        ..      CMP      r6,#0x80
        0x00128bc6:    d1ab        ..      BNE      0x128b20 ; app_qspi_multi_read_32bits + 64
        0x00128bc8:    3802        .8      SUBS     r0,#2
        0x00128bca:    b2c3        ..      UXTB     r3,r0
        0x00128bcc:    e7a8        ..      B        0x128b20 ; app_qspi_multi_read_32bits + 64
        0x00128bce:    9b02        ..      LDR      r3,[sp,#8]
        0x00128bd0:    6123        #a      STR      r3,[r4,#0x10]
        0x00128bd2:    2304        .#      MOVS     r3,#4
        0x00128bd4:    6aa2        .j      LDR      r2,[r4,#0x28]
        0x00128bd6:    421a        .B      TST      r2,r3
        0x00128bd8:    d0fc        ..      BEQ      0x128bd4 ; app_qspi_multi_read_32bits + 244
        0x00128bda:    2201        ."      MOVS     r2,#1
        0x00128bdc:    6aa3        .j      LDR      r3,[r4,#0x28]
        0x00128bde:    4013        .@      ANDS     r3,r3,r2
        0x00128be0:    d1fc        ..      BNE      0x128bdc ; app_qspi_multi_read_32bits + 252
        0x00128be2:    0022        ".      MOVS     r2,r4
        0x00128be4:    32ec        .2      ADDS     r2,r2,#0xec
        0x00128be6:    42bb        .B      CMP      r3,r7
        0x00128be8:    d2d4        ..      BCS      0x128b94 ; app_qspi_multi_read_32bits + 180
        0x00128bea:    6810        .h      LDR      r0,[r2,#0]
        0x00128bec:    9e03        ..      LDR      r6,[sp,#0xc]
        0x00128bee:    0099        ..      LSLS     r1,r3,#2
        0x00128bf0:    3301        .3      ADDS     r3,#1
        0x00128bf2:    5188        .Q      STR      r0,[r1,r6]
        0x00128bf4:    b2db        ..      UXTB     r3,r3
        0x00128bf6:    e7f6        ..      B        0x128be6 ; app_qspi_multi_read_32bits + 262
    $d
        0x00128bf8:    001293a0    ....    DCD    1217440
        0x00128bfc:    001f0200    ....    DCD    2032128
        0x00128c00:    ffffa492    ....    DCD    4294943890
    $t
    app_qspi_config_for_cache
        0x00128c04:    b570        p.      PUSH     {r4-r6,lr}
        0x00128c06:    0005        ..      MOVS     r5,r0
        0x00128c08:    3014        .0      ADDS     r0,r0,#0x14
        0x00128c0a:    000e        ..      MOVS     r6,r1
        0x00128c0c:    0014        ..      MOVS     r4,r2
        0x00128c0e:    f000fa5c    ..\.    BL       periph_lock ; 0x1290ca
        0x00128c12:    2302        .#      MOVS     r3,#2
        0x00128c14:    2800        .(      CMP      r0,#0
        0x00128c16:    d01f        ..      BEQ      0x128c58 ; app_qspi_config_for_cache + 84
        0x00128c18:    4b10        .K      LDR      r3,[pc,#64] ; [0x128c5c] = 0x1293a0
        0x00128c1a:    2100        .!      MOVS     r1,#0
        0x00128c1c:    68db        .h      LDR      r3,[r3,#0xc]
        0x00128c1e:    0028        (.      MOVS     r0,r5
        0x00128c20:    4798        .G      BLX      r3
        0x00128c22:    2086        .       MOVS     r0,#0x86
        0x00128c24:    7a2b        +z      LDRB     r3,[r5,#8]
        0x00128c26:    692a        *i      LDR      r2,[r5,#0x10]
        0x00128c28:    0699        ..      LSLS     r1,r3,#26
        0x00128c2a:    079b        ..      LSLS     r3,r3,#30
        0x00128c2c:    0f09        ..      LSRS     r1,r1,#28
        0x00128c2e:    0f9b        ..      LSRS     r3,r3,#30
        0x00128c30:    0080        ..      LSLS     r0,r0,#2
        0x00128c32:    02c9        ..      LSLS     r1,r1,#11
        0x00128c34:    4303        .C      ORRS     r3,r3,r0
        0x00128c36:    430b        .C      ORRS     r3,r3,r1
        0x00128c38:    0011        ..      MOVS     r1,r2
        0x00128c3a:    31f4        .1      ADDS     r1,r1,#0xf4
        0x00128c3c:    600b        .`      STR      r3,[r1,#0]
        0x00128c3e:    7a2b        +z      LDRB     r3,[r5,#8]
        0x00128c40:    4907        .I      LDR      r1,[pc,#28] ; [0x128c60] = 0x1f0200
        0x00128c42:    099b        ..      LSRS     r3,r3,#6
        0x00128c44:    055b        [.      LSLS     r3,r3,#21
        0x00128c46:    430b        .C      ORRS     r3,r3,r1
        0x00128c48:    6013        .`      STR      r3,[r2,#0]
        0x00128c4a:    2301        .#      MOVS     r3,#1
        0x00128c4c:    08a4        ..      LSRS     r4,r4,#2
        0x00128c4e:    3c01        .<      SUBS     r4,#1
        0x00128c50:    6054        T`      STR      r4,[r2,#4]
        0x00128c52:    6116        .a      STR      r6,[r2,#0x10]
        0x00128c54:    6093        .`      STR      r3,[r2,#8]
        0x00128c56:    2300        .#      MOVS     r3,#0
        0x00128c58:    0018        ..      MOVS     r0,r3
        0x00128c5a:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x00128c5c:    001293a0    ....    DCD    1217440
        0x00128c60:    001f0200    ....    DCD    2032128
    $t
    app_qspi_dr_reg_addr_for_cache
        0x00128c64:    6900        .i      LDR      r0,[r0,#0x10]
        0x00128c66:    3060        `0      ADDS     r0,r0,#0x60
        0x00128c68:    4770        pG      BX       lr
    $t
    app_qspi_multi_read_cmd_get
        0x00128c6a:    79c0        .y      LDRB     r0,[r0,#7]
        0x00128c6c:    4770        pG      BX       lr
        0x00128c6e:    0000        ..      MOVS     r0,r0
    $t
    app_qspi_disable_for_cache
        0x00128c70:    b570        p.      PUSH     {r4-r6,lr}
        0x00128c72:    0006        ..      MOVS     r6,r0
        0x00128c74:    3614        .6      ADDS     r6,r6,#0x14
        0x00128c76:    0005        ..      MOVS     r5,r0
        0x00128c78:    0030        0.      MOVS     r0,r6
        0x00128c7a:    f000fa41    ..A.    BL       periph_lock_state_get ; 0x129100
        0x00128c7e:    2403        .$      MOVS     r4,#3
        0x00128c80:    2800        .(      CMP      r0,#0
        0x00128c82:    d00e        ..      BEQ      0x128ca2 ; app_qspi_disable_for_cache + 50
        0x00128c84:    2201        ."      MOVS     r2,#1
        0x00128c86:    692b        +i      LDR      r3,[r5,#0x10]
        0x00128c88:    6a9c        .j      LDR      r4,[r3,#0x28]
        0x00128c8a:    4014        .@      ANDS     r4,r4,r2
        0x00128c8c:    d1fc        ..      BNE      0x128c88 ; app_qspi_disable_for_cache + 24
        0x00128c8e:    609c        .`      STR      r4,[r3,#8]
        0x00128c90:    611c        .a      STR      r4,[r3,#0x10]
        0x00128c92:    4b05        .K      LDR      r3,[pc,#20] ; [0x128ca8] = 0x1293a0
        0x00128c94:    0028        (.      MOVS     r0,r5
        0x00128c96:    68db        .h      LDR      r3,[r3,#0xc]
        0x00128c98:    2101        .!      MOVS     r1,#1
        0x00128c9a:    4798        .G      BLX      r3
        0x00128c9c:    0030        0.      MOVS     r0,r6
        0x00128c9e:    f000fa22    ..".    BL       periph_unlock ; 0x1290e6
        0x00128ca2:    0020         .      MOVS     r0,r4
        0x00128ca4:    bd70        p.      POP      {r4-r6,pc}
        0x00128ca6:    46c0        .F      MOV      r8,r8
    $d
        0x00128ca8:    001293a0    ....    DCD    1217440
    $t
    app_qspi_param_init_wrapper
        0x00128cac:    2202        ."      MOVS     r2,#2
        0x00128cae:    2301        .#      MOVS     r3,#1
        0x00128cb0:    b510        ..      PUSH     {r4,lr}
        0x00128cb2:    4c0a        .L      LDR      r4,[pc,#40] ; [0x128cdc] = 0x1293d8
        0x00128cb4:    0001        ..      MOVS     r1,r0
        0x00128cb6:    1de0        ..      ADDS     r0,r4,#7
        0x00128cb8:    71a3        .q      STRB     r3,[r4,#6]
        0x00128cba:    80a2        ..      STRH     r2,[r4,#4]
        0x00128cbc:    f6d8ff0c    ....    BL       0x1ad8 ; 0x1ad8
        0x00128cc0:    2319        .#      MOVS     r3,#0x19
        0x00128cc2:    7263        cr      STRB     r3,[r4,#9]
        0x00128cc4:    3301        .3      ADDS     r3,#1
        0x00128cc6:    72a3        .r      STRB     r3,[r4,#0xa]
        0x00128cc8:    3301        .3      ADDS     r3,#1
        0x00128cca:    72e3        .r      STRB     r3,[r4,#0xb]
        0x00128ccc:    3301        .3      ADDS     r3,#1
        0x00128cce:    7323        #s      STRB     r3,[r4,#0xc]
        0x00128cd0:    3301        .3      ADDS     r3,#1
        0x00128cd2:    7363        cs      STRB     r3,[r4,#0xd]
        0x00128cd4:    3b05        .;      SUBS     r3,#5
        0x00128cd6:    73a3        .s      STRB     r3,[r4,#0xe]
        0x00128cd8:    bd10        ..      POP      {r4,pc}
        0x00128cda:    46c0        .F      MOV      r8,r8
    $d
        0x00128cdc:    001293d8    ....    DCD    1217496
    $t
    app_qspi_init_wrapper
        0x00128ce0:    b510        ..      PUSH     {r4,lr}
        0x00128ce2:    4802        .H      LDR      r0,[pc,#8] ; [0x128cec] = 0x1293d8
        0x00128ce4:    f7fffd80    ....    BL       app_qspi_init ; 0x1287e8
        0x00128ce8:    bd10        ..      POP      {r4,pc}
        0x00128cea:    46c0        .F      MOV      r8,r8
    $d
        0x00128cec:    001293d8    ....    DCD    1217496
    $t
    app_qspi_std_write_wrapper
        0x00128cf0:    b510        ..      PUSH     {r4,lr}
        0x00128cf2:    0002        ..      MOVS     r2,r0
        0x00128cf4:    000b        ..      MOVS     r3,r1
        0x00128cf6:    4802        .H      LDR      r0,[pc,#8] ; [0x128d00] = 0x1293d8
        0x00128cf8:    2101        .!      MOVS     r1,#1
        0x00128cfa:    f7fffdbb    ....    BL       app_qspi_std_write ; 0x128874
        0x00128cfe:    bd10        ..      POP      {r4,pc}
    $d
        0x00128d00:    001293d8    ....    DCD    1217496
    $t
    app_qspi_std_write_no_dma_wrapper
        0x00128d04:    b510        ..      PUSH     {r4,lr}
        0x00128d06:    0002        ..      MOVS     r2,r0
        0x00128d08:    000b        ..      MOVS     r3,r1
        0x00128d0a:    4802        .H      LDR      r0,[pc,#8] ; [0x128d14] = 0x1293d8
        0x00128d0c:    2101        .!      MOVS     r1,#1
        0x00128d0e:    f7fffdf1    ....    BL       app_qspi_std_write_no_dma ; 0x1288f4
        0x00128d12:    bd10        ..      POP      {r4,pc}
    $d
        0x00128d14:    001293d8    ....    DCD    1217496
    $t
    app_qspi_flash_program_wrapper
        0x00128d18:    b507        ..      PUSH     {r0-r2,lr}
        0x00128d1a:    9301        ..      STR      r3,[sp,#4]
        0x00128d1c:    9200        ..      STR      r2,[sp,#0]
        0x00128d1e:    000b        ..      MOVS     r3,r1
        0x00128d20:    0002        ..      MOVS     r2,r0
        0x00128d22:    2101        .!      MOVS     r1,#1
        0x00128d24:    4801        .H      LDR      r0,[pc,#4] ; [0x128d2c] = 0x1293d8
        0x00128d26:    f7fffe2d    ..-.    BL       app_qspi_flash_program ; 0x128984
        0x00128d2a:    bd0e        ..      POP      {r1-r3,pc}
    $d
        0x00128d2c:    001293d8    ....    DCD    1217496
    $t
    app_qspi_std_read_wrapper
        0x00128d30:    b507        ..      PUSH     {r0-r2,lr}
        0x00128d32:    9301        ..      STR      r3,[sp,#4]
        0x00128d34:    9200        ..      STR      r2,[sp,#0]
        0x00128d36:    000b        ..      MOVS     r3,r1
        0x00128d38:    0002        ..      MOVS     r2,r0
        0x00128d3a:    2101        .!      MOVS     r1,#1
        0x00128d3c:    4801        .H      LDR      r0,[pc,#4] ; [0x128d44] = 0x1293d8
        0x00128d3e:    f7fffe6f    ..o.    BL       app_qspi_std_read ; 0x128a20
        0x00128d42:    bd0e        ..      POP      {r1-r3,pc}
    $d
        0x00128d44:    001293d8    ....    DCD    1217496
    $t
    app_qspi_multi_read_32bits_wrapper
        0x00128d48:    b507        ..      PUSH     {r0-r2,lr}
        0x00128d4a:    000b        ..      MOVS     r3,r1
        0x00128d4c:    9200        ..      STR      r2,[sp,#0]
        0x00128d4e:    2101        .!      MOVS     r1,#1
        0x00128d50:    0002        ..      MOVS     r2,r0
        0x00128d52:    4802        .H      LDR      r0,[pc,#8] ; [0x128d5c] = 0x1293d8
        0x00128d54:    f7fffec4    ....    BL       app_qspi_multi_read_32bits ; 0x128ae0
        0x00128d58:    bd0e        ..      POP      {r1-r3,pc}
        0x00128d5a:    46c0        .F      MOV      r8,r8
    $d
        0x00128d5c:    001293d8    ....    DCD    1217496
    $t
    app_qspi_config_for_cache_wrapper
        0x00128d60:    b510        ..      PUSH     {r4,lr}
        0x00128d62:    0002        ..      MOVS     r2,r0
        0x00128d64:    2101        .!      MOVS     r1,#1
        0x00128d66:    4802        .H      LDR      r0,[pc,#8] ; [0x128d70] = 0x1293d8
        0x00128d68:    f7ffff4c    ..L.    BL       app_qspi_config_for_cache ; 0x128c04
        0x00128d6c:    bd10        ..      POP      {r4,pc}
        0x00128d6e:    46c0        .F      MOV      r8,r8
    $d
        0x00128d70:    001293d8    ....    DCD    1217496
    $t
    app_qspi_multi_read_cmd_get_wrapper
        0x00128d74:    b510        ..      PUSH     {r4,lr}
        0x00128d76:    4802        .H      LDR      r0,[pc,#8] ; [0x128d80] = 0x1293d8
        0x00128d78:    f7ffff77    ..w.    BL       app_qspi_multi_read_cmd_get ; 0x128c6a
        0x00128d7c:    bd10        ..      POP      {r4,pc}
        0x00128d7e:    46c0        .F      MOV      r8,r8
    $d
        0x00128d80:    001293d8    ....    DCD    1217496
    $t
    app_qspi_dr_reg_addr_for_cache_wrapper
        0x00128d84:    b510        ..      PUSH     {r4,lr}
        0x00128d86:    4802        .H      LDR      r0,[pc,#8] ; [0x128d90] = 0x1293d8
        0x00128d88:    f7ffff6c    ..l.    BL       app_qspi_dr_reg_addr_for_cache ; 0x128c64
        0x00128d8c:    bd10        ..      POP      {r4,pc}
        0x00128d8e:    46c0        .F      MOV      r8,r8
    $d
        0x00128d90:    001293d8    ....    DCD    1217496
    $t
    app_qspi_disable_for_cache_wrapper
        0x00128d94:    b510        ..      PUSH     {r4,lr}
        0x00128d96:    4802        .H      LDR      r0,[pc,#8] ; [0x128da0] = 0x1293d8
        0x00128d98:    f7ffff6a    ..j.    BL       app_qspi_disable_for_cache ; 0x128c70
        0x00128d9c:    bd10        ..      POP      {r4,pc}
        0x00128d9e:    46c0        .F      MOV      r8,r8
    $d
        0x00128da0:    001293d8    ....    DCD    1217496
    $t
    dmac_block_ts_config
        0x00128da4:    230c        .#      MOVS     r3,#0xc
        0x00128da6:    434b        KC      MULS     r3,r1,r3
        0x00128da8:    6842        Bh      LDR      r2,[r0,#4]
        0x00128daa:    b530        0.      PUSH     {r4,r5,lr}
        0x00128dac:    589d        .X      LDR      r5,[r3,r2]
        0x00128dae:    2358        X#      MOVS     r3,#0x58
        0x00128db0:    434b        KC      MULS     r3,r1,r3
        0x00128db2:    68c4        .h      LDR      r4,[r0,#0xc]
        0x00128db4:    4806        .H      LDR      r0,[pc,#24] ; [0x128dd0] = 0xfff
        0x00128db6:    18e3        ..      ADDS     r3,r4,r3
        0x00128db8:    69da        .i      LDR      r2,[r3,#0x1c]
        0x00128dba:    4285        .B      CMP      r5,r0
        0x00128dbc:    d902        ..      BLS      0x128dc4 ; dmac_block_ts_config + 32
        0x00128dbe:    4310        .C      ORRS     r0,r0,r2
        0x00128dc0:    61d8        .a      STR      r0,[r3,#0x1c]
        0x00128dc2:    bd30        0.      POP      {r4,r5,pc}
        0x00128dc4:    0b12        ..      LSRS     r2,r2,#12
        0x00128dc6:    0312        ..      LSLS     r2,r2,#12
        0x00128dc8:    432a        *C      ORRS     r2,r2,r5
        0x00128dca:    61da        .a      STR      r2,[r3,#0x1c]
        0x00128dcc:    e7f9        ..      B        0x128dc2 ; dmac_block_ts_config + 30
        0x00128dce:    46c0        .F      MOV      r8,r8
    $d
        0x00128dd0:    00000fff    ....    DCD    4095
    $t
    dmac_stat_clean_if_all_transfer_done
        0x00128dd4:    b570        p.      PUSH     {r4-r6,lr}
        0x00128dd6:    0004        ..      MOVS     r4,r0
        0x00128dd8:    f3ef8610    ....    MRS      r6,PRIMASK
        0x00128ddc:    b672        r.      CPSID    i
        0x00128dde:    7a43        Cz      LDRB     r3,[r0,#9]
        0x00128de0:    2b00        .+      CMP      r3,#0
        0x00128de2:    d112        ..      BNE      0x128e0a ; dmac_stat_clean_if_all_transfer_done + 54
        0x00128de4:    22ba        ."      MOVS     r2,#0xba
        0x00128de6:    68c3        .h      LDR      r3,[r0,#0xc]
        0x00128de8:    0092        ..      LSLS     r2,r2,#2
        0x00128dea:    589a        .X      LDR      r2,[r3,r2]
        0x00128dec:    2a00        .*      CMP      r2,#0
        0x00128dee:    d10c        ..      BNE      0x128e0a ; dmac_stat_clean_if_all_transfer_done + 54
        0x00128df0:    22c2        ."      MOVS     r2,#0xc2
        0x00128df2:    0092        ..      LSLS     r2,r2,#2
        0x00128df4:    589b        .X      LDR      r3,[r3,r2]
        0x00128df6:    2b00        .+      CMP      r3,#0
        0x00128df8:    d107        ..      BNE      0x128e0a ; dmac_stat_clean_if_all_transfer_done + 54
        0x00128dfa:    4d06        .M      LDR      r5,[pc,#24] ; [0x128e14] = 0x129388
        0x00128dfc:    2101        .!      MOVS     r1,#1
        0x00128dfe:    68eb        .h      LDR      r3,[r5,#0xc]
        0x00128e00:    4798        .G      BLX      r3
        0x00128e02:    696b        ki      LDR      r3,[r5,#0x14]
        0x00128e04:    2103        .!      MOVS     r1,#3
        0x00128e06:    0020         .      MOVS     r0,r4
        0x00128e08:    4798        .G      BLX      r3
        0x00128e0a:    2e00        ..      CMP      r6,#0
        0x00128e0c:    d100        ..      BNE      0x128e10 ; dmac_stat_clean_if_all_transfer_done + 60
        0x00128e0e:    b662        b.      CPSIE    i
        0x00128e10:    bd70        p.      POP      {r4-r6,pc}
        0x00128e12:    46c0        .F      MOV      r8,r8
    $d
        0x00128e14:    00129388    ....    DCD    1217416
    $t
    dmac_ch_free.isra.0
        0x00128e18:    f3ef8310    ....    MRS      r3,PRIMASK
        0x00128e1c:    b672        r.      CPSID    i
        0x00128e1e:    2201        ."      MOVS     r2,#1
        0x00128e20:    408a        .@      LSLS     r2,r2,r1
        0x00128e22:    0011        ..      MOVS     r1,r2
        0x00128e24:    7802        .x      LDRB     r2,[r0,#0]
        0x00128e26:    438a        .C      BICS     r2,r2,r1
        0x00128e28:    7002        .p      STRB     r2,[r0,#0]
        0x00128e2a:    2b00        .+      CMP      r3,#0
        0x00128e2c:    d100        ..      BNE      0x128e30 ; dmac_ch_free.isra.0 + 24
        0x00128e2e:    b662        b.      CPSIE    i
        0x00128e30:    4770        pG      BX       lr
        0x00128e32:    0000        ..      MOVS     r0,r0
    $t
    app_dmac_init
        0x00128e34:    b570        p.      PUSH     {r4-r6,lr}
        0x00128e36:    0004        ..      MOVS     r4,r0
        0x00128e38:    2601        .&      MOVS     r6,#1
        0x00128e3a:    4d17        .M      LDR      r5,[pc,#92] ; [0x128e98] = 0x129388
        0x00128e3c:    686b        kh      LDR      r3,[r5,#4]
        0x00128e3e:    4798        .G      BLX      r3
        0x00128e40:    68eb        .h      LDR      r3,[r5,#0xc]
        0x00128e42:    0020         .      MOVS     r0,r4
        0x00128e44:    2100        .!      MOVS     r1,#0
        0x00128e46:    4798        .G      BLX      r3
        0x00128e48:    682b        +h      LDR      r3,[r5,#0]
        0x00128e4a:    0020         .      MOVS     r0,r4
        0x00128e4c:    2102        .!      MOVS     r1,#2
        0x00128e4e:    4798        .G      BLX      r3
        0x00128e50:    682b        +h      LDR      r3,[r5,#0]
        0x00128e52:    0020         .      MOVS     r0,r4
        0x00128e54:    2100        .!      MOVS     r1,#0
        0x00128e56:    4798        .G      BLX      r3
        0x00128e58:    23e6        .#      MOVS     r3,#0xe6
        0x00128e5a:    0031        1.      MOVS     r1,r6
        0x00128e5c:    68e2        .h      LDR      r2,[r4,#0xc]
        0x00128e5e:    009b        ..      LSLS     r3,r3,#2
        0x00128e60:    50d6        .P      STR      r6,[r2,r3]
        0x00128e62:    7a23        #z      LDRB     r3,[r4,#8]
        0x00128e64:    20fc        .       MOVS     r0,#0xfc
        0x00128e66:    4099        .@      LSLS     r1,r1,r3
        0x00128e68:    000b        ..      MOVS     r3,r1
        0x00128e6a:    3b01        .;      SUBS     r3,#1
        0x00128e6c:    b2db        ..      UXTB     r3,r3
        0x00128e6e:    0219        ..      LSLS     r1,r3,#8
        0x00128e70:    0180        ..      LSLS     r0,r0,#6
        0x00128e72:    4001        .@      ANDS     r1,r1,r0
        0x00128e74:    203f        ?       MOVS     r0,#0x3f
        0x00128e76:    4003        .@      ANDS     r3,r3,r0
        0x00128e78:    430b        .C      ORRS     r3,r3,r1
        0x00128e7a:    21cc        .!      MOVS     r1,#0xcc
        0x00128e7c:    0089        ..      LSLS     r1,r1,#2
        0x00128e7e:    5053        SP      STR      r3,[r2,r1]
        0x00128e80:    3920         9      SUBS     r1,r1,#0x20
        0x00128e82:    5053        SP      STR      r3,[r2,r1]
        0x00128e84:    0020         .      MOVS     r0,r4
        0x00128e86:    696b        ki      LDR      r3,[r5,#0x14]
        0x00128e88:    2100        .!      MOVS     r1,#0
        0x00128e8a:    4798        .G      BLX      r3
        0x00128e8c:    68eb        .h      LDR      r3,[r5,#0xc]
        0x00128e8e:    0031        1.      MOVS     r1,r6
        0x00128e90:    0020         .      MOVS     r0,r4
        0x00128e92:    4798        .G      BLX      r3
        0x00128e94:    2000        .       MOVS     r0,#0
        0x00128e96:    bd70        p.      POP      {r4-r6,pc}
    $d
        0x00128e98:    00129388    ....    DCD    1217416
    $t
    app_dmac_start
        0x00128e9c:    b5f0        ..      PUSH     {r4-r7,lr}
        0x00128e9e:    0006        ..      MOVS     r6,r0
        0x00128ea0:    000d        ..      MOVS     r5,r1
        0x00128ea2:    2400        .$      MOVS     r4,#0
        0x00128ea4:    2001        .       MOVS     r0,#1
        0x00128ea6:    b085        ..      SUB      sp,sp,#0x14
        0x00128ea8:    9203        ..      STR      r2,[sp,#0xc]
        0x00128eaa:    7a33        3z      LDRB     r3,[r6,#8]
        0x00128eac:    42a3        .B      CMP      r3,r4
        0x00128eae:    d802        ..      BHI      0x128eb6 ; app_dmac_start + 26
        0x00128eb0:    2005        .       MOVS     r0,#5
        0x00128eb2:    b005        ..      ADD      sp,sp,#0x14
        0x00128eb4:    bdf0        ..      POP      {r4-r7,pc}
        0x00128eb6:    0003        ..      MOVS     r3,r0
        0x00128eb8:    40a3        .@      LSLS     r3,r3,r4
        0x00128eba:    9302        ..      STR      r3,[sp,#8]
        0x00128ebc:    466b        kF      MOV      r3,sp
        0x00128ebe:    7a1b        .z      LDRB     r3,[r3,#8]
        0x00128ec0:    f3ef8110    ....    MRS      r1,PRIMASK
        0x00128ec4:    b672        r.      CPSID    i
        0x00128ec6:    7a77        wz      LDRB     r7,[r6,#9]
        0x00128ec8:    003a        :.      MOVS     r2,r7
        0x00128eca:    401a        .@      ANDS     r2,r2,r3
        0x00128ecc:    d17d        }.      BNE      0x128fca ; app_dmac_start + 302
        0x00128ece:    433b        ;C      ORRS     r3,r3,r7
        0x00128ed0:    7273        sr      STRB     r3,[r6,#9]
        0x00128ed2:    2900        .)      CMP      r1,#0
        0x00128ed4:    d105        ..      BNE      0x128ee2 ; app_dmac_start + 70
        0x00128ed6:    b662        b.      CPSIE    i
        0x00128ed8:    2a00        .*      CMP      r2,#0
        0x00128eda:    d002        ..      BEQ      0x128ee2 ; app_dmac_start + 70
        0x00128edc:    3401        .4      ADDS     r4,#1
        0x00128ede:    b2e4        ..      UXTB     r4,r4
        0x00128ee0:    e7e3        ..      B        0x128eaa ; app_dmac_start + 14
        0x00128ee2:    2cff        .,      CMP      r4,#0xff
        0x00128ee4:    d0e4        ..      BEQ      0x128eb0 ; app_dmac_start + 20
        0x00128ee6:    230c        .#      MOVS     r3,#0xc
        0x00128ee8:    4363        cC      MULS     r3,r4,r3
        0x00128eea:    6872        rh      LDR      r2,[r6,#4]
        0x00128eec:    4f38        8O      LDR      r7,[pc,#224] ; [0x128fd0] = 0x129388
        0x00128eee:    18d3        ..      ADDS     r3,r2,r3
        0x00128ef0:    682a        *h      LDR      r2,[r5,#0]
        0x00128ef2:    2100        .!      MOVS     r1,#0
        0x00128ef4:    605a        Z`      STR      r2,[r3,#4]
        0x00128ef6:    686a        jh      LDR      r2,[r5,#4]
        0x00128ef8:    0030        0.      MOVS     r0,r6
        0x00128efa:    609a        .`      STR      r2,[r3,#8]
        0x00128efc:    692a        *i      LDR      r2,[r5,#0x10]
        0x00128efe:    601a        .`      STR      r2,[r3,#0]
        0x00128f00:    68fb        .h      LDR      r3,[r7,#0xc]
        0x00128f02:    4798        .G      BLX      r3
        0x00128f04:    697b        {i      LDR      r3,[r7,#0x14]
        0x00128f06:    2102        .!      MOVS     r1,#2
        0x00128f08:    0030        0.      MOVS     r0,r6
        0x00128f0a:    4798        .G      BLX      r3
        0x00128f0c:    0021        !.      MOVS     r1,r4
        0x00128f0e:    0030        0.      MOVS     r0,r6
        0x00128f10:    f7ffff48    ..H.    BL       dmac_block_ts_config ; 0x128da4
        0x00128f14:    2370        p#      MOVS     r3,#0x70
        0x00128f16:    7d69        i}      LDRB     r1,[r5,#0x15]
        0x00128f18:    400b        .@      ANDS     r3,r3,r1
        0x00128f1a:    2b20         +      CMP      r3,#0x20
        0x00128f1c:    d04d        M.      BEQ      0x128fba ; app_dmac_start + 286
        0x00128f1e:    2b10        .+      CMP      r3,#0x10
        0x00128f20:    d04f        O.      BEQ      0x128fc2 ; app_dmac_start + 294
        0x00128f22:    2b00        .+      CMP      r3,#0
        0x00128f24:    d101        ..      BNE      0x128f2a ; app_dmac_start + 142
        0x00128f26:    9300        ..      STR      r3,[sp,#0]
        0x00128f28:    9301        ..      STR      r3,[sp,#4]
        0x00128f2a:    8aaa        ..      LDRH     r2,[r5,#0x14]
        0x00128f2c:    070b        ..      LSLS     r3,r1,#28
        0x00128f2e:    05d2        ..      LSLS     r2,r2,#23
        0x00128f30:    0f52        R.      LSRS     r2,r2,#29
        0x00128f32:    0f5b        [.      LSRS     r3,r3,#29
        0x00128f34:    68f0        .h      LDR      r0,[r6,#0xc]
        0x00128f36:    02db        ..      LSLS     r3,r3,#11
        0x00128f38:    7dae        .}      LDRB     r6,[r5,#0x16]
        0x00128f3a:    0392        ..      LSLS     r2,r2,#14
        0x00128f3c:    431a        .C      ORRS     r2,r2,r3
        0x00128f3e:    7d2b        +}      LDRB     r3,[r5,#0x14]
        0x00128f40:    09f6        ..      LSRS     r6,r6,#7
        0x00128f42:    4332        2C      ORRS     r2,r2,r6
        0x00128f44:    075e        ^.      LSLS     r6,r3,#29
        0x00128f46:    069b        ..      LSLS     r3,r3,#26
        0x00128f48:    0e76        v.      LSRS     r6,r6,#25
        0x00128f4a:    0f5b        [.      LSRS     r3,r3,#29
        0x00128f4c:    4332        2C      ORRS     r2,r2,r6
        0x00128f4e:    005b        [.      LSLS     r3,r3,#1
        0x00128f50:    4313        .C      ORRS     r3,r3,r2
        0x00128f52:    22c0        ."      MOVS     r2,#0xc0
        0x00128f54:    0409        ..      LSLS     r1,r1,#16
        0x00128f56:    0392        ..      LSLS     r2,r2,#14
        0x00128f58:    4011        .@      ANDS     r1,r1,r2
        0x00128f5a:    430b        .C      ORRS     r3,r3,r1
        0x00128f5c:    2158        X!      MOVS     r1,#0x58
        0x00128f5e:    9a01        ..      LDR      r2,[sp,#4]
        0x00128f60:    4361        aC      MULS     r1,r4,r1
        0x00128f62:    0252        R.      LSLS     r2,r2,#9
        0x00128f64:    4313        .C      ORRS     r3,r3,r2
        0x00128f66:    9a00        ..      LDR      r2,[sp,#0]
        0x00128f68:    2600        .&      MOVS     r6,#0
        0x00128f6a:    01d2        ..      LSLS     r2,r2,#7
        0x00128f6c:    4313        .C      ORRS     r3,r3,r2
        0x00128f6e:    1842        B.      ADDS     r2,r0,r1
        0x00128f70:    6193        .a      STR      r3,[r2,#0x18]
        0x00128f72:    7dab        .}      LDRB     r3,[r5,#0x16]
        0x00128f74:    6416        .d      STR      r6,[r2,#0x40]
        0x00128f76:    065b        [.      LSLS     r3,r3,#25
        0x00128f78:    0f1b        ..      LSRS     r3,r3,#28
        0x00128f7a:    02df        ..      LSLS     r7,r3,#11
        0x00128f7c:    696b        ki      LDR      r3,[r5,#0x14]
        0x00128f7e:    035b        [.      LSLS     r3,r3,#13
        0x00128f80:    0f1b        ..      LSRS     r3,r3,#28
        0x00128f82:    01db        ..      LSLS     r3,r3,#7
        0x00128f84:    433b        ;C      ORRS     r3,r3,r7
        0x00128f86:    2702        .'      MOVS     r7,#2
        0x00128f88:    433b        ;C      ORRS     r3,r3,r7
        0x00128f8a:    6453        Sd      STR      r3,[r2,#0x44]
        0x00128f8c:    68ab        .h      LDR      r3,[r5,#8]
        0x00128f8e:    500b        .P      STR      r3,[r1,r0]
        0x00128f90:    68eb        .h      LDR      r3,[r5,#0xc]
        0x00128f92:    9902        ..      LDR      r1,[sp,#8]
        0x00128f94:    6093        .`      STR      r3,[r2,#8]
        0x00128f96:    22fc        ."      MOVS     r2,#0xfc
        0x00128f98:    9b02        ..      LDR      r3,[sp,#8]
        0x00128f9a:    0192        ..      LSLS     r2,r2,#6
        0x00128f9c:    021b        ..      LSLS     r3,r3,#8
        0x00128f9e:    4013        .@      ANDS     r3,r3,r2
        0x00128fa0:    223f        ?"      MOVS     r2,#0x3f
        0x00128fa2:    400a        .@      ANDS     r2,r2,r1
        0x00128fa4:    4313        .C      ORRS     r3,r3,r2
        0x00128fa6:    22e8        ."      MOVS     r2,#0xe8
        0x00128fa8:    0092        ..      LSLS     r2,r2,#2
        0x00128faa:    5083        .P      STR      r3,[r0,r2]
        0x00128fac:    9803        ..      LDR      r0,[sp,#0xc]
        0x00128fae:    42b0        .B      CMP      r0,r6
        0x00128fb0:    d100        ..      BNE      0x128fb4 ; app_dmac_start + 280
        0x00128fb2:    e77e        ~.      B        0x128eb2 ; app_dmac_start + 22
        0x00128fb4:    7004        .p      STRB     r4,[r0,#0]
        0x00128fb6:    0030        0.      MOVS     r0,r6
        0x00128fb8:    e77b        {.      B        0x128eb2 ; app_dmac_start + 22
        0x00128fba:    2300        .#      MOVS     r3,#0
        0x00128fbc:    9300        ..      STR      r3,[sp,#0]
        0x00128fbe:    3302        .3      ADDS     r3,#2
        0x00128fc0:    e7b2        ..      B        0x128f28 ; app_dmac_start + 140
        0x00128fc2:    2302        .#      MOVS     r3,#2
        0x00128fc4:    9300        ..      STR      r3,[sp,#0]
        0x00128fc6:    2300        .#      MOVS     r3,#0
        0x00128fc8:    e7ae        ..      B        0x128f28 ; app_dmac_start + 140
        0x00128fca:    2900        .)      CMP      r1,#0
        0x00128fcc:    d186        ..      BNE      0x128edc ; app_dmac_start + 64
        0x00128fce:    e782        ..      B        0x128ed6 ; app_dmac_start + 58
    $d
        0x00128fd0:    00129388    ....    DCD    1217416
    $t
    app_dmac_transfer_wait
        0x00128fd4:    b5f0        ..      PUSH     {r4-r7,lr}
        0x00128fd6:    7a03        .z      LDRB     r3,[r0,#8]
        0x00128fd8:    0005        ..      MOVS     r5,r0
        0x00128fda:    b085        ..      SUB      sp,sp,#0x14
        0x00128fdc:    000e        ..      MOVS     r6,r1
        0x00128fde:    2001        .       MOVS     r0,#1
        0x00128fe0:    428b        .B      CMP      r3,r1
        0x00128fe2:    d946        F.      BLS      0x129072 ; app_dmac_transfer_wait + 158
        0x00128fe4:    0007        ..      MOVS     r7,r0
        0x00128fe6:    68eb        .h      LDR      r3,[r5,#0xc]
        0x00128fe8:    408f        .@      LSLS     r7,r7,r1
        0x00128fea:    9300        ..      STR      r3,[sp,#0]
        0x00128fec:    23e8        .#      MOVS     r3,#0xe8
        0x00128fee:    9a00        ..      LDR      r2,[sp,#0]
        0x00128ff0:    009b        ..      LSLS     r3,r3,#2
        0x00128ff2:    58d2        .X      LDR      r2,[r2,r3]
        0x00128ff4:    427b        {B      RSBS     r3,r7,#0
        0x00128ff6:    417b        {A      ADCS     r3,r3,r7
        0x00128ff8:    421a        .B      TST      r2,r3
        0x00128ffa:    d13c        <.      BNE      0x129076 ; app_dmac_transfer_wait + 162
        0x00128ffc:    2358        X#      MOVS     r3,#0x58
        0x00128ffe:    4373        sC      MULS     r3,r6,r3
        0x00129000:    9a00        ..      LDR      r2,[sp,#0]
        0x00129002:    18d3        ..      ADDS     r3,r2,r3
        0x00129004:    699a        .i      LDR      r2,[r3,#0x18]
        0x00129006:    4202        .B      TST      r2,r0
        0x00129008:    d137        7.      BNE      0x12907a ; app_dmac_transfer_wait + 166
        0x0012900a:    220c        ."      MOVS     r2,#0xc
        0x0012900c:    4372        rC      MULS     r2,r6,r2
        0x0012900e:    9201        ..      STR      r2,[sp,#4]
        0x00129010:    22fc        ."      MOVS     r2,#0xfc
        0x00129012:    0239        9.      LSLS     r1,r7,#8
        0x00129014:    0192        ..      LSLS     r2,r2,#6
        0x00129016:    4011        .@      ANDS     r1,r1,r2
        0x00129018:    223f        ?"      MOVS     r2,#0x3f
        0x0012901a:    403a        :@      ANDS     r2,r2,r7
        0x0012901c:    4311        .C      ORRS     r1,r1,r2
        0x0012901e:    9102        ..      STR      r1,[sp,#8]
        0x00129020:    9303        ..      STR      r3,[sp,#0xc]
        0x00129022:    22b0        ."      MOVS     r2,#0xb0
        0x00129024:    9b00        ..      LDR      r3,[sp,#0]
        0x00129026:    0092        ..      LSLS     r2,r2,#2
        0x00129028:    589b        .X      LDR      r3,[r3,r2]
        0x0012902a:    421f        .B      TST      r7,r3
        0x0012902c:    d0f9        ..      BEQ      0x129022 ; app_dmac_transfer_wait + 78
        0x0012902e:    23ce        .#      MOVS     r3,#0xce
        0x00129030:    9a00        ..      LDR      r2,[sp,#0]
        0x00129032:    009b        ..      LSLS     r3,r3,#2
        0x00129034:    50d7        .P      STR      r7,[r2,r3]
        0x00129036:    9b03        ..      LDR      r3,[sp,#0xc]
        0x00129038:    9a01        ..      LDR      r2,[sp,#4]
        0x0012903a:    69dc        .i      LDR      r4,[r3,#0x1c]
        0x0012903c:    686b        kh      LDR      r3,[r5,#4]
        0x0012903e:    0524        $.      LSLS     r4,r4,#20
        0x00129040:    189b        ..      ADDS     r3,r3,r2
        0x00129042:    681a        .h      LDR      r2,[r3,#0]
        0x00129044:    0d24        $.      LSRS     r4,r4,#20
        0x00129046:    1b14        ..      SUBS     r4,r2,r4
        0x00129048:    601c        .`      STR      r4,[r3,#0]
        0x0012904a:    d009        ..      BEQ      0x129060 ; app_dmac_transfer_wait + 140
        0x0012904c:    0031        1.      MOVS     r1,r6
        0x0012904e:    0028        (.      MOVS     r0,r5
        0x00129050:    f7fffea8    ....    BL       dmac_block_ts_config ; 0x128da4
        0x00129054:    23e8        .#      MOVS     r3,#0xe8
        0x00129056:    9a00        ..      LDR      r2,[sp,#0]
        0x00129058:    9902        ..      LDR      r1,[sp,#8]
        0x0012905a:    009b        ..      LSLS     r3,r3,#2
        0x0012905c:    50d1        .P      STR      r1,[r2,r3]
        0x0012905e:    e7e0        ..      B        0x129022 ; app_dmac_transfer_wait + 78
        0x00129060:    0028        (.      MOVS     r0,r5
        0x00129062:    0031        1.      MOVS     r1,r6
        0x00129064:    3009        .0      ADDS     r0,r0,#9
        0x00129066:    f7fffed7    ....    BL       dmac_ch_free.isra.0 ; 0x128e18
        0x0012906a:    0028        (.      MOVS     r0,r5
        0x0012906c:    f7fffeb2    ....    BL       dmac_stat_clean_if_all_transfer_done ; 0x128dd4
        0x00129070:    0020         .      MOVS     r0,r4
        0x00129072:    b005        ..      ADD      sp,sp,#0x14
        0x00129074:    bdf0        ..      POP      {r4-r7,pc}
        0x00129076:    2003        .       MOVS     r0,#3
        0x00129078:    e7fb        ..      B        0x129072 ; app_dmac_transfer_wait + 158
        0x0012907a:    2004        .       MOVS     r0,#4
        0x0012907c:    e7f9        ..      B        0x129072 ; app_dmac_transfer_wait + 158
        0x0012907e:    0000        ..      MOVS     r0,r0
    $t
    dmac_get_max_block_transfer_size
        0x00129080:    4800        .H      LDR      r0,[pc,#0] ; [0x129084] = 0xfff
        0x00129082:    4770        pG      BX       lr
    $d
        0x00129084:    00000fff    ....    DCD    4095
    $t
    app_dmac_init_wrapper
        0x00129088:    b510        ..      PUSH     {r4,lr}
        0x0012908a:    4802        .H      LDR      r0,[pc,#8] ; [0x129094] = 0x1293f0
        0x0012908c:    f7fffed2    ....    BL       app_dmac_init ; 0x128e34
        0x00129090:    bd10        ..      POP      {r4,pc}
        0x00129092:    46c0        .F      MOV      r8,r8
    $d
        0x00129094:    001293f0    ....    DCD    1217520
    $t
    app_dmac_start_wrapper
        0x00129098:    b510        ..      PUSH     {r4,lr}
        0x0012909a:    000a        ..      MOVS     r2,r1
        0x0012909c:    0001        ..      MOVS     r1,r0
        0x0012909e:    4802        .H      LDR      r0,[pc,#8] ; [0x1290a8] = 0x1293f0
        0x001290a0:    f7fffefc    ....    BL       app_dmac_start ; 0x128e9c
        0x001290a4:    bd10        ..      POP      {r4,pc}
        0x001290a6:    46c0        .F      MOV      r8,r8
    $d
        0x001290a8:    001293f0    ....    DCD    1217520
    $t
    app_dmac_transfer_wait_wrapper
        0x001290ac:    b510        ..      PUSH     {r4,lr}
        0x001290ae:    0001        ..      MOVS     r1,r0
        0x001290b0:    4801        .H      LDR      r0,[pc,#4] ; [0x1290b8] = 0x1293f0
        0x001290b2:    f7ffff8f    ....    BL       app_dmac_transfer_wait ; 0x128fd4
        0x001290b6:    bd10        ..      POP      {r4,pc}
    $d
        0x001290b8:    001293f0    ....    DCD    1217520
    $t
    recovery_list_add
        0x001290bc:    0089        ..      LSLS     r1,r1,#2
        0x001290be:    500a        .P      STR      r2,[r1,r0]
        0x001290c0:    4770        pG      BX       lr
    $t
    recovery_list_remove
        0x001290c2:    2300        .#      MOVS     r3,#0
        0x001290c4:    0089        ..      LSLS     r1,r1,#2
        0x001290c6:    500b        .P      STR      r3,[r1,r0]
        0x001290c8:    4770        pG      BX       lr
    $t
    periph_lock
        0x001290ca:    0002        ..      MOVS     r2,r0
        0x001290cc:    f3ef8110    ....    MRS      r1,PRIMASK
        0x001290d0:    b672        r.      CPSID    i
        0x001290d2:    7803        .x      LDRB     r3,[r0,#0]
        0x001290d4:    2000        .       MOVS     r0,#0
        0x001290d6:    4283        .B      CMP      r3,r0
        0x001290d8:    d101        ..      BNE      0x1290de ; periph_lock + 20
        0x001290da:    3001        .0      ADDS     r0,#1
        0x001290dc:    7010        .p      STRB     r0,[r2,#0]
        0x001290de:    2900        .)      CMP      r1,#0
        0x001290e0:    d100        ..      BNE      0x1290e4 ; periph_lock + 26
        0x001290e2:    b662        b.      CPSIE    i
        0x001290e4:    4770        pG      BX       lr
    $t
    periph_unlock
        0x001290e6:    f3ef8210    ....    MRS      r2,PRIMASK
        0x001290ea:    b672        r.      CPSID    i
        0x001290ec:    7803        .x      LDRB     r3,[r0,#0]
        0x001290ee:    2b00        .+      CMP      r3,#0
        0x001290f0:    d001        ..      BEQ      0x1290f6 ; periph_unlock + 16
        0x001290f2:    2100        .!      MOVS     r1,#0
        0x001290f4:    7001        .p      STRB     r1,[r0,#0]
        0x001290f6:    2a00        .*      CMP      r2,#0
        0x001290f8:    d100        ..      BNE      0x1290fc ; periph_unlock + 22
        0x001290fa:    b662        b.      CPSIE    i
        0x001290fc:    0018        ..      MOVS     r0,r3
        0x001290fe:    4770        pG      BX       lr
    $t
    periph_lock_state_get
        0x00129100:    7800        .x      LDRB     r0,[r0,#0]
        0x00129102:    4770        pG      BX       lr
    $t
    flash_write_enable
        0x00129104:    b507        ..      PUSH     {r0-r2,lr}
        0x00129106:    466b        kF      MOV      r3,sp
        0x00129108:    1dd8        ..      ADDS     r0,r3,#7
        0x0012910a:    2306        .#      MOVS     r3,#6
        0x0012910c:    2101        .!      MOVS     r1,#1
        0x0012910e:    7003        .p      STRB     r3,[r0,#0]
        0x00129110:    f7fffdee    ....    BL       app_qspi_std_write_wrapper ; 0x128cf0
        0x00129114:    bd0e        ..      POP      {r1-r3,pc}
    $t
    flash_operation_wait.constprop.0
        0x00129116:    b573        s.      PUSH     {r0,r1,r4-r6,lr}
        0x00129118:    466b        kF      MOV      r3,sp
        0x0012911a:    1ddd        ..      ADDS     r5,r3,#7
        0x0012911c:    2305        .#      MOVS     r3,#5
        0x0012911e:    2401        .$      MOVS     r4,#1
        0x00129120:    702b        +p      STRB     r3,[r5,#0]
        0x00129122:    466b        kF      MOV      r3,sp
        0x00129124:    1d9e        ..      ADDS     r6,r3,#6
        0x00129126:    0032        2.      MOVS     r2,r6
        0x00129128:    0023        #.      MOVS     r3,r4
        0x0012912a:    0021        !.      MOVS     r1,r4
        0x0012912c:    0028        (.      MOVS     r0,r5
        0x0012912e:    f7fffdff    ....    BL       app_qspi_std_read_wrapper ; 0x128d30
        0x00129132:    7833        3x      LDRB     r3,[r6,#0]
        0x00129134:    4223        #B      TST      r3,r4
        0x00129136:    d001        ..      BEQ      0x12913c ; flash_operation_wait.constprop.0 + 38
        0x00129138:    2800        .(      CMP      r0,#0
        0x0012913a:    d0f2        ..      BEQ      0x129122 ; flash_operation_wait.constprop.0 + 12
        0x0012913c:    bd76        v.      POP      {r1,r2,r4-r6,pc}
    $t
    flash_program_operation_start
        0x0012913e:    b5f8        ..      PUSH     {r3-r7,lr}
        0x00129140:    0004        ..      MOVS     r4,r0
        0x00129142:    000d        ..      MOVS     r5,r1
        0x00129144:    0017        ..      MOVS     r7,r2
        0x00129146:    001e        ..      MOVS     r6,r3
        0x00129148:    f7ffffdc    ....    BL       flash_write_enable ; 0x129104
        0x0012914c:    2800        .(      CMP      r0,#0
        0x0012914e:    d109        ..      BNE      0x129164 ; flash_program_operation_start + 38
        0x00129150:    003b        ;.      MOVS     r3,r7
        0x00129152:    0032        2.      MOVS     r2,r6
        0x00129154:    0029        ).      MOVS     r1,r5
        0x00129156:    0020         .      MOVS     r0,r4
        0x00129158:    f7fffdde    ....    BL       app_qspi_flash_program_wrapper ; 0x128d18
        0x0012915c:    2800        .(      CMP      r0,#0
        0x0012915e:    d101        ..      BNE      0x129164 ; flash_program_operation_start + 38
        0x00129160:    f7ffffd9    ....    BL       flash_operation_wait.constprop.0 ; 0x129116
        0x00129164:    bdf8        ..      POP      {r3-r7,pc}
    $t
    flash_erase_operation_start
        0x00129166:    b57f        ..      PUSH     {r0-r6,lr}
        0x00129168:    466b        kF      MOV      r3,sp
        0x0012916a:    1ddd        ..      ADDS     r5,r3,#7
        0x0012916c:    000c        ..      MOVS     r4,r1
        0x0012916e:    0016        ..      MOVS     r6,r2
        0x00129170:    7028        (p      STRB     r0,[r5,#0]
        0x00129172:    f7ffffc7    ....    BL       flash_write_enable ; 0x129104
        0x00129176:    2800        .(      CMP      r0,#0
        0x00129178:    d109        ..      BNE      0x12918e ; flash_erase_operation_start + 40
        0x0012917a:    2e00        ..      CMP      r6,#0
        0x0012917c:    d009        ..      BEQ      0x129192 ; flash_erase_operation_start + 44
        0x0012917e:    2101        .!      MOVS     r1,#1
        0x00129180:    0028        (.      MOVS     r0,r5
        0x00129182:    f7fffdb5    ....    BL       app_qspi_std_write_wrapper ; 0x128cf0
        0x00129186:    2800        .(      CMP      r0,#0
        0x00129188:    d101        ..      BNE      0x12918e ; flash_erase_operation_start + 40
        0x0012918a:    f7ffffc4    ....    BL       flash_operation_wait.constprop.0 ; 0x129116
        0x0012918e:    b004        ..      ADD      sp,sp,#0x10
        0x00129190:    bd70        p.      POP      {r4-r6,pc}
        0x00129192:    782b        +x      LDRB     r3,[r5,#0]
        0x00129194:    a803        ..      ADD      r0,sp,#0xc
        0x00129196:    7003        .p      STRB     r3,[r0,#0]
        0x00129198:    0c23        #.      LSRS     r3,r4,#16
        0x0012919a:    7043        Cp      STRB     r3,[r0,#1]
        0x0012919c:    0a23        #.      LSRS     r3,r4,#8
        0x0012919e:    7083        .p      STRB     r3,[r0,#2]
        0x001291a0:    70c4        .p      STRB     r4,[r0,#3]
        0x001291a2:    2104        .!      MOVS     r1,#4
        0x001291a4:    e7ed        ..      B        0x129182 ; flash_erase_operation_start + 28
    $t
    flash_multi_read_32bits_operation_start
        0x001291a6:    b510        ..      PUSH     {r4,lr}
        0x001291a8:    0212        ..      LSLS     r2,r2,#8
        0x001291aa:    f7fffdcd    ....    BL       app_qspi_multi_read_32bits_wrapper ; 0x128d48
        0x001291ae:    bd10        ..      POP      {r4,pc}
    $t
    flash_read_operation_start
        0x001291b0:    b510        ..      PUSH     {r4,lr}
        0x001291b2:    f7fffdbd    ....    BL       app_qspi_std_read_wrapper ; 0x128d30
        0x001291b6:    bd10        ..      POP      {r4,pc}
    $t
    flash_write_status_reg_start
        0x001291b8:    b5f7        ..      PUSH     {r0-r2,r4-r7,lr}
        0x001291ba:    466b        kF      MOV      r3,sp
        0x001291bc:    af00        ..      ADD      r7,sp,#0
        0x001291be:    0006        ..      MOVS     r6,r0
        0x001291c0:    000d        ..      MOVS     r5,r1
        0x001291c2:    0014        ..      MOVS     r4,r2
        0x001291c4:    607b        {`      STR      r3,[r7,#4]
        0x001291c6:    f7ffff9d    ....    BL       flash_write_enable ; 0x129104
        0x001291ca:    2800        .(      CMP      r0,#0
        0x001291cc:    d114        ..      BNE      0x1291f8 ; flash_write_status_reg_start + 64
        0x001291ce:    0023        #.      MOVS     r3,r4
        0x001291d0:    466a        jF      MOV      r2,sp
        0x001291d2:    3308        .3      ADDS     r3,r3,#8
        0x001291d4:    08db        ..      LSRS     r3,r3,#3
        0x001291d6:    00db        ..      LSLS     r3,r3,#3
        0x001291d8:    1ad3        ..      SUBS     r3,r2,r3
        0x001291da:    469d        .F      MOV      sp,r3
        0x001291dc:    0029        ).      MOVS     r1,r5
        0x001291de:    701e        .p      STRB     r6,[r3,#0]
        0x001291e0:    1c58        X.      ADDS     r0,r3,#1
        0x001291e2:    0022        ".      MOVS     r2,r4
        0x001291e4:    f6d8fc78    ..x.    BL       0x1ad8 ; 0x1ad8
        0x001291e8:    1c61        a.      ADDS     r1,r4,#1
        0x001291ea:    4668        hF      MOV      r0,sp
        0x001291ec:    f7fffd8a    ....    BL       app_qspi_std_write_no_dma_wrapper ; 0x128d04
        0x001291f0:    2800        .(      CMP      r0,#0
        0x001291f2:    d101        ..      BNE      0x1291f8 ; flash_write_status_reg_start + 64
        0x001291f4:    f7ffff8f    ....    BL       flash_operation_wait.constprop.0 ; 0x129116
        0x001291f8:    687b        {h      LDR      r3,[r7,#4]
        0x001291fa:    469d        .F      MOV      sp,r3
        0x001291fc:    46bd        .F      MOV      sp,r7
        0x001291fe:    bdfe        ..      POP      {r1-r7,pc}
    $t
    flash_multi_read
        0x00129200:    b5f0        ..      PUSH     {r4-r7,lr}
        0x00129202:    2503        .%      MOVS     r5,#3
        0x00129204:    b087        ..      SUB      sp,sp,#0x1c
        0x00129206:    0006        ..      MOVS     r6,r0
        0x00129208:    000f        ..      MOVS     r7,r1
        0x0012920a:    0014        ..      MOVS     r4,r2
        0x0012920c:    4015        .@      ANDS     r5,r5,r2
        0x0012920e:    d017        ..      BEQ      0x129240 ; flash_multi_read + 64
        0x00129210:    0002        ..      MOVS     r2,r0
        0x00129212:    2101        .!      MOVS     r1,#1
        0x00129214:    a805        ..      ADD      r0,sp,#0x14
        0x00129216:    f7fff9b8    ....    BL       flash_multi_read_32bits_operation ; 0x12858a
        0x0012921a:    2800        .(      CMP      r0,#0
        0x0012921c:    d003        ..      BEQ      0x129226 ; flash_multi_read + 38
        0x0012921e:    2500        .%      MOVS     r5,#0
        0x00129220:    0028        (.      MOVS     r0,r5
        0x00129222:    b007        ..      ADD      sp,sp,#0x1c
        0x00129224:    bdf0        ..      POP      {r4-r7,pc}
        0x00129226:    2304        .#      MOVS     r3,#4
        0x00129228:    1b5d        ].      SUBS     r5,r3,r5
        0x0012922a:    42bd        .B      CMP      r5,r7
        0x0012922c:    d900        ..      BLS      0x129230 ; flash_multi_read + 48
        0x0012922e:    003d        =.      MOVS     r5,r7
        0x00129230:    0020         .      MOVS     r0,r4
        0x00129232:    002a        *.      MOVS     r2,r5
        0x00129234:    a905        ..      ADD      r1,sp,#0x14
        0x00129236:    f6d8fc4f    ..O.    BL       0x1ad8 ; 0x1ad8
        0x0012923a:    1964        d.      ADDS     r4,r4,r5
        0x0012923c:    1976        v.      ADDS     r6,r6,r5
        0x0012923e:    1b7f        ..      SUBS     r7,r7,r5
        0x00129240:    f7ffff1e    ....    BL       dmac_get_max_block_transfer_size ; 0x129080
        0x00129244:    08bb        ..      LSRS     r3,r7,#2
        0x00129246:    9003        ..      STR      r0,[sp,#0xc]
        0x00129248:    9301        ..      STR      r3,[sp,#4]
        0x0012924a:    9b01        ..      LDR      r3,[sp,#4]
        0x0012924c:    2b00        .+      CMP      r3,#0
        0x0012924e:    d110        ..      BNE      0x129272 ; flash_multi_read + 114
        0x00129250:    3303        .3      ADDS     r3,#3
        0x00129252:    401f        .@      ANDS     r7,r7,r3
        0x00129254:    9d01        ..      LDR      r5,[sp,#4]
        0x00129256:    d0e3        ..      BEQ      0x129220 ; flash_multi_read + 32
        0x00129258:    0032        2.      MOVS     r2,r6
        0x0012925a:    2101        .!      MOVS     r1,#1
        0x0012925c:    a805        ..      ADD      r0,sp,#0x14
        0x0012925e:    f7fff994    ....    BL       flash_multi_read_32bits_operation ; 0x12858a
        0x00129262:    1e05        ..      SUBS     r5,r0,#0
        0x00129264:    d1db        ..      BNE      0x12921e ; flash_multi_read + 30
        0x00129266:    003a        :.      MOVS     r2,r7
        0x00129268:    a905        ..      ADD      r1,sp,#0x14
        0x0012926a:    0020         .      MOVS     r0,r4
        0x0012926c:    f6d8fc34    ..4.    BL       0x1ad8 ; 0x1ad8
        0x00129270:    e7d6        ..      B        0x129220 ; flash_multi_read + 32
        0x00129272:    9b03        ..      LDR      r3,[sp,#0xc]
        0x00129274:    9a01        ..      LDR      r2,[sp,#4]
        0x00129276:    9302        ..      STR      r3,[sp,#8]
        0x00129278:    4293        .B      CMP      r3,r2
        0x0012927a:    d900        ..      BLS      0x12927e ; flash_multi_read + 126
        0x0012927c:    9202        ..      STR      r2,[sp,#8]
        0x0012927e:    466b        kF      MOV      r3,sp
        0x00129280:    0032        2.      MOVS     r2,r6
        0x00129282:    8919        ..      LDRH     r1,[r3,#8]
        0x00129284:    0020         .      MOVS     r0,r4
        0x00129286:    f7fff980    ....    BL       flash_multi_read_32bits_operation ; 0x12858a
        0x0012928a:    1e05        ..      SUBS     r5,r0,#0
        0x0012928c:    d1c8        ..      BNE      0x129220 ; flash_multi_read + 32
        0x0012928e:    9b02        ..      LDR      r3,[sp,#8]
        0x00129290:    9a02        ..      LDR      r2,[sp,#8]
        0x00129292:    009b        ..      LSLS     r3,r3,#2
        0x00129294:    18f6        ..      ADDS     r6,r6,r3
        0x00129296:    18e4        ..      ADDS     r4,r4,r3
        0x00129298:    9b01        ..      LDR      r3,[sp,#4]
        0x0012929a:    1a9b        ..      SUBS     r3,r3,r2
        0x0012929c:    e7d4        ..      B        0x129248 ; flash_multi_read + 72
    $t
    flash_program
        0x0012929e:    b5f7        ..      PUSH     {r0-r2,r4-r7,lr}
        0x001292a0:    23ff        .#      MOVS     r3,#0xff
        0x001292a2:    0005        ..      MOVS     r5,r0
        0x001292a4:    0007        ..      MOVS     r7,r0
        0x001292a6:    000c        ..      MOVS     r4,r1
        0x001292a8:    9200        ..      STR      r2,[sp,#0]
        0x001292aa:    439d        .C      BICS     r5,r5,r3
        0x001292ac:    42a8        .B      CMP      r0,r5
        0x001292ae:    d012        ..      BEQ      0x1292d6 ; flash_program + 56
        0x001292b0:    1a2d        -.      SUBS     r5,r5,r0
        0x001292b2:    1c6e        n.      ADDS     r6,r5,#1
        0x001292b4:    36ff        .6      ADDS     r6,r6,#0xff
        0x001292b6:    428e        .B      CMP      r6,r1
        0x001292b8:    d900        ..      BLS      0x1292bc ; flash_program + 30
        0x001292ba:    000e        ..      MOVS     r6,r1
        0x001292bc:    9b00        ..      LDR      r3,[sp,#0]
        0x001292be:    0032        2.      MOVS     r2,r6
        0x001292c0:    0039        9.      MOVS     r1,r7
        0x001292c2:    2002        .       MOVS     r0,#2
        0x001292c4:    f7fff90e    ....    BL       flash_program_operation ; 0x1284e4
        0x001292c8:    2800        .(      CMP      r0,#0
        0x001292ca:    d11a        ..      BNE      0x129302 ; flash_program + 100
        0x001292cc:    9b00        ..      LDR      r3,[sp,#0]
        0x001292ce:    19bd        ..      ADDS     r5,r7,r6
        0x001292d0:    199b        ..      ADDS     r3,r3,r6
        0x001292d2:    9300        ..      STR      r3,[sp,#0]
        0x001292d4:    1ba4        ..      SUBS     r4,r4,r6
        0x001292d6:    2780        .'      MOVS     r7,#0x80
        0x001292d8:    002e        ..      MOVS     r6,r5
        0x001292da:    0a23        #.      LSRS     r3,r4,#8
        0x001292dc:    b29b        ..      UXTH     r3,r3
        0x001292de:    021b        ..      LSLS     r3,r3,#8
        0x001292e0:    195b        [.      ADDS     r3,r3,r5
        0x001292e2:    9301        ..      STR      r3,[sp,#4]
        0x001292e4:    007f        ..      LSLS     r7,r7,#1
        0x001292e6:    9b00        ..      LDR      r3,[sp,#0]
        0x001292e8:    9a01        ..      LDR      r2,[sp,#4]
        0x001292ea:    1b5b        [.      SUBS     r3,r3,r5
        0x001292ec:    199b        ..      ADDS     r3,r3,r6
        0x001292ee:    4296        .B      CMP      r6,r2
        0x001292f0:    d108        ..      BNE      0x129304 ; flash_program + 102
        0x001292f2:    2000        .       MOVS     r0,#0
        0x001292f4:    b2e2        ..      UXTB     r2,r4
        0x001292f6:    4282        .B      CMP      r2,r0
        0x001292f8:    d003        ..      BEQ      0x129302 ; flash_program + 100
        0x001292fa:    0031        1.      MOVS     r1,r6
        0x001292fc:    3002        .0      ADDS     r0,#2
        0x001292fe:    f7fff8f1    ....    BL       flash_program_operation ; 0x1284e4
        0x00129302:    bdfe        ..      POP      {r1-r7,pc}
        0x00129304:    003a        :.      MOVS     r2,r7
        0x00129306:    0031        1.      MOVS     r1,r6
        0x00129308:    2002        .       MOVS     r0,#2
        0x0012930a:    f7fff8eb    ....    BL       flash_program_operation ; 0x1284e4
        0x0012930e:    2800        .(      CMP      r0,#0
        0x00129310:    d1f7        ..      BNE      0x129302 ; flash_program + 100
        0x00129312:    3601        .6      ADDS     r6,#1
        0x00129314:    36ff        .6      ADDS     r6,r6,#0xff
        0x00129316:    e7e6        ..      B        0x1292e6 ; flash_program + 72
    $t
    flash_erase
        0x00129318:    b510        ..      PUSH     {r4,lr}
        0x0012931a:    0004        ..      MOVS     r4,r0
        0x0012931c:    2904        .)      CMP      r1,#4
        0x0012931e:    d807        ..      BHI      0x129330 ; flash_erase + 24
        0x00129320:    0008        ..      MOVS     r0,r1
        0x00129322:    f000f823    ..#.    BL       __gnu_thumb1_case_uqi ; 0x12936c
    $d
        0x00129326:    0303        ..      DCW    771
        0x00129328:    0d0a        ..      DCW    3338
        0x0012932a:    10          .       DCB    16
    $d
        0x0012932b:    00          .       DCB    0
    $t
        0x0012932c:    2200        ."      MOVS     r2,#0
        0x0012932e:    2320         #      MOVS     r3,#0x20
        0x00129330:    0021        !.      MOVS     r1,r4
        0x00129332:    0018        ..      MOVS     r0,r3
        0x00129334:    f7fff8f1    ....    BL       flash_erase_operation ; 0x12851a
        0x00129338:    bd10        ..      POP      {r4,pc}
        0x0012933a:    2200        ."      MOVS     r2,#0
        0x0012933c:    2352        R#      MOVS     r3,#0x52
        0x0012933e:    e7f7        ..      B        0x129330 ; flash_erase + 24
        0x00129340:    2200        ."      MOVS     r2,#0
        0x00129342:    23d8        .#      MOVS     r3,#0xd8
        0x00129344:    e7f4        ..      B        0x129330 ; flash_erase + 24
        0x00129346:    2201        ."      MOVS     r2,#1
        0x00129348:    2360        `#      MOVS     r3,#0x60
        0x0012934a:    e7f1        ..      B        0x129330 ; flash_erase + 24
    $t
    flash_read_status_reg
        0x0012934c:    b507        ..      PUSH     {r0-r2,lr}
        0x0012934e:    0003        ..      MOVS     r3,r0
        0x00129350:    4668        hF      MOV      r0,sp
        0x00129352:    3007        .0      ADDS     r0,#7
        0x00129354:    7003        .p      STRB     r3,[r0,#0]
        0x00129356:    b293        ..      UXTH     r3,r2
        0x00129358:    000a        ..      MOVS     r2,r1
        0x0012935a:    2101        .!      MOVS     r1,#1
        0x0012935c:    f7fff8fa    ....    BL       flash_read_operation ; 0x128554
        0x00129360:    bd0e        ..      POP      {r1-r3,pc}
    $t
    flash_write_status_reg
        0x00129362:    b510        ..      PUSH     {r4,lr}
        0x00129364:    f7fff92c    ..,.    BL       flash_write_status_reg_operation ; 0x1285c0
        0x00129368:    bd10        ..      POP      {r4,pc}
        0x0012936a:    0000        ..      MOVS     r0,r0
    $t
    __gnu_thumb1_case_uqi
        0x0012936c:    b402        ..      PUSH     {r1}
        0x0012936e:    4671        qF      MOV      r1,lr
        0x00129370:    0849        I.      LSRS     r1,r1,#1
        0x00129372:    0049        I.      LSLS     r1,r1,#1
        0x00129374:    5c09        .\      LDRB     r1,[r1,r0]
        0x00129376:    0049        I.      LSLS     r1,r1,#1
        0x00129378:    448e        .D      ADD      lr,lr,r1
        0x0012937a:    bc02        ..      POP      {r1}
        0x0012937c:    4770        pG      BX       lr
        0x0012937e:    46c0        .F      MOV      r8,r8
    $t
    _init
        0x00129380:    b5f8        ..      PUSH     {r3-r7,lr}
        0x00129382:    46c0        .F      MOV      r8,r8
    $t
    _fini
        0x00129384:    b5f8        ..      PUSH     {r3-r7,lr}
        0x00129386:    46c0        .F      MOV      r8,r8
    $d
    dmac_universal_func
        0x00129388:    00128389    ....    DCD    1213321
        0x0012938c:    0012837d    }...    DCD    1213309
        0x00129390:    00000000    ....    DCD    0
        0x00129394:    0012836d    m...    DCD    1213293
        0x00129398:    00000000    ....    DCD    0
        0x0012939c:    001283c1    ....    DCD    1213377
    $d
    qspi_universal_func
        0x001293a0:    00000000    ....    DCD    0
        0x001293a4:    00128413    ....    DCD    1213459
        0x001293a8:    00000000    ....    DCD    0
        0x001293ac:    001283ff    ....    DCD    1213439
        0x001293b0:    00128421    !...    DCD    1213473
        0x001293b4:    001283fd    ....    DCD    1213437
    $d
    cache_clk_gate_func
        0x001293b8:    00128499    ....    DCD    1213593
    $d
    cache_sys_stat_func
        0x001293bc:    0012847d    }...    DCD    1213565
    $d
    read_buf
        0x001293c0:    00120000    ....    DCD    1179648
    $d
    io_mngt
        0x001293c4:    00000003    ....    DCD    3
        0x001293c8:    00000003    ....    DCD    3
        0x001293cc:    00000000    ....    DCD    0
        0x001293d0:    00000000    ....    DCD    0
        0x001293d4:    00000000    ....    DCD    0
    $d
    qspi_inst
        0x001293d8:    001287e9    ....    DCD    1214441
        0x001293dc:    00000000    ....    DCD    0
        0x001293e0:    00000000    ....    DCD    0
        0x001293e4:    00000000    ....    DCD    0
        0x001293e8:    20300000    ..0     DCD    540016640
        0x001293ec:    00000000    ....    DCD    0
    $d
    dmac_inst
        0x001293f0:    00128e35    5...    DCD    1216053
        0x001293f4:    00129914    ....    DCD    1218836
        0x001293f8:    00000006    ....    DCD    6
        0x001293fc:    20120000    ...     DCD    538050560
        0x00129400:    00000000    ....    DCD    0

====================================

** Section #2

    Name        : .zero.table
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : SHF_ALLOC + SHF_WRITE (0x00000003)
    Addr        : 0x00129404
    File Offset : 37892 (0x9404)
    Size        : 8 bytes (0x8)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0

    0x129404:   0c 94 12 00 08 04 00 00                            ........

    __zero_table_end__

====================================

** Section #3

    Name        : bss
    Type        : SHT_NOBITS (0x00000008)
    Flags       : SHF_ALLOC + SHF_WRITE (0x00000003)
    Addr        : 0x0012940c
    File Offset : 37900 (0x940c)
    Size        : 1032 bytes (0x408)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0


====================================

** Section #4

    Name        : .ARM.attributes
    Type        : SHT_ARM_ATTRIBUTES (0x70000003)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 37900 (0x940c)
    Size        : 40 bytes (0x28)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0

    'aeabi' file build attributes:
    0x000000:   05 36 53 2d 4d 00 06 0c 07 4d 09 01 12 04 14 01    .6S-M....M......
    0x000010:   15 01 17 03 18 01 1a 01                            ........
        Tag_CPU_name = "6S-M"
        Tag_CPU_arch = ARM v6S-M (=12)
        Tag_CPU_arch_profile = The microcontroller profile 'M' (e.g. for Cortex M3) (=77)
        Tag_THUMB_ISA_use = Thumb instructions were permitted to be used (=1)
        Tag_ABI_PCS_wchar_t = Size of wchar_t is 4 (=4)
        Tag_ABI_FP_denormal = This code was permitted to require IEEE 754 denormal numbers (=1)
        Tag_ABI_FP_exceptions = This code was permitted to check the IEEE 754 inexact exception (=1)
        Tag_ABI_FP_number_model = This code may use all the IEEE 754-defined FP encodings (=3)
        Tag_ABI_align8_needed = Code was permitted to depend on the 8-byte alignment of 8-byte data items (=1)
        Tag_ABI_enum_size = Enum values occupy the smallest container big enough to hold all values (=1)


====================================

** Section #5

    Name        : .comment
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : SHF_MERGE + SHF_STRINGS (0x00000030)
    Addr        : 0x00000000
    File Offset : 37940 (0x9434)
    Size        : 126 bytes (0x7e)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 1

    GCC: (GNU Tools for Arm Embedded Processors 7-2017-q4-major) 7.2.1 20170904 (release) [ARM/embedded-7-branch revision 255204]

====================================

** Section #6

    Name        : .debug_info
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 38066 (0x94b2)
    Size        : 126461 bytes (0x1edfd)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #7

    Name        : .debug_abbrev
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 164527 (0x282af)
    Size        : 14747 bytes (0x399b)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #8

    Name        : .debug_loc
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 179274 (0x2bc4a)
    Size        : 18025 bytes (0x4669)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #9

    Name        : .debug_aranges
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 197299 (0x302b3)
    Size        : 1752 bytes (0x6d8)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #10

    Name        : .debug_ranges
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 199051 (0x3098b)
    Size        : 3848 bytes (0xf08)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #11

    Name        : .debug_line
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 202899 (0x31893)
    Size        : 24213 bytes (0x5e95)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #12

    Name        : .debug_str
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : SHF_MERGE + SHF_STRINGS (0x00000030)
    Addr        : 0x00000000
    File Offset : 227112 (0x37728)
    Size        : 28996 bytes (0x7144)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 1


====================================

** Section #13

    Name        : .debug_frame
    Type        : SHT_PROGBITS (0x00000001)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 256108 (0x3e86c)
    Size        : 4144 bytes (0x1030)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0


====================================

** Section #14

    Name        : .bss
    Type        : SHT_NOBITS (0x00000008)
    Flags       : SHF_ALLOC + SHF_WRITE (0x00000003)
    Addr        : 0x00129814
    File Offset : 37900 (0x940c)
    Size        : 406 bytes (0x196)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 4
    Entry Size  : 0


====================================

** Section #15

    Name        : .symtab
    Type        : SHT_SYMTAB (0x00000002)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 260252 (0x3f89c)
    Size        : 15408 bytes (0x3c30)
    Link        : Section 16 (.strtab)
    Info        : Last local symbol no = 232
    Alignment   : 4
    Entry Size  : 16


====================================

** Section #16

    Name        : .strtab
    Type        : SHT_STRTAB (0x00000003)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 275660 (0x434cc)
    Size        : 14953 bytes (0x3a69)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

** Section #17

    Name        : .shstrtab
    Type        : SHT_STRTAB (0x00000003)
    Flags       : None (0x00000000)
    Addr        : 0x00000000
    File Offset : 290613 (0x46f35)
    Size        : 180 bytes (0xb4)
    Link        : SHN_UNDEF
    Info        : 0
    Alignment   : 1
    Entry Size  : 0


====================================

address     size       variable name                            type
0x00127ff0  0x20       boot_ram_head                            boot_ram_header_t
0x00127ff0  0x10       boot_ram_head.header                     boot_header_t
0x00127ff0  0x4        boot_ram_head.header.bx_flag             array[4] of uint8_t
0x00127ff4  0x4        boot_ram_head.header.base_addr           pointer to uint8_t
0x00127ff8  0x4        boot_ram_head.header.length              uint32_t
0x00127ffc  0x4        boot_ram_head.header.entry_point         entry_point_t
0x00128000  0x8        boot_ram_head.app                        app_info_t
0x00128000  0x4        boot_ram_head.app.ota_base               uint32_t
0x00128004  0x4        boot_ram_head.app.data_base              uint32_t
0x00128008  0x8        boot_ram_head.flash                      flash_info_t
0x00128008  0x2        boot_ram_head.flash.total_size_64k       uint16_t
0x0012800a  0x2        boot_ram_head.flash.multi_read_param     multi_read_param_t
0x0012800a  0x1        boot_ram_head.flash.multi_read_param.cmd uint8_t
0x0012800b  0x1(6:2)   boot_ram_head.flash.multi_read_param.trans_type uint8_t
0x0012800b  0x1(2:4)   boot_ram_head.flash.multi_read_param.wait_cycles uint8_t
0x0012800b  0x1(0:2)   boot_ram_head.flash.multi_read_param.dual_quad uint8_t
0x0012800c  0x4        boot_ram_head.flash.quad_enable_config   quad_enable_config_t
0x0012800c  0x2        boot_ram_head.flash.quad_enable_config.read quad_status_rw_t
0x0012800c  0x1        boot_ram_head.flash.quad_enable_config.read.cmd uint8_t
0x0012800d  0x1(4:4)   boot_ram_head.flash.quad_enable_config.read.quad_bit_offset uint8_t
0x0012800d  0x1(2:2)   boot_ram_head.flash.quad_enable_config.read.status_length uint8_t
0x0012800e  0x2        boot_ram_head.flash.quad_enable_config.write quad_status_rw_t
0x0012800e  0x1        boot_ram_head.flash.quad_enable_config.write.cmd uint8_t
0x0012800f  0x1(4:4)   boot_ram_head.flash.quad_enable_config.write.quad_bit_offset uint8_t
0x0012800f  0x1(2:2)   boot_ram_head.flash.quad_enable_config.write.status_length uint8_t

address     size       variable name                            type
0x00129814  0x100      image1_header                            ota_image_header_t
0x00129814  0xc        image1_header.s                          ota_image_header_struct_t
0x00129814  0x4        image1_header.s.valid_flag               uint32_t
0x00129818  0x4        image1_header.s.crc32                    uint32_t
0x0012981c  0x4        image1_header.s.image_length             uint32_t
0x00129814  0x100      image1_header.a                          array[256] of uint8_t

address     size       variable name                            type
0x0012940c  0x4        ota_debug_show                           uint32_t

address     size       variable name                            type
0x001293c0  0x4        read_buf                                 pointer to uint8_t

address     size       variable name                            type
0x00129410  0x400      l_crc32_table                            array[256] of long unsigned int

address     size       variable name                            type
0x00000000  0x8        app_info                                 app_info_t
0x00000000  0x4        app_info.ota_base                        uint32_t
0x00000004  0x4        app_info.data_base                       uint32_t

address     size       variable name                            type
0x00000000  0x4        error                                    uint32_t

address     size       variable name                            type
0x00000000  0x8        flash_info                               flash_info_t
0x00000000  0x2        flash_info.total_size_64k                uint16_t
0x00000002  0x2        flash_info.multi_read_param              multi_read_param_t
0x00000002  0x1        flash_info.multi_read_param.cmd          uint8_t
0x00000003  0x1(6:2)   flash_info.multi_read_param.trans_type   uint8_t
0x00000003  0x1(2:4)   flash_info.multi_read_param.wait_cycles  uint8_t
0x00000003  0x1(0:2)   flash_info.multi_read_param.dual_quad    uint8_t
0x00000004  0x4        flash_info.quad_enable_config            quad_enable_config_t
0x00000004  0x2        flash_info.quad_enable_config.read       quad_status_rw_t
0x00000004  0x1        flash_info.quad_enable_config.read.cmd   uint8_t
0x00000005  0x1(4:4)   flash_info.quad_enable_config.read.quad_bit_offset uint8_t
0x00000005  0x1(2:2)   flash_info.quad_enable_config.read.status_length uint8_t
0x00000006  0x2        flash_info.quad_enable_config.write      quad_status_rw_t
0x00000006  0x1        flash_info.quad_enable_config.write.cmd  uint8_t
0x00000007  0x1(4:4)   flash_info.quad_enable_config.write.quad_bit_offset uint8_t
0x00000007  0x1(2:2)   flash_info.quad_enable_config.write.status_length uint8_t

address     size       variable name                            type
0x00000000  0x4        unloaded_area                            pointer to unloaded_area_tag

address     size       variable name                            type
0x00129810  0x4        dmac_inst_env                            pointer to app_dmac_inst_t

address     size       variable name                            type
0x00129388  0x18       dmac_universal_func                      const periph_universal_func_set_t
0x00129388  0x4        dmac_universal_func.intr_op_func         intr_op_func_t
0x0012938c  0x4        dmac_universal_func.sw_rst_func          sw_rst_func_t
0x00129390  0x4        dmac_universal_func.clk_src_cfg_func     clk_src_cfg_func_t
0x00129394  0x4        dmac_universal_func.clk_gate_func        clk_gate_func_t
0x00129398  0x4        dmac_universal_func.pin_cfg_func         pin_cfg_func_t
0x0012939c  0x4        dmac_universal_func.sys_stat_func        sys_stat_func_t

address     size       variable name                            type
0x001293a0  0x18       qspi_universal_func                      const periph_universal_func_set_t
0x001293a0  0x4        qspi_universal_func.intr_op_func         intr_op_func_t
0x001293a4  0x4        qspi_universal_func.sw_rst_func          sw_rst_func_t
0x001293a8  0x4        qspi_universal_func.clk_src_cfg_func     clk_src_cfg_func_t
0x001293ac  0x4        qspi_universal_func.clk_gate_func        clk_gate_func_t
0x001293b0  0x4        qspi_universal_func.pin_cfg_func         pin_cfg_func_t
0x001293b4  0x4        qspi_universal_func.sys_stat_func        sys_stat_func_t

address     size       variable name                            type
0x001293b8  0x4        cache_clk_gate_func                      const clk_gate_func_t

address     size       variable name                            type
0x001293bc  0x4        cache_sys_stat_func                      const sys_stat_func_t

address     size       variable name                            type
0x001299a0  0x4        _next

address     size       variable name                            type
0x00000000  0x1        pwr_pwm_2                                _Bool

address     size       variable name                            type
0x001293d8  0x18       qspi_inst                                app_qspi_inst_t
0x001293d8  0x4        qspi_inst.inst                           periph_inst_t
0x001293d8  0x4        qspi_inst.inst.init_func                 pointer to function 
0x001293dc  0xc        qspi_inst.param                          app_qspi_init_param_t
0x001293dc  0x2        qspi_inst.param.clk_div                  uint16_t
0x001293de  0x1        qspi_inst.param.rxsample_dly             uint8_t
0x001293df  0x2        qspi_inst.param.multi_read               multi_read_param_t
0x001293df  0x1        qspi_inst.param.multi_read.cmd           uint8_t
0x001293e0  0x1(6:2)   qspi_inst.param.multi_read.trans_type    uint8_t
0x001293e0  0x1(2:4)   qspi_inst.param.multi_read.wait_cycles   uint8_t
0x001293e0  0x1(0:2)   qspi_inst.param.multi_read.dual_quad     uint8_t
0x001293e1  0x1        qspi_inst.param.clk_pin_no               uint8_t
0x001293e2  0x4        qspi_inst.param.data_pin_no              array[4] of uint8_t
0x001293e6  0x1      * qspi_inst.param.cs_pin_no                array[1] of uint8_t
0x001293e8  0x4        qspi_inst.reg                            pointer to reg_ssi_t
0x001293ec  0x1        qspi_inst.qspi_lock                      periph_lock_t
0x001293ed  0x1        qspi_inst.idx                            uint8_t

address     size       variable name                            type
0x001293f0  0x14       dmac_inst                                app_dmac_inst_t
0x001293f0  0x4        dmac_inst.inst                           periph_inst_t
0x001293f0  0x4        dmac_inst.inst.init_func                 pointer to function 
0x001293f4  0x8        dmac_inst.env                            dmac_env_t
0x001293f4  0x4        dmac_inst.env.ch                         pointer to dmac_ch_env_t
0x001293f8  0x1        dmac_inst.env.ch_num                     uint8_t
0x001293f9  0x1      * dmac_inst.env.ch_stat                    uint8_t
0x001293fc  0x4        dmac_inst.reg                            pointer to reg_dmac_t
0x00129400  0x1        dmac_inst.idx                            uint8_t

