; Put your custom ASM code for your hack into this file.

; You can also .include other ASM files into this one. For example:
;.include "includes/skip_intro.asm"
;.include "includes/bgm_file.asm"


;.include "includes/bgm_file.asm"


.include "includes/skip_intro.asm"

.open "sys/main.dol"

    .org @NextFreeSpace ;let assembler decide where this can fit
        .include "../../TWW_Practice_Rom/main.c"

    .org 0x80006458 ;0x8000645c ; inject code to branch to test_code
        bl _main_loop

    .org 0x80006450 ; remove original calls to mDoAud_Execute and fapGm_Execute
        nop
        nop
    
.close