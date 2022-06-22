/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_fd_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:58:31 by ydahni            #+#    #+#             */
/*   Updated: 2022/06/20 23:35:52 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_fd_0_heredoc(char *av)
{
	int	fd;

	fd = open(av, O_RDONLY, 0644);
	g_global.flag_exit = 0;
	if (fd == -1)
	{
		write(2, "minishell : ", 12);
		write(2, av, ft_strlen(av));
		write(2, ": No such file or directory\n", 29);
		g_global.exit_status = 1;
	}
	return (fd);
}

int	check_fd_1_heredoc(char *av)
{
	int	fileout;

	fileout = open(av, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	g_global.flag_exit = 0;
	if (fileout == -1)
	{
		write(2, "minishell : ", 12);
		write(2, av, ft_strlen(av));
		write(2, ": Permission denied\n", 21);
		g_global.exit_status = 126;
	}
	return (fileout);
}

int	check_fd_2_heredoc(char *av)
{
	int	fileout;

	fileout = open(av, O_CREAT | O_APPEND | O_WRONLY, 0644);
	g_global.flag_exit = 0;
	if (fileout == -1)
	{
		write(2, "minishell : ", 12);
		write(2, av, ft_strlen(av));
		write(2, ": No such file or directory\n", 29);
		g_global.exit_status = 1;
	}
	return (fileout);
}
