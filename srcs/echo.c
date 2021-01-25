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

int		get_echo(t_minishell *ms)
{
	if (ms->line[0] == '-' && ms->line[1] == 'n')
	{
		if (!(get_command(ms, 0)))
			return (0);
	}
	else
	{
		ms->line = ft_strjoin_free_s1(ms->line, "\n");
	}
	return (1);
}