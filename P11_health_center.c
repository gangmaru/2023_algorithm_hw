#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 1000000

int dist[505][505];

int main() {
    int f, I; 
    while (scanf("%d %d", &f, &I) == 2) { //health center number , intersection number
        for (int i = 1; i <= I; i++) {
            for (int j = 1; j <= I; j++) {
                dist[i][j] = (i == j) ? 0 : INF;
            }
        }

        for (int i = 0; i < f; i++) {
            int center;
            scanf("%d", &center); //health center location
            dist[center][center] = 0;
        }

        int a, b, c;
        while (scanf("%d %d %d", &a, &b, &c) == 3) { //intersection distance
            if (dist[a][b] > c) {
                dist[a][b] = dist[b][a] = c;
            }
        }

        // Floyd-Warshall algorithm to find shortest distances
        for (int k = 1; k <= I; k++) {
            for (int i = 1; i <= I; i++) {
                for (int j = 1; j <= I; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        int maxDist = INF;
        int bestLocation = 1;

        // Check each intersection as the new health center location
        for (int i = 1; i <= I; i++) {
            int maxDistFromCenter = 0;
            for (int j = 1; j <= I; j++) {
                if (dist[i][j] > maxDistFromCenter) {
                    maxDistFromCenter = dist[i][j];
                }
            }
            if (maxDistFromCenter < maxDist) {
                maxDist = maxDistFromCenter;
                bestLocation = i;
            }
        }

        printf("%d\n\n", bestLocation);
    }

    return 0;
}
