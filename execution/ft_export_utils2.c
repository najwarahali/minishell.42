/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:33:59 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/12 23:58:51 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_value_of_type_norm(char *value, char *arg, t_env *ev, char *check)
{
	value = env_value(arg);
	free(ev->value);
	ev->value = value;
	free(check);
	return (1);
}

int	change_value_of_type(t_env **tmp, char *arg)
{
	t_env	*ev;
	char	*check;
	char	*value;

	ev = *tmp;
	value = NULL;
	check = NULL;
	check = env_type(arg);
	while (ev)
	{
		if (check_for_equal(arg) == 1)
		{
			if (ft_strncmp(ev->type, check,
					ft_strlen(check)) == 0 && ev != NULL)
				return (change_value_of_type_norm(value, arg, ev, check));
		}
		ev = ev->next;
	}
	if (check != NULL)
		free(check);
	return (0);
}

int	change_arg_if_not_equal(t_env **tmp, char *arg)
{
	t_env	*ev;
	char	*check;
	char	*value;

	ev = *tmp;
	value = NULL;
	check = NULL;
	while (ev)
	{
		if (check_for_equal(arg) == 0)
		{
			if (ft_strncmp(ev->arg,
					arg, ft_strlen(arg)) == 0 && ev->arg != NULL)
			{
				if (check_for_equal(ev->arg) == 0)
				{
					free(ev->arg);
					ev->arg = ft_strdup(arg);
				}
				return (1);
			}
		}
		ev = ev->next;
	}
	return (0);
}

int	case_delet_arg_if_equal_norm(t_env **tmp, t_env *ev, char *type)
{
	free(type);
	del_midd_node(tmp, ev->arg);
	return (0);
}

int	case_delet_arg_if_equal(t_env **tmp, char *arg)
{
	t_env	*ev;
	char	*type;
	int		i;

	i = 0;
	ev = *tmp;
	type = NULL;
	type = env_type_2(arg);
	while (ev)
	{
		if (check_for_equal(arg) == 1)
		{
			if (ft_strncmp(ev->arg, type,
					ft_strlen(type)) == 0 && ev->arg != NULL)
				return (case_delet_arg_if_equal_norm(tmp, ev, type));
		}
		i++;
		ev = ev->next;
	}
	if (type != NULL)
		free(type);
	return (0);
}
