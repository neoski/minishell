#include <stdlib.h>
#include "shell.h"

static int	check_del_alias_error(char **board, char **alias, char *tmp)
{
  int		i;

  i = 0;
  if (board[2] != NULL)
    return (my_putstr("Too much args. Correct use : delalias name\n", 2));
  while (alias[i])
    if (check_if_same_elem(alias[i++], tmp))
      return (0);
  return (my_putstr("Error : This alias doesn't exist.\n", 2));
}

int	del_alias_elem(t_shell *s)
{
  char	*tmp;

  if (s->alias == NULL || s->alias[0] == NULL)
    return (my_putstr("Alias list is empty.\n", 4));
  if (s->board[1] == NULL)
    return (my_putstr("Missing name. Correct use : delalias name\n", 4));
  if ((tmp = my_str_fusion(s->board[1], "=")) == NULL)
    return (-1);
  if (check_del_alias_error(s->board, s->alias, tmp) == -1)
    {
      free(tmp);
      return (0);
    }
  if ((s->alias = update_env(NULL, s->alias, tmp, 2)) == NULL)
    {
      free(tmp);
      return (-1);
    }
  free(tmp);
  return (0);
}
