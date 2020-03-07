/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 06:48:43 by merras            #+#    #+#             */
/*   Updated: 2020/03/07 22:00:13 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** valid_options format: ".boolean:keyvalue"
** -b and --boolean are equivalent
** -k value and --key value are equivalent
** CONVENTIONS:
**	- short key-value options can't be mixed with boolean options,
**		e.g. $> command -kb file where b is boolean and k is keyvalue. 
**	- next argument after a key-value option is taken as the value.
**	- every option is characterized by its first character. --key ≡ -k
*/

#ifndef GET_OPTIONS
# define  GET_OPTIONS

# include "centropy.h"

typedef struct	s_option
{
	char	*option;
	char	type;
	char	*value;
}				t_option;

typedef t_option*	t_options;

int			get_options(char **argv, t_options *options, char *valid_options, int *offset);
char		*read_option(t_options options, char *option);
void		destroy_options(t_options options);


t_options	parse_options_format(char *valid_options);
int			get_option_index(char option, t_options options);
int			ft_crawl(char *string, char *delimiters);
int			set_short_options(char *argument, t_options options, int *index);
int			set_long_option(char *argument, t_options options, int *index);


# define BOOLEAN_O '.'
# define KEYVALUE_O ':'

# define ABS(x) ((x) > 0 ? (x) : -1 * (x))

# define NO_VALUE_SPECIFIED 1 // let `type` be a key-value option. examples: "$> command --type"
# define UNRECOGNIZED_OPTION 2 // when option is not defined in the valid_options string
# define MIXED_FLAGS_TYPE 3 // let `k` be a key-value option and `b` a boolean option. examples: "$> command -ob" 
# define SYNTAX_ERROR 4 // for valid_options string when option is empty string or not unique options.

#endif
