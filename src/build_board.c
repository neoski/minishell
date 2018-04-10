#include <stdlib.h>
#include "shell.h"

int	max_args(char *str, int res, int i)
{
  while (str[i])
    {
      if (str[i] == ' ' || str[i] == '\t')
        ++res;
      while (str[i] == ' ' || str[i] == '\t')
	++i;
      if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
	  res += 1;
	  while (str[i] == '|' || str[i] == '>' || str[i] == '<')
	    ++i;
	  if (str[i])
	    ++res;
	}
      if (str[i] == '"')
	++res;
      if (str[i])
	++i;
    }
  return (res);
}

int	complete_board(char **board, char *str, int i, int y)
{
  int	z;

  while (str[i] && str[i] != ';' && board[y])
    {
      z = 0;
      while (str[i] == ' ' || str[i] == '\t')
	i++;
      if (str[i] == '"')
	{
	  ++i;
	  while (str[i] != '"' && str[i])
	    board[y][z++] = str[i++];
	  if (str[i] == '"')
	    ++i;
	}
      else
	while (str[i] && str[i] != ' ' && str[i] != ';' && str[i] != '\t'
	       && str[i] != '>' && str[i] != '<' && str[i] != '|')
	  board[y][z++] = str[i++];
      board[y][z] = 0;
      case_redir(board, str, &i, &y);
    }
  board[y] = NULL;
  return (0);
}

int	build_board(t_shell *s, char *str)
{
  int	args;
  int	col;

  args = max_args(str, 1, 0);
  col = my_strlen(str);
  if ((s->board = my_double_malloc(NULL, args, col)) == NULL)
    return (-1);
  complete_board(s->board, str, 0, 0);
  if (build_exec(s, s->board, 0, 0) == -1)
    return (-1);
  return (0);
}
