#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

int	restore_std(t_shell *s)
{
  if ((dup2(s->stdout, 1)) == -1 || (dup2(s->stdin, 0)) == -1)
    return (-1);
  s->fdkey = 0;
  if (s->tmpfd != -1)
    {
      close(s->tmpfd);
      s->tmpfd = -1;
    }
  return (0);
}

int	ini_struct(t_shell *s, char **env)
{
  if ((s->my_env = env_cpy(NULL, env)) == NULL)
    return (-1);
  s->path = NULL;
  s->alias = NULL;
  s->oldpwd = NULL;
  s->home = NULL;
  s->tmpfd = -1;
  s->tmpid = 0;
  s->pwd = my_getenv(s->my_env, "PWD=", NULL);
  s->fdkey = 0;
  if ((s->stdout = dup(1)) == -1)
    return (-1);
  if ((s->stdin = dup(0)) == -1)
    return (-1);
  return (0);
}
