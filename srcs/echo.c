/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 12:40:30 by pbesson           #+#    #+#             */
/*   Updated: 2021/02/10 16:23:18 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		get_command_echo(t_minishell *ms, int i)
{
	int			j;
	int			k;
	k = 0;
	j = 0;
	while (ms->command_tab[i][k] && ((ms->command_tab[i][k] == ' ')
		|| (ms->command_tab[i][k] == '-' && ms->command_tab[i][k + 1] == 'n')
		|| (ms->command_tab[i][k] == 'n' && ms->command_tab[i][k - 1] == '-')))
		k++;
	j = k;
	if (!(ms->command = ft_substr(ms->command_tab[i], k, j - k)))
		return (0);
	while (ms->command_tab[i][j] && ms->command_tab[i][j] == ' ')
		j++;
	if (!(ms->command_tab[i] = ft_substr_free(ms->command_tab[i], j,
	ft_strlen(ms->command_tab[i]))))
		return (0);
	return (1);
}

int				get_echo(t_minishell *ms, int i)
{
	if (ms->command_tab[i][0] == '-' && ms->command_tab[i][1] == 'n')
	{
		if (!(get_command_echo(ms, i)))
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

int				get_echo_pipe(t_minishell *ms, int i)
{
	if (ms->command_pipe[i][0] == '-' && ms->command_pipe[i][1] == 'n')
	{
		if (!(get_command_echo_pipe(ms, i)))
			return (0);
		ft_printf("%s", ms->command_pipe[i]);
	}
	else
	{
		ms->command_pipe[i] = ft_strtrim_free(ms->command_pipe[i], " ");
		ft_strdel_free(&(ms->line));
		ms->line = ft_strjoin(ms->command_pipe[i], "\n");
		ft_printf("%s", ms->line);
		free(ms->line);
		ms->line = ft_strdup("");
	}
	return (1);
}

int				get_echo_inf(t_minishell *ms, int i)
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
		ms->line = ft_strjoin(ms->command_inf[0], "\n");
		ft_printf("%s", ms->line);
		free(ms->line);
		ms->line = ft_strdup("");
	}
	return (1);
}
