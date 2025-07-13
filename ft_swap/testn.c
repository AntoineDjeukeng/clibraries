#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 200000

typedef struct Node {
    int value;
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

// Create a new node
Node* new_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

// Append node at tail (used only in init)
void append(Node** head, int value) {
    Node* node = new_node(value);
    if (*head == NULL) {
        *head = node;
    } else {
        Node* cur = *head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = node;
    }
}

// Print linked list from top (head) to bottom (tail)
void print_list(Node* head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
}

// Free linked list
void free_list(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

// Check if val in array
int contains(int* arr, int size, int val) {
    for (int i = 0; i < size; i++)
        if (arr[i] == val)
            return 1;
    return 0;
}

// Simple selection sort
void simple_sort(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        int tmp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = tmp;
    }
}

// Build index map for values in stack
void indexify(Stack* s, int* values, int count) {
    int unique[MAX_SIZE];
    int u_size = 0;
    for (int i = 0; i < count; i++) {
        if (!contains(unique, u_size, values[i])) {
            unique[u_size++] = values[i];
        }
    }
    simple_sort(unique, u_size);
    for (int i = 0; i < u_size; i++) {
        s->keys[i] = unique[i];
        s->indexes[i] = i;
    }
    s->index_size = u_size;
}

// Push: pop from src top, push to dst top, log operation
void push(Node** src, Node** dst, Stack* s, const char* name) {
    if (*src == NULL) return;

    Node* node = *src;
    *src = node->next;
    node->next = *dst;
    *dst = node;

    s->ops[s->op_count++] = strdup(name);
}

// Swap first two nodes of stack s, log operation
void swap(Node** s, Stack* stack, const char* name) {
    if (*s == NULL || (*s)->next == NULL) return;

    Node* first = *s;
    Node* second = first->next;

    first->next = second->next;
    second->next = first;
    *s = second;

    stack->ops[stack->op_count++] = strdup(name);
}

// Rotate: move head to tail, log operation
void rotate(Node** s, Stack* stack, const char* name) {
    if (*s == NULL || (*s)->next == NULL) return;

    Node* head = *s;
    Node* tail = head;
    while (tail->next != NULL)
        tail = tail->next;

    *s = head->next;
    head->next = NULL;
    tail->next = head;

    stack->ops[stack->op_count++] = strdup(name);
}

// Reverse rotate: move tail to head, log operation
void reverse_rotate(Node** s, Stack* stack, const char* name) {
    if (*s == NULL || (*s)->next == NULL) return;

    Node* prev = NULL;
    Node* tail = *s;

    while (tail->next != NULL) {
        prev = tail;
        tail = tail->next;
    }
    prev->next = NULL;
    tail->next = *s;
    *s = tail;

    stack->ops[stack->op_count++] = strdup(name);
}

// Stack-specific operation wrappers
void ra(Stack* s) { rotate(&(s->a), s, "ra"); }
void rb(Stack* s) { rotate(&(s->b), s, "rb"); }
void rra(Stack* s) { reverse_rotate(&(s->a), s, "rra"); }
void rrb(Stack* s) { reverse_rotate(&(s->b), s, "rrb"); }
void sa(Stack* s) { swap(&(s->a), s, "sa"); }
void sb(Stack* s) { swap(&(s->b), s, "sb"); }
void pa(Stack* s) { push(&(s->b), &(s->a), s, "pa"); }
void pb(Stack* s) { push(&(s->a), &(s->b), s, "pb"); }

// Rotate both stacks a and b simultaneously, log "rr" once
void rr(Stack* s) {
    if (s->a && s->b) {
        rotate(&(s->a), s, "ra");
        rotate(&(s->b), s, "rb");
        s->op_count -= 2; // remove ra and rb logs
        s->ops[s->op_count++] = strdup("rr");
    }
}

// Reverse rotate both stacks a and b simultaneously, log "rrr" once
void rrr(Stack* s) {
    if (s->a && s->b) {
        reverse_rotate(&(s->a), s, "rra");
        reverse_rotate(&(s->b), s, "rrb");
        s->op_count -= 2; // remove rra and rrb logs
        s->ops[s->op_count++] = strdup("rrr");
    }
}

// Initialize Stack with values in stack a, indexify keys
Stack* init_stack(int* values, int count) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->a = NULL;
    s->b = NULL;
    s->op_count = 0;
    s->size = count;
    s->index_size = 0;

    for (int i = 0; i < count; i++) {
        append(&(s->a), values[i]);
    }

    indexify(s, values, count);
    return s;
}

#include <stdio.h>

// void print_state_to_file(Stack* s, const char* filename) {
//     FILE* fp = fopen(filename, "w");
//     if (!fp) {
//         perror("Failed to open file");
//         return;
//     }

//     fprintf(fp, "Stack a: ");
//     Node* curr = s->a;
//     while (curr) {
//         fprintf(fp, "%d ", curr->value);
//         curr = curr->next;
//     }

//     fprintf(fp, "\nStack b: ");
//     curr = s->b;
//     while (curr) {
//         fprintf(fp, "%d ", curr->value);
//         curr = curr->next;
//     }

//     fprintf(fp, "\nIndexed map:\n");
//     for (int i = 0; i < s->index_size; i++) {
//         fprintf(fp, "  %d => %d\n", s->keys[i], s->indexes[i]);
//     }

//     fprintf(fp, "Operations performed: ");
//     for (int i = 0; i < s->op_count; i++) {
//         fprintf(fp, "%s ", s->ops[i]);
//     }
//     fprintf(fp, "\n");

//     fclose(fp);
// }

// Helper to get length of linked list
int list_length(Node* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

// Get value at index idx in linked list
int value_at(Node* head, int idx) {
    int i = 0;
    while (head && i < idx) {
        head = head->next;
        i++;
    }
    return head ? head->value : INT_MIN; // INT_MIN as invalid sentinel
}

// Find index of minimal value in linked list
int min_value_index(Node* head) {
    int min_val = INT_MAX;
    int min_idx = 0;
    int idx = 0;
    while (head) {
        if (head->value < min_val) {
            min_val = head->value;
            min_idx = idx;
        }
        idx++;
        head = head->next;
    }
    return min_idx;
}

// Determine target insertion index in stack a for value (sorted ascending)
int get_target_position(Stack* s, int value) {
    if (s->a == NULL) {
        return 0;  // empty stack
    }

    int len = list_length(s->a);
    for (int i = 0; i < len; i++) {
        int prev_idx = (i == 0) ? (len - 1) : (i - 1);
        int prev = value_at(s->a, prev_idx);
        int curr = value_at(s->a, i);

        if (prev < value && value <= curr) {
            return i;
        }
    }

    // If not found, return index of smallest element
    return min_value_index(s->a);
}

// Rotate stack 'a' or 'b' to bring element at idx to top (minimum rotations)
void rotate_to_top(Stack* s, char stack_name, int idx) {
    Node* stack = (stack_name == 'a') ? s->a : s->b;
    int len = list_length(stack);
    if (len == 0) return;

    if (idx <= len / 2) {
        for (int i = 0; i < idx; i++) {
            if (stack_name == 'a')
                ra(s);
            else
                rb(s);
        }
    } else {
        for (int i = 0; i < len - idx; i++) {
            if (stack_name == 'a')
                rra(s);
            else
                rrb(s);
        }
    }
}

// // Rotate both stacks to minimize moves: positive = rotate, negative = reverse rotate
void rotate_both(Stack* s, int a_rot, int b_rot) {
    while (a_rot > 0 && b_rot > 0) {
        rr(s);
        a_rot--;
        b_rot--;
    }
    while (a_rot > 0) {
        ra(s);
        a_rot--;
    }
    while (b_rot > 0) {
        rb(s);
        b_rot--;
    }
    while (a_rot < 0 && b_rot < 0) {
        rrr(s);
        a_rot++;
        b_rot++;
    }
    while (a_rot < 0) {
        rra(s);
        a_rot++;
    }
    while (b_rot < 0) {
        rrb(s);
        b_rot++;
    }
}





#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for abs()

void move_element(Stack* s) {
    if (s->b == NULL) return;

    int min_moves = INT_MAX;
    int best_i = -1;
    int best_val = 0;
    int best_a_rot = 0;
    int best_b_rot = 0;

    int b_len = list_length(s->b);
    int a_len = list_length(s->a);

    for (int i = 0; i < b_len; i++) {
        int val = value_at(s->b, i);
        int target_pos = get_target_position(s, val);

        int a_rot;
        if (target_pos <= a_len / 2) {
            a_rot = target_pos;
        } else {
            a_rot = target_pos - a_len;
        }

        int b_rot;
        if (i <= b_len / 2) {
            b_rot = i;
        } else {
            b_rot = i - b_len;
        }

        int abs_a = (a_rot < 0) ? -a_rot : a_rot;
        int abs_b = (b_rot < 0) ? -b_rot : b_rot;

        int moves;
        if (abs_a > abs_b) {
            moves = abs_a;
        } else {
            moves = abs_b;
        }

        if (moves < min_moves) {
            min_moves = moves;
            best_i = i;
            best_val = val;
            best_a_rot = a_rot;
            best_b_rot = b_rot;
        }
    }


    // printf("the valuse are %d and %d \n",best_a_rot, best_b_rot);
    // best_a_rot++;
    // best_b_rot++;
    rotate_both(s, best_a_rot, best_b_rot);
    pa(s);
}

void sort(Stack* s) {

    int len = list_length(s->a);
    int* values = malloc(sizeof(int) * len);
    Node* cur = s->a;
    for (int i = 0; i < len; i++) {
        values[i] = cur->value;
        cur = cur->next;
    }

    // Map values to indexes using s->keys and s->indexes
    int* indexed_values = malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++) {
        int val = values[i];
        // Find index corresponding to val
        int index_val = 0;
        for (int j = 0; j < s->index_size; j++) {
            if (s->keys[j] == val) {
                index_val = s->indexes[j];
                break;
            }
        }
        indexed_values[i] = index_val;
    }

    // Free old list a and replace with new list with indexed values
    free_list(s->a);
    s->a = NULL;
    for (int i = 0; i < len; i++) {
        append(&(s->a), indexed_values[i]);
    }
    free(values);
    free(indexed_values);

    // Set chunk size based on size n
    int n = s->size;
    int chunk_size = (n > 100) ? 50 : 20;

    int i = 0;
    while (s->a != NULL) {
        int a_front = s->a->value;
        if (a_front <= i) {
            pb(s);
            i++;
        } else if (a_front <= i + chunk_size) {
            pb(s);
            rb(s);
            i++;
        } else {
            ra(s);
        }
    }

    // Push all elements back from b to a using move_element
    while (s->b != NULL) {
        move_element(s);
    }
}

// Free all allocated memory
void cleanup(Stack* s) {
    free_list(s->a);
    free_list(s->b);
    for (int i = 0; i < s->op_count; i++) {
        free(s->ops[i]);
    }
    free(s);
}

// int print_ops(Stack* s) {
//     return s->op_count;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 1000

// Reads a specific line of integers from the input file
int read_input_file(const char* filename, int* array, int* count, int line_number) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open input file");
        return 0;
    }

    char buffer[10000];
    int current_line = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        if (current_line == line_number) {
            char* token = strtok(buffer, " \n");
            int idx = 0;
            while (token != NULL && idx < MAX_NUMBERS) {
                array[idx++] = atoi(token);
                token = strtok(NULL, " \n");
            }
            *count = idx;
            fclose(file);
            return 1;
        }
        current_line++;
    }

    fclose(file);
    return 0;
}

// Optional: Write final stack state and operations to output file
void print_state_to_file(Stack* s, FILE* f) {
    fprintf(f, "Stack a: ");
    Node* cur = s->a;
    while (cur) {
        fprintf(f, "%d ", cur->value);
        cur = cur->next;
    }

    fprintf(f, "\nStack b: ");
    cur = s->b;
    while (cur) {
        fprintf(f, "%d ", cur->value);
        cur = cur->next;
    }

    fprintf(f, "\nOperations performed (%d total):\n", s->op_count);
    for (int i = 0; i < s->op_count; i++) {
        fprintf(f, "%s ", s->ops[i]);
    }
    fprintf(f, "\n");
}

// Assume this function already exists and returns op_count
int print_ops(Stack* s) {
    return s->op_count;
}

void bring_smallest_to_top(Stack* s) {
    if (!s || !s->a) return;

    // Step 1: Find index of smallest value
    int min_val = s->a->value;
    int min_index = 0;
    int i = 0;

    Node* cur = s->a;
    while (cur) {
        if (cur->value < min_val) {
            min_val = cur->value;
            min_index = i;
        }
        cur = cur->next;
        i++;
    }

    int len = i;

    // Step 2: Rotate or reverse rotate to bring min_index to top
    if (min_index <= len / 2) {
        for (int j = 0; j < min_index; j++) {
            ra(s);
        }
    } else {
        for (int j = 0; j < len - min_index; j++) {
            rra(s);
        }
    }
}

int main() {
    int values[MAX_NUMBERS];
    int count;

    if (!read_input_file("input_arrays.txt", values, &count, 0)) {
        fprintf(stderr, "Failed to read array from file.\n");
        return 1;
    }

    Stack* s = init_stack(values, count);
    sort(s);
    bring_smallest_to_top(s);
    // Write result to output.txt
    FILE* out = fopen("output.txt", "w");
    if (!out) {
        perror("Failed to open output file");
        cleanup(s);
        return 1;
    }

    fprintf(out, "Number of operations: %d\n", print_ops(s));
    print_state_to_file(s, out);
    fclose(out);

    cleanup(s);
    return 0;
}
