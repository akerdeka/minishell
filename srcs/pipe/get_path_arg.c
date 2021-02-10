/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasayad <wasayad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:49:14 by akerdeka          #+#    #+#             */
/*   Updated: 2021/02/08 16:31:34 by wasayad          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	gpapin(t_minishell *ms, t_env_var *t
, char **path, char **tempo)
{
	int		id;
	int		i;

	i = -1;
	while (t->next_var && ft_strcmp(t->var, "PATH") != 0)
		t = t->next_var;
	path = ft_split(t->content, ':');
	while (path[++i])
	{
		*tempo = ft_strjoin(path[i], "/");
		*tempo = ft_strjoin_free_s1(*tempo, ms->command);
		id = open(*tempo, O_RDONLY);
		if (id > 0)
			break ;
		close(id);
		ft_strdel_free(tempo);
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
}
