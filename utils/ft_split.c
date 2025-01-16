/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:58:58 by qudomino          #+#    #+#             */
/*   Updated: 2025/01/14 19:25:52 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	char_is_separator(char c, char separator)
{
	return (c == separator);
}

int	count_words(char const *str, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i] != '\0')
	{
		if (!char_is_separator(str[i], c) && (char_is_separator(str[i + 1], c)
				|| str[i + 1] == '\0'))
		{
			words++;
		}
		i++;
	}
	return (words);
}

char	*allocate_word(char const *str, char c, int *i)
{
	int		j;
	char	*word;

	j = 0;
	while (!char_is_separator(str[*i + j], c) && str[*i + j] != '\0')
		j++;
	word = (char *)malloc(sizeof(char) * (j + 1));
	if (word == NULL)
		return (NULL);
	j = 0;
	while (!char_is_separator(str[*i], c) && str[*i] != '\0')
	{
		word[j] = str[*i];
		j++;
		(*i)++;
	}
	word[j] = '\0';
	return (word);
}

int	write_split(char **split, char const *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i], c) == 1)
			i++;
		else
		{
			split[word] = allocate_word(str, c, &i);
			if (split[word] == NULL)
				return (0);
			word++;
		}
	}
	split[word] = NULL;
	return (1);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		words;

	words = count_words(str, c);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	if (res == NULL)
		return (NULL);
	if (!write_split(res, str, c))
	{
		while (words-- > 0)
			free(res[words]);
		free(res);
		return (NULL);
	}
	return (res);
}
