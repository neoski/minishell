#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "shell.h"

int	case_first_exec(t_shell *s)
{
  if ((s->tmpid = fork()) == -1)
    return (my_putstr("Fork problem : Couldn't create a new processus.\n", 2));
  if (s->tmpid == 0)
    if (execve(s->path_res, s->exec, s->my_env) == -1)
      return (my_putstr("Execve error : Couldn't exec the command.\n", 2));
  if (s->path_res != s->exec[0])
    free(s->path_res);
  return (0);
}
