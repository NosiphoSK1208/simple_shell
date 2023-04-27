#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + one] == '|')
	{
		buf[j] = zero;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + one] == '&')
	{
		buf[j] = zero;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = zero; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (zero);
	*p = j;
	return (one);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = zero;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = zero;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = zero; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[zero], '=');
		if (!node)
			return (zero);
		free(info->argv[zero]);
		p = _strchr(node->str, '=');
		if (!p)
			return (zero);
		p = _strdup(p + one);
		if (!p)
			return (zero);
		info->argv[zero] = p;
	}
	return (one);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = zero;
	list_t *node;

	for (i = zero; info->argv[i]; i++)
	{
		if (info->argv[i][zero] != '$' || !info->argv[i][one])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(info->status, 10, zero)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(getpid(), 10, zero)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][one], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
						   _strdup(_strchr(node->str, '=') + one));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (zero);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (one);
}
