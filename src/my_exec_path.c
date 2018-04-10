#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

int	check_if_path_exist(t_shell *s)
{
  if (s->path != NULL)
    free(s->path);
  if ((s->path = my_getenv(s->my_env, "PATH=", NULL)) == NULL)
    {
      my_putstr("Error : Var PATH not found in the **env.\n", 2);
      return (-1);
    }
  return (0);
}

char	*my_exec_path(t_shell *s, char *command, int i, int y)
{
  char	*res;

  if (check_if_path_exist(s) == -1)
    return (NULL);
  if ((res = malloc(my_strlen(s->path) + my_strlen(command))) == NULL)
    return (NULL);
  while (s->path[i])
    {
      while (s->path[i] && s->path[i] != ':')
	res[y++] = s->path[i++];
      res[y++] = '/';
      my_strcpy(res, command, y);
      if (access(res, X_OK) == 0)
	return (res);
      if (s->path[i] == ':')
	i++;
      y = 0;
    }
  my_putstr("Cannot find the command ", 2);
  my_putstr(command, 2);
  my_putstr("\n", 2);
  return (NULL);
}
