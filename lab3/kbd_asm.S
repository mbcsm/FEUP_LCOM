#include <machine/asm.h>
#include "i8042.h"

.intel_syntax

.global _C_LABEL(kbd_asm_ih)

.data

_C_LABEL(st):
.long 0

_C_LABEL(OBF_DATA):
.long 0 

.text
_C_LABEL(kbd_asm_ih):
in al, STAT_REG
mov dl, OBF
mov cl, al
and cl, dl
cmp cl, 1
jne return
mov cl, al
in al, OUT_BUF
mov dl, (PAR_ERR | TO_ERR)
and cl, dl
cmp cl, 0
jne return
mov _C_LABEL(OBF_DATA), al
jmp end
return: mov al, 0
mov _C_LABEL(OBF_DATA), al
end: ret

