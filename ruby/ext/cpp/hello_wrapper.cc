#include <ruby/ruby.h>
#include "hello.hpp"

int hello(int x);

VALUE hello_wrapper(VALUE self, VALUE val_a) {
    int a = FIX2INT(val_a);
    int b = hello(a);
    return INT2FIX(b);
}

void Hello_free(Hello *hello) {
    hello->~Hello();
}

VALUE Hello_alloc(VALUE cls) {
    Hello *hello = new Hello();
    return Data_Wrap_Struct(cls, nullptr, Hello_free, hello);
}

VALUE Hello_init(VALUE self, VALUE n) {
    Hello* p;
    Data_Get_Struct(self, Hello, p);
    p->n_ = FIX2INT(n);
    return Qnil;
}

VALUE Hello_say(VALUE self) {
    Hello* p;
    Data_Get_Struct(self, Hello, p);

    p->say();
    return Qnil;
}

extern "C" void Init_test() {
    VALUE top_module = rb_define_module("Test");
    VALUE core_module = rb_define_module_under(top_module, "Core");
    VALUE server_module = rb_define_class_under(core_module, "Server", rb_cObject);
    VALUE hello_module = rb_define_class_under(core_module, "Hello", rb_cObject);

    rb_define_method(server_module, "start", RUBY_METHOD_FUNC(hello_wrapper), 1);

    rb_define_alloc_func(hello_module, Hello_alloc);
    rb_define_method(hello_module, "initialize", RUBY_METHOD_FUNC(Hello_init), 1);
    rb_define_method(hello_module, "say", RUBY_METHOD_FUNC(Hello_say), 0);

    // rb_define_method(hello_module, "start", RUBY_METHOD_FUNC(hello_wrapper), 1);
}
