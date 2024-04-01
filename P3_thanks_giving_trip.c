#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	while (1) {
		int people;
		scanf("%d", &people);
		if (people == 0)
			break;
		else if (people >= 100) {
			printf("The number of students cann't be more than 100\n");
			break;
		}
		int* arr = malloc(sizeof(int) * people);
		float sum = 0, avg = 0;
		for (int i = 0; i < people; i++) {
			scanf("%d", &arr[i]);
			if (arr[i] >= 100000) {
				printf("Student can't spent more than 100000won\n");
				printf("Please type again\n");
				i--;
			}
			else {
				sum = sum + arr[i];
				//printf("sum=%f\n", sum);
			}
		}
		avg = floor(((sum / people) / 10) * 10);
		sum = 0;
		for (int i = 0; i < people; i++) {
			if (avg - arr[i] > 0) {
				sum = sum + (avg - arr[i]);
			}
		}
		printf("output: %.0f\n", sum);
	}
}