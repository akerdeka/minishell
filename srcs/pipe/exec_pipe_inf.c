/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_inf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:39:13 by wasayad           #+#    #+#             */
/*   Updated: 2021/02/10 16:08:32 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		get_command_pipe_inf(t_minishell *ms, int k)
{
	int i;
	int j;

	i = 0;
	j = 0;
	k = 0;
	while (ms->command_inf[0][i] && ms->command_inf[0][i] == ' ')
		i++;
	j = i;
	while (ms->command_inf[0][j] && ms->command_inf[0][j] != ' ')
		j++;
	if (!(ms->command = ft_substr(ms->command_inf[0], i, j - i)))
		return (0);
	while (ms->command_inf[0][j] && ms->command_inf[0][j] == ' ')
		j++;
	if (!(ms->command_inf[0] = ft_substr_free(ms->command_inf[0], j,
	ft_strlen(ms->command_inf[1]))))
		return (0);
	return (1);
}

void	get_path_arg_pipe_inf(t_minishell *ms)
{
	t_env_var	*temp;
	char		**path;
	int			i;
	char		*tempo;

	i = -1;
	tempo = NULL;
	path = NULL;
	temp = ms->ev->next_var;
	if (ms->command[0] == '/')
		tempo = ft_strdup(ms->command);
	else
	{
		gpapin(ms, temp, path, &tempo);
	}
	ms->command_inf[0] = ft_strjoin_free_s2(" ", ms->command_inf[0]);
	ms->command_inf[0] = ft_strjoin_free_s2(ms->command, ms->command_inf[0]);
	ms->argv = ft_split(ms->command_inf[0], ' ');
	free(ms->argv[0]);
	ms->argv[0] = ft_strdup(tempo);
	i = -1;
	ft_strdel_free(&(tempo));
	while (path && path[++i])
		free(path[i]);
	free(path);
}

void	try_exec_pipe_inf_read(t_minishell *ms, int i)
{
	int		ret;
	char	*buffer;

	if (!(ft_strchr(ms->command_pipe[i], -52)))
	{
		buffer = malloc(sizeof(char *) * 10000);
		free(ms->line);
		ms->line = ft_strdup("");
		close(ms->pfd[1]);
		while (((ret = read(ms->pfd[0], buffer, 1023)) > 0))
		{
			buffer[ret] = 0;
			ms->line = ft_strjoin_free_s1(ms->line, buffer);
		}
		close(ms->pfd[0]);
		free(buffer);
	}
}

void	try_exec_pipe_inf(t_minishell *ms, int i)
{
	int		id;
	int		j;

	j = -1;
	get_path_arg_pipe_inf(ms);
	pipe(ms->pfd);
	id = fork();
	if (id == 0)
	{
		close(ms->pfd[0]);
		if (!(ft_strchr(ms->command_pipe[i], -52)))
			dup2(ms->pfd[1], 1);
		execve(ms->argv[0], ms->argv, ms->envp);
		ft_printf("%s\n", strerror(errno));
		exit(1);
	}
	else
	{
		while (ms->argv[++j])
			free(ms->argv[j]);
		free(ms->argv);
		signal_handler(id);
		wait(&(ms->status));
		ms->ev->content = ft_itoa(WEXITSTATUS(ms->status));
		try_exec_pipe_inf_read(ms, i);
	}
}

void	get_different_option_pipe_inf(t_minishell *ms, int i)
{
	if (!(get_command_pipe_inf(ms, i)))
		ft_exit(ms);
	if (ft_strcmp(ms->command, "echo") == 0)
		get_echo_inf(ms, i);
	else if (ft_strcmp(ms->command, "pwd") == 0)
		ft_pwd(ms);
	else if (ft_strcmp(ms->command, "cd") == 0)
		ft_printf("");
	else if (ft_strcmp(ms->command, "exit") == 0)
		ft_printf("");
	else if (ft_strcmp(ms->command, "export") == 0)
		ft_export(ms, i);
	else if (ft_strcmp(ms->command, "unset") == 0)
		ft_unset(ms, i);
	else if (ft_strcmp(ms->command, "env") == 0)
		ft_env(ms);
	else
		try_exec_pipe_inf(ms, i);
}
