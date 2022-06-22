/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 22:43:25 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/13 00:32:42 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_env **tmp)
{
	t_env	*ev;

	ev = *tmp;
	while (ev)
	{
		if (ev->type[0] != '\0')
			printf("%s", ev->type);
		if (ev->type[0] != '\0')
			printf("%s", ev->value);
		if (ev->type[0] != '\0')
			printf("\n");
		ev = ev->next;
	}
}

void	print_export(t_env **tmp)
{
	t_env	*ev;

	ev = *tmp;
	while (ev)
	{
		if (ev->value[0] != '\0' && ev != NULL)
			printf("declare -x %s", ev->type);
		else if (ev->type != NULL
			&& ev->value[0] == '\0' && (ev->arg == NULL || ev->arg[0] == '\0'))
		{
			printf("declare -x %s", ev->type);
		}
		if (ev->arg == NULL || ev->arg[0] == '\0')
			printf("\"%s\"\n", ev->value);
		if (ev->arg[0] != '\0')
			printf("declare -x %s\n", ev->arg);
		ev = ev->next;
	}
}

void	complete_fun_export(t_env **tmp, t_token *tmp2)
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
			g_global.flag_exit = 1;
			printf("minishell: export: `%s': not a valid identifier\n",
				new->arg[i]);
			if (new->arg[i + 1] == NULL)
				break ;
		}
		complete_fun_export_norm(new->arg[i], tmp);
		i++;
	}
}

void	ft_export(t_env **tmp, t_token *tmp2)
{
	t_token	*new;

	new = tmp2;
	g_global.flag_exit = 0;
	change_pwd_env(tmp);
	if (new->opt != NULL)
	{
		g_global.flag_exit = 1;
		printf("minishell: export: %s: invalid option\n", new->opt);
		printf("export: usage: export [-nf] [name[=value] ...] or export -p\n");
		return ;
	}
	if (new->arg != NULL || new->opt != NULL)
	{
		complete_fun_export(tmp, tmp2);
	}
}
