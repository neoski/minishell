#include <unistd.h>
#include <stdlib.h>
#include "shell.h"

int	add_elem_to_exec(char **exec, char *wanted)
{
  int	i;

  i = 0;
  while (exec[i] && exec[i][0])
    ++i;
  if (wanted != NULL)
    {
      my_strcpy(exec[i], wanted, 0);
      exec[i + 1][0] = '\0';
    }
  else
    exec[i] = NULL;
  return (0);
}

int	check_if_reverse_redir(char **board, int i)
{
  char	*tmp;

  if ((((board[i][0] == '<' || board[i][0] == '>') && !board[i][1])
       || (((board[i][0] == '<' && board[i][1] == '<') ||
	    (board[i][0] == '>' && board[i][1] == '>'))
	   && !board[i][2])) && board[i + 1] && board[i + 2] &&
          board[i + 2][0] != '<' && board[i + 2][0] != '>'
      && board[i + 2][0] != '|')
    {
      if ((tmp = malloc(my_strlen(board[i + 2]) + 1)) == NULL)
	return (-1);
      my_strcpy(tmp, board[i + 2], 0);
      my_strcpy(board[i + 2], board[i + 1], 0);
      my_strcpy(board[i + 1], board[i], 0);
      my_strcpy(board[i], tmp, 0);
      free(tmp);
    }
  return (0);
}

int	build_exec(t_shell *s, char **board, int i, int key)
{
  int	y;

  y = 0;
  if ((s->exec = my_double_malloc(NULL, env_size(board) + 1,
				  max_env_col(board, 1, 0))) == NULL)
    return (-1);
  if (s->exec[y])
    s->exec[y][0] = '\0';
  if (!board[i])
    return (0);
  if (check_if_reverse_redir(board, 0) == -1)
    return (-1);
  while (board[i] && key == 0)
    {
      if (board[i][0] == '>' || board[i][0] == '<' || board[i][0] == '|')
	key = 1;
      else
	my_strcpy(s->exec[y], board[i], 0);
      if (key != 1)
	++y;
      ++i;
    }
  s->exec[y][0] = '\0';
  return (0);
}
