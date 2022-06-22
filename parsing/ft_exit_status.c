/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 02:00:29 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/22 02:31:19 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_exit_status(void)
{
	if (g_global.exit_status > 255)
		g_global.exit_status /= 256;
	if (g_global.exit_status == 2)
		g_global.exit_status = 130;
	if (g_global.exit_status == 3)
		g_global.exit_status = 131;
	if (g_global.flag_exit == 1)
		g_global.exit_status = 1;
	if (g_global.flag_exit == 126)
		g_global.exit_status = 126;
	if (g_global.flag_exit == 258)
		g_global.exit_status = 258;
	if (g_global.flag_exit == 127)
		g_global.exit_status = 127;
	if (g_global.flag_heredoc == -1)
	{
		g_global.flag_heredoc = 0;
		g_global.exit_status = 1;
	}
}
