#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Point {
	double x, y;
};

struct Point p0;

// A utility function to find next to top in a struct
struct Point nextToTop(struct Point* S, int* top) {
	struct Point p = S[*top];
	(*top)--;
	struct Point res = S[*top];
	S[(*top)++] = p;
	return res;
}

// A utility function to swap two points
void swap(struct Point* p1, struct Point* p2) {
	struct Point temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(struct Point p1, struct Point p2) {
	return (int)((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// To find orientation of ordered triplet (p, q, r)
int orientation(struct Point p, struct Point q, struct Point r) {
	int val = (int)((q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y));
	if (val == 0)
		return 0;
	return (val > 0) ? 1 : 2;
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void* vp1, const void* vp2) {
	struct Point* p1 = (struct Point*)vp1;
	struct Point* p2 = (struct Point*)vp2;

    // Find orientation
	int o = orientation(p0, *p1, *p2);
	if (o == 0)
		return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

	return (o == 2) ? -1 : 1;
}

// Prints convex hull of a set of n points
void convexHull(struct Point* points, int n, struct Point* hull, int* hullsize) {
    
    // Find the bottommost point
    double ymin = points[0].y;
    int min = 0;
    for (int i = 1; i < n; i++){
        double y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Place the bottom-most point at first position
    swap(&points[0], &points[min]);
    p0 = points[0];
    qsort(&points[1], n - 1, sizeof(struct Point), compare);

    int m = 1; // Initialize size of modified array
    for (int i = 1; i < n; i++){
        while (i < n - 1 && orientation(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++; // Update size of modified array
    }

    if (m < 3)
        return;

    int top = 2;
    // Create an empty stack and push first three points to it
    struct Point* S = (struct Point*)malloc(m * sizeof(struct Point));
    S[0] = points[0];
    S[1] = points[1];
    S[2] = points[2];

    for (int i = 3; i < m; i++){
        while (top > 1 && orientation(nextToTop(S, &top), S[top], points[i]) != 2)
            top--;
        S[++top] = points[i];
    }

    *hullsize = top + 1;

    // Now stack has the output points, print contents of stack
    for (int i = 0; i < *hullsize; i++){
        hull[i] = S[i];
        printf("(%f, %f)\n", hull[i].x, hull[i].y);
    }

    free(S);
}


int main() {
    int numCases;
    int numFrosh;

    scanf("%d", &numCases);
    while (numCases--) {
        scanf("%d", &numFrosh);

        struct Point* frosh = (struct Point*)malloc(numFrosh * sizeof(struct Point));
        struct Point* hull = (struct Point*)malloc(numFrosh * sizeof(struct Point));
        int hullsize = 0;

        for (int i = 0; i < numFrosh; i++) {
            scanf("%lf %lf", &frosh[i].x, &frosh[i].y);
        }

        convexHull(frosh, numFrosh, hull, &hullsize);

        double P = 0;
        double* distances = (double*)malloc(hullsize * sizeof(double));

        for (int i = 0; i < hullsize; i++) {
            distances[i] = sqrt(hull[i].x * hull[i].x + hull[i].y * hull[i].y);
        }

        double S = 0;
        // Find shortest length from origin to vertex
        for (int i = 0; i < hullsize; i++) {
            if (distances[i] < S)
                S = distances[i];
        }

        double length = P + 2 * S;

        printf("%.2f\n", length);

        free(frosh);
        free(hull);
        free(distances);
    }

}