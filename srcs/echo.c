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
		if (!(get_command(ms, 0)))
			return (0);
	}
	else
	{
		ft_strdel_free(&(ms->line));
		ms->line = ft_strjoin_free_s1(ms->command_tab[i], "\n");
	}
	return (1);
}