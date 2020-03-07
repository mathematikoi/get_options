#include "get_options.h"

static int	options_format_check(char *valid_options)
{
	int d;
	int	options_count;
	int	uniqueness[128];

	if (*valid_options != '.' && *valid_options != ':')
		return (SYNTAX_ERROR);
	ft_bzero(uniqueness, 128);
	options_count = 0;
	while (*valid_options)
	{
		d = ABS(*valid_options - *(valid_options + 1));
		if (d == 0 || d == 12)
			return (SYNTAX_ERROR);
		if (*valid_options == '.' || *valid_options == ':')
		{
			if (uniqueness[(int)*(valid_options + 1)])
				return (SYNTAX_ERROR);
			uniqueness[(int)*(valid_options + 1)] = 1;
			options_count++;
		}
		valid_options++;
	}
	if (*(valid_options - 1) == '.' || *(valid_options - 1) == ':')
		return (SYNTAX_ERROR);
	return (options_count);
}

t_options	parse_options_format(char *valid_options, int *err)
{
	t_options	options;
	int			options_count;
	int			options_length;
	int			offset;
	int			i;

	if ((options_count = options_format_check(valid_options) <= 0))
	{
		*err = options_count ? options_count : SYNTAX_ERROR;
		return (NULL);
	}
	if (!(options = malloc(sizeof(t_option) * (options_count + 1))))
	{
		*err = RESOURCE_ERROR;
		return (NULL);
	}
	ft_bzero(options, sizeof(t_option) * (options_count + 1));
	i = -1;
	offset = 1;
	while (++i < options_count)
	{
		options_length = ft_crawl(valid_options + offset, ".:");
		options[i] = (t_option){ft_strsub(valid_options, offset, options_length),
			*(valid_options + offset - 1),
			NULL};
		offset += options_length + 1;
	}
	options[i] = (t_option){NULL, 0, NULL};
	return (options);
}