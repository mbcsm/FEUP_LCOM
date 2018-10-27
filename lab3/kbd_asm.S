#include <machine/asm.h>
#include "i8042.h"

.intel_syntax

.global _C_LABEL(kbd_asm_ih)

.data

_C_LABEL(st):
.long 0

_C_LABEL(OBF_content):
.long 0 

.text
_C_LABEL(kbd_asm_ih):/*
in al, STAT_REG
and al, OBF
mov cl, al
cmp cl, 1
jne return
mov eax, OUT_BUF
mov cl, (cl & (PAR_ERR | TO_ERR))
cmp cl, 0
jne return
mov _C_LABEL(OBF_content), eax
jmp end
return: mov _C_LABEL(OBF_content), 0*/
end: ret

