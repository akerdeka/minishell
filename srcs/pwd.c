/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 20:25:39 by pbesson           #+#    #+#             */
/*   Updated: 2020/09/21 20:25:39 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_minishell *ms)
{
	int i;

	i = 10;
	if (!(ms->current_workdir = malloc(sizeof(char) * i)))
		ft_exit(ms);
	while (!(getcwd(ms->current_workdir, i)))
	{
		i++;
		ft_strdel(ms->current_workdir);
		if (!(ms->current_workdir = malloc(sizeof(char) * i)))
			ft_exit(ms);
	}
	if (errno == 13)
	{
		ft_printf("Permission denied.");
		ft_strdel(ms->current_workdir);
	}
	else
	{
		ft_printf("%s\n", ms->current_workdir);
		ft_strdel(ms->current_workdir);
	}
}
