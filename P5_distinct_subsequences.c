#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//global variable
int count;

void loop(int flag, int num, int len, char s[], char t[]) {
	int k = 0;
	if (flag == 0)
		k = 0;
	else
		k = flag + 1;

	for (int i = k; i < len; i++) {
		//Change num and count values while comparing s[], t[]
		if (s[i]==t[num]) {
			num++;
			if (num == strlen(t)) {
				count++;
			}
			else {
				loop(i, num, len, s, t);
			}
			num--;
		}
	}
}

int main() {
	//Enter how many times you want to compare
	int time;
	printf("time: ");
	scanf("%d", &time);

	char s[100];
	char t[100];
	int len1;
	int len2;
	int len;

	while (time != 0) {
		char line[100];

		printf("S= ");
		scanf("%s", line);
		len1 = sizeof(line);
		//Copy the input line one letter at a time as an s[]
		for (int i = 0; i < len1; i++) {
			s[i] = line[i];
		}
		printf("T= ");
		scanf("%s", line);
		len2 = sizeof(line);
		//Copy the input line one letter at a time as an t[]
		for (int i = 0; i < len2; i++) {
			t[i] = line[i];
		}

		len = strlen(s);
		count = 0;

		loop(0, 0, len, s, t);

		printf("output: %d\n\n", count);
		time--;
	}
}