#include <ruby/ruby.h>
#include "hello.hpp"

int hello(int x);

VALUE hello_wrapper(VALUE self, VALUE val_a) {
    int a = FIX2INT(val_a);
    int b = hello(a);
    return INT2FIX(b);
}

extern "C" void Init_test() {
    VALUE top_module = rb_define_module("Test");
    VALUE core_module = rb_define_module_under(top_module, "Core");
    VALUE server_module = rb_define_class_under(core_module, "Server", rb_cObject);

    rb_define_method(server_module, "start", RUBY_METHOD_FUNC(hello_wrapper), 1);
}
