#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX_N 10000

typedef struct {
	double x, y;
}xy;

xy pt[MAX_N];
xy pt_by_y[MAX_N];
int num;
xy area[MAX_N];

//function to compare two dimensional each x values
int compare_by_x(const void* arg1, const void* arg2) {
	xy* pt1, * pt2;
	double diff;
	pt1 = (xy*)arg1;
	pt2 = (xy*)arg2;
	diff = pt1->x - pt2->x;
	if (diff < 0)
		return -1;
	if (diff > 0)
		return 1;
	return 0;
}
//function to get result about distance between the closest pair of points
double get_result(int left, int right) {
	int i, point1, point2, point3;
	double min_result, temp;
	int mid = (left + right) / 2;
	double leftmost_x, rightmost_x;
	if (left == right) {
		pt_by_y[left].x = pt[left].x;
		pt_by_y[left].y = pt[left].y;
		return 80000.0;
	}
	min_result = get_result(left, mid);
	temp = get_result(mid + 1, right);
	if (min_result == -1 || (temp > -1 && temp < min_result)) {
		min_result = temp;
	}
	point1 = left;
	point2 = mid + 1;
	point3 = left;
	while (point1 <= mid || point2 <= right) {
		if (point2 > right || (point1 <= mid && pt_by_y[point1].y <= pt_by_y[point2].y)) {
			area[point3].x = pt_by_y[point1].x;
			area[point3].y = pt_by_y[point1].y;
			point1++;
		}
		else {
			area[point3].x = pt_by_y[point2].x;
			area[point3].y = pt_by_y[point2].y;
			point2++;
		}
		point3++;
	}
	for (i = left; i <= right; i++) {
		pt_by_y[i].x = area[i].x;
		pt_by_y[i].y = area[i].y;
	}
	leftmost_x = pt[mid].x - min_result;
	rightmost_x = pt[mid].x + min_result;
	num = 0;
	for (i = left; i <= right; i++)
		if (pt_by_y[i].x >= leftmost_x && pt_by_y[i].x <= rightmost_x) {
			area[num].x = pt_by_y[i].x;
			area[num].y = pt_by_y[i].y;
			num++;
		}
	for (i = 0; i < num; i++) {
		int point = i - 1;
		while (point >= 0 && (area[point].y >= area[i].y - min_result)) {
			double diff = sqrt((area[point].x - area[i].x) * (area[point].x - area[i].x) +
				(area[point].y - area[i].y) * (area[point].y - area[i].y));
			if (diff < min_result) {
				min_result = diff;
			}
			point--;
		}
		point = i + 1;
		while (point < num && (area[point].y <= area[i].y + min_result)) {

			double diff = sqrt((area[point].x - area[i].x) * (area[point].x - area[i].x) +
				(area[point].y - area[i].y) * (area[point].y - area[i].y));
			if (diff < min_result) {
				min_result = diff;
			}
			point++;
		}
	}
	return min_result;
}

int main() {
	int i, n;
	double result;

	FILE* file = fopen("marketing_strategy_input.txt", "r");
	
	fscanf(file, "%d", &n);

	while (n != 0) {
		//input two dimensional points
		for (i = 0; i < n; i++) {
			fscanf(file, "%lf %lf", &pt[i].x, &pt[i].y);
		}
		qsort(pt, (size_t)n, sizeof(xy), compare_by_x);
		result = get_result(0, n - 1);
		if (result < 10000)
			printf("%.4f\n", result);
		else
			printf("INFINITY\n"); //if two points distance is more than 10000
		//if n==0, quit program
		fscanf(file, "%d", &n);
	}
	
}