#include<stdio.h>
#include<ruby.h>

VALUE cFoo;

void Init_foo()
{
  puts("Init_fooですよ");

  rb_define_class("Foo", rb_cObject);
}
