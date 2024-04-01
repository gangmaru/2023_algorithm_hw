#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void find_cheapest_way(int** mat, int m, int n) {
	int minsum = 0;
	int* cost = (int*)malloc(n * 2 * sizeof(int));
	int i, j, k;

	for (i = m - 1, j = n - 1, k = 0; i > 0 || j > 0; k++) {
		cost[k] = mat[i][j];
		minsum += mat[i][j];
		if (i == 0 && j == 1) break;
		else if (i == 1 && j == 1) break;
		else if (i == 0 && j == 1)break;

		int row = i, column = j;
		int c = 20;


		if (i > 1) {
			if (c > mat[i - 1][j] + mat[i - 2][j]) {
				c = mat[i - 1][j] + mat[i - 2][j];
				row = i - 1;
				column = j;
			}
			if (j > 0) {
				if (c > mat[i - 1][j] + mat[i - 2][j - 1]) {
					c = mat[i - 1][j] + mat[i - 2][j - 1];
					row = i - 1;
					column = j;
				}
				if (c >= mat[i - 1][j - 1] + mat[i - 2][j - 1]) {
					c = mat[i - 1][j - 1] + mat[i - 2][j - 1];
					row = i - 1;
					column = j - 1;
				}
			}
		}
		if (j > 1) {
			if (c > mat[i][j - 1] + mat[i][j - 2]) {
				c = mat[i][j - 1] + mat[i][j - 2];
				row = i;
				column = j - 1;
			}if (i > 0) {
				if (c > mat[i][j - 1] + mat[i - 1][j - 2]) {
					c = mat[i][j - 1] + mat[i - 1][j - 2];
					row = i;
					column = j - 1;
				}
				if (c >= mat[i - 1][j - 1] + mat[i - 1][j - 2]) {
					c = mat[i - 1][j - 1] + mat[i - 1][j - 2];
					row = i - 1;
					column = j - 1;
				}
			}
		}
		if (i > 1 && j > 1) {
			if (c >= mat[i - 1][j - 1] + mat[i - 2][j - 2]) {
				c = mat[i - 1][j - 1] + mat[i - 2][j - 2];
				row = i - 1;
				column = j - 1;
			}
		}
		if (i > 0 && j > 0) {
			if (c > mat[i - 1][j] + mat[i - 1][j - 1]) {
				c = mat[i - 1][j] + mat[i - 1][j - 1];
				row = i - 1;
				column = j;
			}
			if (c > mat[i][j - 1] + mat[i - 1][j - 1]) {
				c = mat[i][j - 1] + mat[i - 1][j - 1];
				row = i;
				column = j - 1;
			}
		}
		if (i == m - 1 && j > 1) {
			if (c >= mat[0][j - 1] + mat[0][j - 2]) {
				c = mat[0][j - 1] + mat[0][j - 2];
				row = 0;
				column = j - 1;
			}
		}
		if (i == m - 1 && j == 3) {
			if (c >= mat[0][j - 1] + mat[1][j - 2]) {
				c = mat[0][j - 1] + mat[1][j - 2];
				row = 0;
				column = j - 1;
			}
		}
		if (i == 0 && j == 2) {
			if (c >= mat[1][1] + mat[0][0]) {
				c = mat[1][1] + mat[0][0];
				row = 1;
				column = 1;
			}
		}
		i = row;
		j = column;
	}
	minsum += mat[0][0];
	cost[k + 1] = mat[0][0];

	for (int x = k + 1; x > -1; x--) {
		printf("%d ", cost[x]);
	}
	printf("\n");

	printf("%d\n", minsum);

}

int main() {
	int row, col, a, b;
	FILE* fr = fopen("the_cheapest_way_input.txt", "r");
	while (fscanf(fr, "%d %d", &row, &col) != EOF) {
		int** mat;
		mat = (int**)malloc(row * sizeof(int*));
		for (a = 0; a < row; a++) {
			mat[a] = (int*)malloc(col * sizeof(int));
		}

		for (a = 0; a < row; a++) {
			for (b = 0; b < col; b++) {
				fscanf(fr, "%d", &mat[a][b]);
			}
		}

		find_cheapest_way(mat, row, col);
	}
	return 0;
}