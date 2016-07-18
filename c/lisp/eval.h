#ifndef EVAL_H
#define EVAL_H

#include "mlisp.h"

obj_t *eval(env_t **env, obj_t* obj);

obj_t *eval_list(env_t **env, obj_t* obj);

#endif
