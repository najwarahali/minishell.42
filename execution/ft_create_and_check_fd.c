/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_and_check_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrahali <nrahali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:57:07 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/20 22:44:26 by nrahali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_fd_0(char *av)
{
	int		fd;

	fd = open(av, O_RDONLY, 0644);
	g_global.flag_exit = 0;
	if (fd == -1)
	{
		write(2, "minishell : ", 12);
		write(2, av, ft_strlen(av));
		write(2, ": No such file or directory\n", 29);
		g_global.flag_exit = 1;
		exit (1);
	}
	return (fd);
}

int	check_fd_1(char *av)
{
	int	fileout;

	fileout = open(av, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	g_global.flag_exit = 0;
	if (fileout == -1)
	{
		write(2, "minishell : ", 12);
		write(2, av, ft_strlen(av));
		write(2, ": Permission denied\n", 21);
		g_global.flag_exit = 126;
		exit (126);
	}
	return (fileout);
}

int	check_fd_2(char *av)
{
	int	fileout;

	fileout = open(av, O_CREAT | O_APPEND | O_WRONLY, 0644);
	g_global.flag_exit = 0;
	if (fileout == -1)
	{
		write(2, "minishell : ", 12);
		write(2, av, ft_strlen(av));
		write(2, ": No such file or directory\n", 29);
		g_global.flag_exit = 1;
		exit (1);
	}
	return (fileout);
}
