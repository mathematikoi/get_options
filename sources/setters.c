#include "get_options.h"

int			set_long_option(char *argument, t_option *options, int *index)
{
	int option_index;

	if ((option_index = get_option_index(*(argument + 2), options)) == -1)
		return (UNRECOGNIZED_OPTION);
	if (options[option_index].type == BOOLEAN_O)
		options[option_index].value = (char *)1;
	else
	{
		if (!*(argument + 1))
			return (NO_VALUE_SPECIFIED);
		options[option_index].value = ft_strdup(argument + 1);
		(*index)++;
	}
	return (0);
}

int			set_short_options(char *argument, t_option *options, int *index)
{
	int option_index;
	int	i;

	i = 0;
	while (argument[++i])
	{
		if ((option_index = get_option_index(argument[i], options) == -1))
			return (UNRECOGNIZED_OPTION);
		if (options[option_index].type == BOOLEAN_O)
			options[option_index].value = (char *)1;
		else
		{
			if (ft_strlen(argument) != 2)
				return (MIXED_FLAGS_TYPE);
			if (!*(argument + 1))
				return (NO_VALUE_SPECIFIED);
			options[option_index].value = ft_strdup(argument + 1);
			(*index)++;
		}
	}
	return (0);
}