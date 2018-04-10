#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

int	printboard(char **board, int key)
{
  int	i;

  i = 0;
  if (board == NULL || board[i] == NULL)
    return (my_putstr("The list is empty.\n", 4));
  while (board[i])
    {
      my_putstr(board[i++], 1);
      if (key == 0)
	my_putstr("\n", 1);
    }
  return (0);
}

char	*my_str_fusion(char *start, char *end)
{
  char	*res;
  int	y;
  int	i;

  if ((res = malloc(my_strlen(start) + my_strlen(end) + 1)) == NULL)
    return (NULL);
  y = 0;
  i = 0;
  while (start[i])
    {
      res[i] = start[i];
      ++i;
    }
  while (end[y])
    res[i++] = end[y++];
  res[i] = '\0';
  return (res);
}

int	my_putstr(char *str, int output)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i])
    ++i;
  if (output == 3)
    {
      write(1, str, i);
      write(1, "\n", 1);
      return (0);
    }
  if (output == 4)
    {
      write(2, str, i);
      return (0);
    }
  write(output, str, i);
  if (output == 2)
    return (-1);
  return (0);
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  if (str == NULL)
    return (1);
  while (str[i] != '\0')
    ++i;
  return (i);
}

int	my_strcpy(char *scr, char *wanted, int i)
{
  int	y;

  if (scr == NULL|| wanted == NULL)
    return (0);
  y = 0;
  while (wanted[y++])
    scr[i++] = wanted[y - 1];
  scr[i] = '\0';
  return (0);
}
