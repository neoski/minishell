#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "shell.h"

int	check_if_redir_here(char **board, char *redir, int i)
{
  int	y;

  while (board[i] != NULL && board[i][0] != '|')
    {
      if ((y = str_compar(board[i], redir, 0)) != 0 && board[i][y] == '\0'
	  && board[i + 1] != NULL)
	return (i + 1);
      ++i;
    }
  return (0);
}

int	redir_right(t_shell *s, int i)
{
  while (s->board[i] && s->board[i][0] != '|')
    {
      if (s->board[i - 1][0] == '>')
	{
	  if (s->tmpfd != -1)
            close(s->tmpfd);
	  if (s->board[i - 1][1] == '>' && s->board[i] &&
	      (s->tmpfd = open(s->board[i], O_APPEND | O_WRONLY)) != -1)
	    ;
	  else
	    if ((s->tmpfd = open(s->board[i], O_CREAT | O_TRUNC | O_WRONLY,
				 S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR)) == -1)
	      return (my_putstr("Couldn't open.\n", 2));
	}
      ++i;
    }
  dup2(s->tmpfd, 1);
  s->fdkey = 1;
  return (0);
}

int	redir_left(t_shell *s, int i, int y, int key)
{
  s->tmpfd = -1;
  while (s->board[i] && s->board[i][0] != '|')
    {
      if (s->board[i - 1][0] == '<')
        {
          if (s->tmpfd != -1)
            close(s->tmpfd);
          if (s->board[i - 1][1] == '<' && s->board[i])
	    double_redir_left(s, i, &key);
          else if (s->board[i])
            {
              if ((s->tmpfd = open(s->board[i], O_RDONLY)) == -1)
		return (my_putstr("couldn't open the file next '<'\n", 2));
	      key = 0;
            }
        }
      ++i;
    }
  if (key == 1 || (s->tmpfd = open(s->board[y], O_RDONLY)) == -1)
    return (0);
  dup2(s->tmpfd, 0);
  s->fdkey = 1;
  return (0);
}

int	check_if_flag_after_redir(char **board, char **exec, char *tmp, int i)
{
  while (board[i] && board[i][0] != '|')
    {
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
	  my_strcpy(board[i++], tmp, 0);
	  add_elem_to_exec(exec, tmp);
	  while (board[i + 2] && board[i + 2][0] != '>' &&
		 board[i + 2][0] != '<' && board[i + 2][0] != '|')
	    add_elem_to_exec(exec, board[2 + i++]);
	  free(tmp);
	}
      else
	++i;
    }
  return (0);
}

int	check_if_redir(t_shell *s, int z)
{
  int	i;
  int	y;

  if ((i = check_if_redir_here(s->board, ">", z)) > 0 ||
      (y = check_if_redir_here(s->board, ">>", z)) > 0)
    {
      y = check_if_redir_here(s->board, ">>", z);
      if ((i <= y && i != 0) || y == 0)
	redir_right(s, i);
      else
	redir_right(s, y);
    }
  if ((i = check_if_redir_here(s->board, "<", z)) > 0 ||
      (y = check_if_redir_here(s->board, "<<", z)) > 0)
    {
      y = check_if_redir_here(s->board, "<<", z);
      if ((i <= y && i != 0) || y == 0)
        redir_left(s, i, i, 0);
      else
	redir_left(s, y, y, 0);
    }
  add_elem_to_exec(s->exec, NULL);
  return (0);
}
