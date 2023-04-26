#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info_parameter: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info_parameter, char *buffer, size_t *position)
{
	size_t index = *position;

	if (buffer[index] == '|' && buffer[index + one] == '|')
	{
		buffer[index] = zero;
		index++;
		info_parameter->cmd_buf_type = CMD_OR;
	}
	else if (buffer[index] == '&' && buffer[index + one] == '&')
	{
		buffer[index] = zero;
		index++;
		info_parameter->cmd_buf_type = CMD_AND;
	}
	else if (buffer[index] == ';') /* found end of this command */
	{
		buffer[index] = zero; /* replace semicolon with null */
		info_parameter->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (zero);
	*position = index;
	return (one);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info_parameter: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *info_parameter, char *buffer, size_t *position,
		size_t i, size_t len)
{
	size_t index = *position;

	if (info_parameter->cmd_buf_type == CMD_AND)
	{
		if (info_parameter->status)
		{
			buffer[i] = zero;
			index = len;
		}
	}
	if (info_parameter->cmd_buf_type == CMD_OR)
	{
		if (!info_parameter->status)
		{
			buffer[i] = zero;
			index = len;
		}
	}

	*position = index;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info_parameter: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info_parameter)
{
	int i;
	list_t *node;
	char *position;

	for (i = zero; i < 10; i++)
	{
		node = node_starts_with(info_parameter->alias, 
		info_parameter->argv[zero], '=');
		if (!node)
			return (zero);
		free(info_parameter->argv[zero]);
		position = _strchr(node->str, '=');
		if (!position)
			return (zero);
		position = _strdup(position + one);
		if (!position)
			return (zero);
		info_parameter->argv[zero] = position;
	}
	return (one);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info_parameter: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info_parameter)
{
	int i = zero;
	list_t *node;

	for (i = zero; info_parameter->argv[i]; i++)
	{
		if (info_parameter->argv[i][zero] != '$' || !info_parameter->argv[i][one])
			continue;

		if (!_strcmp(info_parameter->argv[i], "$?"))
		{
			replace_string(&(info_parameter->argv[i]),
						   _strdup(convert_number(info_parameter->status, 10, zero)));
			continue;
		}
		if (!_strcmp(info_parameter->argv[i], "$$"))
		{
			replace_string(&(info_parameter->argv[i]),
						   _strdup(convert_number(getpid(), 10, zero)));
			continue;
		}
		node = node_starts_with(info_parameter->env, 
		&info_parameter->argv[i][one], '=');
		if (node)
		{
			replace_string(&(info_parameter->argv[i]),
					_strdup(_strchr(node->str, '=') + one));
			continue;
		}
		replace_string(&info_parameter->argv[i], _strdup(""));
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

