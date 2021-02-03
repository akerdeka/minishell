/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:44:55 by wasayad           #+#    #+#             */
/*   Updated: 2021/02/03 11:46:07 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
#include "stdio.h"
void	get_path_arg(t_minishell *ms, int j)
{
	t_env_var	*temp;
	char		**path;
	int			i;
	char		*tempo;
	int			id;

	i = -1;
	temp = ms->ev->next_var;
	if (ms->command[0] == '/')
	{
		tempo = ft_strdup(ms->command);
	}
	else
	{
		while (temp->next_var && ft_strcmp(temp->var, "PATH") != 0)
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
	}
	ms->command_tab[j] = ft_strjoin_free_s2(" ", ms->command_tab[j]);
	ms->command_tab[j] = ft_strjoin_free_s2(ms->command, ms->command_tab[j]);
	ms->argv = ft_split(ms->command_tab[j], ' ');
	free(ms->argv[0]);
	ms->argv[0] = ft_strdup(tempo);
	ft_strdel_free(&(tempo));
}

//static void	try_exec_read(t_minishell *ms)
//{
//	int		ret;
//	char	*buffer;
//
//	buffer = malloc(sizeof(char *) * 10000);
//	ft_strdel_free(&(ms->line));
//	ms->line = ft_strdup("");
//	close(ms->pfd[1]);
//	while (((ret = read(ms->pfd[0], buffer, 1023)) > 0))
//	{
//		buffer[ret] = 0;
//		ms->line = ft_strjoin_free_s1(ms->line, buffer);
//	}
//	close(ms->pfd[0]);
//	free(buffer);
//}

static void	try_exec(t_minishell *ms, int i)
{
	int		id;

	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup("");
	get_path_arg(ms, i);
	if (ft_strchr(ms->command, '.') && ft_strchr(ms->command, '/'))
	{
		ms->command = ft_strtrim(ms->command, "./");
		ms->command = ft_strjoin_free_s2("/", ms->command);
		if (!(ms->argv[0] = malloc(sizeof(char) * 2000)))
			ft_exit(ms);
		getcwd(ms->argv[0], 2000);
		ms->argv[0] = ft_strjoin_free_s1(ms->argv[0], ms->command);
	}
	id = fork();
	if (id == 0)
	{
		close(ms->pfd[0]);
		get_environement(ms);
		if (execve(ms->argv[0], ms->argv, ms->envps) == -1)
		{
			ft_printf("%s: %s\n", ms->command, strerror(errno));
			exit(1);
		}
	}
	else
	{
		signal_handler(id);
		wait(0);
	}
}

void	get_different_option(t_minishell *ms, int i)
{
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup("");
	if (!(get_command(ms, i)))
		ft_exit(ms);
	if (ft_strcmp(ms->command, "echo") == 0)
		get_echo(ms, i);
	else if (ft_strcmp(ms->command, "pwd") == 0)
		ft_pwd(ms);
	else if (ft_strcmp(ms->command, "cd") == 0)
		ft_cd(ms, i);
	else if (ft_strcmp(ms->command, "exit") == 0)
		check_exit(ms, i);
	else if (ft_strcmp(ms->command, "export") == 0)
		ft_export(ms, i);
	else if (ft_strcmp(ms->command, "unset") == 0)
		ft_unset(ms, i);
	else if (ft_strcmp(ms->command, "env") == 0)
		ft_env(ms);
	else
		try_exec(ms, i);
}
