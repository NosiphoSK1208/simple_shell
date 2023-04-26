#include "shell.h"

/**
 *input_buf - buffers chained commands
 *@info: parameter struct
 *@buf: address of buffer
 *@len: address of len var
 *
 *Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r_size = zero;
	size_t len_p = zero;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r_size = getline(buf, &len_p, stdin);
#else r_size = _getline(info, buf, &len_p);
#endif if (r_size > zero)
		{
			if ((*buf)[r_size - one] == '\n')
			{
				(*buf)[r_size - one] = '\zero';
				r_size--;
			}

			info->linecount_flag = one;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/*if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r_size;
				info->cmd_buf = buf;
			}
		}
	}

	return (r_size);
}

/**
 *get_input - gets a line minus the newline
 *@info: parameter struct
 *
 *Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t index, j_t, len_t;
	ssize_t r_size = zero;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r_size = input_buf(info, &buf, &len_t);
	if (r_size == n_one) /*EOF */
		return (n_one);
	if (len_t)
	{
		j_t = index;
		p = buf + index;

		check_chain(info, buf, &j_t, index, len_t);
		while (j_t < len_t)
		{
			if (is_chain(info, buf, &j_t))
				break;
			j_t++;
		}

		index = j_t + one;
		if (index >= len_t)
		{
			index = len_t = zero;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r_size);
}

/**
 *read_buf - reads a buffer
 *@info: parameter struct
 *@buf: buffer
 *@i: size
 *
 *Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r_size = zero;

	if (*i)
		return (zero);
	r_size = read(info->readfd, buf, READ_BUF_SIZE);
	if (r_size >= zero)
		*i = r_size;
	return (r_size);
}

/**
 *_getline - gets the next line of input from STDIN
 *@info: parameter struct
 *@ptr: address of pointer to buffer, preallocated or NULL
 *@length: size of preallocated ptr buffer if not NULL
 *
 *Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t index, len_t;
	size_t k_size;
	ssize_t r_size = zero, s_size = zero;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s_size = *length;
	if (index == len_t)
		index = len_t = zero;

	r_size = read_buf(info, buf, &len_t);
	if (r_size == n_one || (r_size == zero && len_t == zero))
		return (n_one);

	c = _strchr(buf + index, '\n');
	k_size = c ? one + (unsigned int)(c - buf) : len_t;
	new_p = _realloc(p, s_size, s_size ? s_size + k_size : k_size + one);
	if (!new_p) /*MALLOC FAILURE! */
		return (p ? free(p), n_one : n_one);

	if (s_size)
		_strncat(new_p, buf + index, k_size - index);
	else
		_strncpy(new_p, buf + index, k_size - index + one);

	s_size += k_size - index;
	index = k_size;
	p = new_p;

	if (length)
		*length = s_size;
	*ptr = p;
	return (s_size);
}

/**
 *sigintHandler - blocks ctrl-C
 *@sig_num: the signal number
 *
 *Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

