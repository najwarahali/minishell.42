/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rdr_outpout.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:00:06 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 23:38:42 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rdr_output_here_doc_utl(t_rdr *new)
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

void	create_fd_befor_herdoc_without_cmd(t_rdr *r)
{
	while (r)
	{
		if (r->type == 0 || r->type == 1 || r->type == 2)
			rdr_output_here_doc_utl(r);
		r = r->next;
	}
}

t_token	*rdr_output_here_doc(t_token *new)
{
	t_rdr	*r;

	r = new->rdr;
	while (new)
	{
		if (new->cmd != NULL)
			break ;
		if (new->rdr != NULL && new->cmd == NULL)
		{
			create_fd_befor_herdoc_without_cmd(r);
			r = new->rdr;
			while (r)
			{
				if (r->type == 3)
					return (new);
				r = r->next;
			}
		}
		new = new->next;
	}
	return (new);
}
