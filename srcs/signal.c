/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbesson <pbesson@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 12:18:48 by pbesson           #+#    #+#             */
/*   Updated: 2021/02/01 12:22:40 by pbesson          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signum)
{
static int pid;

	if (signum > 32)
	{
		pid = signum;
		return ;
	}
	if ((signum == SIGINT || signum == SIGQUIT) && pid != 0)
	{
		if (kill(pid, signum) == 0)
		{
			if (signum == SIGQUIT)
				ft_printf("Quit: 3\n");
			else if (signum == SIGINT)
				ft_printf("\n");
		}
		else if (signum == SIGINT)
			ft_printf("\n\033[0;31mMinishell > \033[00m");
	}
	else
	{
		if (signum == SIGQUIT)
			return ;
		ft_printf("\n\033[0;31mMinishell > \033[00m");
	}
}