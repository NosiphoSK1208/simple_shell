#include "shell.h"

/**
 *interactive - returns true if shell is interactive mode
 *@info: struct address
 *
 *Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	bool result = (isatty(STDIN_FILENO) && info->readfd <= two);

	return (result);
}

/**
 *is_delim - checks if character is a delimeter
 *@c: the char to check
 *@delim: the delimeter string
 *Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (one);
	return (zero);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (one);
	else
		return (zero);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: zero if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = one, flag = zero, out_put;
	unsigned int results = zero;

	for (i = zero; s[i] != '\0' && flag != two; i++)
	{
		if (s[i] == '-')
			sign *= n_one;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = one;
			results *= 10;
			results += (s[i] - '0');
		}
		else if (flag == one)
			flag = two;
	}

	if (sign == n_one)
		out_put = -results;
	else
		out_put = results;
	return (out_put);
}


