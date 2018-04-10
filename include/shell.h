#ifndef SHELL_H_
# define SHELL_H_

typedef struct	s_shell
{
  char		**my_env;
  char		**board;
  char		**alias;
  char		**exec;
  char		*pwd;
  char		*oldpwd;
  char		*path;
  char		*path_res;
  char		*home;
  int		stdout;
  int		stdin;
  int		fdkey;
  int		tmpfd;
  int		tmpid;
}		t_shell;

void	ctrlc(int sig);
int	max_env_col(char **env, int res, int tmp);
int	env_size(char **env);
int	do_env_cpy(char **scr, char **dest, int key);
int	my_double_free(char **str);
int	printboard(char **board, int key);
int	my_setenv(t_shell *s, char *newenv);
int	my_unsetenv(t_shell *s, char *delenv);
int	my_strlen(char *str);
int	my_putstr(char *str, int output);
int	my_strcpy(char *scr, char *wanted, int i);
int	str_compar(char *scr, char *wanted, int i);
int	my_cd(t_shell *s, char *where);
int	check_if_same_elem(char *str, char *wanted);
int	replace_tilt(char *res, char *home, char *where);
int	update_alias(t_shell *s);
int	add_env_elem(char **env, char *newvar, int env_size, int i);
int	del_alias_elem(t_shell *s);
int	my_getnbr(char *str);
int	ini_struct(t_shell *s, char **env);
int	ini_shell(t_shell *s, char **env);
int	check_if_redir(t_shell *s, int z);
int	restore_std(t_shell *s);
int	case_redir(char **board, char *str, int *i, int *y);
int	double_redir_left(t_shell *s, int i, int *key);
int	build_board(t_shell *s, char *str);
int	add_elem_to_exec(char **exec, char *wanted);
int	build_exec(t_shell *s, char **board, int i, int key);
int	loop_elem(t_shell *s, char *res);
int	check_for_pipes(t_shell *s, int i);
int	check_if_flag_after_redir(char **board, char **exec, char *tmp, int i);
int	check_builtins(t_shell *s, char *res, int key);
int	case_first_exec(t_shell *s);
char	*check_if_cd_possible(t_shell *s, char *where);
char	*check_if_alias(t_shell *s, char *res, int i);
char	*check_if_semicolon(char *res, int *i);
char	**my_double_malloc(char **str, int sizeb, int size);
char	**env_cpy(char **res, char **env);
char	**update_env(char **res, char **env, char *newvar, int key);
char	*res_not_finish(char *res, int i);
char	*my_exec_path(t_shell *s, char *command, int i, int y);
char	*my_getenv(char **env, char *value, char *res);
char	*my_str_fusion(char *start, char *end);

#endif /* !SHELL_H_ */
