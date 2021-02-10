/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:32:27 by wasayad           #+#    #+#             */
/*   Updated: 2021/02/10 16:09:29 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_path_arg_pipe_norme(t_minishell *ms,
		t_env_var *temp, char **tempo, char **path)
{
	int			id;
	int			i;

	i = -1;
	if (ms->command[0] == '/')
		*tempo = ft_strdup(ms->command);
	else
	{
		while (temp->next_var && ft_strcmp(temp->var, "PATH") != 0)
			temp = temp->next_var;
		path = ft_split(temp->content, ':');
		while (path[++i])
		{
			*tempo = ft_strjoin(path[i], "/");
			*tempo = ft_strjoin_free_s1(*tempo, ms->command);
			id = open(*tempo, O_RDONLY);
			if (id > 0)
				break ;
			close(id);
			free(*tempo);
		}
	}
	return (path);
}

static void	get_path_arg_pipe(t_minishell *ms, int k)
{
	t_env_var	*temp;
	char		**path;
	int			i;
	char		*tempo;

	i = -1;
	temp = ms->ev->next_var;
	path = NULL;
	path = get_path_arg_pipe_norme(ms, temp, &tempo, path);
	ms->command_pipe[k] = ft_strjoin_free_s2(" ", ms->command_pipe[k]);
	ms->command_pipe[k] = ft_strjoin_free_s2(ms->command, ms->command_pipe[k]);
	ms->argv = ft_split(ms->command_pipe[k], ' ');
	free(ms->argv[0]);
	ms->argv[0] = ft_strdup(tempo);
	i = -1;
	ft_strdel_free(&(tempo));
	while (path && path[++i])
		free(path[i]);
	free(path);
}

static void	try_exec_pipe(t_minishell *ms, int k)
{
	int		id;
	int		i;

	i = -1;
	id = fork();
	get_path_arg_pipe(ms, k);
	if (id == 0)
	{
		get_environement(ms);
		execve(ms->argv[0], ms->argv, ms->envps);
		dprintf(2, "%s\n", strerror(errno));
		exit(1);
	}
	else
	{
		signal_handler(id);
		while (ms->argv[++i])
			free(ms->argv[i]);
		free(ms->argv);
		wait(&(ms->status));
		ms->ev->content = ft_itoa(WEXITSTATUS(ms->status));
	}
}

static int	get_command_pipe(t_minishell *ms, int k)
{
	int i;
	int j;

	i = 0;
	while (ms->command_pipe[k][i] && ms->command_pipe[k][i] == ' ')
		i++;
	j = i;
	while (ms->command_pipe[k][j] && ms->command_pipe[k][j] != ' ')
		j++;
	if (!(ms->command = ft_substr(ms->command_pipe[k], i, j - i)))
		return (0);
	while (ms->command_pipe[k][j] && ms->command_pipe[k][j] == ' ')
		j++;
	if (!(ms->command_pipe[k] = ft_substr_free(ms->command_pipe[k], j,
	ft_strlen(ms->command_pipe[k]))))
		return (0);
	return (1);
}

void		get_different_option_pipe(t_minishell *ms, int i)
{
	if (!(get_command_pipe(ms, i)))
		ft_exit(ms);
	if (ft_strcmp(ms->command, "echo") == 0)
		get_echo_pipe(ms, i);
	else if (ft_strcmp(ms->command, "cd") == 0)
		ft_printf("");
	else if (ft_strcmp(ms->command, "exit") == 0)
		ft_printf("");
	else if (ft_strcmp(ms->command, "pwd") == 0)
		ft_pwd(ms);
	else if (ft_strcmp(ms->command, "unset") == 0)
		ft_unset(ms, i);
	else if (ft_strcmp(ms->command, "env") == 0)
		ft_env(ms);
	else
		try_exec_pipe(ms, i);
}
