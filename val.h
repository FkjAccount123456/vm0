/*
注意分清Copy和Clone
*/
#ifndef VAL_H
#define VAL_H

#include <stddef.h>

char *str_clone(char *base);

// 传递时复制构造
typedef struct {
  size_t size, max;
  char *val;
} String;

// base会被复制
String *String_new(char *base);
String *String_clone(String *base);
void String_append(String *str, char ch);
void String_cat(String *str, String *other);
void String_free(String *str);

typedef struct Val Val;

// 默认传递引用，所以需要引用计数
// 传递时必须调用Copy
typedef struct {
  size_t *rc;
  size_t size, max;
  Val *val;
} Vec;

Vec *Vec_new();
Vec *Vec_clone(Vec *vec);
Vec *Vec_copy(Vec *vec);
// Val会被Copy
void Vec_append(Vec *vec, Val val);
// rc归零才会真正被回收
void Vec_free(Vec *vec);
void Vec_print(Vec *vec);

typedef enum {
  IntVal,
  StrVal,
  VecVal,
} ValType;

typedef struct Val {
  ValType tp;
  union {
    long long i;
    String *s;
    Vec *v;
  };
} Val;

Val Val_int(long long i);
// 不会Clone，直接传递
Val Val_String(String *s);
// 不会Clone，直接传递
Val Val_Vec(Vec *vec);
Val Val_copy(Val v);
Val Val_clone(Val v);
void Val_print(Val v);
void Val_free(Val v);

#endif
