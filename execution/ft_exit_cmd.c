/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 00:40:18 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 02:08:02 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_digit_exit_01(char **arg)
{
	int	i;
	int	j;

	i = 0;
	if (arg != NULL)
	{
		while (arg[i])
		{
			j = 0;
			while (arg[i][j])
			{
				if (ft_isdigit(arg[i][j]) == 1)
					j++;
				else
					return (0);
			}
			i++;
		}
	}
	return (1);
}

int	check_digit_exit(char *arg)
{
	int	i;

	i = 0;
	if (arg != NULL)
	{
		while (arg[i])
		{
			if (ft_isdigit(arg[i]) == 1)
				i++;
			else
				return (0);
		}
	}
	return (1);
}

void	ft_exit_complete(t_token *new)
{
	if (new->opt != NULL)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", new->opt);
		exit(255);
	}
	if (check_digit_exit(new->arg[0]) == 0 && new->arg[0] != NULL)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", new->arg[0]);
		exit(255);
	}
}

void	ft_exit(t_token *new)
{
	if (new->arg[0] == NULL)
	{
		printf("exit\n");
		exit(g_global.exit_status);
	}
	if (check_digit_exit_01(new->arg) == 1 && new->arg[1] != NULL)
	{
		g_global.flag_exit = 1;
		printf ("exit \nminishell : exit: too many arguments\n");
		return ;
	}
	if (check_digit_exit(new->arg[0]) == 1
		&& new->arg[0] != NULL && new->opt == NULL)
	{
		printf("exit\n");
		exit(ft_atoi(new->arg[0]));
	}
	ft_exit_complete(new);
}

void	ft_exit_child(t_token *new)
{
	if (new->arg == NULL)
		exit(g_global.exit_status);
	if (check_digit_exit_01(new->arg) == 1 && new->arg[1] != NULL)
	{
		printf ("minishell : exit: too many arguments\n");
		exit(1);
	}
	if (check_digit_exit(new->arg[0]) == 1
		&& new->arg != NULL && new->opt == NULL)
		exit(ft_atoi(new->arg[0]));
	if (new->opt != NULL)
	{
		printf("minishell: exit: %s: numeric argument required\n", new->opt);
		exit(255);
	}
	if (check_digit_exit(new->arg[0]) == 0 && new->arg != NULL)
	{
		printf("minishell: exit: %s: numeric argument required\n", new->arg[0]);
		exit(255);
	}
}
