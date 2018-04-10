#include <stdlib.h>
#include "shell.h"

int	max_env_col(char **env, int res, int tmp)
{
  int	i;

  i = 0;
  while (env[i])
    {
      tmp = my_strlen(env[i++]);
      if (tmp > res)
	res = tmp;
    }
  return (res);
}

int	env_size(char **env)
{
  int	i;

  i = 0;
  while (env[i])
    i++;
  return (i);
}

int	do_env_cpy(char **scr, char **dest, int key)
{
  int	i;
  int	y;

  i = 0;
  while (scr[i])
    {
      y = 0;
      while (scr[i][y])
	{
	  dest[i][y] = scr[i][y];
	  ++y;
	}
      dest[i][y] = '\0';
      ++i;
    }
  if (key == 2)
    dest[i + 1] = NULL;
  else
    dest[i] = NULL;
  return (0);
}

char	**env_cpy(char **res, char **env)
{
  if ((res =
       my_double_malloc(res, env_size(env), max_env_col(env, 1, 0))) == NULL)
    return (NULL);
  do_env_cpy(env, res, 1);
  return (res);
}
