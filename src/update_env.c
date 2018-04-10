#include <stdlib.h>
#include "shell.h"

int	check_if_same_elem(char *str, char *wanted)
{
  int	i;

  i = 0;
  while (str[i] && wanted[i] && str[i] != '=' && wanted[i] == str[i])
    i++;
  if (str[i] == '=' && wanted[i] == '=')
    return (1);
  else
    return (0);
}

int	add_env_elem(char **env, char *newvar, int env_size, int i)
{
  while (i != env_size)
    {
      if (check_if_same_elem(env[i], newvar) == 1)
	{
	  my_strcpy(env[i], newvar, 0);
	  env[env_size] = NULL;
	  return (0);
	}
      i++;
    }
  if (i == env_size)
    my_strcpy(env[i++], newvar, 0);
  env[i] = NULL;
  return (0);
}

int	del_env_elem(char **res, char **env, char *delelem, int i)
{
  int	y;
  int	z;

  z = 0;
  while (env[i])
    {
      y = 0;
      if (check_if_same_elem(env[i], delelem) != 1)
	{
	  while (env[i][y])
	    {
	      res[z][y] = env[i][y];
	      ++y;
	    }
	  res[z][y] = '\0';
	  ++z;
	}
      ++i;
    }
  res[z] = NULL;
  return (0);
}

char	**update_env(char **res, char **env, char *newvar, int key)
{
  int	sizecol;

  if (key == 1)
    {
      sizecol = max_env_col(env, 1, 0);
      if (sizecol < my_strlen(newvar) + 1)
	sizecol = my_strlen(newvar) + 1;
      if ((res =
	   my_double_malloc(res, env_size(env) + 1, sizecol)) == NULL)
	return (NULL);
      do_env_cpy(env, res, 2);
      add_env_elem(res, newvar, env_size(env), 0);
    }
  else
    {
      sizecol = max_env_col(env, 1, 0);
      if ((res =
	   my_double_malloc(res, env_size(env), sizecol)) == NULL)
	return (NULL);
      del_env_elem(res, env, newvar, 0);
    }
  my_double_free(env);
  return (res);
}
