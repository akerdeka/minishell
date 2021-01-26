/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:25:39 by pbesson           #+#    #+#             */
/*   Updated: 2020/09/21 20:25:39 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//GERER LES EXIT
//PARSING CASSE SUR LE CAS '"salut"' '"salut"'

int		get_echo(t_minishell *ms, int i)
{
	if (ms->command_tab[i][0] == '-' && ms->command_tab[i][1] == 'n')
	{
		if (!(get_command(ms, i)))
			return (0);
		ms->line = ft_strdup(ms->command_tab[i]);
	}
	else
	{
		ft_strdel_free(&(ms->line));
		ms->line = ft_strjoin_free_s1(ms->command_tab[i], "\n");
	}
	return (1);
}

int		get_echo_pipe(t_minishell *ms, int i)
{
	if (ms->command_pipe[i][0] == '-' && ms->command_pipe[i][1] == 'n')
	{
		if (!(get_command(ms, 0)))
			return (0);
	}
	else
	{
		ft_printf("%s\n", ms->command_pipe[i]);
		ft_strdel_free(&(ms->line));
		ms->line = ft_strjoin_free_s1(ms->command_pipe[i], "\n");
	}
	return (1);
}

int		get_echo_inf(t_minishell *ms, int i)
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
	}
	return (1);
}