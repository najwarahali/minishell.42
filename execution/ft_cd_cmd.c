/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:22:07 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 02:07:48 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_home(t_env **env)
{
	t_env	*tmp_env;
	int		chgdir;

	tmp_env = *env;
	change_old_pwd(env);
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->type, "HOME=") == 0)
			chgdir = chdir(tmp_env->value);
		tmp_env = tmp_env->next;
	}
	if (check_unset_home(env) == 1)
	{	
		g_global.flag_exit = 1;
		printf("minishell: cd: HOME not set\n");
	}
}

void	ft_cd_home_child(t_env **env)
{
	t_env	*tmp_env;
	int		chgdir;

	tmp_env = *env;
	change_old_pwd(env);
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->type, "HOME=") == 0)
			chgdir = chdir(tmp_env->value);
		tmp_env = tmp_env->next;
	}
	if (check_unset_home(env) == 1)
	{	
		write(2, "minishell: cd: HOME not set\n", 29);
		exit(1);
	}
}

void	ft_cd_(t_env **env)
{
	t_env	*tmp_env;
	int		chgdir;

	tmp_env = *env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->type, "OLDPWD=") == 0)
		{
			printf("%s\n", tmp_env->value);
			chgdir = chdir(tmp_env->value);
			if (chgdir < 0)
			{
				printf("minishell: cd: OLDPWD not set\n");
				break ;
			}
			else
				break ;
		}
		tmp_env = tmp_env->next;
	}
}

int	ft_cd_old(t_token *tmp, t_env **env)
{
	int	count_;

	count_ = ft_count_(tmp->opt);
	if (tmp->opt != NULL && ft_check_(tmp->opt) == 0)
	{
		if (count_ == 1)
		{
			ft_cd_(env);
			return (1);
		}
		if (count_ == 2)
		{
			ft_cd_home(env);
			return (1);
		}
		if (count_ > 2)
		{
			g_global.flag_exit = 1;
			printf("minishell: cd: --: invalid option\n");
			printf("cd: usage: cd [-L|-P] [dir]\n");
			return (1);
		}
	}
	return (0);
}

void	ft_cd(t_token *tmp, t_env **env)
{
	int	chgdir;

	g_global.flag_exit = 0;
	if (tmp->arg[0] == NULL)
	{
		free (tmp->arg);
		tmp->arg = NULL;
	}
	if (ft_cd_old(tmp, env) == 1)
		return ;
	if ((tmp->arg == NULL && tmp->cmd != NULL)
		|| (tmp->arg[0][0] == '~' && !tmp->arg[0][1]))
		ft_cd_home(env);
	else if (tmp->arg != NULL && tmp->cmd != NULL)
	{
		change_old_pwd(env);
		chgdir = chdir(tmp->arg[0]);
		if (chgdir < 0)
		{
			g_global.flag_exit = 1;
			perror("minishell : cd");
		}
	}
}
