#include "../includes/minishell.h"

void	ft_env(t_minishell *ms)
{
	t_env_var	*temp;

	temp = ms->ev;
	ft_strdel(ms->line);
	ms->line = ft_strdup("");
	while (temp->last != 1)
	{
		ms->line = ft_strjoin_free_s1(ms->line, temp->var);
		ms->line = ft_strjoin_free_s1(ms->line, "=");
		ms->line = ft_strjoin_free_s1(ms->line, temp->content);
		ms->line = ft_strjoin_free_s1(ms->line, "\n");
		temp = temp->next_var;
	}
	ms->line = ft_strjoin_free_s1(ms->line, temp->var);
	ms->line = ft_strjoin_free_s1(ms->line, "=");
	ms->line = ft_strjoin_free_s1(ms->line, temp->content);
	ms->line = ft_strjoin_free_s1(ms->line, "\n");
}