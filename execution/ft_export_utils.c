/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:20:17 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/12 23:58:51 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_double_arg(t_env **tmp, char *arg)
{
	t_env	*ev;

	ev = *tmp;
	while (ev)
	{
		if (check_for_equal(arg) == 0)
		{
			if (ft_strncmp(ev->type, arg, ft_strlen(arg)) == 0 && ev != NULL)
				return (1);
		}
		ev = ev->next;
	}
	return (0);
}

int	ft_isalnum_2(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else if (c == 61 || c == 95)
		return (1);
	else
		return (0);
}

int	check_for_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	complete_fun_export_norm(char *arg, t_env **tmp)
{
	t_env	*n;

	if (check_errors_e_u(arg) == 0
		&& change_value_of_type(tmp, arg) == 0
		&& case_delet_arg_if_equal(tmp, arg) == 0 && check_for_equal(arg) == 1)
	{
		n = creation_nodes_export(arg);
		add_node_last_env(n, tmp);
	}
	if (check_errors_e_u(arg) == 0
		&& change_arg_if_not_equal(tmp, arg) == 0
		&& check_for_equal(arg) == 0)
	{
		if (check_double_arg(tmp, arg) == 0)
		{
			n = creation_nodes_export(arg);
			add_node_last_env(n, tmp);
		}
	}
}
