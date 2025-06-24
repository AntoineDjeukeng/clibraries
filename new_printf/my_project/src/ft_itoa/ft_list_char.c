#include "ft_itoa.h"

void ft_add_char(t_word **head, char c)
{
    t_word *new_node;

    new_node = (t_word *)malloc(sizeof(t_word));
    if (!new_node)
        return;
    new_node->c = c;
    new_node->next = *head;
    *head = new_node;
}

char *ft_free_word(t_word *head, int len)
{
    char *str;

    str = calloc(len + 1, sizeof(char));
    if (!str)
        return (NULL);
    str[len] = '\0';
    while (head)
    {
        t_word *tmp = head;
        head = head->next;
        str[--len] = tmp->c;
        free(tmp);
    }
    return (str);

}


