# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/05 19:29:53 by ydahni            #+#    #+#              #
#    Updated: 2022/06/21 23:34:11 by ydahni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


minishell = minishell
FLAGS =  -lreadline -Wextra -Wall -Werror
CONTROL = @stty -echoctl
RDLINE  := -lreadline -L/Users/ydahni/goinfre/.brew/opt/readline/lib -I /Users/ydahni/goinfre/.brew/opt/readline/include
CC = cc
SRC = ./libft/ft_bzero.c ./libft/ft_isalnum.c ./libft/ft_isalpha.c ./libft/ft_isascii.c ./libft/ft_isdigit.c ./libft/ft_isprint.c ./libft/ft_memcpy.c ./libft/ft_memmove.c ./libft/ft_memset.c \
	  ./libft/ft_strlcpy.c ./libft/ft_strlen.c ./libft/ft_tolower.c ./libft/ft_toupper.c ./libft/ft_strncmp.c ./libft/ft_memcmp.c ./libft/ft_strlcat.c ./libft/ft_strchr.c ./libft/ft_strrchr.c \
	  ./libft/ft_memchr.c ./libft/ft_strnstr.c ./libft/ft_atoi.c ./libft/ft_substr.c ./libft/ft_strjoin.c ./libft/ft_calloc.c ./libft/ft_strdup.c  ./libft/ft_strmapi.c \
	  ./libft/ft_putchar_fd.c  ./libft/ft_putstr_fd.c ./libft/ft_putnbr_fd.c ./libft/ft_putendl_fd.c ./libft/ft_strtrim.c ./libft/ft_split.c ./libft/ft_itoa.c ./libft/ft_striteri.c \
	  ./execution/ft_builtins_fnc.c ./execution/ft_cd_cmd_complete.c ./execution/ft_cd_cmd.c ./execution/ft_check_fd_heredoc.c ./execution/ft_create_and_check_fd.c ./execution/ft_dup_child.c \
	  ./execution/ft_echo_cmd_utl.c ./execution/ft_echo_cmd.c ./execution/ft_exit_cmd.c ./execution/ft_export_utils.c ./execution/ft_export_utils2.c ./execution/ft_export_utils3.c ./execution/ft_export.c \
	  ./execution/ft_get_path.c ./execution/ft_here_doc.c ./execution/ft_pipe.c ./execution/ft_pwd_cmd.c ./execution/ft_rdr_outpout.c ./execution/ft_unset_complete.c ./execution/ft_unset.c ./execution/new_env_utl.c \
	  ./execution/new_env.c \
	  ./parsing/add_last_nodes.c ./parsing/add_space.c ./parsing/calcul_rdr_pipe.c ./parsing/check_errors_quote.c ./parsing/check_syntax_errors_double_rdr.c ./parsing/check_syntax_errors_pipe_complete.c \
	  ./parsing/check_syntax_errors_pipe.c ./parsing/check_syntax_errors_rdr.c ./parsing/check_syntax_errors_single_rdr.c ./parsing/creation_nodes.c ./parsing/creation_of_linked_list.c \
	  ./parsing/define_cmd_after_pipe.c ./parsing/final_struct.c ./parsing/free_functions_2.c ./parsing/free_functions.c ./parsing/ft_exit_status.c ./parsing/get_env_dollar_sign.c ./parsing/here_doc_string.c \
	  ./parsing/parse_qoutes_complete.c ./parsing/parse_qoutes.c ./parsing/parsing_utl.c ./parsing/rdr_redirect_erros.c ./parsing/read_line.c ./parsing/split_add_number.c ./parsing/split_space.c ./parsing/here_doc_string_output.c \
	  main.c \

OBJ = ${SRC:.c=.o}

all : minishell
	
$(minishell): $(OBJ)
	$(CONTROL)	
	@$(CC) $(FLAGS) $(RDLINE) $(OBJ) -o minishell
	@tput setaf 2; echo "MINISHELL IS READY"

clean :
	@rm -f $(OBJ)
	@tput setaf 1; echo "CLEAN COMPLET"

fclean : clean
	@rm -f minishell

re: fclean all 