#include <machine/asm.h>
#include "i8042.h"

.intel_syntax

.global _C_LABEL(kbd_asm_ih)

.global _C_LABEL(data_obf)

.data
_C_LABEL(data_obf):
.short

.text
_C_LABEL(kbd_asm_ih):
    xor eax, eax
    in  al, STAT_REG
    mov cl, al
    test cl, OBF
    jz return
    in al, OUT_BUF
    test cl, PAR_ERR
    jnz return
    test cl, TO_ERR
    jnz return
    mov _C_LABEL(data_obf), al
    jmp end
return: 
    mov al, 0x11
    mov _C_LABEL(data_obf), al
end:
    ret
