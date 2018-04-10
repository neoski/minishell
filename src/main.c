#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "shell.h"

static int	loop(t_shell *s, char *res, int key, int i)
{
  while (key == 0)
    {
      my_putstr("minishell $> ", 1);
      i = 0;
      if ((res = get_next_line(0)) != NULL)
	{
	  while (res[i])
	    {
	      if (loop_elem(s, res) == -1)
		return (0);
	      if ((res = check_if_semicolon(res, &i)) == NULL)
		return (-1);
	      if (s->fdkey == 2)
		return (0);
	      if (s->fdkey == 1)
		restore_std(s);
	    }
	  free(res);
	}
      else
	key = 1;
    }
  return (0);
}

int		main(__attribute__((unused))int ac,
		     __attribute__((unused))char **av, char **env)
{
  t_shell	*s;
  int		tmp;

  tmp = 0;
  signal(SIGINT, ctrlc);
  if ((s = malloc(sizeof(*s))) == NULL)
    return (0);
  if (ini_struct(s, env) == -1)
    return (0);
  loop(s, NULL, 0, 0);
  if (s->my_env != NULL)
    my_double_free(s->my_env);
  if (s->path != NULL)
    free(s->path);
  if (s->pwd != NULL)
    free(s->pwd);
  if (s->home != NULL)
    free(s->home);
  if (s->fdkey == 2)
    tmp = s->tmpfd;
  if (s->alias != NULL && s->alias[0] != NULL)
    my_double_free(s->alias);
  free(s);
  return (tmp);
}
