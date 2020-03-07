#include "get_options.h"

int			get_option_index(char option, t_options options)
{
	int i;

	i = -1;
	while (options[++i].option)
		if (options[i].option[0] == option)
			return (i);
	return (-1);
}

int			ft_crawl(char *string, char *delimiters)
{
	int length;

	length = 0;
	while (*string)
	{
		if (ft_strchr(delimiters, *string))
			return (length);
		length++;
		string++;
	}
	return (length);
}