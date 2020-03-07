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
*/

#ifndef GET_OPTIONS
# define  GET_OPTIONS

typedef *t_option	t_options;

typedef struct	s_option
{
	char	*option;
	char	type;
	char	*value;
}				t_option;

# define BOOLEAN_O '.'
# define KEYVALUE_O ':'

# define ABS(x) ((x) > 0 ? (x) : -1 * (x))
# define MIN(x, y) x < y ? x : y

#endif
