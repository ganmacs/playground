#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "env.h"

env_t *new_env(obj_t *val, char* name, env_t *old_env)
{
  env_t *env = malloc(sizeof(env_t));
  env->val = val;
  if (name == NULL) {
    env->name = NULL;
  } else {
    env->name = strdup(name);
  }
  env->next = old_env;
  return env;
}

env_t *init_env()
{
  return new_env(NULL, NULL, NULL);
}

void destroy_env(env_t *env)
{
  while (env != NULL) {
    /* TODO fix that obj_t is leaking */
    env_t *next = env->next;
    free(env);
    env = next;
  }
}

void add_variable(env_t **env, char *name, obj_t *var)
{
  *env = new_env(var, name, *env);
}

obj_t *find_variable(env_t *env, char *name)
{
  for (; env != NULL; env = env->next) {
    if ((env->name != NULL) && !strcmp(env->name, name))
      return env->val;
  }
  return NULL;
}
