#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAXN 100
#define MAXT 1000
#define MAXNAMELENGTH 100

static char cityname[MAXN][MAXNAMELENGTH];
static int n, t, depart, start, end, tn[MAXT], train[MAXT][MAXN][2];
static int mintime[MAXN][2], check[MAXN];

int getcitytag(char* name) {
	int i;

	for (i = 0; i < n; i++) {
		if (strcmp(name, cityname[i]) == 0)
			return i;
	}

	return -1;
}


void solve() {
	int i, j, k, z, now;

	for (i = 0; i < n; i++) {
		mintime[i][0] = 10000;
		mintime[i][1] = -1;
		check[i] = 0;
	}

	//Using the Dijkstra algorithm to find the route with the fastest arrival time
	mintime[start][0] = depart;

	for (i = 0; i < n; i++) {
		now = -1;
		for (j = 0; j < n; j++) {
			if (check[j])
				continue;
			if (now == -1 || mintime[now][0] > mintime[j][0])
				now = j;
		}

		if (mintime[now][0] == 10000)
			break;

		check[now] = 1;
		for (j = 0; j < t; j++) {
			for (k = 0; k < tn[j] - 1; k++) {
				if (train[j][k][1] == now && mintime[now][0] <= train[j][k][0]) {
					z = k + 1;
					if (mintime[train[j][z][1]][0] > train[j][z][0])
						mintime[train[j][z][1]][0] = train[j][z][0];
				}
			}
		}
	}

	if (check[end] == 0)
		return;

	//The latest departure time to arrive by the arrival time obtained above is 
	//obtained by applying the Dijkstra algorithm
	for (i = 0; i < n; i++) {
		check[i] = 0;
	}
	mintime[end][1] = mintime[end][0];

	for (i = 0; i < n; i++) {
		now = -1;
		for (j = 0; j < n; j++) {
			if (check[j])
				continue;

			if (now == -1 || mintime[now][1] < mintime[j][1])
				now = j;
		}

		check[now] = 1;
		for (j = 0; j < t; j++) {
			for (k = 1; k < tn[j]; k++) {
				if (train[j][k][1] == now && mintime[now][1] >= train[j][k][0]) {
					z = k - 1;
					if (mintime[train[j][z][1]][1] < train[j][z][0])
						mintime[train[j][z][1]][1] = train[j][z][0];
				}
			}
		}
	}
}
void main() {
	int s;
	FILE* fr = fopen("contest_trip_imput.txt", "r");

	fscanf_s(fr, "%d", &s);
	for (t = 1; t <= s; t++) {
		int i, j;
		char name[MAXNAMELENGTH];

		fscanf_s(fr, "%d", &n);
		for (i = 0; i < n; i++) {
			fscanf(fr, "%s", cityname[i]);
		}

		fscanf_s(fr, "%d", &t);
		for (i = 0; i < t; i++) {
			fscanf_s(fr, "%d", &tn[i]);
			for (j = 0; j < tn[i]; j++) {
				fscanf(fr, "%d %s", &train[i][j][0], name);
				train[i][j][1] = getcitytag(name);
			}
		}

		fscanf_s(fr, "%d", &depart);
		fscanf(fr, "%s", name);
		start = getcitytag(name);
		fscanf(fr, "%s", name);
		end = getcitytag(name);

		solve();

		printf("Scenario %d\n", t);

		if (check[end]) {
			printf("Departure %04d %s\n", mintime[start][1], cityname[start]);
			printf("Arrival   %04d %s\n", mintime[end][0], cityname[end]);
		}
		else
			printf("No connection\n");
		printf("\n");
	}
}