/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasayad <wasayad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:21:36 by wasayad           #+#    #+#             */
/*   Updated: 2021/02/08 17:02:55 by wasayad          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manage_command_51(t_minishell *ms, int i, int j, int k)
{
	if (!(ms->command_inf = ft_split(ms->command_pipe[i], -51)))
		ft_exit(ms);
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup(ms->command_inf[0]);
	get_different_option_pipe_inf(ms, i);
	ms->command_inf[1] = ft_strtrim_free(ms->command_inf[1], " ");
	while (ms->command_inf[j])
	{
		k = 0;
		ms->command_inf[j] = ft_strtrim_free(ms->command_inf[j], " ");
		ms->fd = open(ms->command_inf[j], O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (ms->command_inf[j + 1] == NULL)
			write(ms->fd, ms->line, ft_strlen(ms->line));
		close(ms->fd);
		j++;
	}
}

void	manage_command_55(t_minishell *ms, int i, int **fd)
{
	int		fdi;
	int		tempstdin;

	if (!(ms->command_inf = ft_split(ms->command_pipe[i], -52)))
		ft_exit(ms);
	ms->command_inf[1] = ft_strtrim_free(ms->command_inf[1], " ");
	fdi = open(ms->command_inf[1], O_RDONLY);
	tempstdin = dup(0);
	dup2(fdi, STDIN_FILENO);
	dup2(fd[i][1], STDOUT_FILENO);
	get_different_option_pipe_inf(ms, i);
	dup2(tempstdin, STDIN_FILENO);
	close(fdi);
}

void	manage_command_53(t_minishell *ms, int i, int j, int k)
{
	if (!(ms->command_inf = ft_split(ms->command_pipe[i], -53)))
		ft_exit(ms);
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup(ms->command_inf[0]);
	get_different_option_pipe_inf(ms, i);
	while (ms->command_inf[j])
	{
		k = 0;
		ms->command_inf[j] = ft_strtrim_free(ms->command_inf[j], " ");
		ms->fd = open(ms->command_inf[j] + k, O_WRONLY | O_CREAT | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (ms->command_inf[j + 1] == NULL)
			write(ms->fd, ms->line, ft_strlen(ms->line));
		close(ms->fd);
		j++;
	}
}

void	manage_inf_pipe(t_minishell *ms, int i)
{
	int		j;
	int		k;
	int		tempstdout;

	tempstdout = dup(1);
	j = 1;
	k = 0;
	if (ft_strchr(ms->command_pipe[i], -51))
	{
		manage_command_51(ms, i, j, k);
	}
	else if (ft_strchr(ms->command_pipe[i], -53))
	{
		manage_command_53(ms, i, j, k);
	}
	ft_strdel_free(&(ms->line));
	j = 0;
	while (ms->command_inf[j])
		free(ms->command_inf[j++]);
}
