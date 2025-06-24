#include <stdlib.h>
#include <stdio.h>


struct node
{
    int data;
    struct node *next;
};
typedef struct  node node_t;

void printlist(node_t *head)
{
    node_t *temporary = head;

    while (temporary!=NULL)
    {
        printf("%d - ", temporary->data);
        temporary= temporary->next;
    }
    printf("\n");
}

node_t *create_new_node(int data)
{
    node_t *result = malloc(sizeof(node_t));
    result->data = data;
    result->next = NULL;
    return result;
}

node_t *insert_at_head(node_t **head, node_t *node_to_insert)
{
    node_to_insert->next= *head;
    *head =node_to_insert;
    return node_to_insert;
}

node_t *find_node(node_t *head, int data)
{
    node_t *temp =head;
    while (temp != NULL)
    {
        if (temp->data == data) return temp;
        temp = temp->next;
        
    }
    return NULL;
    
}

void insert_after_node(node_t *node_to_insert_after, node_t *new_node)
{
    new_node->next = node_to_insert_after->next;
    node_to_insert_after->next=new_node;
}



int main()
{
    node_t *head;
    
    node_t *temp;

    head = NULL;

    for (int i = 0; i< 25; i++)
    {
        temp = create_new_node(i);
        insert_at_head(&head, temp);
    }
    temp = find_node(head,13);
    printf("the value of node is %d\n",temp->data);
    insert_after_node(temp, create_new_node(75));

    printlist(head);

    return (0);
}