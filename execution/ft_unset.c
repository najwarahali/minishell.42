/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:43:59 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/20 22:35:53 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset1_norm(t_env **head, char *type)
{
	t_env	*temp1;
	t_env	*temp2;

	temp1 = *head;
	while (temp1)
	{
		if (ft_strncmp(temp1->type, type, ft_strlen(type)) == 0)
		{
			temp2->next = temp1->next;
			free(temp1->arg);
			free(temp1->value);
			free(temp1->type);
			free(temp1->data);
			free(temp1);
			break ;
		}
		temp2 = temp1;
		temp1 = temp1->next;
	}
}

void	unset1(t_env **head, char *arg)
{
	char	*type;
	t_env	*temp1;

	type = NULL;
	temp1 = *head;
	type = ft_strdup("");
	type = ft_strjoin(type, arg);
	type = ft_charjoin(type, '=');
	if (ft_strncmp((*head)->type, type, ft_strlen(type)) == 0)
	{
		(*head) = (*head)->next;
		temp1->next = NULL;
		free(temp1->arg);
		free(temp1->value);
		free(temp1->type);
		free(temp1->data);
		free(temp1);
	}
	unset1_norm(head, type);
	free(type);
}

void	unset2(t_env **head, char *arg)
{
	t_env	*temp1;
	t_env	*temp2;

	temp1 = *head;
	while (temp1)
	{
		if (temp1->arg && ft_strcmp(temp1->arg, arg) == 0)
		{
			temp2->next = temp1->next;
			free(temp1->arg);
			free(temp1->value);
			free(temp1->type);
			free(temp1->data);
			free(temp1);
			break ;
		}
		temp2 = temp1;
		temp1 = temp1->next;
	}
}
