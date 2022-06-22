/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:27:39 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 22:57:24 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calcul_add_arg_at_cmd(t_token *tmp)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (tmp->cmd != NULL)
		j++;
	if (tmp->opt != NULL)
		j++;
	if (tmp->arg != NULL)
	{
		i = 0;
		while (tmp->arg[i])
			i++;
	}
	j = j + i;
	return (j);
}

char	**add_arg_at_cmd(t_token *tmp)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = calcul_add_arg_at_cmd(tmp);
	new = malloc(sizeof(char *) * (j + 1));
	j = 0;
	if (tmp->cmd != NULL)
		new[j++] = ft_strdup(tmp->cmd);
	if (tmp->opt != NULL)
		new[j++] = ft_strdup(tmp->opt);
	if (tmp->arg != NULL)
	{
		i = 0;
		while (tmp->arg[i])
			new[j++] = ft_strdup(tmp->arg[i++]);
	}
	new[j] = NULL;
	return (new);
}

char	**get_path(t_env **tmp, char **cmd)
{
	char	*multiple_path;
	char	**r;
	t_env	*ev;

	(void)cmd;
	ev = *tmp;
	while (ev)
	{
		if (!ft_strncmp(ev->data, "PATH=", 5))
		{
			multiple_path = ft_substr(ev->data, 5, ft_strlen(ev->data));
			r = ft_split(multiple_path, ':');
			free (multiple_path);
			return (r);
		}
		ev = ev->next;
	}
	return (NULL);
}

char	**access_path_norm(char **r, char **cmd)
{
	int		i;
	char	*join2;

	i = 0;
	while (r[i])
	{
		r[i] = ft_strjoin(r[i], "/");
		join2 = ft_strjoin(r[i], cmd[0]);
		if (!(access(join2, X_OK)))
		{
			free (cmd[0]);
			cmd[0] = join2;
			ft_free_it(r, ++i);
			return (cmd);
		}
		free (join2);
		i++;
	}
	free(r);
	return (cmd);
}

char	**access_path(t_env **ev, t_token *tmp)
{
	char	**r;
	char	**cmd;

	g_global.flag_exit = 0;
	cmd = add_arg_at_cmd(tmp);
	r = get_path(ev, cmd);
	if (r == NULL)
		return (cmd);
	cmd = access_path_norm(r, cmd);
	return (cmd);
}
