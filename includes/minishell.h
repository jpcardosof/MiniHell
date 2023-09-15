#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>//  write, dup2, close
# include <fcntl.h>//  O_RDONLY, O_...
# include <stdlib.h>//  EXIT_FAILURE, malloc, free
# include <stdio.h>//  STDIN
# include <sys/types.h>//	wait
# include <sys/wait.h>//	wait
# include <errno.h>//	ERROR
# include <signal.h>//	SIG
# include <dirent.h>//	DIR
# include <limits.h>// MAX / MIN VALUES
# include <readline/readline.h>//	ReadLine
# include <readline/history.h>//	History
# include "../libft/include/libft.h"
# include "parse.h"
# define TRUE 1
# define FALSE 0
# define GREEN "\033[0;32m"
# define TEMP_FILE "./.temp"

typedef struct s_data
{
	int			nbr_tokens;
	char		**tokens;
	char		*str_cmd;
	char		**env_p;
	char		***cmds;
	int			fd[2][2];
	int			curr_cmd;
	int			curr_fd;
	int			count;
	int			warning;
	int			shlvl;
	char		**here_doc;
	char		*str_tmp;
	int			error;
}			t_data;

// ---------- PARSE ------------

//Data init
t_data			*data(void);

//split_cmds
void			ft_spc(int size);
char			**ft_cmd(void);
int				ft_matriz_size(void);
int				ft_ptrlen(int v);
char			*get_path(char *cmd);

//split_cmds2
char			*get_path_loop(char *cmd, char **path);
char			*add_path(char *path, int i, char *cmds);
char			*check_path(char *cmd);

// ---------- EXECUTION ------------
// cmds
void			swap_fd(void);
void			generate_fds(void);
void			child_exec(void);
void			execute_cmd(void);
void			cmd_to_exec(void);

// fd_checker
void			fd_input(int tmp_curr);
void			fd_red_append(int tmp_curr);
void			fd_redirect(int tmp_curr);
void			fd_pipe(void);
int				fd_check(int tmp_curr);

// fd_heredoc
int				handle_here(char *exit);
void			fd_heredoc(int tmp_curr);

// free
void			free_double_ptr(char **str);
void			free_triple_ptr(char ***str);

// get_path
char			*ft_getenv(char **env, char *str, int size);
char			*get_path_loop(char *cmd, char **path);
char			*add_path(char *path, int i, char *cmds);
char			*get_path(char *cmd);
char			*check_path(char *cmd);

// utils
int				is_spc(char *cmd);
int				mn_strcmp(char *s1, char *s2);

// generate_cmd
int				ft_cmdlen(void);
char			**spc_cmd(int i, int j, int size);
char			**get_cmd(int i, int j, int size);
char			***generate_cmd(void);

// generate_cmd2
int				ft_mtzlen(char ***mtz);
char			***my_realloc(char ***cmds);
void			free_token(int i);
int				is_valid_cmd(int i);

// ---------- BUILTINS ------------

// check_builtins
int				mn_is_builtins(char *cmd);
void			builtins_call(char **cmd);
void			child_exit(void);

// msg_error
void			msg_error(char *option, char *var_option, \
				char *msg, int err);
void			permission_checker(void);
void			exec_error(void);
void			free_all(void);
void			exit_child(void);

//  ft_cd
void			add_cd_to_env(char *path);
void			apply_cd(char *oldcd, char *newcd);
void			cd_to(char *str);
int				ft_check_cd(char **str);
void			ft_cd(char **str);

// ft_echo
int				is_flag(char *str);
void			print_echo(char **str, int flag);
void			ft_echo_beg(char **str, int flag);
void			ft_echo(char **str);

// ft_env
void			ft_env(char **str);
void			ft_env_exec(char **str);

// ft_exit
int				ft_exit_err(void);
long long int	ft_atoli_checker(char *nptr, int i, int sing);
long long int	ft_atoli(char *nptr);
void			ft_exit(char **str);

// ft_export
void			export_declare_exec(char **str);
void			export_declare(void);
void			check_env_name(char **env, char *str, int size);
int				check_export(char **str, int i, int j);
void			ft_export(void);

// ft_pwd
void			ft_pwd(char **str);
void			ft_pwd_exec(char **str);

// ft_unset
void			ft_unset(char **str, char *find);
void			unset_var(char **env, int skip);

#endif
