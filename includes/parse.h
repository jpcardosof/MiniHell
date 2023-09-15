/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:42:43 by jferreir          #+#    #+#             */
/*   Updated: 2023/08/05 13:39:48 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// Parse_utils
int				get_tokens(void);
char			**alloc_tokens(char *str, int nbr_tokens);
void			characters_special_handle(char **str, int *count);

// init_parse
void			init_parse(void);
char			*my_getenv(char *str);

// Parse_quotes
int				check_quotes(char *str);
int				quotes_outside(char *str);
int				quotes_inside(char *str, char c);
char			*check_envp(char	*str);
char			*handle_quote(char	*str, char c);

// Utils
char			*env_var(char *str);
void			error_var(void);
void			handle_shlvl(char c);
char			*strjoin_var(char *s1, char s2);
char			*strjoin(char *s1, char *s2);
char			*strjoin_null(char *s1, char *s2);

// Utils 2
void			handle_env(char *str);
int				skip_blank(char *str);
void			skip_non_blank_and_sign_dolar(char **str);

// Utils 3
int				handle_dollar_sign(char *str);
void			check_echo(void);
int				token_is_space(char *str, int *i);

// Utils 4
char			**init_tokens(int nbr_tokens);
int				token_inside_quote(char	*str, char **tokens);
int				token_special_char(char *str, char **token, int *i);
int				token_space_dolar_sig(char *str, char **token, int nbr_tokens);
int				token_other_chars(char *str, char **token, int *i);

// Utils 5
char			*handle_single_spc_quote(char *str);

#endif
