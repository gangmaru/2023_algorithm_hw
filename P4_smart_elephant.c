#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//elephant structure
struct elephant {
	int order;
	int weight;
	int IQ;
};
typedef struct elephant Elephant;
typedef Elephant* Elephantptr;
    //function: input.txt's line counting
	int lineCount(FILE * file) {
		int count = 0;
		char tmp[20];
		while (fgets(tmp, sizeof(tmp), file) != NULL) {
			count++;
		}
		rewind(file);
		return count;
	}
	//function: sorting elephant weight and IQ
	void sort(Elephantptr elephant, int len) {
		int min = 0, index = 0;

		for (int i = 0; i < len - 1; i++) {
			min = (elephant + i)->weight; //min value
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
	//function: increasing weight, decreasing IQ
	void smart(Elephantptr elephant, int len) {
		int count = 0;
		int iq = 0;
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
		
		FILE* file = fopen("smart_elephant_input.txt", "r");
		if (file == NULL) {
			printf("FILE doesn't exists!\n");
			exit(0);
		}

		char temp[20];
		int length = lineCount(file), j = 0;
		Elephantptr elephant = (Elephantptr)malloc(sizeof(Elephant) * length);
		while (fgets(temp, sizeof(temp), file) != NULL) {
			(elephant + j)->weight = atoi(strtok(temp, " "));
			(elephant + j)->IQ = atoi(strtok(NULL, " "));
			(elephant + j)->order = j + 1;
			j++;
		}
		sort(elephant, length);
		smart(elephant, length);
		fclose(file);
	}