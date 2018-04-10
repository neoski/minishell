#include <stdlib.h>
#include "shell.h"

char	*res_not_finish(char *res, int i)
{
  int	y;
  char	*new;

  y = 0;
  if ((new = malloc(my_strlen(res))) == NULL)
    return (NULL);
  ++i;
  while (res[i])
    new[y++] = res[i++];
  new[y] = '\0';
  free(res);
  return (new);
}

char	*check_if_semicolon(char *res, int *i)
{
  while (res[*i] && res[*i] != ';')
    *i += 1;
  if (res[*i] == ';')
    {
      if ((res = res_not_finish(res, *i)) == NULL)
	return (NULL);
      *i = 0;
    }
  return (res);
}
