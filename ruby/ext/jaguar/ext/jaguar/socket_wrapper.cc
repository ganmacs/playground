#pragma once

#include "socket_wrapper.hpp"
#include <errno.h>

VALUE jaguar_WouldBlock = Qnil;


void Socket_free(Socket *socket) {
    socket->~Socket();
    xfree(socket);
}

VALUE Socket_alloc(VALUE self) {
    void* sock = xmalloc(sizeof(Socket));
    Socket *s = new (sock) Socket("127.0.0.1", 3000);
    return Data_Wrap_Struct(self, nullptr, Socket_free, sock);
}


VALUE Socket_connect(VALUE self) {
    Socket* p;
    Data_Get_Struct(self, Socket, p);
    auto rv = p->connect();

    if (rv == -1) {
        if (errno == EINPROGRESS) {
            rb_raise(jaguar_WouldBlock, "socket would block");
        } else {
            rb_raise(rb_eStandardError, "while socket connecting: %s", strerror(errno));
        }
    }

    return INT2FIX(rv);
}

VALUE Socket_request(VALUE self, VALUE message) {
    Check_Type(message, T_STRING);

    Socket* p;
    Data_Get_Struct(self, Socket, p);

    std::string s {StringValueCStr(message)};
    auto rv = p->request(s);
    return INT2FIX(rv);
}

extern "C" void Init_Socket() {
    VALUE socket_class = rb_define_class_under(core_module, "Socket", rb_cObject);
    jaguar_WouldBlock = rb_define_class_under(socket_class, "WouldBlock", rb_eStandardError);

    rb_define_alloc_func(socket_class, Socket_alloc);
    rb_define_method(socket_class, "connect", RUBY_METHOD_FUNC(Socket_connect), 0);
    rb_define_method(socket_class, "request", RUBY_METHOD_FUNC(Socket_request), 1);
}
