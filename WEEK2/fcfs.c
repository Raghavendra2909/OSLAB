#include <stdio.h>
#include <limits.h>
//week1

int n;

int findMinIndex(int arr[]) {
    int mini = INT_MAX;
    int minIndex = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] < mini) {
            mini = arr[i];
            minIndex = i;
        }
    }
    return minIndex;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival[n], burst[n], completion[n], turnaround[n], waiting[n];
    int helper[n];

    printf("\nEnter the Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);

        printf("Process %d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);

        helper[i] = arrival[i]; 
    }

    int time = 0, a = n;

    while (a > 0) {
        int index = findMinIndex(helper);

        if (index == -1) {
            time++;
            continue;
        }

        if (arrival[index] > time) {
            time = arrival[index]; 
        }

        time += burst[index];
        completion[index] = time;
        helper[index] = INT_MAX; 
        a--;
    }

    
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];

        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", i + 1, arrival[i], burst[i], completion[i], turnaround[i], waiting[i]);
    }

    return 0;
}


/*
Enter the number of processes: 3

Enter the Arrival Time and Burst Time for each process:
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
