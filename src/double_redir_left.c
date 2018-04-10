#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"
#include "shell.h"

int	complete_file(int fd, char *end)
{
  char	*str;
  int	y;

  while ((str = get_next_line(0)) != NULL)
    {
      if ((y = str_compar(str, end, 0)) > 0 && str[y] == '\0')
	{
	  free(str);
	  return (0);
	}
      write(fd, str, my_strlen(str));
      write(fd, "\n", 1);
      free(str);
    }
  return (0);
}

int	double_redir_left(t_shell *s, int i, int *key)
{
  *key = 1;
  if ((s->tmpfd = open("/tmp/redirtmp.c", O_CREAT | O_WRONLY | O_TRUNC,
		       S_IROTH | S_IRGRP | S_IRUSR | S_IWUSR)) == -1)
    return (my_putstr("Couldn't open.\n", 2));
  if (dup2(s->stdin, 0) == -1)
    return (0);
  complete_file(s->tmpfd, s->board[i]);
  close(s->tmpfd);
  if ((s->tmpfd = open("/tmp/redirtmp.c", O_RDONLY)) == -1)
    return (0);
  dup2(s->tmpfd, 0);
  s->fdkey = 1;
  return (0);
}
