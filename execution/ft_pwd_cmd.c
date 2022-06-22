/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:22:26 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 02:51:39 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_pwd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == 'p' || cmd[i] == 'P') && (cmd[i + 1] == 'w'
				|| cmd[i + 1] == 'W') && (cmd[i + 2] == 'd'
				|| cmd[i + 2] == 'D') && !cmd[i + 3])
			return (0);
		else
			return (1);
	}
	return (1);
}

void	change_pwd_env(t_env **tmp1)
{
	t_env	*ev;
	char	cmd[100];
	char	*str;

	str = NULL;
	getcwd(cmd, sizeof(cmd));
	str = ft_strdup(cmd);
	ev = *tmp1;
	while (ev)
	{
		if (ft_strncmp(ev->type, "PWD=", 4) == 0)
		{
			free(ev->value);
			ev->value = str;
			return ;
		}
		ev = ev->next;
	}
	free(str);
}

void	ft_pwd(t_token *tmp)
{
	char	cwd[100];

	g_global.flag_exit = 0;
	if (tmp->opt == NULL)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
			return ;
		}
		printf("%s\n", cwd);
	}
	else if (tmp->opt != NULL)
	{
		g_global.flag_exit = 1;
		printf("minishell: pwd: %s: invalid option \n%s: usage: pwd [-LP]\n",
			tmp->opt, tmp->cmd);
	}
}
