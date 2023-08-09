/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazerou <abazerou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:40:47 by gghaya            #+#    #+#             */
/*   Updated: 2023/08/08 22:13:48 by abazerou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <fcntl.h>
# include "ft_libft/libft.h"
# include <stdbool.h>
# include <signal.h>

# define OUT		0
# define IN			1
# define APPEND		2
# define HEREDOC	3

int	g_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirection
{
	int						token;
	char					*file;
	struct s_redirection	*next;
}	t_redirect;

typedef struct s_tmpliste
{
	char						*arg;
	int							quotes;
	int							fd;
	struct s_redirection		*redct;
	struct s_tmpliste			*next;
}	t_tmpliste;

typedef struct s_finalstruct
{
	char					**cmd;
	struct s_redirection	*rdct;
	struct s_finalstruct	*next;
}	t_final;

typedef struct s_ex
{
	int		len;
	int		i;
	int		j;
	int		start;
	int		x;
	char	*expnd;
	char	*res;
}	t_ex;

typedef struct s_strct
{
	t_tmpliste	*cur;
	t_tmpliste	*prev;
	char		*str;
}	t_strct;

typedef struct s_s
{
	int		i;
	int		start;
	int		len;
	char	*s;
	char	*str;
}	t_s;

bool		balanced_quotes(char *str);
t_tmpliste	*ft_splt(char *s);
t_tmpliste	*ft_lstnw(char *content, int quotes);
void		ft_print(t_tmpliste *t);
void		ft_spacepipe(t_tmpliste **head, char *s, int *i);
void		ft_quotes(t_tmpliste **head, char *s, int *i);
void		ft_lstad_back(t_tmpliste **lst, t_tmpliste *new);
void		ft_string(t_tmpliste **head, char *s, int *i);
void		ft_stclear(t_tmpliste **lst, void (*del)(void*));
void		ft_deletenode(t_tmpliste **begin_list, t_tmpliste *node);
void		ft_deletespace(t_tmpliste **begin_list);
bool		ft_help(char	*input, t_env *envp);
int			not_in(char *string, char c);
void		ft_redirection(t_tmpliste **begin_list, int k);
t_tmpliste	*add_node(t_tmpliste *prev, char *content);
char		*ft_check_cmd(char *arg, int	*i);
t_tmpliste	*ft_check_redirect(char *arg, t_tmpliste	*redirect,
				int	*i, int k);
t_tmpliste	*ft_red1(char	*arg, int	*i, t_tmpliste	*red, int k);
int			lstsize(t_tmpliste *lst);
int			is_token(char *string);
bool		syntax_error(t_tmpliste *tmp);
int			ft_strcmp(char *s1, char *s2);
void		delete_empty(t_tmpliste **tmp);
int			sstrlen(const char *s);
bool		help_syntax(t_tmpliste *cur, t_tmpliste *tmp);
void		ft_heredoc(t_tmpliste **tmp, t_env	*env);
void		deletesp(t_tmpliste **tmp);
int			ft_hendel_heredoc(t_tmpliste *h_doc, t_env	*env);
t_env		*ft_envnw(char *key);
void		ft_add_env(t_env **lst, t_env *new);
t_env		*fill_env(char	**envp);
void		ft_expanding(t_tmpliste **tmp, t_env	*env);
char		*fill_arg(char	*arg, char	**substring, int *len, int klen);
char		*getenv_(char	*key, t_env *env);
int			is_id(char c);
void		ft_envclear(t_env **lst, void (*del)(void*));
int			*without_dollar(char	*s);
int			nw_lenght(char	*arg, t_env	*env);
char		*expandd(char	*s, t_env *env);
void		ft_join(t_tmpliste **tmp);
t_redirect	*ft_rednw(int token);
int			get_token(char	*s);
void		collect_red(t_tmpliste	**tmp);
t_tmpliste	*rm_node(t_tmpliste **begin_list, t_tmpliste *node);
t_tmpliste	*rm(t_tmpliste **begin_list, t_tmpliste *node);
t_final		*ft_help1(t_tmpliste *liste, t_env *env);
int			collect_help(t_tmpliste	**cur, char	*s);
int			red_error(t_tmpliste *tmp);
t_redirect	*copy_red(int token, char	*file);
t_final		*new_final(int len);
void		add_final_back(t_final **lst, t_final *new);
void		ft_redct_back(t_redirect **lst, t_redirect *new);
t_tmpliste	*help_final(t_final	**fhead, t_tmpliste	*cur, int len);
int			cmd_len(t_tmpliste	*prev);
t_final		*fill_final(t_tmpliste **tmp);
void		show_final(t_final	*f);
void		quit_handler(int signum);
void		c_handler(int signum);
int			do_1(t_s *s);
int			do_2(t_s *s, char	*arg, t_env *env);
int			expand_2(t_ex	*ex, char	*s, t_env	*env);
int			expand_1(t_ex	*ex);

// *************EXCUTION***********//

typedef struct s_var
{
	pid_t			child_pid;
	int				fd[2];
	int				save_fd;
	int				fd_out;
	int				i;
	int				j;
	int				x;
	int				found;
	int				size;
	int				save_stdin;
	int				_stdin;
	int				_stdout;
}	t_var;

t_redirect	*ft_lstlast_red(t_redirect *lst);
int			execution(t_final *lst, t_env **env, t_var *v);
int			check_echo_option(t_final *lst, char c);
int			check_echo_option_all(t_final *lst, char c, int n);
void		echo_built(t_final *lst);
int			is_op_valid(t_final *lst);
void		print_arg(t_final *lst, int n);
void		op_not_valid(t_final *lst, int i);
int			check_next_op(t_final *lst);
void		print_no_option(t_final *lst);
int			ft_strncmp_low(const char *s1, const char *s2);
void		pwd_built(t_env *env);
void		cd_built(t_final *lst, t_env *env);
void		p_error(t_final *lst, char *s, int j);
void		env_built(t_env *env);
int			home_dr(t_env *env);
void		back_dr(t_env *env, char *old_pwd);
void		forward_dr(t_env *env, char *old_pwd, char *new_cwd);
int			unset_built(t_final *lst, t_env **env);
void		exit_built(t_final *lst);
void		exec_command(t_final *lst, t_env *env);
char		**list_to_tab(t_env *env);
char		**spliting_path(t_env *env, t_final *lst);
void		executing_cmd(t_final *lst, char **env_tab, t_env *env, t_var *v);
int			env_size(t_env *env);
void		replace_pwd(t_env *cd_b, t_env *cd_b_tmp, char *save_p, char *old_pwd);
int			place_dr(t_env *env, char *new_cwd);
int			ft_env_size(t_env *env);
void		export_built(t_final *lst, t_env *env);
int			my_isspace(char c);
int			my_isalpha(char c);
int			my_isalnum(int c);
int			my_isalnum_eq(char c);
int			ex_without_equal(t_final *lst, char **tab, t_var *v, t_env *e);
void		ex_equal(t_final *lst, t_env *env, char **tab, t_var *v);
void		ex_join(t_final *lst, t_env *env, char **tab, t_var *v);
void		print_export(t_env *tmp);
int			check_space(t_final *lst, t_var *v);
int			check_num(t_final *lst, t_var *v);
void		loop_check(t_final *lst, t_env *env);
int			check_equal_join(t_final *lst, t_env *env, char **tab, t_var *v);
int			check_equal_join_helper(t_final *lst, t_env *env, char **tab, t_var *v);
void		loop_check_help(t_final *lst, t_env *env, t_var *v);
void		join_value(t_env *tmp, char **tab, t_env *env);
char		*copy_str(char *str, char *non_eq, int size);
int			parse_export(t_final *lst, int j, int i);
int			parse_exprt_helper(t_final *lst, int j, int i);
void		ft_delete_node(t_env **head, char *key);
int			parse_unset(t_final *lst, int i, int j);
int			check_firstchar(t_final *lst, int i);
int			loop_arg(t_final *lst, int i, int j);
char		*find_path(t_env *env);
void		piping(t_var *v);
void		search_path(char **splited_p, t_final *tmp, char **env_tab, t_var *v);
int			is_builtins(t_final *lst);
void		redirection(t_final *lst);
int			out_red(t_final *lst);
int			input_red(t_final *lst);
int			appand_red(t_final *lst);
void		save_fd(int save_stdout, int save_stdin);
void		duping(int _stdin, int _stdout, int save_stdin);
int			cd_parse(t_final *lst);
void		set_pwd(t_env *env, char *home_d_value);
void		my_perror(t_final *lst);
int			cd_home(t_final *lst, t_env *env);
void		p_error_export(t_final *lst, char *s, int j);
int			loop_check_help_helper(t_final *lst, t_env *env, char **tab, t_var *v);
char		**sub_var(t_final *lst, char **tab, t_var *v);
void		check_if_found(t_final *tmp, char **splited_path, t_var *v);
void		p_error_exit(t_final *lst, char *s, int j);
t_env		*lstnew_env(char **content);
char		**ft_freetab(char **tab);
void		free_lst(t_final *lst);



#endif