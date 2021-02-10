/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:43:50 by acharras          #+#    #+#             */
/*   Updated: 2021/02/10 13:36:37 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_norm(t_minishell *ms, int i)
{
	ft_testing(ms);
	while (ms->command_tab[i])
	{
		main_manager(ms, i);
		free(ms->command_pipe);
		free(ms->command_inf);
		ms->command_inf = NULL;
		ms->command_pipe = NULL;
		free(ms->command_tab[i]);
		i++;
	}
	free(ms->command_tab);
	ft_strdel_free(&(ms->line));
	i = 0;
	ft_printf("\033[0;31mMinishell > \033[00m");
	free(ms->line);
}
