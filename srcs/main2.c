/****************************************************************************/
/*                                                                          */
/*                                                       :::      ::::::::  */
/*  main2.c                                            :+:      :+:    :+:  */
/*                                                   +:+ +:+         +:+    */
/*  By: wasayad <wasayad@student.42lyon.fr>        +#+  +:+       +#+       */
/*                                               +#+#+#+#+#+   +#+          */
/*  Created: 2021/01/22 15:59:28 by wasayad           #+#    #+#            */
/*  Updated: 2021/01/22 15:59:28 by wasayad          ###   ########lyon.fr  */
/*                                                                          */
/****************************************************************************/

#include "../includes/minishell.h"

static int	ft_find_equal(char *envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
#include "stdio.h"
void		ft_init_env_var(t_minishell *ms)
{
	int			i;
	t_env_var	*temp;
	t_env_var	*actual;

	i = -1;
	if (!(ms->ev = malloc(sizeof(t_env_var) * 1)))
		ft_exit(ms);
	ms->ev->var = NULL;
	//ms->ev->var = ft_substr(ms->envp[i], 0, ft_find_equal(ms->envp[i]));
	//ms->ev->content = ft_substr(ms->envp[i], ft_find_equal(ms->envp[i]) + 1, ft_strlen(ms->envp[i]) - ft_find_equal(ms->envp[i]));
	//ms->ev->last = 0;
	//ms->ev->first_var = NULL;
	////ms->ev->first_var = ms->ev;
	actual = ms->ev;
	while (ms->envp[++i])
	{
		if (!(temp = malloc(sizeof(t_env_var) * 1)))
			ft_exit(ms);
		temp->var = ft_substr(ms->envp[i], 0, ft_find_equal(ms->envp[i]));
		temp->content = ft_substr(ms->envp[i], ft_find_equal(ms->envp[i]) + 1, ft_strlen(ms->envp[i]) - ft_find_equal(ms->envp[i]));
		actual->next_var = temp;
		temp->prev_var = actual;
		if (ms->envp[i + 1] == NULL)
			actual->next_var = NULL;
		else
			actual = actual->next_var;

	}
}

void		ft_init(t_minishell *ms)
{
	ms->line = NULL;
	ms->command = NULL;
	ms->current_workdir = NULL;
	ms->return_value = 0;
	get_next_line(1, NULL);
	ft_init_env_var(ms);
}
static void	main_manager(t_minishell *ms, int i)
{
	if (ft_strchr(ms->command_tab[i], -54))
		manage_pipe(ms, i);
	else if (ft_strchr(ms->command_tab[i], -51) ||
	ft_strchr(ms->command_tab[i], -52)
	|| ft_strchr(ms->command_tab[i], -53))
	{
		ft_strdel_free(&(ms->line));
		ms->line = ft_strdup("");
		manage_inf(ms, i);
		ft_printf("%s", ms->line);
	}
	else
	{
		get_different_option(ms, i);
		ft_printf("%s", ms->line);
		ft_strdel_free(&(ms->line));
		ft_strdel_free(&(ms->command));
	}
}

int			main(int argc __attribute__((unused)),
		char **argv __attribute__((unused)), char **envp)
{
	t_minishell ms[1];
	int			i;

	i = 0;
	ms->envp = envp;
	ft_init(ms);
	ft_add_shlvl(ms);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ft_printf("\033[0;31mMinishell > \033[00m");
	while (get_next_line(0, &ms->line) != 0)
	{
		ft_testing(ms);
		while (ms->command_tab[i])
		{
			int j = 0;
			while (ms->command_tab[j])
			{
				j++;
			}
			main_manager(ms, i);
			//ft_strdel(ms->command_tab[i]);
			i++;
		}
		//ft_strdel(ms->command_tab[i]);
		//ft_memdel((void **)ms->command_tab);
		i = 0;
		ft_printf("\033[0;31mMinishell > \033[00m");
	}
	ft_printf("exit\n");
	ft_exit(ms);
	return (1);
}
