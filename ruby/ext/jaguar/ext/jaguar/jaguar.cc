#include "jaguar.hpp"

VALUE top_module = Qnil;
VALUE core_module = Qnil;

extern "C" void Init_jaguar() {
    top_module = rb_define_module("Jaguar");
    core_module = rb_define_module_under(top_module, "Core");

    Init_Socket();
}
