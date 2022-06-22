/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cmd_complete.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 00:46:17 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 02:07:44 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_(char	*opt)
{
	int	i;

	i = 0;
	if (!opt)
		return (-1);
	while (opt[i])
	{
		if (opt[i] == '-')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_count_(char	*opt)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!opt)
		return (-1);
	while (opt[i])
	{
		if (opt[i] == '-')
			count++;
		i++;
	}
	return (count);
}

int	ft_check_cd_name(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == 'c' || cmd[i] == 'C')
			&& (cmd[i + 1] == 'd' || cmd[i + 1] == 'D') && !cmd[i + 2])
			return (0);
		else
			return (1);
	}
	return (1);
}

int	check_unset_home(t_env **env)
{
	t_env	*tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->type, "HOME=") == 0)
			return (0);
		tmp_env = tmp_env->next;
	}
	return (1);
}

void	change_old_pwd(t_env **env)
{
	t_env	*ev;
	char	cwd[100];
	char	*str;

	str = NULL;
	ev = *env;
	getcwd(cwd, sizeof(cwd));
	str = ft_strdup(cwd);
	while (ev)
	{
		if (ft_strncmp(ev->type, "OLDPWD=", 7) == 0)
		{
			free(ev->value);
			ev->value = str;
			return ;
		}
		ev = ev->next;
	}
	free(str);
}
