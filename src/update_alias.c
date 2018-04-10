#include <stdlib.h>
#include "shell.h"

static int	check_alias_error(char **board)
{
  if (board[1] == NULL || board[2] == NULL || board[3] == NULL)
    {
      my_putstr("Missing alias. Correct use : alias name = value\n", 2);
      return (-1);
    }
  if (board[4] != NULL)
    {
      my_putstr("Too much args. Correct use : alias name = value\n", 2);
      return (-1);
    }
  if ((board[1][0] == '"' && board[1][1] == '\0') ||
      (board[1][0] == '"' && board[1][1] == '"') ||
      board[2][0] != '=' || board[2][1] != '\0' ||
      (board[3][0] == '"' && board[3][1] == '\0') ||
      (board[3][0] == '"' && board[3][1] == '"'))
    {
      my_putstr("Missing args. Correct use : alias name = value\n", 2);
      return (-1);
    }
  return (0);
}

char	**first_alias(char **res, char *new)
{
  int	i;

  i = 0;
  if ((res = my_double_malloc(NULL, 2, my_strlen(new) + 1)) == NULL)
    return (NULL);
  while (new[i])
    {
      res[0][i] = new[i];
      ++i;
    }
  res[0][i] = '\0';
  res[1] = NULL;
  return (res);
}

char	**add_alias(char **res, char **alias, char *new)
{
  int	sizecol;

  sizecol = max_env_col(alias, 1, 0);
  if (sizecol < my_strlen(new) + 1)
    sizecol = my_strlen(new) + 1;
  if ((res =
       my_double_malloc(NULL, env_size(alias) + 1, sizecol)) == NULL)
    return (NULL);
  do_env_cpy(alias, res, 2);
  add_env_elem(res, new, env_size(alias), 0);
  my_double_free(alias);
  return (res);
}

int	update_alias(t_shell *s)
{
  char	*tmp;
  char	*new;

  if (check_alias_error(s->board) == -1)
    return (0);
  if ((tmp = my_str_fusion(s->board[1], "=")) == NULL)
    return (-1);
  if ((new = my_str_fusion(tmp, s->board[3])) == NULL)
    return (-1);
  free(tmp);
  if (s->alias == NULL)
    {
      if ((s->alias = first_alias(NULL, new)) == NULL)
	return (-1);
    }
  else
    if ((s->alias = add_alias(NULL, s->alias, new)) == NULL)
      return (-1);
  free(new);
  return (0);
}
