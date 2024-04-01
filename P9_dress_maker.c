#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int n;
int result[1000];
int* ti, * si;
int main() {
    FILE* fr = fopen("dress_maker_input.txt", "r");
    int t, tempti, tempsi;
    fscanf(fr, "%d", &t);

    for (int i = 0; i < t; i++) {
        fscanf(fr, "%d", &n);

        ti = (int*)malloc(n * sizeof(int));
        si = (int*)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            fscanf(fr, "%d %d", &tempti, &tempsi);
            ti[i] = tempti;
            si[i] = tempsi;
        }

        for (int k = 0; k < n; k++) {
            result[k] = k;
        }

        int temp;
        for (int k = 1; k < n; k++) {
            for (int kk = 0; kk < n - k; kk++) {
                if (ti[result[kk]] * si[result[kk + 1]] > ti[result[kk + 1]] * si[result[kk]]) {
                    temp = result[kk];
                    result[kk] = result[kk + 1];
                    result[kk + 1] = temp;
                }
            }
        }

        for (int j = 0; j < n - 1; j++) {
            printf("%d ", result[j] + 1);
        }

        printf("%d ", result[n - 1] + 1);
        printf("\n");

        free(ti);
        free(si);
    }
    fclose(fr);
    return 0;
}
struct elephants {
	int order;
	int weight;
	int IQ;
};
typedef struct elephants Elephant;
typedef Elephant* ElephantPtr;
int lineCount(FILE* fr) {
	int count = 0;
	char temp[20];
	while (fgets(temp, sizeof(temp), fr) != NULL){
		count++;
	}
	rewind(fr);
	return count;
}
void sort(ElephantPtr elephant, int len) {
	int min = 0, index = 0;
	for (int i = 0; i < len - 1; i++){
		min = (elephant + i)->weight;
		index = i;
		for (int j = i + 1; j < len; j++){
			if ((elephant + j)->weight < min){
				min = (elephant + j)->weight;
				index = j;
			}
		}
		int temp1 = (elephant + index)->order;
		int temp2 = (elephant + index)->IQ;
		int temp3 = (elephant + index)->weight;
		(elephant + index)->order = (elephant + i)->order;
		(elephant + index)->IQ = (elephant + i)->IQ;
		(elephant + index)->weight = (elephant + i)->weight;
		(elephant + i)->order = temp1;
		(elephant + i)->IQ = temp2;
		(elephant + i)->weight = temp3;
	}
}
void smart(ElephantPtr elephant, int len) {
	int count = 0, iq = 0;
	int* list = (int*)malloc(sizeof(int) * len);
	for (int i = 0; i < len; i++){
		if (i == 0){
			list[count] = (elephant + i)->order;
			iq = (elephant + i)->IQ;
			count++;
			continue;
		}
		if (iq < (elephant + i)->IQ){
			if (count < 2){
				count = 0;
				list[count] = (elephant + i)->order;
				iq = (elephant + i)->IQ;
				count++;
				continue;
			}
			else
				continue;
		}
		else{
			list[count] = (elephant + i)->order;
			iq = (elephant + i)->IQ;
			count++;
			continue;
		}
	}
	printf("%d\n", count);
	for (int i = 0; i < count; i++){
		printf("%d\n", list[i]);
	}
}
void main() {
	FILE* fr = fopen("input.txt", "r");
	if (fr == NULL) {
		printf("FILE doesn't exists!\n");
		exit(0);
	}
	char temp[20];
	int length = lineCount(fr), j = 0;
	ElephantPtr elephant = (ElephantPtr)malloc(sizeof(Elephant) * length);
	while (fgets(temp, sizeof(temp), fr) != NULL) {
		(elephant + j)->weight = atoi(strtok(temp, " "));
		(elephant + j)->IQ = atoi(strtok(NULL, " "));
		(elephant + j)->order = j + 1;
		j++;
	}
	sort(elephant, length);
	smart(elephant, length);
	fclose(fr);
}

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
	FILE* fr = fopen("sample.txt", "r");
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
struct elephants {
	int order;
	int weight;
	int IQ;
};
typedef struct elephants Elephant;
typedef Elephant* ElephantPtr;
int lineCount(FILE* fr) {
	int count = 0;
	char temp[20];
	while (fgets(temp, sizeof(temp), fr) != NULL) {
		count++;
	}
	rewind(fr);
	return count;
}
void sort(ElephantPtr elephant, int len) {
	int min = 0, index = 0;
	for (int i = 0; i < len - 1; i++) {
		min = (elephant + i)->weight;
		index = i;
		for (int j = i + 1; j < len; j++) {
			if ((elephant + j)->weight < min) {
				min = (elephant + j)->weight;
				index = j;
			}
		}
		int temp1 = (elephant + index)->order;
		int temp2 = (elephant + index)->IQ;
		int temp3 = (elephant + index)->weight;
		(elephant + index)->order = (elephant + i)->order;
		(elephant + index)->IQ = (elephant + i)->IQ;
		(elephant + index)->weight = (elephant + i)->weight;
		(elephant + i)->order = temp1;
		(elephant + i)->IQ = temp2;
		(elephant + i)->weight = temp3;
	}
}
void smart(ElephantPtr elephant, int len) {
	int count = 0, iq = 0;
	int* list = (int*)malloc(sizeof(int) * len);
	for (int i = 0; i < len; i++) {
		if (i == 0) {
			list[count] = (elephant + i)->order;
			iq = (elephant + i)->IQ;
			count++;
			continue;
		}
		if (iq < (elephant + i)->IQ) {
			if (count < 2) {
				count = 0;
				list[count] = (elephant + i)->order;
				iq = (elephant + i)->IQ;
				count++;
				continue;
			}
			else
				continue;
		}
		else {
			list[count] = (elephant + i)->order;
			iq = (elephant + i)->IQ;
			count++;
			continue;
		}
	}
	printf("%d\n", count);
	for (int i = 0; i < count; i++) {
		printf("%d\n", list[i]);
	}
}
void main() {
	FILE* fr = fopen("input.txt", "r");
	if (fr == NULL) {
		printf("FILE doesn't exists!\n");
		exit(0);
	}
	char temp[20];
	int length = lineCount(fr), j = 0;
	ElephantPtr elephant = (ElephantPtr)malloc(sizeof(Elephant) * length);
	while (fgets(temp, sizeof(temp), fr) != NULL) {
		(elephant + j)->weight = atoi(strtok(temp, " "));
		(elephant + j)->IQ = atoi(strtok(NULL, " "));
		(elephant + j)->order = j + 1;
		j++;
	}
	sort(elephant, length);
	smart(elephant, length);
	fclose(fr);
}

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
	FILE* fr = fopen("sample.txt", "r");
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