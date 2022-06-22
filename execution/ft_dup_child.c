/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 20:57:56 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/22 00:02:04 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rdr_output(t_token *new)
{
	t_norm	fd;

	while (new->rdr)
	{
		if (new->rdr->type == 0)
		{
			fd.filein = check_fd_0(new->rdr->value);
			dup2(fd.filein, 0);
		}
		if (new->rdr->type == 1)
		{
			fd.fileout = check_fd_1(new->rdr->value);
			if (new->cmd == NULL)
				exit(1);
			else
				dup2(fd.fileout, 1);
		}
		if (new->rdr->type == 2)
		{
			fd.fileappend = check_fd_2(new->rdr->value);
			dup2(fd.fileappend, 1);
		}
		new->rdr = new->rdr->next;
	}
}

void	child_1(t_token *new, t_pip *pip)
{
	if (new->cmd == NULL && new->next == NULL)
		close(pip->file_tem);
	if (pip->save != -1)
	{
		dup2(pip->save, 0);
		close(pip->save);
	}
	if (new->next != NULL)
	{
		dup2(pip->fd[1], 1);
		close(pip->fd[1]);
		close(pip->fd[0]);
	}
}

void	child_2(t_token *new, t_pip *pip, t_env **ev)
{
	if (new->rdr != NULL)
		rdr_output(new);
	if (pip->file_tem != 0)
	{
		dup2(pip->file_tem, 0);
		close(pip->file_tem);
	}
	if (builtins_function(new, ev) == 1)
		exit (0);
	else if (new->cmd != NULL)
	{
		pip->cmd = access_path(ev, new);
		if (execve(pip->cmd[0], pip->cmd, (*ev)->env) == -1)
		{
			if (new->cmd[0] == '\0')
				exit (0);
			write(2, "minishell : ", 12);
			write(2, pip->cmd[0], ft_strlen(pip->cmd[0]));
			write(2, ": command not found\n", 20);
			exit (127);
		}
	}
}
