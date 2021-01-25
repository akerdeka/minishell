/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasayad <wasayad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:21:36 by wasayad           #+#    #+#             */
/*   Updated: 2021/01/23 16:52:01 by wasayad          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	manage_command_51(t_minishell *ms, int i, int j, int k)
{
	if (!(ms->command_inf = ft_split(ms->command_pipe[i], -51)))
		ft_exit(ms);
	free(ms->line);
	ms->line = ms->command_inf[0];
	get_different_option_pipe_inf(ms, i);
	while (ms->command_inf[j])
	{
		k = 0;
		while (ms->command_inf[j][i] && ms->command_inf[j][k] == ' ')
			k++;
		ms->fd = open(ms->command_inf[j] + k, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (ms->command_inf[j + 1] == NULL)
			write(ms->fd, ms->line, ft_strlen(ms->line));
		close(ms->fd);
		j++;
	}
}

void	manage_command_52(t_minishell *ms, int i)
{
	if (!(ms->command_inf = ft_split(ms->command_pipe[i], -52)))
		ft_exit(ms);
	free(ms->line);
	ms->line = ms->command_inf[0];
}

void	manage_command_53(t_minishell *ms, int i, int j, int k)
{
	if (!(ms->command_inf = ft_split(ms->command_pipe[i], -53)))
		ft_exit(ms);
	free(ms->line);
	ms->line = ms->command_inf[0];
	get_different_option_pipe_inf(ms, i);
	while (ms->command_inf[j])
	{
		k = 0;
		while (ms->command_inf[j][i] && ms->command_inf[j][k] == ' ')
			k++;
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
	else if (ft_strchr(ms->command_pipe[i], -52))
	{
		manage_command_52(ms, i);
	}
	else if (ft_strchr(ms->command_pipe[i], -53))
	{
		manage_command_53(ms, i, j, k);
	}
	ft_strdel(ms->line);
	j = 0;
	// while (ms->command_inf[j])
	// {
	// 	ft_strdel(ms->command_inf[j]);
	// }
	// ft_strdel(ms->command_inf[j]);
	// ft_memdel((void **)ms->command_inf);
	//FREE COMMAND INF
}
