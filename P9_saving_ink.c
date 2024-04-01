#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

struct EDGE{
	int v1, v2;
	double len;
};
int cmp(const void* a, const void* b){
	if (((struct EDGE*)a)->len > ((struct EDGE*)b)->len)
		return 1;
	if (((struct EDGE*)a)->len < ((struct EDGE*)b)->len)
		return -1;
	return 0;
}
int main(){
	FILE* fr = fopen("saving_ink_input.txt", "r");

	struct EDGE edge[100];
	double mat[100][2], sum, key;
	int i, j, a = 0, n, temp;
	int save[100];

	fscanf(fr, "%d", &n);


	for (i = 0; i < n; i++) {
		fscanf(fr, "%lf %lf", &mat[i][0], &mat[i][1]);
	}

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			edge[a].v1 = i;
			edge[a].v2 = j;
			key = sqrt(pow(mat[i][0] - mat[j][0], 2) + pow(mat[i][1] - mat[j][1], 2));
			edge[a++].len = key;
		}
	}

	qsort(edge, a, sizeof(struct EDGE), cmp);
	for (i = 0; i < n; i++) {
		save[i] = i;
	}

	sum = 0;
	for (i = 0; i < a; i++)
		if (save[edge[i].v1] != save[edge[i].v2]){
			temp = save[edge[i].v1];
			for (j = 0; j < n; j++)
				if (save[j] == temp)
					save[j] = save[edge[i].v2];
			sum += edge[i].len;
		}
	printf("%.2lf\n", sum);
	return 0;
}