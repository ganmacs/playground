#include <foo.h>

VALUE mFoo;
VALUE cFooServer;
VALUE cFooServer2;

static const rb_data_type_t foo_server_type = {
  "Foo/server",
  {0, xfree, 0,},
  0, 0,
#ifdef RUBY_TYPED_FREE_IMMEDIATELY
  RUBY_TYPED_FREE_IMMEDIATELY,
#endif
};


static VALUE allocate_server(VALUE klass)
{
  return TypedData_Wrap_Struct(klass, &foo_server_type, NULL);
}

static VALUE foo_server_initialize(VALUE self) {
  DATA_PTR(self) = xmalloc(123456*5);
  return self;
}

static void freee2(void *ptr) {
  nghttp2_session *s = ptr;
  nghttp2_session_del(s);
}

static const rb_data_type_t nghttp2_session_type = {
  "Foo/server2",
  {0, freee2, 0,},
  0, 0,
#ifdef RUBY_TYPED_FREE_IMMEDIATELY
  RUBY_TYPED_FREE_IMMEDIATELY,
#endif
};

static VALUE allocate_server2(VALUE klass)
{
  return TypedData_Wrap_Struct(klass, &nghttp2_session_type, NULL);
}

static VALUE foo_server2_initialize(VALUE self) {
  nghttp2_session *session;
  nghttp2_session_callbacks *callbacks;
  /* nghttp2_session_callbacks_new(&callbacks); */

  nghttp2_session_server_new(&session, callbacks, (void *)self);
  /* nghttp2_session_del(session); */
  /* nghttp2_session_callbacks_del(callbacks); */
  DATA_PTR(self) = session;
  return self;
}

struct session {
  nghttp2_session *session;
};

static void freee(void *ptr) {
  struct session *data = ptr;
  nghttp2_session_del(data->session);
  xfree(data);
}

static const rb_data_type_t session_type = {
  "Foo/server3",
  {0, freee, 0,},
  0, 0,
  RUBY_TYPED_FREE_IMMEDIATELY,
};

static VALUE allocate_server3(VALUE klass)
{
  struct session *s;
  return TypedData_Make_Struct(klass, struct session, &session_type, s);
}

static VALUE foo_server3_initialize(VALUE self) {
  struct session *s;
  nghttp2_session_callbacks *callbacks;
  TypedData_Get_Struct(self, struct session, &session_type, s);

  nghttp2_session *session2;
  nghttp2_session_server_new(&session2, callbacks, (void *)self);
  s->session = session2;

  return self;
}

void Init_foo(void)
{
  mFoo = rb_define_module("Foo");

  cFooServer = rb_define_class_under(mFoo, "Server", rb_cObject);
  rb_define_alloc_func(cFooServer, allocate_server);
  rb_define_method(cFooServer, "initialize", foo_server_initialize, 0);

  cFooServer2 = rb_define_class_under(mFoo, "Server2", rb_cObject);
  rb_define_alloc_func(cFooServer2, allocate_server2);
  rb_define_method(cFooServer2, "initialize", foo_server2_initialize, 0);

  /* rb_define_alloc_func(cFooServer2, allocate_server3); */
  /* rb_define_method(cFooServer2, "initialize", foo_server3_initialize, 0); */
}
