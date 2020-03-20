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

int			get_options(char **argv, t_options *options, char *valid_options)
{
	int			i;
	int			err;
	
	err = 0;
	if ((options->options_ = parse_options_format(valid_options, &err)))
		return (err);
	i = -1;
	while (ft_strcmp(argv[++i], "--"))
	{
		if (argv[i][0] != '-')
			break ;
		if (argv[i][1] == '-')
		{
			if ((err = set_long_option(argv[i], options->options_, &i)))
				break ;
		}
		else
		{
			if ((err = set_short_options(argv[i], options->options_, &i)))
				break ;
		}
	}
	if (err)
		destroy_options(*options);
	options->argv_offset = i;
	return (err);
}

char		*read_option(t_options options, char *option)
{
	int i;

	if ((i = get_option_index(option[0], options.options_)) == -1)
		return (NULL);
	return (options.options_[i].value);
}

void		destroy_options(t_options options)
{
	int i;

	i = -1;
	while (options.options_[++i].option)
	{
		free(options.options_[i].option);
		if (options.options_[i].type == KEYVALUE_O)
			free(options.options_[i].value);
	}
	free(options.options_);
}