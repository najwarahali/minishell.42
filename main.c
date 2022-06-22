/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:02:42 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/22 02:36:08 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_errors(t_lexer *lexer, t_env **ev)
{
	if (rdr(lexer, ev) == NULL)
		return (0);
	if (error_pipe(lexer) == NULL)
		return (0);
	return (1);
}

t_token	*final_struct_fnc(char *line, t_lexer *tmp, t_env **ev)
{
	t_node	*head;
	t_node	*old;
	t_token	*new_struct;
	char	*new;

	old = NULL;
	new = add_space(line, tmp);
	head = create_linked_list(new, ev);
	head = here_doc_string(tmp, head);
	old = head;
	new_struct = final_struct(old);
	free_fnc2(head);
	free(new);
	return (new_struct);
}

void	pipe_check(t_token *tmp, t_env **ev)
{
	t_token	*new;

	new = tmp;
	if (new != NULL)
	{
		if (new->cmd != NULL && new->next == NULL)
		{
			if (ft_strcmp(new->cmd, "cd") == 0)
				ft_cd(new, ev);
			else if (ft_strcmp(new->cmd, "export") == 0)
				builtins(ev, new);
			else if (ft_strcmp(new->cmd, "unset") == 0)
				builtins(ev, new);
			else if (ft_strcmp(new->cmd, "exit") == 0)
				builtins(ev, new);
			else
				pipe_fnc(new, ev);
		}
		else
			pipe_fnc(new, ev);
	}
}

void	main_fnc(t_token *new, t_lexer *tmp, t_env *ev)
{
	char	*line;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline("minishell $ ");
	if (!line)
		exit_control_d();
	if (*line != '\0')
		add_history(line);
	if (line != NULL)
		tmp = init_lexer(line);
	if (check_errors(tmp, &ev) != 0 && check_error_quote(tmp) != 0)
	{
		new = final_struct_fnc(line, tmp, &ev);
		pipe_check(new, &ev);
		free_fnc_token(new);
		if (errno == 13)
			g_global.flag_exit = 126;
	}
	if (tmp->str != NULL)
		free(tmp->str);
	free(tmp);
}

int	main(int ac, char **av, char **env)
{
	t_lexer	*tmp;
	t_token	*new;
	t_env	*ev;

	(void)av;
	tmp = NULL;
	new = NULL;
	ev = NULL;
	if (ac == 1)
	{
		g_global.fd = dup(0);
		ev = get_env2(env);
		while (1)
		{
			main_fnc(new, tmp, ev);
		}
	}
}
