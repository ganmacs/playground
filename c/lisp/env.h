#ifndef MLISP_ENV_H
#define MLISP_ENV_H

#include "mlisp.h"

env_t *init_env();

env_t *new_env(obj_t *val, char* name, env_t *old_env);

void destroy_env(env_t *env);

void add_variable(env_t **env, char *name, obj_t *var);

obj_t *find_variable(env_t *env, char *name);

#endif
