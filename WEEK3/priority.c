#include <stdio.h>

#define MAX 100

void priorityPreemptive(int n, int at[], int bt[], int pr[]) {
    int ct[n], tat[n], wt[n], rem_bt[n], is_completed[n];
    int time = 0, completed = 0, min_priority, index;

    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
        is_completed[i] = 0;
    }

    while (completed < n) {
        min_priority = 9999;
        index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && is_completed[i] == 0 && pr[i] < min_priority && rem_bt[i] > 0) {
                min_priority = pr[i];
                index = i;
            }
        }

        if (index == -1) {
            time++;
        } else {
            rem_bt[index]--;
            time++;

            if (rem_bt[index] == 0) {
                ct[index] = time;
                is_completed[index] = 1;
                completed++;
            }
        }
    }

    float total_tat = 0, total_wt = 0;
    printf("\nP#\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_tat += tat[i];
        total_wt += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);
}

void priorityNonPreemptive(int n, int at[], int bt[], int pr[]) {
    int ct[n], tat[n], wt[n], is_completed[n], rem_bt[n];
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        is_completed[i] = 0;
        rem_bt[i] = bt[i];
    }

    while (completed < n) {
        int min_priority = 9999, index = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && is_completed[i] == 0 && pr[i] < min_priority) {
                min_priority = pr[i];
                index = i;
            }
        }

        if (index == -1) {
            time++;
        } else {
            time += bt[index];
            ct[index] = time;
            is_completed[index] = 1;
            completed++;
        }
    }

    float total_tat = 0, total_wt = 0;
    printf("\nP#\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_tat += tat[i];
        total_wt += wt[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
    }

    printf("Average TAT: %.2f\n", total_tat / n);
    printf("Average WT: %.2f\n", total_wt / n);
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter AT, BT, and Priority P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);
    }

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. Preemptive Priority Scheduling\n");
    printf("2. Non-Preemptive Priority Scheduling\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        priorityPreemptive(n, at, bt, pr);
    } else if (choice == 2) {
        priorityNonPreemptive(n, at, bt, pr);
    } else {
        printf("Invalid choice!\n");
    }

    return 0;
}



/*
Enter number of processes: 4
Enter AT, BT, and Priority P1: 0 5 10
Enter AT, BT, and Priority P2: 1 4 20
Enter AT, BT, and Priority P3: 2 2 30
Enter AT, BT, and Priority P4: 4 1 40

Choose Scheduling Algorithm:
1. Preemptive Priority Scheduling
2. Non-Preemptive Priority Scheduling
Enter choice: 1

P#      AT      BT      PR      CT      TAT     WT
1       0       5       10      5       5       0
2       1       4       20      9       8       4
3       2       2       30      11      9       7
4       4       1       40      12      8       7
Average TAT: 7.50
Average WT: 4.50

PS C:\Users\Admin\Downloads\1BM23CS258> cd "c:\Users\Admin\Downloads\1BM23CS258\" ; if ($?) { gcc priority.c -o priority } ; if ($?) { .\priority }
Enter number of processes: 5
Enter AT, BT, and Priority P1: 0 3 5 
Enter AT, BT, and Priority P2: 2 2 3
Enter AT, BT, and Priority P3: 3 5 2
Enter AT, BT, and Priority P4: 4 4 4
Enter AT, BT, and Priority P5: 6 1 1 

Choose Scheduling Algorithm:
1. Preemptive Priority Scheduling
2. Non-Preemptive Priority Scheduling
Enter choice: 2

P#      AT      BT      PR      CT      TAT     WT
1       0       3       5       3       3       0
2       2       2       3       11      9       7
3       3       5       2       8       5       0
4       4       4       4       15      11      7
5       6       1       1       9       3       2
Average TAT: 6.20
Average WT: 3.20
*/
