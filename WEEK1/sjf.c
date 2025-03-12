#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], remaining[n];
    int completion[n], turnaround[n], waiting[n];
    int finished = 0, currentTime = 0, shortest = -1, minBurst = INT_MAX;
    int isCompleted[n];

    // Input: Arrival & Burst Times
    printf("\nEnter Arrival and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);

        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);

        remaining[i] = burst[i]; 
        isCompleted[i] = 0;     
    }

    
    while (finished < n) {
        shortest = -1;
        minBurst = INT_MAX;

        // Find the process with the shortest remaining burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (arrival[i] <= currentTime && remaining[i] > 0 && remaining[i] < minBurst) {
                minBurst = remaining[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++; // No process available, increase time
            continue;
        }

        remaining[shortest]--; // Execute the process for 1 unit time
        currentTime++;

        // If the process is finished, calculate completion time
        if (remaining[shortest] == 0) {
            completion[shortest] = currentTime;
            finished++;
            isCompleted[shortest] = 1;
        }
    }

    // Calculate Turnaround Time & Waiting Time
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];

        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
    }

    return 0;
}

/*
OUTPUT:
Enter the number of processes: 3

Enter Arrival and Burst Time for each process:
Process 1 Arrival Time: 0
Process 1 Burst Time: 2
Process 2 Arrival Time: 3
Process 2 Burst Time: 4
Process 3 Arrival Time: 5
Process 3 Burst Time: 8

Process Arrival Burst   Completion      Turnaround      Waiting
1       0       2       2               2               0
2       3       4       7               4               0
3       5       8       15              10              2
*/
