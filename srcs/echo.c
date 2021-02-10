/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharras <acharras@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 12:40:30 by pbesson           #+#    #+#             */
/*   Updated: 2021/02/09 14:17:49 by acharras         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_echo(t_minishell *ms, int i)
{
	if (ms->command_tab[i][0] == '-' && ms->command_tab[i][1] == 'n')
	{
		if (!(get_command(ms, i)))
			return (0);
		ft_strdel_free(&(ms->line));
		ms->line = ft_strdup(ms->command_tab[i]);
		ft_printf("%s", ms->line);
		free(ms->line);
		ms->line = ft_strdup("");
	}
	else
	{
		ft_strdel_free(&(ms->line));
		ms->line = ft_strjoin(ms->command_tab[i], "\n");
		ft_printf("%s", ms->line);
		free(ms->line);
		ms->line = ft_strdup("");
	}
	return (1);
}

int	get_echo_pipe(t_minishell *ms, int i)
{
	if (ms->command_pipe[i][0] == '-' && ms->command_pipe[i][1] == 'n')
	{
		if (!(get_command(ms, 0)))
			return (0);
	}
	else
	{
		ms->command_pipe[i] = ft_strtrim_free(ms->command_pipe[i], " ");
		ft_printf("%s\n", ms->command_pipe[i]);
		ft_strdel_free(&(ms->line));
		ms->line = ft_strjoin_free(ms->command_pipe[i], "\n");
		ft_printf("%s", ms->line);
		free(ms->line);
		ms->line = ft_strdup("");
	}
	return (1);
}

int	get_echo_inf(t_minishell *ms, int i)
{
	i = 0;
	if (ms->command_inf[0][0] == '-' && ms->command_inf[0][1] == 'n')
	{
		if (!(get_command(ms, 0)))
			return (0);
	}
	else
	{
		ft_strdel_free(&(ms->line));
		ms->line = ft_strjoin_free_s1(ms->command_inf[0], "\n");
		ft_printf("%s", ms->line);
		free(ms->line);
		ms->line = ft_strdup("");
	}
	return (1);
}
