#include "../libft/libft.h"
#include "errno.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
typedef struct      env_var //liste chaînée pour variable d'environnement 
{
    char    *var;
    char    *content;
    void    *first_var;
    void    *next_var;
    void    *prev_var;
    int     last;
}                   t_env_var;

typedef struct		s_minishell
{
    int     fd;
    int     pfd[2];
	char	*line;
    char	*command;
    char    **command_tab;
    char	*current_workdir;
	int		return_value;
    char    **command_pipe;
    char    **command_inf;
    char    *path_to_exec;
    char    **argv;
    char    **envp;
    char    **exec_arg;
    t_env_var *ev;
}					t_minishell;


int			get_quotes(t_minishell *ms);
int			get_echo(t_minishell *ms, int i);
int			get_command(t_minishell *ms, int i);
void		ft_exit(t_minishell *ms);
void		check_exit(t_minishell *ms);


int			remove_no_backslash_quotes(t_minishell *ms, char c);
void		str_remove_index(int i, t_minishell *ms);
void		backslash_checker_no_quotes(t_minishell *ms);
void		backslash_checker(t_minishell *ms);


void		ft_pwd(t_minishell *ms);
int			ft_cd(t_minishell *ms, int j);
void		check_exit(t_minishell *ms);
void		ft_exit(t_minishell *ms);
int 	    ft_export(t_minishell *ms);
void        ft_unset(t_minishell *ms);
void	    ft_env(t_minishell *ms);


void	manage_inf(t_minishell *ms, int i);
void	manage_pipe(t_minishell *ms, int i);
void	manage_inf_pipe(t_minishell *ms, int i);

void	get_different_option(t_minishell *ms, int i);
void	get_different_option_pipe(t_minishell *ms, int i);
void	get_different_option_pipe_inf(t_minishell *ms, int i);
int		get_command_pipe_inf(t_minishell *ms, int k);

int		ischaracter_quotes(t_minishell *ms, int i);
int		ischaracter_squotes(t_minishell *ms, int i);
void	ischaracter_slash(t_minishell *ms, int i);
void	ischaracter_slash_next(t_minishell *ms, int i);
void	ft_testing(t_minishell *ms);
void	ft_strdel_free(char **str);