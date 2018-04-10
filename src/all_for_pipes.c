#include <signal.h>
#include <unistd.h>
#include "shell.h"

int	do_pipe(t_shell *s, int i)
{
  int	fd[2];

  pipe(fd);
  s->fdkey = 1;
  while (i != 0 && s->board[i - 1][0] != '|')
    --i;
  dup2(fd[1], 1);
  my_double_free(s->exec);
  if (build_exec(s, s->board, i, 0) == -1)
    return (-1);
  if (check_if_flag_after_redir(s->board, s->exec, NULL, i) == -1)
    return (-1);
  check_if_redir(s, i);
  if (i != 0 && check_builtins(s, s->exec[0], 1) == -1)
    return (-1);
  if (i == 0 && check_builtins(s, s->exec[0], 3) == -1)
    return (-1);
  close(fd[1]);
  dup2(fd[0], 0);
  return (0);
}

int	check_for_pipes(t_shell *s, int i)
{
  if (s->board[i] == NULL || s->exec[i] == NULL)
    return (0);
  while (s->board[i])
    if (s->board[i++][0] == '|')
      if (do_pipe(s, i - 1) == -1)
	return (-1);
  while (i != 0 && s->board[i - 1][0] != '|')
    --i;
  dup2(s->stdout, 1);
  my_double_free(s->exec);
  if (build_exec(s, s->board, i, 0) == -1 ||
      check_if_flag_after_redir(s->board, s->exec, NULL, i) == -1)
    return (-1);
  check_if_redir(s, i);
  if (check_builtins(s, s->exec[0], 2) == -1)
    return (-1);
  if (s->tmpid != 0)
    kill(s->tmpid, SIGINT);
  s->tmpid = 0;
  return (0);
}
