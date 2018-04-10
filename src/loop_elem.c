#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"

static int	check_if_end(char *res, char *str)
{
  int		size;

  size = my_strlen(str);
  if (res[size] == '\0')
    return (1);
  return (0);
}

static int	exec_command(t_shell *s, int i, int key)
{
  pid_t		pid;

  if (s->exec[0][0] == '/' || (s->exec[0][0] == '.' && s->exec[0][1] == '/'))
    {
      s->path_res = s->exec[0];
      if (access(s->path_res, X_OK) != 0)
        return (my_putstr("Command not found.\n", 4));
    }
  else
    if ((s->path_res = my_exec_path(s, s->exec[0], 0, 0)) == NULL)
      return (0);
  if (key == 3)
    return (case_first_exec(s));
  if ((pid = fork()) == -1)
    return (my_putstr("Fork problem : Couldn't create a new processus.\n", 2));
  if (pid == 0)
    if (execve(s->path_res, s->exec, s->my_env) == -1)
      return (my_putstr("Execve error : Couldn't exec the command.\n", 2));
  if (key == 2 && waitpid(pid, &i, 0) == -1)
    return (my_putstr("Fatal wait error : Couldn't wait end of proc.\n", 2));
  if (s->path_res != s->exec[0])
    free(s->path_res);
  return (0);
}

static int	config_exit_value(t_shell *s)
{
  s->fdkey = 2;
  if (s->board[1])
    s->tmpfd = my_getnbr(s->board[1]);
  else
    s->tmpfd = 0;
  return (0);
}

int	check_builtins(t_shell *s, char *res, int key)
{
  if (s->exec[0] == NULL)
    return (0);
  if (str_compar(res, "exit", 0) && check_if_end(res, "exit"))
    return (config_exit_value(s));
  if (str_compar(res, "printalias", 0) && check_if_end(res, "printalias"))
    return (printboard(s->alias, 0));
  if (str_compar(res, "delalias", 0) && check_if_end(res, "delalias"))
    return (del_alias_elem(s));
  if (str_compar(res, "alias", 0) && check_if_end(res, "alias"))
    return (update_alias(s));
  if (str_compar(res, "unsetenv", 0) && check_if_end(res, "unsetenv"))
    return (my_unsetenv(s, s->exec[1]));
  if (str_compar(res, "setenv", 0) && check_if_end(res, "setenv"))
    return (my_setenv(s, s->exec[1]));
  if (str_compar(res, "env", 0) && s->exec[1] == NULL)
    return (printboard(s->my_env, 0));
  if (str_compar(res, "cd", 0) && check_if_end(res, "cd"))
    return (my_cd(s, s->exec[1]));
  if (str_compar(res, "pwd", 0) && check_if_end(res, "pwd"))
    return (my_putstr(s->pwd, 3));
  if (s->exec[1] && str_compar(s->exec[0], "env", 0) &&
      check_if_end(s->exec[0], "env") && str_compar(s->exec[1], "-0", 0)
      && check_if_end(s->exec[1], "-0"))
    return (printboard(s->my_env, 1));
  return (exec_command(s, 0, key));
}

int	loop_elem(t_shell *s, char *res)
{
  if ((res = check_if_alias(s, res, 0)) == NULL)
    return (-1);
  if (build_board(s, res) == -1)
    return (my_putstr("Couldn't alloc memory.\n", 2));
  if (check_for_pipes(s, 0) == -1)
    return (-1);
  my_double_free(s->exec);
  my_double_free(s->board);
  return (0);
}
