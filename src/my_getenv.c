#include <stdlib.h>

int	str_compar(char *scr, char *wanted, int i)
{
  int	y;

  y = 0;
  while (scr[i] && wanted[y])
    {
      if (wanted[y] == scr[i])
	{
	  i++;
	  y++;
	}
      else
	return (0);
    }
  if (wanted[y] != '\0')
    return (0);
  return (i);
}

char	*my_getenv(char **env, char *value, char *res)
{
  int	i;
  int	s;
  int	y;

  i = 0;
  y = 0;
  while (env[i])
    {
      if ((y = str_compar(env[i], value, 0)) != 0)
	{
	  s = y;
	  while (env[i][y])
	    y++;
	  if ((res = malloc(y)) == NULL)
	    return (NULL);
	  y = s;
	  s = 0;
	  while (env[i][y])
	    res[s++] = env[i][y++];
	  res[s] = '\0';
	  return (res);
	}
      i++;
    }
  return (NULL);
}
