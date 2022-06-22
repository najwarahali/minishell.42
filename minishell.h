/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydahni <ydahni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 03:22:28 by nrahali           #+#    #+#             */
/*   Updated: 2022/06/22 02:37:22 by ydahni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include <signal.h>
# include <errno.h>

////////////////////////struct_utl/////////////////////////

typedef struct global
{
	int	exit_status;
	int	flag_exit;
	int	flag_heredoc;
	int	fd;
}	t_global;

t_global	g_global;

typedef struct env
{
	int			i;
	char		*data;
	char		*value;
	char		*type;
	char		*arg;
	char		**env;
	struct env	*next;
}	t_env;

typedef struct pip
{
	int		fd[2];
	int		fid;
	int		save;
	char	**cmd;
	char	*str;
	int		file_tem;
	char	*old_str;
}	t_pip;

typedef struct norm
{
	int		i;
	int		j;
	int		h;
	int		l;
	int		f;
	int		filein;
	int		fileout;
	int		fileappend;
	int		counter;
	char	*p;
	char	**split;
}	t_norm;

typedef struct lexer
{
	char	*str;
	char	*p;
	char	c;
	int		i;
	int		str_size;
}	t_lexer;

typedef struct node
{
	int			i;
	char		*data;
	struct node	*next;
	enum
	{
		TOKEN_INPUT,
		TOKEN_OUTPUT,
		TOKEN_APPEND,
		TOKEN_HEREDOC,
		TOKEN_CMD,
		TOKEN_PIPE,
		TOKEN_ARG,
		TOKEN_SIGN,
		TOKEN_OPTION,
		TOKEN_SQUOTE,
		TOKEN_DQOUTE,
		TOKEN_DOLLARSIGN,
	}	e_type;
}	t_node;

typedef struct rdr
{
	int			type;
	char		*value;
	struct rdr	*next;
}	t_rdr;

typedef struct token
{
	char			*cmd;
	char			*opt;
	char			**arg;
	t_rdr			*rdr;
	int				pid;
	struct token	*next;
}	t_token;

///////////////////////parsing///////////////////

//add_space
char	*add_space(char *line, t_lexer *tmp);
char	*add_space_pipe(char *str, t_lexer *tmp);
char	*add_space_rdr(char *str, t_lexer *tmp);
void	add_space_rdr_norm(char *save, char *str, int i, int j);
char	*add_space_2(char *str, t_lexer *tmp);

//parse_qoutes
t_node	*check_qoute(t_node *tmp, t_env **ev);
char	*quote(t_node *line, t_env **ev);
char	*skip_single_qoutes(t_node *line, char *str_quote);
char	*skip_double_qoutes(t_node *line, t_env **ev, char *str_quote);
char	*skip_double_qoutes_2(t_node *line, t_env **ev, char *str_quote);

//parse_qoutes_complete
char	*define_string(t_node *line, t_env **ev, char *str_quote);
char	*add_env_sting(t_node *line, t_env **ev, char *str_quote);
char	*add_exit_code(t_node *line, char *str_quote);

//calcule_rdr_pipe
int		calcul_c(t_lexer *lexer, int c);
int		calcul_q(t_lexer *line);
int		calcul_quote1(t_lexer *line, int j);
int		calcul_dquote(t_lexer *line);
int		calcul_squote(t_lexer *line);

//check_errors_qoute
int		check_error_quote(t_lexer *tmp);
t_lexer	*single_qoutes_errors(t_lexer *lexer);
t_lexer	*double_qoutes_errors(t_lexer *lexer);
int		quote_error(t_lexer *lexer, int c);

//check_syntax_errors_double_rdr
void	printf_error(t_lexer *lexer, int c);
void	printf_error_norm(int i, int c);
int		calcul_rdr(t_lexer *lexer, int c);
t_lexer	*double_rdr_error(t_lexer *lexer, t_norm *l);
t_lexer	*double_rdr_error_norm(t_lexer *lexer, t_norm *l);

//check_syntax_errors_pipe
t_lexer	*error_pipe(t_lexer *tmp);
t_lexer	*error_pipe_complete(t_lexer *lexer, t_norm *l);
t_lexer	*error_pipe_norm(t_lexer *lexer, t_norm *l);

//check_syntax_errors_pipe_complete
t_lexer	*error_pipe_norm_1(t_lexer *lexer, t_norm *l);
t_lexer	*error_pipe_norm_2(t_lexer *lexer, t_norm *l);
t_lexer	*error_pipe_norm_3(t_lexer *lexer, t_norm *l);

//check_syntax_errors_rdr
t_lexer	*rdr(t_lexer *tmp, t_env **ev);
t_lexer	*rdr_norm1(t_lexer *lexer, t_norm *l, t_env **ev);
t_lexer	*rdr_norm(t_lexer *lexer, t_norm *l, t_env **ev);

//check_syntax_errors_single_rdr
t_lexer	*singl_rdr_error_norm1(t_lexer *lexer, t_norm *l);
t_lexer	*singl_rdr_error_norm(t_lexer *lexer, t_norm *l);
t_lexer	*singl_rdr_error(t_lexer *lexer, t_norm *l);

//creation_nodes
t_node	*creation_nodes(char *value, int type);
t_env	*creation_nodes_env(char *values);
t_env	*creation_nodes_export(char *values);
t_token	*init_token_f(t_token *new);
t_lexer	*init_lexer(char *src);

//add_last_nodes
void	add_node_last_env(t_env *temp, t_env **head);
void	add_node_last(t_node *temp, t_node **head);
void	add_node_last_rdr(t_rdr *temp, t_rdr **head);
void	add_node_last_token_f(t_token *temp, t_token **head);

//creation_of_linked_list
t_node	*create_linked_list(char *tmp, t_env **ev);
t_node	*create_linked_list_norm(t_norm *l, t_node *arg, t_node *new);
t_node	*create_linked_list_norm1(t_norm *l, t_node *new);
t_node	*check_all(t_node *arg, t_env **ev);
int		check_option(t_node *new);

//define_cmd_after_pipe
int		check_arg(t_node *new);
int		check_cmd(t_node *new);
t_node	*check_optin(t_node *tmp);
t_node	*pipe_add(t_node *tmp);
t_node	*pipe_add_norm(t_node *arg);

//free_functions
void	ft_free_it(char	**cmd, int i);
void	free_fnc_arg(char **split);
void	free_fnc(char **split);
void	free_spc(t_norm *l);
void	fnc_free_spc(char *str, t_norm *l);

//free_functions_2
void	free_fnc2(t_node *s);
void	free_fnc_token(t_token *new);
void	free_fnc_token_complete(t_token *new, t_token *tmp);
void	free_norm(t_norm *l);

//get_env_dollar_sign
char	*get_env(char *env, char *str, t_env **ev);
char	*env(t_node *line, t_env **ev);
char	*string_after_dollar_sign(char *str_quote, t_node *line);

//final_struct
t_token	*final_struct(t_node *old);
t_token	*final_struct_norm(t_token *new, t_node *old, t_norm *l);
t_token	*final_struct_norm2(t_token *new, t_node *old, t_rdr *tmp);
int		calcul_arg_allocation(t_node *old);

//here_doc_string
t_node	*here_doc_string(t_lexer *tmp, t_node *tmp2);
char	*here_doc_string_norm(t_lexer *lexer, char *str);
char	*get_str_old(t_lexer *lexer, char *str);
char	*single_qoutes_her_doc(t_lexer *lexer, char *str);
char	*double_qoutes_her_doc(t_lexer *lexer, char *str);

//split_space
char	**ft_split_a(char *s, char c);
int		ft_counterchar_a(char *s, int x, char c, char *tmp);
int		ft_counterword_a(char *s, char c, char *tmp);

//split_add_number
t_norm	*add_number(char *s);
t_norm	*add_number_double_qoutes(t_norm *l, char *s);
t_norm	*add_number_single_qoutes(t_norm *l, char *s);

//parsing_utl
char	*ft_charjoin(char *s1, char c);
int		ft_strcmp(char *s1, char *s2);
void	skip_whitespace(t_lexer *lexer);

//rdr_redirect_erros
t_lexer	*error_redirect(t_lexer *lexer, t_norm *l, t_env **ev);
t_lexer	*print_error_redirect(char *str, char *env);
char	*error_redirect_norm(t_lexer *lexer, t_norm *l);
char	*get_env_new(char *str, t_env **ev);
char	*get_env_new_1(char *str);

//read_line
void	handler(int sign);
void	exit_control_d(void);
void	rl_replace_line(const char *text, int clear_undo);

//void	check_exit_status(void)
void	check_exit_status(void);

//here_doc_string_output.c
char	*new_string_of_here_doc_output(char	*tmp, t_env **ev);
char	*string_here_doc_new(t_node *line, t_env **ev);

////////////////////////execution/////////////////////////

//ft_builtins_fnc
void	builtins(t_env **tmp, t_token *new);
int		builtins_function(t_token *tmp, t_env **ev);
int		builtins_function_complete(t_token *tmp, t_env **ev);

//ft_cd_cmd_complete
int		ft_check_(char *opt);
int		ft_count_(char	*opt);
int		ft_check_cd_name(char *cmd);
int		check_unset_home(t_env **env);
void	change_old_pwd(t_env **env);

//ft_cd_cmd
void	ft_cd_home(t_env **env);
void	ft_cd_home_child(t_env **env);
void	ft_cd_(t_env **env);
int		ft_cd_old(t_token *tmp, t_env **env);
void	ft_cd(t_token *tmp, t_env **env);

//ft_check_fd_heredoc
int		check_fd_0_heredoc(char *av);
int		check_fd_1_heredoc(char *av);
int		check_fd_2_heredoc(char *av);

//ft_echo_cmd_utl
int		ft_check_echo(char *cmd);
int		check_opt(char *opt);
void	ft_echo_0_norm(t_token *tmp);

//ft_echo_cmd
void	ft_print_n(t_token *tmp, int i);
void	ft_echo_0(t_token *tmp);
void	ft_echo_1(t_token *tmp);
void	ft_print_echo(t_token *tmp);
void	ft_echo(t_token *tmp);

//ft_exit_cmd
int		check_digit_exit_01(char **arg);
int		check_digit_exit(char *arg);
void	ft_exit_complete(t_token *new);
void	ft_exit(t_token *new);
void	ft_exit_child(t_token *new);

//ft_export_utils
int		check_double_arg(t_env **tmp, char *arg);
int		ft_isalnum_2(int c);
int		check_for_equal(char *str);
void	complete_fun_export_norm(char *arg, t_env **tmp);

//ft_export_utils2
int		change_value_of_type_norm(char *value, char *arg,
			t_env *ev, char *check);
int		change_value_of_type(t_env **tmp, char *arg);
int		change_arg_if_not_equal(t_env **tmp, char *arg);
int		case_delet_arg_if_equal_norm(t_env **tmp, t_env *ev, char *type);
int		case_delet_arg_if_equal(t_env **tmp, char *arg);

//ft_export_utils3
int		check_errors_e_u_norm(char *arg, char *type);
int		check_errors_e_u_norm_complete(char *arg);
int		check_errors_e_u(char *arg);
char	*env_type_2(char *env);
void	del_midd_node(t_env **head, char *arg);

//ft_export
void	print_env(t_env **tmp);
void	print_export(t_env **tmp);
void	complete_fun_export(t_env **tmp, t_token *tmp2);
void	ft_export(t_env **tmp, t_token *tmp2);

//ft_here_doc
void	create_fd_in_herdoc(t_rdr *new);
t_token	*create_fd_after_herdoc_without_cmd(t_rdr *r, t_token *new);
t_token	*here_doc(t_token *new, t_pip *pip, t_env **ev);
int		here_doc_fnc(t_rdr *new, t_env **ev);

//ft_pwd_cmd
int		ft_check_pwd(char *cmd);
void	change_pwd_env(t_env **tmp1);
void	ft_pwd(t_token *tmp);

//new_env_utl
char	**table2d(char **env);
char	*env_type(char *env);
char	*env_arg(char *env);
t_env	*get_double_env(t_env *ev);
int		ft_strchr_arg(char *n, int c);

//new_env
t_env	*env_new2(char **env);
char	*env_value_norm(char *env, char *str);
char	*env_value(char *env);
t_env	*get_env_list(t_env *arg);
t_env	*get_env2(char **e);

//ft_unset
void	unset1_norm(t_env **head, char *type);
void	unset1(t_env **head, char *arg);
void	unset2(t_env **head, char *arg);

//ft_unset_complete
void	complete_fun_unset_norm(t_env **tmp, char *arg);
void	complete_fun_unset_norm_01(t_token	*new, int i);
void	complete_fun_unset(t_env **tmp, t_token *tmp2);
void	unset(t_env **tmp, t_token *tmp2);

//ft_create_and_check_fd
int		check_fd_0(char *av);
int		check_fd_1(char *av);
int		check_fd_2(char *av);

//ft_get_path
char	**access_path(t_env **ev, t_token *tmp);
char	**access_path_norm(char **r, char **cmd);
char	**get_path(t_env **tmp, char **cmd);
int		calcul_add_arg_at_cmd(t_token *tmp);
char	**add_arg_at_cmd(t_token *tmp);

//ft_dup_child
void	rdr_output(t_token *new);
void	child_1(t_token *new, t_pip *pip);
void	child_2(t_token *new, t_pip *pip, t_env **ev);

//ft_pipe
void	wait_pid(t_token *tmp);
void	parent(t_token *new, t_env **ev, t_pip *pip);
void	pipe_fnc_complete(t_token *new, t_env **ev, t_pip *pip);
void	pipe_fnc(t_token *tmp, t_env **ev);
void	parent_main(t_token *new, t_pip *pip);

//ft_rdr_outpout
void	rdr_output_here_doc_utl(t_rdr *new);
void	create_fd_befor_herdoc_without_cmd(t_rdr *r);
t_token	*rdr_output_here_doc(t_token *new);

////////////////////////////////////////////////////////

//main
int		check_errors(t_lexer *lexer, t_env **ev);
t_token	*final_struct_fnc(char *line, t_lexer *tmp, t_env **ev);
void	pipe_check(t_token *tmp, t_env **ev);
void	main_fnc(t_token *new, t_lexer *tmp, t_env *ev);
int		main(int ac, char **av, char **env);

////////////////////////////////////////////////////////

#endif