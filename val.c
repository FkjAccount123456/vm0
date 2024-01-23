#include "val.h"
#include "stdlib.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

char *str_clone(char *base) {
  char *str = (char *)malloc(sizeof(char) * strlen(base));
  strcpy(str, base);
  return str;
}

String *String_new(char *base) {
  String *str = (String *)malloc(sizeof(String));
  str->max = str->size = strlen(base);
  str->val = str_clone(base);
  return str;
}

String *String_clone(String *base) { return String_new(base->val); }

void String_append(String *str, char ch) {
  assert(str);
  if (str->max == str->size) {
    str->max *= 2;
    str->val = (char *)realloc(str->val, (str->max + 1) * sizeof(char));
  }
  str->val[str->size++] = ch;
  str->val[str->size] = '\0';
}

void String_cat(String *str, String *other) {
  assert(str && other);
  size_t new_size = str->size + other->size;
  if (new_size > str->max) {
    str->max = new_size;
    str->val = (char *)realloc(str->val, (str->max + 1) * sizeof(char));
  }
  strcpy(str->val + str->size, other->val);
  str->size = new_size;
}

void String_free(String *str) {
  assert(str);
  free(str->val);
  free(str);
}

Vec *Vec_new() {
  Vec *vec = (Vec *)malloc(sizeof(Vec));
  vec->rc = (size_t *)malloc(sizeof(size_t));
  *vec->rc = 1;
  vec->size = 0;
  vec->max = 8;
  vec->val = (Val *)malloc(sizeof(Val) * vec->max);
  return vec;
}

Vec *Vec_clone(Vec *vec) {
  assert(vec);
  Vec *new = Vec_new();
  for (size_t i = 0; i < vec->size; i++)
    Vec_append(new, vec->val[i]);
  return new;
}

Vec *Vec_copy(Vec *vec) {
  assert(vec);
  Vec *new = (Vec *)malloc(sizeof(Vec));
  new->max = vec->max;
  new->size = vec->size;
  new->val = vec->val;
  new->rc = vec->rc;
  (*vec->rc)++;
  return vec;
}

void Vec_append(Vec *vec, Val val) {
  assert(vec);
  if (vec->max == vec->size) {
    vec->max *= 2;
    vec->val = (Val *)realloc(vec->val, vec->max * sizeof(Val));
  }
  vec->val[vec->size++] = Val_copy(val);
}

void Vec_free(Vec *vec) {
  assert(vec);
  (*vec->rc)--;
  if (!*vec->rc) {
    free(vec->rc);
    for (size_t i = 0; i < vec->size; i++)
      Val_free(vec->val[i]);
    free(vec->val);
  }
  free(vec);
}

void Vec_print(Vec *vec) {
  assert(vec);
  printf("[");
  if (vec->size) {
    Val_print(vec->val[0]);
    for (size_t i = 1; i < vec->size; i++) {
      printf(", ");
      Val_print(vec->val[i]);
    }
  }
  printf("]");
}

Val Val_int(long long i) {
  Val v;
  v.tp = IntVal;
  v.i = i;
  return v;
}

Val Val_String(String *s) {
  assert(s);
  Val v;
  v.tp = StrVal;
  v.s = s;
  return v;
}

Val Val_Vec(Vec *vec) {
  assert(vec);
  Val v;
  v.tp = VecVal;
  v.v = vec;
  return v;
}

Val Val_copy(Val v) {
  Val new;
  new.tp = v.tp;
  if (new.tp == IntVal)
    new.i = v.i;
  else if (new.tp == StrVal)
    new.s = String_clone(v.s);
  else if (new.tp == VecVal)
    new.v = Vec_copy(v.v);
  return new;
}

Val Val_clone(Val v) {
  Val new;
  new.tp = v.tp;
  if (new.tp == IntVal)
    new.i = v.i;
  else if (new.tp == StrVal)
    new.s = String_clone(v.s);
  else if (new.tp == VecVal)
    new.v = Vec_clone(v.v);
  return new;
}

void Val_print(Val v) {
  if (v.tp == IntVal) {
    printf("%lld", v.i);
  } else if (v.tp == StrVal) {
    printf("%s", v.s->val);
  } else if (v.tp == VecVal) {
    Vec_print(v.v);
  } else {
    printf("Unknown value type.\n");
    exit(-1);
  }
}

void Val_free(Val v) {
  if (v.tp == StrVal)
    String_free(v.s);
  else if (v.tp == VecVal)
    Vec_free(v.v);
}
