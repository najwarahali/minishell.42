/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:45:40 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/22 04:52:46 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_pid(t_token *tmp)
{
	t_token	*new;

	new = tmp;
	g_global.flag_exit = 0;
	while (new)
	{
		waitpid(new->pid, &g_global.exit_status, 0);
		WIFEXITED(g_global.exit_status);
		new = new->next;
	}
}

void	parent(t_token *new, t_env **ev, t_pip *pip)
{
	if (new->next != NULL)
	{
		if (pipe(pip->fd) == -1)
			perror("pipe error");
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pip->fid = fork();
	if (pip->fid == -1)
		perror("fork error");
	if (pip->fid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (new->cmd == NULL && pip->file_tem != 0)
		{
			close(pip->file_tem);
			exit(0);
		}
		child_1(new, pip);
		child_2(new, pip, ev);
	}
	else
		parent_main(new, pip);
}

void	pipe_fnc_complete(t_token *new, t_env **ev, t_pip *pip)
{
	while (new)
	{
		pip->file_tem = 0;
		if (new->rdr != NULL)
		{
			new = here_doc(new, pip, ev);
			if (new == NULL)
				return ;
		}
		parent(new, ev, pip);
		new->pid = pip->fid;
		new = new->next;
	}
}

void	pipe_fnc(t_token *tmp, t_env **ev)
{
	t_token	*new;
	t_pip	*pip;

	new = tmp;
	pip = malloc(sizeof(t_pip));
	pip->save = -1;
	new->pid = 0;
	pip->str = NULL;
	if (new->cmd == NULL && new->rdr != NULL && new->rdr->type != 3)
		new = rdr_output_here_doc(new);
	pipe_fnc_complete(new, ev, pip);
	wait_pid(tmp);
	free(pip);
}

void	parent_main(t_token *new, t_pip *pip)
{
	if (pip->file_tem != 0)
		close(pip->file_tem);
	if (pip->save != -1)
		close(pip->save);
	pip->save = pip->fd[0];
	if (new->next != NULL)
		close(pip->fd[1]);
}
