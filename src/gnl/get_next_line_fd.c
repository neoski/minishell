/*
** get_next_line_fd.c for check_if_new_fd in /home/stoilo_s/rendu/MUL_2014_fdf
** 
** Made by sebastien stoilov
** Login   <stoilo_s@epitech.net>
** 
** Started on  Sat Dec  6 02:47:25 2014 sebastien stoilov
** Last update Fri Jan 30 01:37:27 2015 sebastien stoilov
*/

#include <stdlib.h>
#include "get_next_line.h"

char		*check_if_new_fd(int fd, char *str, int *key)
{
  static int	new = 0;

  if (new == 0)
    new = fd;
  else if (new != fd)
    {
      new = fd;
      *key = 0;
    }
  if (*key == 2 || ((str = my_gnl_realloc(str, 0, key))) == NULL)
    return (NULL);
  if (new != fd)
    {
      new = fd;
      *key = 0;
    }
  return (str);
}
