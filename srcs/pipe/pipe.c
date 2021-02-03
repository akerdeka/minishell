/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:10:58 by wasayad           #+#    #+#             */
/*   Updated: 2021/02/03 11:47:54 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	manage_dup_loop(t_minishell *ms, int **fd, int tempstdout, int j)
{
	int		tempstdin;

	tempstdin = dup(0);
	while (ms->command_pipe[++j])
	{
		if (ft_strchr(ms->command_pipe[j], -51)
			|| ft_strchr(ms->command_pipe[j], -53))
		{
			if (ms->command_pipe[j + 1] == NULL)
			{
				dup2(tempstdout, STDOUT_FILENO);
				close(fd[j - 1][1]);
				dup2(fd[j - 1][0], STDIN_FILENO);
			}
			manage_inf_pipe(ms, j);
		}
		else
		{
			if (ft_strchr(ms->command_pipe[j], -52))
			{
				manage_command_55(ms, j, fd);
			}
			else if (j == 0 && ms->command_pipe[j + 1] != NULL)
			{
				dup2(fd[j][1], STDOUT_FILENO);
				get_different_option_pipe(ms, j);
			}
			else if (ms->command_pipe[j + 1] != NULL)
			{
				close(fd[j - 1][1]);
				dup2(fd[j - 1][0], STDIN_FILENO);
				dup2(fd[j][1], STDOUT_FILENO);
				get_different_option_pipe(ms, j);
			}
			else
			{
				dup2(tempstdout, STDOUT_FILENO);
				close(fd[j - 1][1]);
				dup2(fd[j - 1][0], STDIN_FILENO);
				get_different_option_pipe(ms, j);
			}
		}
	}
	dup2(tempstdin, 0);
}

void		manage_pipe(t_minishell *ms, int i)
{
	int		j;
	int		tempstdout;
	int		tempstdin;
	int		**fd;

	tempstdout = dup(1);
	tempstdin = dup(0);
	ms->command_pipe = ft_split(ms->command_tab[i], -54);
	i = 0;
	while (ms->command_pipe[i])
		i++;
	fd = malloc(sizeof(int *) * (i + 1));
	j = 0;
	while (j < i)
	{
		fd[j] = malloc(sizeof(int) * 2);
		pipe(fd[j]);
		j++;
	}
	j = -1;
	manage_dup_loop(ms, fd, tempstdout, j);
}
