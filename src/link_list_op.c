/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:59:41 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/29 14:26:04 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_philo *new_node(int status, int id, char **argv)
{
    t_philo *node;

    node = malloc(sizeof(t_philo));
    if(!node)
        return (NULL);
    node->id = id;
    node->state = status;
    node->next = NULL;
    node->prev = NULL;
    node->philo = 0;
    node->argv = argv;
    return (node);
}

void    add_back(t_philo **lst, t_philo *node)
{
    t_philo *ptr;

    if (!lst || !node)
        return ;

    ptr = *lst;
    if (!*lst)
    {
        *lst = node;
        node->next = node;
        node->prev = node;
        return ;
    }
    else
    {
        while (ptr->next != *lst)
            ptr = ptr->next;
        ptr->next = node;
        node->prev = ptr;
        node->next = *lst;
        (*lst)->prev = node;
    }
}
void lst_clear(t_philo **lst)
{
    t_philo *temp;
    t_philo *next_node;

    if (!lst || !*lst)
        return ;
    temp = *lst;
    while (temp)
    {
        next_node = temp->next;
        if (next_node == *lst)
            next_node = NULL;
        if (pthread_join(temp->philo, NULL) != 0)
        {
            free(temp);
            temp = next_node;
            continue;
        }
        free(temp);
        temp = next_node;
    }
    *lst = NULL;
}
