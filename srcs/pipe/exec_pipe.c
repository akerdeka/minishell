/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasayad <wasayad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:32:27 by wasayad           #+#    #+#             */
/*   Updated: 2021/01/23 16:57:40 by wasayad          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_path_arg_pipe(t_minishell *ms, int k)
{
	t_env_var	*temp;
	char		**path;
	int			i;
	char		*tempo;
	int			id;

	i = -1;
	temp = ms->ev;
	while (temp->last != 1 && ft_strcmp(temp->var, "PATH") != 0)
		temp = temp->next_var;
	path = ft_split(temp->content, ':');
	while (path[++i])
	{
		tempo = ft_strjoin(path[i], "/");
		tempo = ft_strjoin_free_s1(tempo, ms->command);
		id = open(tempo, O_RDONLY);
		if (id > 0)
			break ;
		close(id);
		free(tempo);
	}
	ms->command_pipe[k] = ft_strjoin_free_s2(" ", ms->command_pipe[k]);
	ms->command_pipe[k] = ft_strjoin_free_s2(ms->command, ms->command_pipe[k]);
	ms->argv = ft_split(ms->command_pipe[k], ' ');
	ms->argv[0] = tempo;
}

static void	try_exec_pipe(t_minishell *ms, int k)
{
	int		id;

	get_path_arg_pipe(ms, k);
	id = fork();
	if (id == 0)
		execve(ms->argv[0], ms->argv, NULL);
}

static int	get_command_pipe(t_minishell *ms, int k)
{
	int i;
	int j;

	i = 0;
	j = 0;
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

void	get_different_option_pipe(t_minishell *ms, int i)
{
	if (!(get_command_pipe(ms, i)))
		ft_exit(ms);
	if (ft_strcmp(ms->command, "echo") == 0)
		get_echo(ms);
	else if (ft_strcmp(ms->command, "pwd") == 0)
		ft_pwd(ms);
	else if (ft_strcmp(ms->command, "export") == 0)
		ft_export(ms);
	else if (ft_strcmp(ms->command, "unset") == 0)
		ft_unset(ms);
	else if (ft_strcmp(ms->command, "env") == 0)
		ft_env(ms);
	else
		try_exec_pipe(ms, i);
}
