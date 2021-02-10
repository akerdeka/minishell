/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 11:13:13 by akerdeka          #+#    #+#             */
/*   Updated: 2021/02/10 16:25:03 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_add_env(t_minishell *ms)
{
	t_env_var *temp;
	t_env_var *actual;

	if (!(ms->ev = malloc(sizeof(t_env_var) * 1)))
			ft_exit(ms);
	ms->ev->var = NULL;
	actual = ms->ev;
	if (!(temp = malloc(sizeof(t_env_var) * 1)))
		ft_exit(ms);
	temp->var = ft_strdup("PWD");
	temp->content = ft_strdup(getcwd(ms->current_workdir, 100));
	actual->next_var = temp;
	temp->prev_var = actual;
	actual = actual->next_var;
	if (!(temp = malloc(sizeof(t_env_var) * 1)))
		ft_exit(ms);
	temp->var = ft_strdup("SHLVL");
	temp->content = ft_strdup("2");
	actual->next_var = temp;
	temp->prev_var = actual;
	actual = actual->next_var;
	actual->next_var = NULL;
}

void		ft_add__(t_minishell *ms)
{
	t_env_var	*temp;
	char		*str;

	temp = ms->ev->next_var;
	if (temp)
	{
		while (temp->next_var)
		{
			if ((ft_strcmp("_", temp->var)) == 0)
				break ;
			temp = temp->next_var;
		}
		str = ft_strdup(temp->content);
		free(temp->content);
		temp->content = ft_strjoin(ft_strdup(getcwd(ms->current_workdir, 100)), "/");
		temp->content = ft_strjoin_free_s1(temp->content, ms->line);
		free(str);
	}
}

int			get_command_echo_pipe(t_minishell *ms, int i)
{
	int			j;
	int			k;
	k = 0;
	j = 0;
	while (ms->command_pipe[i][k] && ((ms->command_pipe[i][k] == ' ')
		|| (ms->command_pipe[i][k] == '-' && ms->command_pipe[i][k + 1] == 'n')
		|| (ms->command_pipe[i][k] == 'n' && ms->command_pipe[i][k - 1] == '-')))
		k++;
	j = k;
	if (!(ms->command = ft_substr(ms->command_pipe[i], k, j - k)))
		return (0);
	while (ms->command_pipe[i][j] && ms->command_pipe[i][j] == ' ')
		j++;
	if (!(ms->command_pipe[i] = ft_substr_free(ms->command_pipe[i], j,
	ft_strlen(ms->command_pipe[i]))))
		return (0);
	return (1);
}