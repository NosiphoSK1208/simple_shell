#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t index = zero;

	while (h)
	{
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t j, index = list_len(head);
	char **strs;
	char *str;

	if (head == NULL || index == NULL)
		return (NULL);
	strs = malloc(sizeof(char *) * (index + 1));
	if (strs == NULL)
		return (NULL);
	for (index = zero; node; node = node->next, index++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (str == NULL)
		{
			for (j = zero; j < index; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[index] = str;
	}
	strs[index] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t index = zero;

	while (h)
	{
		_puts(convert_number(h->num, 10, zero));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *x = NULL;

	while (node)
	{
		x = starts_with(node->str, prefix);
		if (x && ((*x == c) || (c == n_one)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = zero;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (n_one);
}
