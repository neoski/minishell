#include <stdlib.h>
#include "shell.h"

int	alias_checker(char **alias, char *str, int i, int y)
{
  int	save;
  int	z;

  save = i;
  z = 0;
  while (alias[y])
    {
      while (alias[y][z] == str[i])
	{
	  ++z;
	  ++i;
	  if (alias[y][z] == '=' &&
	      (str[i] == ' ' || str[i] == '\t' ||
	       str[i] == '\0' || str[i] == ';'))
	    return (y);
	}
      i = save;
      z = 0;
      ++y;
    }
  return (-1);
}

char	*place_alias(char *alias, char *res, int i, int y)
{
  int	z;
  char	*new;

  z = 0;
  if ((new = malloc(my_strlen(alias) + my_strlen(res) + 1)) == NULL)
    return (NULL);
  while (alias[y] != '=')
    ++y;
  ++y;
  if (alias[y] == '"')
    ++y;
  while (alias[y] != '"' && alias[y])
    new[z++] = alias[y++];
  while (res[i] && res[i] != '\t' && res[i] != ' ' && res[i] != ';')
    ++i;
  while (res[i])
    new[z++] = res[i++];
  new[z] = '\0';
  return (new);
}

char	*check_if_alias(t_shell *s, char *res, int i)
{
  char	*new;
  int	place;

  if (s->alias == NULL || s->alias[0] == NULL)
    return (res);
  while (res[i] == ' ' || res[i] == '\t')
    ++i;
  if ((place = alias_checker(s->alias, res, i, 0)) == -1)
    return (res);
  if ((new = place_alias(s->alias[place], res, i, 0)) == NULL)
    return (NULL);
  return (new);
}
