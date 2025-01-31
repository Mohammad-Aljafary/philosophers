/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:59:41 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/31 22:45:19 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_philo *new_node(int status, int id, char **argv, t_info *info)
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
    node->fork = malloc(sizeof(t_fork));
    if (!node->fork)
    {
        free (node);
        return (NULL);
    }
    node->info = info;
    return (node);
}

/**
 * add_back - Adds a new node to the end of a circular doubly linked list.
 * @lst: A pointer to the pointer to the head of the list.
 * @node: The new node to be added to the list.
 *
 * This function adds a new node to the end of a circular doubly linked list.
 * If the list is empty, the new node becomes the head and points to itself.
 * Otherwise, the new node is added to the end and the links are updated accordingly.
 */
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
        
/**
 * lst_clear - Clears and frees all nodes in the linked list.
 * @lst: Double pointer to the head of the linked list.
 *
 * This function iterates through the linked list, destroys the mutexes,
 * joins the threads, and frees the memory allocated for each node and its fork.
 * Finally, it sets the head of the list to NULL.
 */

void lst_clear(t_philo **lst)
{
    t_philo *temp;
    t_philo *next_node;

    if (!lst || !*lst)
        return ;
    temp = *lst;
    while (temp && temp != *lst)
    {
        next_node = temp->next;
        if (next_node == *lst)
            next_node = NULL;
        if (pthread_mutex_destroy(&temp->fork->fork) != 0)
            continue;
        if (pthread_join(temp->philo, NULL) != 0)
        {
            free(temp->fork);
            free(temp);
            temp = next_node;
            continue;
        }
        free(temp->fork);
        free(temp);
        temp = next_node;
    }
    *lst = NULL;
}
