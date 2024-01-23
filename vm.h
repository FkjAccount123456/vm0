#ifndef VM_H
#define VM_H

#include <stddef.h>

typedef enum {
  Exit,
  PushI, Pop, PushS,
  Add, Sub, Mul, Div, Mod,
  Eq, Ne, Gt, Lt, Ge, Le,
  And, Or,
  ListAppend,
  Jz, Jnz, Jmp,
  Call, Ret,
  Print, ReadI, ReadC,
} ByteCode;

void run(ByteCode *code);

#endif
