typedef struct s_operations
{
    t_stack *a;
    t_stack *b;
    int ra_count;
    int rb_count;
    int rra_count;
    int rrb_count;
    int rr_count;
    int rrr_count;
    int sa_count;
    int sb_count;
    int pa_count;
    int pb_count;
}   t_operations;

void ra(t_operations *ops)
{
    if (!ops || !ops->a)
        return;
    r(ops->a);
    ops->ra_count++;
}

// Rotate stack b up
void rb(t_operations *ops)
{
    if (!ops || !ops->b)
        return;
    r(ops->b);
    ops->rb_count++;
}

// Rotate both stacks up
void rr(t_operations *ops)
{
    if (!ops || !ops->a || !ops->b)
        return;
    r(ops->a);
    r(ops->b);
    ops->rr_count++;
}

// Reverse rotate stack a down
void rra(t_operations *ops)
{
    if (!ops || !ops->a)
        return;
    rr(ops->a);
    ops->rra_count++;
}

// Reverse rotate stack b down
void rrb(t_operations *ops)
{
    if (!ops || !ops->b)
        return;
    rr(ops->b);
    ops->rrb_count++;
}

// Reverse rotate both stacks down
void rrr(t_operations *ops)
{
    if (!ops || !ops->a || !ops->b)
        return;
    rra(ops);
    rrb(ops);
    ops->rrr_count++;
}

// Swap first two nodes of stack a
void sa(t_operations *ops)
{
    if (!ops || !ops->a)
        return;
    s(ops->a);
    ops->sa_count++;
}

// Swap first two nodes of stack b
void sb(t_operations *ops)
{
    if (!ops || !ops->b)
        return;
    s(ops->b);
    ops->sb_count++;
}

// Push top of stack a to stack b
void pb(t_operations *ops)
{
    if (!ops || !ops->a || !ops->b)
        return;
    p(ops->b, ops->a);
    ops->pb_count++;
}

// Push top of stack b to stack a
void pa(t_operations *ops)
{
    if (!ops || !ops->a || !ops->b)
        return;
    p(ops->a, ops->b);
    ops->pa_count++;
}
