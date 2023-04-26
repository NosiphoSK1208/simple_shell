#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + two));
	if (!buf)
		return (NULL);
	buf[zero] = zero;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd_size;
	char *a_filename = get_history_file(info);
	list_t *node = NULL;

	if (!a_filename)
		return (n_one);

	fd_size = open(a_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(a_filename);
	if (fd_size == n_one)
		return (n_one);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd_size);
		_putfd('\n', fd_size);
	}
	_putfd(BUF_FLUSH, fd_size);
	close(fd_size);
	return (one);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int index, int_last = zero, linecount = zero;
	ssize_t fd_size, rdlen, fsize = zero;
	struct stat st;
	char *buf = NULL, *a_filename = get_history_file(info);

	if (!a_filename)
		return (zero);

	fd_size = open(a_filename, O_RDONLY);
	free(a_filename);
	if (fd_size == n_one)
		return (zero);
	if (!fstat(fd_size, &st))
		fsize = st.st_size;
	if (fsize < two)
		return (zero);
	buf = malloc(sizeof(char) * (fsize + one));
	if (!buf)
		return (zero);
	rdlen = read(fd_size, buf, fsize);
	buf[fsize] = zero;
	if (rdlen <= zero)
		return (free(buf), zero);
	close(fd_size);
	for (index = zero; index < fsize; index++)
		if (buf[index] == '\n')
		{
			buf[index] = zero;
			build_history_list(info, buf + int_last, linecount++);
			int_last = index + one;
		}
	if (int_last != index)
		build_history_list(info, buf + int_last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), zero);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *n = NULL;

	if (!info->history)
		info->history = n;

	if (info->history)
		n = info->history;
	add_node_end(&n, buf, linecount);
	return (zero);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *n = info->history;
	int index = zero;

	while (n)
	{
		n->num = index++;
		n = node->next;
	}
	return (info->histcount = index);
}
