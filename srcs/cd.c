/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharras <acharras@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 17:20:08 by akerdeka          #+#    #+#             */
/*   Updated: 2021/02/09 14:13:50 by acharras         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_cd_errors(t_minishell *ms)
{
	if (errno == 2)
		ft_printf("No such file or directory.\n");
	if (errno == 13)
		ft_printf("Permission denied.\n");
	if (errno == 14)
		ft_printf("Bad address.\n");
	if (errno == 20)
		ft_printf("%s is not a directory.\n", ms->line);
	errno = 0;
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup("");
}

int			ft_cd_norme(t_minishell *ms, int i, t_env_var *temp, char *str)
{
	temp = ms->ev->next_var;
	if (str[0] == '\0')
	{
		while (temp->next_var)
		{
			if (ft_strcmp(temp->var, "HOME") == 0)
				break ;
			temp = temp->next_var;
		}
		chdir(temp->content);
		ft_cd_errors(ms);
		return (0);
	}
	str[i] = '\0';
	chdir(str);
	ft_cd_errors(ms);
	free(str);
	return (1);
}

int			ft_cd(t_minishell *ms, int j)
{
	int			i;
	char		*str;
	t_env_var	*temp;

	i = -1;
	temp = NULL;
	if (!(str = malloc(sizeof(char*) * (ft_strlen(ms->command_tab[j]) + 1))))
		ft_exit(ms);
	str[0] = '\0';
	while (ms->command_tab[j][++i])
	{
		while (ms->command_tab[j][i] == ' ')
			if (ms->command_tab[j][i + 1] != ' ' &&
					ms->command_tab[j][i++ + 1] != '\0')
			{
				ft_printf("Too much arguments.\n");
				free(str);
				return (0);
			}
		str[i] = ms->command_tab[j][i];
	}
	ft_cd_norme(ms, i, temp, str);
	return (1);
}
