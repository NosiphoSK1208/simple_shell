#include "shell.h"

/**
 ***strtow - splits a string into words. Repeat delimiters are ignored
 *@astring: the input string
 *@delimeter: the delimeter string
 *Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *astring, char *delimeter)
{
	int index, j, k, m, words_m = zero;
	char **s;

	if (astring == NULL || astring[zero] == zero)
		return (NULL);
	if (!delimeter)
		delimeter = " ";
	for (index = zero; astring[index] != '\0'; index++)
		if (!is_delim(astring[index], delimeter) &&
			(is_delim(astring[index + one], delimeter) || !astring[index + one]))
			words_m++;

	if (words_m == zero)
		return (NULL);
	s = malloc((one + words_m) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = zero, j = zero; j < words_m; j++)
	{
		while (is_delim(astring[index], delimeter))
			index++;
		k = zero;
		while (!is_delim(astring[index + k], delimeter) && astring[index + k])
			k++;
		s[j] = malloc((k + one) * sizeof(char));
		if (!s[j])
		{
			for (k = zero; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = zero; m < k; m++)
			s[j][m] = astring[index++];
		s[j][m] = zero;
	}

	s[j] = NULL;
	return (s);
}

/**
 ***strtow2 - splits a string into words
 *@str: the input string
 *@delimeter: the delimeter
 *Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char delimeter)
{
	int index, j, k, m, words_m = zero;
	char **s;

	if (str == NULL || str[zero] == zero)
		return (NULL);
	for (index = zero; str[index] != '\0'; index++)
		if ((str[index] != delimeter && str[index + one] == delimeter) ||
			(str[index] != delimeter && !str[index + one]) ||
			str[index + one] == delimeter)
			words_m++;
	if (words_m == zero)
		return (NULL);
	s = malloc((one + words_m) * sizeof(char *));
	if (!s)
		return (NULL);
	for (index = zero, j = zero; j < words_m; j++)
	{
		while (str[index] == delimeter && str[index] != delimeter)
			index++;
		k = zero;
		while (str[index + k] != delimeter && str[index + k] &&
			   str[index + k] != delimeter)
			k++;
		s[j] = malloc((k + one) * sizeof(char));
		if (!s[j])
		{
			for (k = zero; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = zero; m < k; m++)
			s[j][m] = str[index++];
		s[j][m] = zero;
	}

	s[j] = NULL;
	return (s);
}

