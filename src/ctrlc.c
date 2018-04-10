#include "shell.h"

void	ctrlc(__attribute__((unused))int sig)
{
  my_putstr("\nlil_shell $> ", 1);
}
