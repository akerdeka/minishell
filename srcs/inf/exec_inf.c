/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:44:55 by wasayad           #+#    #+#             */
/*   Updated: 2021/01/26 15:44:59 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "stdio.h"
int			get_command(t_minishell *ms, int i)
{
	int j;
	int	k;

	k = 0;
	j = 0;
	while (ms->command_tab[i][k] && ms->command_tab[i][k] == ' ')
		k++;
	j = k;
	while (ms->command_tab[i][j] && ms->command_tab[i][j] != ' ')
		j++;
	if (!(ms->command = ft_substr(ms->command_tab[i], k, j - k)))
		return (0);
	while (ms->command_tab[i][j] && ms->command_tab[i][j] == ' ')
		j++;
	if (!(ms->command_tab[i] = ft_substr_free(ms->command_tab[i], j,
	ft_strlen(ms->command_tab[i]))))
		return (0);
	return (1);
}

void	get_path_arg(t_minishell *ms, int j)
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
		if (id > 0 || path[i + 1] == NULL)
			break ;
		close(id);
		free(tempo);
	}
	ms->command_tab[j] = ft_strjoin_free_s2(" ", ms->command_tab[j]);
	ms->command_tab[j] = ft_strjoin_free_s2(ms->command, ms->command_tab[j]);
	ms->argv = ft_split(ms->command_tab[j], ' ');
	free(ms->argv[0]);
	ms->argv[0] = ft_strdup(tempo);
	free(tempo);
}

static void	try_exec_read(t_minishell *ms)
{
	int		ret;
	char	*buffer;

	buffer = malloc(sizeof(char *) * 10000);
	ft_strdel_free(&(ms->line));
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

static void	try_exec(t_minishell *ms, int i)
{
	int		id;

	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup("");
	get_path_arg(ms, i);
	pipe(ms->pfd);
	id = fork();
	if (id == 0)
	{
		close(ms->pfd[0]);
		dup2(ms->pfd[1], 1);
		if (execve(ms->argv[0], ms->argv, ms->envp) == -1)
		{
			dprintf(2, "%s\n", strerror(errno));
			exit(1);
		}
	}
	else
	{
		try_exec_read(ms);
	}
}

void	get_different_option(t_minishell *ms, int i)
{
	if (!(get_command(ms, i)))
		ft_exit(ms);
	if (ft_strcmp(ms->command, "echo") == 0)
		get_echo(ms, i);
	else if (ft_strcmp(ms->command, "pwd") == 0)
		ft_pwd(ms);
	else if (ft_strcmp(ms->command, "cd") == 0)
		ft_cd(ms, i);
	else if (ft_strcmp(ms->command, "exit") == 0)
		check_exit(ms);
	else if (ft_strcmp(ms->command, "export") == 0)
		ft_export(ms);
	else if (ft_strcmp(ms->command, "unset") == 0)
		ft_unset(ms);
	else if (ft_strcmp(ms->command, "env") == 0)
		ft_env(ms);
	else
		try_exec(ms, i);
}
