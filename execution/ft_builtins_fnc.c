/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_fnc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:22:00 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 02:07:40 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtins_function_complete(t_token *tmp, t_env **ev)
{
	if (!ft_check_echo(tmp->cmd))
	{
		ft_echo(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp->cmd, "cd") == 0)
	{
		ft_cd_home_child(ev);
		return (1);
	}
	else if (!ft_check_cd_name(tmp->cmd))
		return (1);
	else if (!ft_check_pwd(tmp->cmd))
	{
		ft_pwd(tmp);
		return (1);
	}
	else if (ft_strcmp(tmp->cmd, "export") == 0)
	{
		ft_export(ev, tmp);
		if (tmp->arg == NULL && tmp->opt == NULL)
			print_export(ev);
		return (1);
	}
	return (0);
}

int	builtins_function(t_token *tmp, t_env **ev)
{
	if (tmp->arg[0] == NULL)
		tmp->arg = NULL;
	if (tmp->cmd != NULL)
	{
		if (builtins_function_complete(tmp, ev) == 1)
			return (1);
		else if (ft_strcmp(tmp->cmd, "env") == 0)
		{
			change_pwd_env(ev);
			if (tmp->arg != NULL)
				perror("env");
			if (tmp->arg == NULL)
				print_env(ev);
			return (1);
		}
		else if (ft_strcmp(tmp->cmd, "exit") == 0)
		{
			ft_exit_child(tmp);
			return (1);
		}
	}
	return (0);
}

void	builtins(t_env **tmp, t_token *new)
{
	if (ft_strcmp(new->cmd, "export") == 0)
	{
		if (new->next == NULL)
		{
			ft_export(tmp, new);
			if (new->arg[0] == NULL && new->opt == NULL)
				print_export(tmp);
		}
	}
	if (ft_strcmp(new->cmd, "unset") == 0)
		unset(tmp, new);
	if (ft_strcmp(new->cmd, "exit") == 0)
	{
		if (new->next == NULL)
			ft_exit(new);
	}
}
