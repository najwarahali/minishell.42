/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:22:20 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 03:38:53 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_n(t_token *tmp, int i)
{
	while (tmp->arg[i])
	{
		printf("%s", tmp->arg[i]);
		if (tmp->arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (tmp->opt[0] == '-' && tmp->opt[1] == '\0')
		printf("\n");
}

void	ft_echo_0(t_token *tmp)
{
	int	i;

	i = 0;
	ft_echo_0_norm(tmp);
	if (tmp->arg != NULL)
	{
		if (tmp->arg[i][0] == '-')
		{
			while (tmp->arg[i])
			{
				if (check_opt(tmp->arg[i]))
					break ;
				i++;
			}
		}
		ft_print_n(tmp, i);
	}
}

void	ft_echo_1(t_token *tmp)
{
	int	i;

	i = 0;
	printf("%s", tmp->opt);
	printf(" ");
	if (tmp->arg == NULL)
		printf("\n");
	if (tmp->arg != NULL)
	{
		while (tmp->arg[i])
		{
			printf("%s ", tmp->arg[i]);
			i++;
		}
		printf("\n");
	}
}

void	ft_print_echo(t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp->arg[i])
	{
		printf("%s", tmp->arg[i]);
		if (tmp->arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	ft_echo(t_token *tmp)
{
	if (tmp->opt == NULL && tmp->arg == NULL)
		printf("\n");
	if (tmp->opt != NULL)
	{	
		if (check_opt(tmp->opt) == 0)
			ft_echo_0(tmp);
		if (check_opt(tmp->opt) == 1)
			ft_echo_1(tmp);
	}
	if (tmp->opt == NULL && tmp->arg != NULL)
		ft_print_echo(tmp);
}
