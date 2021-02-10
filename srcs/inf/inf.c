/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wasayad <wasayad@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:41:51 by wasayad           #+#    #+#             */
/*   Updated: 2021/02/08 16:41:39 by wasayad          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	manage_command_51(t_minishell *ms, int i, int j)
{
	int		tempstdout;

	tempstdout = dup(1);
	if (!(ms->command_inf = ft_split(ms->command_tab[i], -51)))
		ft_exit(ms);
	free(ms->command_tab[i]);
	ms->command_tab[i] = ft_strdup(ms->command_inf[0]);
	ms->command_tab[i] = ft_strtrim_free(ms->command_tab[i], " ");
	while (ms->command_inf[++j])
	{
		ms->command_inf[j] = ft_strtrim_free(ms->command_inf[j], " ");
		ms->fd = open(ms->command_inf[j], O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (ms->command_inf[j + 1] == NULL)
			break ;
		close(ms->fd);
	}
	dup2(ms->fd, STDOUT_FILENO);
	get_different_option(ms, i);
	close(ms->fd);
	dup2(tempstdout, STDOUT_FILENO);
	write(ms->fd, ms->line, ft_strlen(ms->line));
	close(ms->fd);
	free(ms->line);
	ms->line = ft_strdup("");
}

static void	manage_command_52(t_minishell *ms, int i)
{
	int		fd;
	int		tempstdin;

	if (!(ms->command_inf = ft_split(ms->command_tab[i], -52)))
		ft_exit(ms);
	ms->command_inf[1] = ft_strtrim_free(ms->command_inf[1], " ");
	fd = open(ms->command_inf[1], O_RDONLY);
	tempstdin = dup(0);
	dup2(fd, STDIN_FILENO);
	ft_strdel_free(&(ms->line));
	ms->line = ft_strdup(ms->command_inf[0]);
	ms->line = ft_strtrim_free(ms->line, " ");
	if (ft_strcmp(ms->line, "echo") != 0)
		get_different_option(ms, i);
	else if ((ft_strcmp(ms->line, "echo")) == 0 && fd > 0)
		ms->line = ft_substr_free(ms->line, 0, 0);
	else if (fd < 0)
	{
		ft_printf("%s : No such file or directory\n", ms->command_inf[1]);
		ft_strdel_free(&(ms->line));
		ms->line = ft_strdup("");
	}
	dup2(tempstdin, STDIN_FILENO);
	close(fd);
}

static void	manage_command_53(t_minishell *ms, int i, int j)
{
	int		tempstdout;

	tempstdout = dup(1);
	if (!(ms->command_inf = ft_split(ms->command_tab[i], -53)))
		ft_exit(ms);
	free(ms->command_tab[i]);
	ms->command_tab[i] = ft_strdup(ms->command_inf[0]);
	ms->command_tab[i] = ft_strtrim_free(ms->command_tab[i], " ");
	while (ms->command_inf[++j])
	{
		ms->command_inf[j] = ft_strtrim_free(ms->command_inf[j], " ");
		ms->fd = open(ms->command_inf[j], O_WRONLY | O_CREAT | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		if (ms->command_inf[j + 1] == NULL)
			break ;
		close(ms->fd);
	}
	dup2(ms->fd, STDOUT_FILENO);
	get_different_option(ms, i);
	close(ms->fd);
	dup2(tempstdout, STDOUT_FILENO);
	write(ms->fd, ms->line, ft_strlen(ms->line));
	close(ms->fd);
	free(ms->line);
	ms->line = ft_strdup("");
}

void		manage_inf(t_minishell *ms, int i)
{
	int		j;
	int		k;

	j = 1;
	k = 0;
	if (ft_strchr(ms->command_tab[i], -51))
	{
		manage_command_51(ms, i, j - 1);
	}
	else if (ft_strchr(ms->command_tab[i], -52))
	{
		manage_command_52(ms, i);
	}
	else if (ft_strchr(ms->command_tab[i], -53))
	{
		manage_command_53(ms, i, j - 1);
	}
	j = 0;
	while (ms->command_inf[j])
	{
		free(ms->command_inf[j++]);
	}
}
