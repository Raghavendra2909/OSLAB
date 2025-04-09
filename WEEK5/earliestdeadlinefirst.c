#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int burst;
    int period;
    int deadline;
    int remaining_bt;
};

struct Process p[10]; // max 10 processes
int n;
int time = 0;

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int calculate_lcm_of_periods() {
    int result = p[0].period;
    for (int i = 1; i < n; i++) {
        result = (result * p[i].period) / gcd(result, p[i].period);
    }
    return result;
}



void earliest_deadline_first(int sim_time) {
    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = 0;
        p[i].deadline = p[i].period;
    }

    printf("\n--- Earliest Deadline First Scheduling ---\n");
    time = 0;

    while (time < sim_time) {
        int idx = -1;
        int min_deadline = 9999;

        for (int i = 0; i < n; i++) {
            if (time % p[i].period == 0) {
                p[i].remaining_bt = p[i].burst;
                p[i].deadline = time + p[i].period;
            }
            if (p[i].remaining_bt > 0 && p[i].deadline < min_deadline) {
                min_deadline = p[i].deadline;
                idx = i;
            }
        }

        if (idx != -1) {
            printf("Time %2d: Task %d\n", time, p[idx].pid);
            p[idx].remaining_bt--;
        } else {
            printf("Time %2d: Idle\n", time);
        }

        time++;
    }
}

int main() {
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time and Period for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d Burst Time: ", p[i].pid);
        scanf("%d", &p[i].burst);
        printf("Process %d Period: ", p[i].pid);
        scanf("%d", &p[i].period);
    }

    int sim_time = calculate_lcm_of_periods();
    printf("\nSimulation Time (LCM of periods): %d ms\n", sim_time);

    earliest_deadline_first(sim_time);

    return 0;
}


/*
OUTPUT:
Enter the number of processes: 3
Enter Burst Time and Period for each process:
Process 1 Burst Time: 2
Process 1 Period: 1
Process 2 Burst Time: 3
Process 2 Period: 2
Process 3 Burst Time: 4
Process 3 Period: 3

Simulation Time (LCM of periods): 6 ms

--- Earliest Deadline First Scheduling ---
Time  0: Task 1
Time  1: Task 1
Time  2: Task 1
Time  3: Task 1
Time  4: Task 1
Time  5: Task 1
*/