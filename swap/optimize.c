// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
#include "push_swap.h"
#define MAX_OPS 100000
#define MAX_LINE 16

int	is_repeated_rotation(const char *op)
{
	return (!strcmp(op, "ra\n") || !strcmp(op, "rb\n") ||
			!strcmp(op, "rra\n") || !strcmp(op, "rrb\n"));
}

int	match_pattern(char **ops, int i, int count, const char **pattern, int len)
{
	if (i + len > count)
		return 0;
	for (int j = 0; j < len; j++)
		if (strcmp(ops[i + j], pattern[j]) != 0)
			return 0;
	return 1;
}



char	**peephole_optimize(char **ops, int count, int *new_count)
{
	char **out = malloc(sizeof(char *) * count);
	int i = 0, j = 0;

	while (i < count)
	{
		// Collapse repeated rotations
		if (i + 1 < count && is_repeated_rotation(ops[i]))
		{
			int k = i + 1;
			while (k < count && strcmp(ops[k], ops[i]) == 0)
				k++;
			// int repeat = k - i;
			// printf("Collapsing %d %s", repeat, ops[i]);
			out[j++] = strdup(ops[i]); // Keep one
			i = k;
			continue;
		}

		// Replace pb pb rb pa pa → sa
		const char *p1[] = {"pb\n", "pb\n", "rb\n", "pa\n", "pa\n"};
		const char *p2[] = {"pb\n", "pb\n", "sb\n", "pa\n", "pa\n"};
		if (match_pattern(ops, i, count, p1, 5) || match_pattern(ops, i, count, p2, 5))
		{
			// printf("Replacing pb pb ? pa pa with sa\n");
			out[j++] = strdup("sa\n");
			i += 5;
			continue;
		}

		// Remove neutral pairs
		if (i + 1 < count)
		{
			if ((strcmp(ops[i], "pb\n") == 0 && strcmp(ops[i+1], "pa\n") == 0) ||
				(strcmp(ops[i], "pa\n") == 0 && strcmp(ops[i+1], "pb\n") == 0))
			{
				// printf("Removing neutral pair: %s%s", ops[i], ops[i+1]);
				i += 2;
				continue;
			}
		}

		// Otherwise, keep current op
		out[j++] = strdup(ops[i++]);
	}
	*new_count = j;
	return out;
}

ARG=$(python3 -c "import random; print(' '.join(map(str, random.sample(range(-300, 300), 600))))")


// int	main(void)
// {
// 	FILE *fp = fopen("out.txt", "r");
// 	if (!fp)
// 	{
// 		perror("Error opening input file");
// 		return 1;
// 	}

// 	char *ops[MAX_OPS];
// 	char line[MAX_LINE];
// 	int count = 0;

// 	while (fgets(line, sizeof(line), fp) && count < MAX_OPS)
// 		ops[count++] = strdup(line);
// 	fclose(fp);

// 	printf("Original ops count: %d\n", count);

// 	int new_count = 0;
// 	char **optimized = peephole_optimize(ops, count, &new_count);

// 	printf("Optimized ops count: %d\n", new_count);

// 	// Save to optimized.txt
// 	fp = fopen("optimized.txt", "w");
// 	if (!fp)
// 	{
// 		perror("Error writing optimized file");
// 		return 1;
// 	}
// 	for (int i = 0; i < new_count; i++)
// 		fprintf(fp, "%s", optimized[i]);
// 	fclose(fp);

// 	// Free memory
// 	for (int i = 0; i < count; i++)
// 		free(ops[i]);
// 	for (int i = 0; i < new_count; i++)
// 		free(optimized[i]);
// 	free(optimized);

// 	return 0;
// }
