/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:59:41 by malja-fa          #+#    #+#             */
/*   Updated: 2025/02/03 14:43:08 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>
/**
    * new_node - Creates a new node with the given status and id.
    * @status: The status of the thread.
    * @id: The id of the thread.
    * @argv: The arguments passed to the program.
    * @info: The info struct that contains the mutex and data to be passed to the thread.
    * @fork: The fork struct that contains the mutex for the fork.
    *
    * Return: If an error occurs, return NULL.
    * Otherwise, return a pointer to the new node. 
*/

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
    node->last_meal = 0;
    node->fork = malloc(sizeof(t_fork));
    pthread_mutex_init(&node->lock, NULL);
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
 * did not free the info struct because it is freed in the main function.
 * did not protect the pthread_mutex_destroy and pthread_join because the list is already protected by the main thread.
 * and i want it to continue the execution even if the thread is not joined or the mutex is not destroyed.
 */

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
        pthread_mutex_destroy(&temp->fork->fork);
        pthread_join(temp->philo, NULL);
        free(temp->fork);
        free(temp);
        temp = next_node;
    }
    *lst = NULL;
}
