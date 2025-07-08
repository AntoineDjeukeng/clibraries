#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a, b, c;
} Triangle;

// Score ordered triple based on how sorted/consecutive it is
int ordered_score(int x, int y, int z) {
    int score = 0;

    if (x < y && y < z)
        score += 5; // Fully increasing
    if (x > y && y > z)
        score += 4; // Fully decreasing

    // Count increasing pairs
    if (x < y) score += 1;
    if (y < z) score += 1;

    // Fully consecutive in order (e.g. 4,5,6)
    if (y == x + 1 && z == y + 1)
        score += 3;

    return score;
}

// Print triangle nicely
void print_triangle(const char *label, int x, int y, int z, int score) {
    printf("%s (%d, %d, %d) => Score: %d\n", label, x, y, z, score);
}

int main() {
    // Define point values
    int A = 4, B = 7, C = 5, A1 = 3, B1 = 6, C1 = 8;

    // Define base triangles (19 of them)
    Triangle base[] = {
        {A, B, C},
        {A, B, A1}, {A, B, B1}, {A, B, C1},
        {A, C, A1}, {A, C, B1}, {A, C, C1},
        {B, C, A1}, {B, C, B1}, {B, C, C1},
        {A, A1, B1}, {A, A1, C1}, {A, B1, C1},
        {B, A1, B1}, {B, A1, C1}, {B, B1, C1},
        {C, A1, B1}, {C, A1, C1}, {C, B1, C1}
    };

    int best_score = -999;
    int best_x = 0, best_y = 0, best_z = 0;

    // Permutation labels for debugging
    const char *labels[] = {
        "ABC", "ACB", "BAC", "BCA", "CAB", "CBA"
    };

    // Evaluate all permutations of all triangles
    for (int t = 0; t < sizeof(base) / sizeof(base[0]); t++) {
        int x = base[t].a, y = base[t].b, z = base[t].c;
        int perms[6][3] = {
            {x, y, z},
            {x, z, y},
            {y, x, z},
            {y, z, x},
            {z, x, y},
            {z, y, x}
        };

        for (int i = 0; i < 6; i++) {
            int a = perms[i][0], b = perms[i][1], c = perms[i][2];
            int score = ordered_score(a, b, c);
            print_triangle(labels[i], a, b, c, score);

            if (score > best_score) {
                best_score = score;
                best_x = a; best_y = b; best_z = c;
            }
        }
    }

    printf("\n✅ Best Ordered Triangle: (%d, %d, %d) with Score: %d\n",
           best_x, best_y, best_z, best_score);

    return 0;
}
