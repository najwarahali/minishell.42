/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 23:40:05 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/22 02:31:33 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sign)
{
	(void)sign;
	if (g_global.flag_heredoc == 1)
	{
		g_global.flag_heredoc = -1;
		close(0);
	}
	else
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_global.flag_exit = 1;
	return ;
}

void	exit_control_d(void)
{
	printf("exit");
	if (g_global.exit_status > 255)
		g_global.exit_status /= 256;
	exit(g_global.exit_status);
}
