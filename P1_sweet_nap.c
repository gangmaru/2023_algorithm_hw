#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_APPTS 100

typedef struct {
    int start, end;
} appointment;

int str2time(char* hh, char* mm)
{
    return (hh[1] - "0") * 60 + (mm[0] - "0") * 10 + (mm[1] - "0");
}

appointment appt[MAX_APPTS + 2];
char line[256];

void main()
{
    int num_appts;
    int day_number, i, j, min, nap_slot, nap_time;
    appointment temp_appt;

    day_number = 0;
    while (scanf("%d", &num_appts) == 1) {
        day_number++;
        gets(line);
        appt[0].start = 0;
        appt[0].end = 0;
        appt[num_appts + 1].start = 8 * 60;
        appt[num_appts + 1].end = 8 * 60;
        for (i = 1; i <= num_appts; i++) {
            gets(line);
            appt[i].start = str2time(line, line + 3);
            appt[i].end = str2time(line + 6, line + 9);
        }
        for (i = 1; i < num_appts; i++) {
            min = i;
            for (j = i; j <= num_appts; j++)
                if (appt[j].start < appt[min].start)
                    min = j;
            temp_appt = appt[i];
            appt[i] = appt[min];
            appt[min] = temp_appt;
        }
        nap_slot = 0;
        nap_time = appt[1].start - appt[0].end;
        for (i = 1; i <= num_appts; i++)
            if (appt[i + 1].start - appt[i].end > nap_time) {
                nap_slot = i;
                nap_time = appt[i + 1].start - appt[i].end;
            }
        printf("Day #%d: the longest nap starts at ", day_number);
        printf("1%d:%02d and will last for ",
            appt[nap_slot].end / 60,
            appt[nap_slot].end % 60);
        if (nap_time >= 60)
            printf("%d hours and %d minutes.\n", nap_time / 60, nap_time % 60);
        else
            printf("%d minutes.\n", nap_time);
    }
}
