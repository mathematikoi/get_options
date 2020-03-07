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

#include "nm_otool.h"

int			ft_crawl(char *string, char *delimiters)
{
	int length;

	length = 0;
	while (*string)
	{
		if (ft_strchr(delimiters, *string))
			return (length);
		length++;
	}
	return (length);
}

int			options_format_check(char *valid_options)
{
	int d;
	int	options_count;

	if (*valid_options != '.' && *valid_options != ':')
		return (-1);
	options_count = 0;
	while (*valid_options)
	{
		d = ABS(*valid_options, *(valid_options + 1));
		if (d == 0 || d == 12)
			return (-1);
		if (*valid_options == '.' || *valid_options == ':')
			options_count++;
		valid_options++;
	}
	return (options_count);
}

t_options	parse_options_format(char *valid_options)
{
	int	options_count;
	int options_length;
	int offset;
	t_options	options;
	int	i;

	if ((options_count = options_format_check(valid_options) == -1))
		return (NULL);
	if (!(options = malloc(sizeof(t_option) * (options_count + 1))))
		return (NULL);
	i = -1;
	offset = 0;
	while (++i < options_count)
	{
		options_length = ft_crawl(valid_options + offset, ".:");
		options[i] = (t_options){ft_strsub(valid_options, offset, options_length),
			*(valid_options + offset),
			NULL};
		offset += options_length;
	}
	options[i] = (t_option){NULL, 0, NULL};
	return (options);
}

int			get_option_index(char option, t_options options)
{
	int i;

	i = -1;
	while (options[++i].option)
			if (options[i].option[0] == option)
				return (i);
	return (-1);
}

int			set_long_option(char *argument, t_options options, int *index)
{
	int option_index;

	if ((option_index = get_option_index(argument + 2)) == -1)
		return (1);
	if (options[option_index].type == BOOLEAN_O)
		options[option_index].value = 1;
	else
	{
		if (!*(argument + 1))
			return (1);
		options[option_index].value = ft_strdup(argument + 1);
		(*index)++;
	}
	return (0);
}

int			set_short_options(char *argument, t_options options)
{
	int option_index;
	int	i;

	i = 0;
	while (argument[++i])
	{
		if ((option_index = get_option_index(NULL, argument[i], options) == -1))
			return (1);
		if (options[option_index].type == BOOLEAN_O)
			options[option_index].value = 1;
		else
		{
			if (ft_strlen(argument) != 2)
				return (1);
			if (!*(argument + 1))
				return (1);
			options[option_index].value = ft_strdup(argument + 1);
			(*index)++;
		}
	}
	return (0);
}

int			get_options(char **argv, t_options *options, char *valid_options, int *offset)
{
	int			i;
	
	ft_bzero(&options_, sizeof(t_options));
	*options = parse_options_format(valid_options);
	i = -1;
	while (ft_strcmp(argv[++i], "--"))
	{
		if (argv[i][0] != '-')
			break ;
		if (argv[i][1] == '-')
			if (set_long_option(argv[i], options))
				return (1);
		else
			if (set_short_options(argv[i], options))
				return (1);
	}
	*offset = i;
	return (0);
}

char		*read_option(t_options options, char *option)
{
	int i;

	if ((i = get_option_index(option[0], options)) == -1)
		return (NULL);
	return (options[i].value);
}
