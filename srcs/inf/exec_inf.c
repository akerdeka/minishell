/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:44:55 by wasayad           #+#    #+#             */
/*   Updated: 2021/02/10 16:52:23 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**get_path_arg_norme(t_minishell *ms,
		t_env_var *temp, char **tempo, char **path)
{
	int		id;
	int		i;

	i = -1;
	while (temp->next_var && ft_strcmp(temp->var, "PATH") != 0)
		temp = temp->next_var;
	path = ft_split(temp->content, ':');
	while (path[++i])
	{
		*tempo = ft_strjoin(path[i], "/");
		*tempo = ft_strjoin_free_s1(*tempo, ms->command);
		id = open(*tempo, O_RDONLY);
		if (id > 0 || path[i + 1] == NULL)
		{
			close(id);
			break ;
		}
		close(id);
		ft_strdel_free(&(*tempo));
	}
	return (path);
}

void		get_path_arg(t_minishell *ms, int j)
{
	t_env_var	*temp;
	char		**path;
	int			i;
	char		*tempo;

	i = -1;
	temp = ms->ev->next_var;
	path = NULL;
	tempo = NULL;
	if (ms->command[0] == '/')
		tempo = ft_strdup(ms->command);
	else
		path = get_path_arg_norme(ms, temp, &tempo, path);
	ms->command_tab[j] = ft_strjoin_free_s2(" ", ms->command_tab[j]);
	ms->command_tab[j] = ft_strjoin_free_s2(ms->command, ms->command_tab[j]);
	ms->argv = ft_split(ms->command_tab[j], ' ');
	free(ms->argv[0]);
	ms->argv[0] = ft_strdup(tempo);
	ft_strdel_free(&(tempo));
	i = -1;
	while (path && path[++i])
		free(path[i]);
	free(path);
	ft_strdel_free(&(tempo));
}

static void	try_exec_2(t_minishell *ms, int id, int j)
{
	if (id == 0)
	{
		close(ms->pfd[0]);
		get_environement(ms);
		if (execve(ms->argv[0], ms->argv, ms->envps) == -1)
		{
			if (ft_strcmp("?", ms->command) == 0)
				ms->status = ft_strdup(ft_itoa(WEXITSTATUS(ms->status)));
			ft_printf("%s: %s\n", ms->command, strerror(errno));
			exit(1);
		}
	}
	else
	{
		signal_handler(id);
		wait(&(ms->status));
		ms->ev->content = ft_itoa(WEXITSTATUS(ms->status));
		while (ms->argv[++j])
			free(ms->argv[j]);
		free(ms->argv);
	}
}

static void	try_exec(t_minishell *ms, int i)
{
	int		id;
	int		j;

	j = -1;
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup("");
	get_path_arg(ms, i);
	if (ft_strchr(ms->command, '.') && ft_strchr(ms->command, '/'))
	{
		ms->command = ft_strtrim_free(ms->command, "./");
		ms->command = ft_strjoin_free_s2("/", ms->command);
		ft_strdel_free(&(ms->argv[0]));
		if (!(ms->argv[0] = malloc(sizeof(char) * 2000)))
			ft_exit(ms);
		getcwd(ms->argv[0], 2000);
		ms->argv[0] = ft_strjoin_free_s1(ms->argv[0], ms->command);
	}
	id = fork();
	try_exec_2(ms, id, j);
}

void		get_different_option(t_minishell *ms, int i)
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
