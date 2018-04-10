#include <stdlib.h>
#include "shell.h"

static int	check_newenv_error(char *newenv, int i, int y)
{
  while (newenv[i])
    {
      if (i != 0 && newenv[i] == '=' && newenv[i + 1])
	++y;
      ++i;
    }
  if (y != 1)
    {
      my_putstr("Error : Bad syntax. Correct use : setenv VAR=value\n", 2);
      return (-1);
    }
  return (0);
}

static int	check_delenv_error(char **env, char *delenv)
{
  int		i;

  i = 0;
  while (env[i])
    if (check_if_same_elem(env[i++], delenv))
      return (0);
  return (my_putstr("Error : This VAR doesn't exist.\n", 2));
}

int	my_unsetenv(t_shell *s, char *delenv)
{
  if (s->my_env == NULL || s->my_env[0] == NULL)
    return (my_putstr("Env list is empty.\n", 4));
  if (delenv == NULL)
    {
      my_putstr("Missing var. Correct use : unsetenv VAR\n", 2);
      return (0);
    }
  if ((delenv = my_str_fusion(delenv, "=")) == NULL)
    return (-1);
  if (check_delenv_error(s->my_env, delenv) == -1)
    {
      free(delenv);
      return (0);
    }
  if ((s->my_env = update_env(NULL, s->my_env, delenv, 2)) == NULL)
    {
      free(delenv);
      return (-1);
    }
  free(delenv);
  return (0);
}

int	my_setenv(t_shell *s, char *newenv)
{
  if (newenv == NULL)
    {
      my_putstr("Missing var. Correct use : setenv VAR=value\n", 2);
      return (0);
    }
  if (check_newenv_error(newenv, 0, 0) == -1)
    return (0);
  if ((s->my_env = update_env(NULL, s->my_env, newenv, 1)) == NULL)
    return (-1);
  return (0);
}
