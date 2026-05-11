/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaguti <rafaguti>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:01:46 by rafaguti          #+#    #+#             */
/*   Updated: 2024/11/01 11:48:22 by rafaguti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

// Helper function to count the number of words in a string.
// PARAMETERS:
// - const char *s: The input string to be analyzed.
// - char c: The delimiter character.
// DESCRIPTION:
// - This function iterates through the string and counts the number of
//   words separated by the delimiter.
// OUTPUT:
// - Returns the total count of words found in the string.
static int	ft_count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

// Helper function to calculate the length of a word in a string.
// PARAMETERS:
// - char const *s: The input string to be analyzed.
// - char c: The delimiter character.
// DESCRIPTION:
// - This function returns the length of the word until the delimiter.
// OUTPUT:
// - Returns the length of the word found.
static int	ft_word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

// Helper function to free allocated memory for split strings in case of failure
// PARAMETERS:
// - char **split: The array of strings to be freed.
// - int count: The number of strings allocated.
// DESCRIPTION:
// - This function iterates through the allocated strings and frees them.
// OUTPUT:
// - Returns NULL after freeing memory.
static char	**ft_free_split(char **split, int count)
{
	while (count--)
		free(split[count]);
	free(split);
	return (NULL);
}

// Main function to split a string into an array of strings based on a delimiter
// PARAMETERS:
// - char const *s: The input string to be split.
// - char c: The delimiter character.
// DESCRIPTION:
// - This function counts the number of words, allocates memory for the
//   resulting array, and fills it with the split strings.
// OUTPUT:
// - Returns an array of strings (words) or NULL on failure.
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		words;
	int		word_len;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	result = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		word_len = ft_word_len(s, c);
		result[i] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!result[i])
			return (ft_free_split(result, i));
		ft_strlcpy(result[i], s, word_len + 1);
		s += word_len;
	}
	result[i] = NULL;
	return (result);
}
/*
#include <stdio.h>
int main() {
    char **result;
    char str[] = "Hello, World! Welcome to ft_split.";
    char delim = ' ';

    result = ft_split(str, delim);
    if (result) {
        for (int i = 0; result[i] != NULL; i++) {
            printf("%s\n", result[i]);
            free(result[i]); // Free each string
        }
        free(result); // Free the array
    } else {
        printf("Failed to split the string.\n");
    }

    return 0;
}
*/
