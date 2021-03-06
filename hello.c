#include <assert.h>
#include <node_api.h>
#include <stdio.h>

typedef struct Vector2 {
    float x;                // Vector x component
    float y;                // Vector y component
} Vector2;

static napi_value hello(napi_env env, napi_callback_info info) {
  size_t argc = 1;
  napi_value argv[argc];

  napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  if (argc < 1) {
    napi_throw_error(env, "EINVAL", "Too few arguments to hello()");
    return NULL;
  }

  int64_t* ptr = 0;
  napi_get_value_int64(env, argv[0], ptr);

  Vector2* v = (Vector2*) ptr;
  printf("Vector2 in C: (%f, %f)\n", v->x, v->y);

  return NULL;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

static napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor desc = DECLARE_NAPI_METHOD("hello", hello);
  status = napi_define_properties(env, exports, 1, &desc);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)