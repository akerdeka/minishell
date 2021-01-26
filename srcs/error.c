/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerdeka <akerdeka@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:39:27 by akerdeka          #+#    #+#             */
/*   Updated: 2021/01/26 15:41:32 by akerdeka         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void    ft_error(t_minishell *ms)
{
    ft_error_ls(ms);
}
void    ft_error_ls(t_minishell *ms)
{
    int     i;
    char    *str;
    char    *check;
    i = 3;
    str = ft_strdup(&ms->line[i]);
    check = ft_substr(ms->line, 0, 2);
    if (ft_strcmp(check, "ls") == 0)
    {
        if (ms->line[i] != '|' && ms->line[i] != '-' && ms->line[i] != '>' && ms->line[i] != '<' &&
            ms->line[i] != ';' && ms->line[i - 1] != ';' && ms->line[2] != '\0')
        {
            ft_printf("%s: No such file or directory\n", str);
            free(ms->command_tab[0]);
            ms->command_tab[0] = NULL;
        }
    }
}