#include <stdlib.h>
#include "shell.h"

char	*where_is_null(t_shell *s, char *where)
{
  if (s->home != NULL)
    free(s->home);
  if ((s->home = my_getenv(s->my_env, "HOME=", NULL)) == NULL)
    {
      my_putstr("Error : Var HOME not found in the **env.\n", 2);
      return (NULL);
    }
  where = s->home;
  return (where);
}

char	*check_if_cd_possible(t_shell *s, char *where)
{
  if (where == NULL || where[0] == '~')
    {
      if ((where = where_is_null(s, where)) == NULL)
	return (NULL);
    }
  else if (where[0] != '/')
    {
      if (where[0] == '-' && where[1] == '\0')
	return (where);
      if (s->pwd != NULL)
	{
	  free(s->pwd);
	  s->pwd = NULL;
	}
      if ((s->pwd = my_getenv(s->my_env, "PWD=", NULL)) == NULL)
	{
	  my_putstr("Error : Var PWD not found in the **env.\n", 2);
	  return (NULL);
	}
    }
  return (where);
}

int	replace_tilt(char *res, char *home, char *where)
{
  int	y;
  int	i;

  i = 0;
  y = 1;
  my_strcpy(res, home, 0);
  while (res[i])
    ++i;
  while (where[y])
    res[i++] = where[y++];
  res[i] = '\0';
  return (0);
}
