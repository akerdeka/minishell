#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "errno.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>

typedef struct		env_var
{
	char		*var;
	char		*content;
	void		*next_var;
	void		*prev_var;
}					t_env_var;

typedef struct		s_minishell
{
	int			fd;
	int			pfd[2];
	char		*line;
	char		*command;
	char		**command_tab;
	char		*current_workdir;
	int			return_value;
	char		**command_pipe;
	char		**command_inf;
	char		*path_to_exec;
	char		**argv;
	char		**envp;
	char		**exec_arg;
	char		**envps;
	t_env_var	*ev;
}					t_minishell;

int			get_quotes(t_minishell *ms);
int			get_echo(t_minishell *ms, int i);
int			get_command(t_minishell *ms, int i);
void		ft_exit(t_minishell *ms);

int			remove_no_backslash_quotes(t_minishell *ms, char c);
void		str_remove_index(int i, t_minishell *ms);
void		backslash_checker_no_quotes(t_minishell *ms);
void		backslash_checker(t_minishell *ms);

void		ft_pwd(t_minishell *ms);
int			ft_cd(t_minishell *ms, int j);
void		check_exit(t_minishell *ms, int j);
void		ft_exit(t_minishell *ms);
int			ft_export(t_minishell *ms, int i);
void		ft_unset(t_minishell *ms, int i);
void		ft_env(t_minishell *ms);

void		manage_inf(t_minishell *ms, int i);
void		manage_pipe(t_minishell *ms, int i);
void		manage_inf_pipe(t_minishell *ms, int i);
void		signal_handler(int signum);

void		get_different_option(t_minishell *ms, int i);
void		get_different_option_pipe(t_minishell *ms, int i);
void		get_different_option_pipe_inf(t_minishell *ms, int i);
int			get_command_pipe_inf(t_minishell *ms, int k);
char		**gpapin(t_minishell *ms, t_env_var *t, char **path, char *tempo, int i);

int			ischaracter_quotes(t_minishell *ms, int i);
int			ischaracter_squotes(t_minishell *ms, int i);
void		ischaracter_slash(t_minishell *ms, int i);
void		ischaracter_slash_next(t_minishell *ms, int i);
void		ft_testing(t_minishell *ms);
void		ft_strdel_free(char **str);

void		manage_command_55(t_minishell *ms, int i, int **fd);

int			get_echo_pipe(t_minishell *ms, int i);
int			get_echo_inf(t_minishell *ms, int i);

void		ft_error(t_minishell *ms);
void		ft_error_ls(t_minishell *ms);
void		get_environement(t_minishell *ms);
void		ft_add_shlvl(t_minishell *ms);

#endif
