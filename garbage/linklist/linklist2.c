
#include <stdlib.h>
#include <stdio.h>


struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}
void storeSorted(struct Node* root, int arr[], int *i) {
    if (root != NULL) {
        storeSorted(root->left, arr, i);
        arr[(*i)++] = root->data;
        storeSorted(root->right, arr, i);
    }
}
void freeTree(struct Node* root) {
    if (root == NULL) return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
void treeSort(int *arr, int n) {
    struct Node *root = NULL;

    // Build the BST
    root = insert(root, arr[0]);
    for (int i = 1; i < n; i++)
        insert(root, arr[i]);

    // Store sorted values back into arr
    int i = 0;
    storeSorted(root, arr, &i);
    freeTree(root);
}


int main() {
    int arr[] = {5, 3, 7, 2,57,12,-4,99, 8, 1};
    int n = sizeof(arr)/sizeof(arr[0]);

    treeSort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}