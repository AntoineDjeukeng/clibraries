/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjeuken  <adjeuken@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 04:28:13 by adjeuken          #+#    #+#             */
/*   Updated: 2025/07/13 05:50:51 by adjeuken         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 200000

typedef struct Node {
    int value;
    int r_value;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* a;
    Node* b;
    char* ops[MAX_SIZE];
    int op_count;
    int size;
    int keys[MAX_SIZE];
    int indexes[MAX_SIZE];
    int index_size;
} Stack;
void	rotate_both(Stack *s, int a_rot, int b_rot);

void	reverse_rotate(Node **s, Stack *stack, const char *name);
void	rotate(Node **s, Stack *stack, const char *name);
void	swap(Node **s, Stack *stack, const char *name);
void	push(Node **src, Node **dst, Stack *s, const char *name);
void	rrr(Stack *s);
void	rr(Stack *s);

void	ft_quicksort(int arr[], int low, int high);