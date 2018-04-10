#include "shell.h"

void	ctrlc(__attribute__((unused))int sig)
{
  my_putstr("\nminishell $> ", 1);
}
