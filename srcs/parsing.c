/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:21:30 by wasayad           #+#    #+#             */
/*   Updated: 2021/02/10 13:31:17 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_dollar_var_norme(t_minishell *ms, t_env_var *temp,
	int j, char *tempo)
{
	int		i;

	i = -1;
	ms->command_tab = ft_split(ms->line, -55);
	while (ms->command_tab[++i + 1])
	{
		j = 0;
		temp = ms->ev;
		if (ms->command_tab[i + 1][(int)ft_strlen(ms->command_tab[i + 1]) - 1]
			== ' ')
			j = 1;
		get_command(ms, i + 1);
		while ((temp = temp->next_var))
			if (ft_strcmp(temp->var, ms->command) == 0)
				break ;
		ft_strdel_free(&(ms->command));
		ms->command = ft_strdup(temp->content);
		ms->command_tab[0] = ft_strjoin_free_s1(ms->command_tab[0],
			ms->command);
		ms->command_tab[0] = ft_strjoin_free_s1(ms->command_tab[0],
			ms->command_tab[i + 1]);
		if (j == 1)
			ms->command_tab[0] = ft_strjoin_free_s1(ms->command_tab[0], tempo);
	}
}

static void	ft_dollar_var(t_minishell *ms)
{
	int			i;
	int			j;
	t_env_var	*temp;
	char		tempo[2];

	i = 0;
	j = 0;
	tempo[0] = -56;
	tempo[1] = '\0';
	temp = NULL;
	if (ft_strchr(ms->line, -55))
	{
		ft_dollar_var_norme(ms, temp, j, tempo);
		free(ms->line);
		ms->line = ft_strdup(ms->command_tab[0]);
		j = -1;
		while (ms->command_tab[++j])
			free(ms->command_tab[j]);
		ft_strdel_free(&(ms->command));
		free(ms->command_tab);
	}
}

static void	ft_delete_useless_space(t_minishell *ms)
{
	char	**temp;
	int		i;

	i = 0;
	if (ft_strchr(ms->line, ' ') != 0)
	{
		temp = ft_split(ms->line, ' ');
		while (temp[i + 1])
		{
			temp[0] = ft_strjoin_free_s1(temp[0], " ");
			temp[0] = ft_strjoin_free_s1(temp[0], temp[i + 1]);
			free(temp[i + 1]);
			i++;
		}
		free(ms->line);
		ms->line = ft_strdup(temp[0]);
		free(temp[0]);
		free(temp);
	}
	i = -1;
	while (ms->line[++i])
		if (ms->line[i] == -56)
			ms->line[i] = ' ';
}

void		ft_testing(t_minishell *ms)
{
	int		i;

	i = 0;
	while (ms->line[i])
	{
		ischaracter_slash(ms, i);
		if (ms->line[i] == '\\' && ms->line[i + 1] == '"')
			str_remove_index(i, ms);
		else if (ms->line[i] == '\\' && ms->line[i + 1] == '\'')
			str_remove_index(i, ms);
		else if (ms->line[i] == '"')
			i = ischaracter_quotes(ms, i);
		else if (ms->line[i] == '\'')
			i = ischaracter_squotes(ms, i);
		i++;
	}
	ft_dollar_var(ms);
	ft_delete_useless_space(ms);
	ms->command_tab = ft_split(ms->line, -50);
}
