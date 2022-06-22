/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_complete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 04:45:13 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 21:29:25 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	complete_fun_unset_norm(t_env **tmp, char *arg)
{
	if (check_errors_e_u(arg) == 0)
		unset1(tmp, arg);
	if (check_errors_e_u(arg) == 0)
		unset2(tmp, arg);
}

void	complete_fun_unset_norm_01(t_token	*new, int i)
{
	g_global.flag_exit = 1;
	printf("minishell: unset: `%s': not a valid identifier\n", new->arg[i]);
}

void	complete_fun_unset(t_env **tmp, t_token *tmp2)
{
	t_token	*new;
	int		i;

	i = 0;
	new = tmp2;
	g_global.flag_exit = 0;
	while (new->arg[i])
	{
		if (check_errors_e_u(new->arg[i]) == 1)
		{
			complete_fun_unset_norm_01(new, i);
			if (new->arg[i + 1] == NULL)
				break ;
		}
		if (check_for_equal(new->arg[i]) == 1)
		{
			g_global.flag_exit = 1;
			printf("minishell: unset: `%s': not a valid identifier\n",
				new->arg[i]);
			if (new->arg[i + 1] == NULL)
				break ;
		}
		complete_fun_unset_norm(tmp, new->arg[i]);
		i++;
	}
}

void	unset(t_env **tmp, t_token *tmp2)
{
	t_token	*new;

	new = tmp2;
	g_global.flag_exit = 0;
	if (new->opt != NULL)
	{
		g_global.flag_exit = 1;
		printf("minishell: export: %s: invalid option\n", new->opt);
		printf("export: usage: export [-nf] [name[=value] ...] or export -p\n");
		return ;
	}
	if (new->arg != NULL || new->opt != NULL)
	{
		complete_fun_unset(tmp, tmp2);
	}
}
