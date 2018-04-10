#include "shell.h"

int	case_redir(char **board, char *str, int *i, int *y)
{
  int	z;

  z = 0;
  if (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
    {
      *y += 1;
      while (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
	{
	  board[*y][z] = str[*i];
	  *i += 1;
	  ++z;
	}
      board[*y][z] = 0;
    }
  *y += 1;
  return (0);
}
