/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:40:39 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/22 22:11:31 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	here_doc_fnc(t_rdr *new, t_env **ev)
{
	char	*str;
	char	*new_str;
	int		fd[2];

	pipe(fd);
	str = readline(">");
	new_str = NULL;
	while (ft_strcmp(new->value, str) != 0)
	{
		new_str = new_string_of_here_doc_output(str, ev);
		write(fd[1], new_str, ft_strlen(new_str));
		write(fd[1], "\n", 1);
		free(new_str);
		free(str);
		str = readline(">");
	}
	free(str);
	close(fd[1]);
	return (fd[0]);
}

void	rdr_output_here_doc_utl_2(t_rdr *new)
{
	int	fileout;
	int	filein;
	int	fileappend;

	if (new->type == 0)
		filein = check_fd_0_heredoc(new->value);
	if (new->type == 1)
		fileout = check_fd_1_heredoc(new->value);
	if (new->type == 2)
		fileappend = check_fd_2_heredoc(new->value);
}

t_token	*create_fd_after_herdoc_without_cmd(t_rdr *r, t_token *new)
{
	r = new->rdr;
	while (r)
	{
		if ((r->type == 0 || r->type == 1 || r->type == 2) && new->cmd == NULL)
		{
			rdr_output_here_doc_utl_2(r);
			return (NULL);
		}
		else if ((r->type == 0 || r->type == 1
				|| r->type == 2) && new->cmd != NULL)
			return (new);
		r = r->next;
	}
	return (new);
}

t_token	*here_doc(t_token *new, t_pip *pip, t_env **ev)
{
	t_rdr	*r;

	r = new->rdr;
	while (r)
	{
		if (r->type == 3)
		{
			signal(SIGINT, handler);
			g_global.flag_heredoc = 1;
			pip->file_tem = here_doc_fnc(r, ev);
			if (g_global.flag_heredoc == -1)
			{
				dup(g_global.fd);
				return (NULL);
			}
			g_global.flag_heredoc = 0;
			dup(g_global.fd);
		}
		r = r->next;
	}
	new = create_fd_after_herdoc_without_cmd(r, new);
	if (new == NULL)
		return (NULL);
	return (new);
}
