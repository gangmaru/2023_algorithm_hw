#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	FILE* file = fopen("P7_test.txt", "r");
	
	while (1) {
		int jewel;
		fscanf(file, "%d", &jewel);

		if (jewel == 0) //total jewel==0
			break;
		else if (jewel < 0 || jewel>1000) { //wrong data
			printf("try again\n");
		}

		//check data
		int c1, n1, c2, n2;
		fscanf(file, "%d %d", &c1, &n1);
		if ((c1 < 0 || c1>1000) || (n1 < 0 || n1>1000)) {
			printf("try again\n");
			continue;
		}

		fscanf(file, "%d %d", &c2, &n2);
		if ((c2 < 0 || c2>1000) || (n2 < 0 || n2>1000)) {
			printf("try again\n");
			continue;
		}

		int max = 0;
		int maxN, extraN;
		//type1
		if (n1 / c1 > n2 / c2) {
			max = jewel / n1;
			maxN = n1;
			extraN = n2;
		}
		//type2
		else {
			max = jewel / n2;
			maxN = n2;
			extraN = n1;
		}

		int i;
		for (i = 0; i < max; i++) {
			if ((max * maxN) + (i * extraN) == jewel) {
				if (maxN == n1) {
					printf("%d %d\n", max, i);
					break;
				}
				else if (maxN == n2) {
					printf("%d %d\n", i, max);
					break;
				}
			}
			else if ((max * n1) + (i * n2) != jewel) {
				max--;
			}
		}
		if ((max * maxN) + (i * extraN) != jewel) {
			printf("failed\n");
		}
	}
	return 0;
}