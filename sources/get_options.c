/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merras <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 06:47:01 by merras            #+#    #+#             */
/*   Updated: 2020/03/07 22:45:43 by merras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_options.h"

int			get_options(char **argv, t_options *options, char *valid_options, int *offset)
{
	int			i;
	int			err;
	
	err = 0;
	if ((*options = parse_options_format(valid_options, &err)))
		return (err);
	i = -1;
	while (ft_strcmp(argv[++i], "--"))
	{
		if (argv[i][0] != '-')
			break ;
		if (argv[i][1] == '-')
		{
			if ((err = set_long_option(argv[i], *options, &i)))
				break ;
		}
		else
		{
			if ((err = set_short_options(argv[i], *options, &i)))
				break ;
		}
	}
	if (err)
		destroy_options(*options);
	*offset = i;
	return (err);
}

char		*read_option(t_options options, char *option)
{
	int i;

	if ((i = get_option_index(option[0], options)) == -1)
		return (NULL);
	return (options[i].value);
}

void		destroy_options(t_options options)
{
	int i;

	i = -1;
	while (options[++i].option)
	{
		free(options[i].option);
		if (options[i].type == KEYVALUE_O)
			free(options[i].value);
	}
	free(options);
}