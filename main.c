#include <stdio.h>
#include "val.h"

void test_string() {
  String *s1 = String_new("Hello,");
  String *s2 = String_new("world!");
  printf("(%s)\n", s1->val);
  String_append(s1, ' ');
  printf("(%s)\n", s1->val);
  String_cat(s1, s2);
  printf("(%s)\n", s1->val);
}

void test_vec() {
  Vec *vec = Vec_new();
  for (int i = 0; i < 10; i++) {
    Vec_append(vec, Val_int(i));
    Vec_print(vec);
    puts("");
  }
  Vec_free(vec);
}

int main() {
  // test_string();
  test_vec();
  return 0;
}
