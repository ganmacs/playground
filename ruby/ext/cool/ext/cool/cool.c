#include "cool.h"

VALUE rb_mCool;

void
Init_cool(void)
{
  rb_mCool = rb_define_module("Cool");
}
