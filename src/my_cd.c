#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

int	go_prev_rep(char *res, int *i)
{
  if (res[*i] == '/' && *i > 0)
    *i -= 1;
  while (res[*i] != '/' && *i > 0)
    *i -= 1;
  return (0);
}

int	put_rep(char *where, char *res, int *i, int *y)
{
  if (*i == 0 || res[*i - 1] != '/')
    {
      res[*i] = '/';
      *i += 1;
    }
  while (where[*y] != '/' && where[*y])
    {
      res[*i] = where[*y];
      *y += 1;
      *i += 1;
    }
  return (0);
}

int	change_cd_path(char *res, char *pwd, char *where, int i)
{
  int	y;

  y = 0;
  if (where[i] == '/')
    return (my_strcpy(res, where, 0));
  my_strcpy(res, pwd, 0);
  while (res[i])
    ++i;
  while (where[y])
    {
      if (where[y] == '.')
	{
	  if (where[y + 1] == '.')
	    go_prev_rep(res, &i);
	}
      else if (where[y] != '/')
	put_rep(where, res, &i, &y);
      if (where[y])
	++y;
    }
  if (i == 0 && res[i] == '/')
    ++i;
  res[i] = '\0';
  return (0);
}

int	cd_update_env(t_shell *s, char *res, char *update)
{
  if (s->oldpwd)
    {
      free(s->oldpwd);
      s->oldpwd = NULL;
    }
  if (s->pwd)
    {
      s->oldpwd = my_str_fusion(s->pwd, "\0");
      free(s->pwd);
    }
  s->pwd = res;
  if ((update = my_str_fusion("PWD=", res)) == NULL)
    return (-1);
  if ((s->my_env = update_env(NULL, s->my_env, update, 1)) == NULL)
    return (-1);
  free(update);
  if (s->oldpwd)
    {
      if ((update = my_str_fusion("OLDPWD=", s->oldpwd)) == NULL)
	return (-1);
      if ((s->my_env = update_env(NULL, s->my_env, update, 1)) == NULL)
	return (-1);
      free(update);
    }
  return (0);
}

int	my_cd(t_shell *s, char *where)
{
  char	*res;

  if ((where = check_if_cd_possible(s, where)) == NULL)
    return (0);
  if (where[0] == '-' && where[1] == '\0')
    {
      if (s->oldpwd == NULL)
	return (my_putstr("cd : OLDPWD not set.\n", 4));
      where = s->oldpwd;
      my_putstr(s->oldpwd, 3);
    }
  if ((res = malloc(my_strlen(s->pwd) + my_strlen(where)
		    + my_strlen(s->home) + 3)) == NULL)
    return (-1);
  if (where[0] == '~')
    replace_tilt(res, s->home, where);
  else
    change_cd_path(res, s->pwd, where, 0);
  if (chdir(res) == -1)
    {
      free(res);
      return (my_putstr("Couldn't go into this directory.\n", 4));
    }
  return (cd_update_env(s, res, NULL));
}
