#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Process {
    int pid;
    int burst;
    int period;
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

void rate_monotonic(int sim_time) {
    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = 0;
    }

    printf("\n--- Rate Monotonic Scheduling ---\n");
    time = 0;

    while (time < sim_time) {
        int idx = -1;
        int min_period = 9999;

        for (int i = 0; i < n; i++) {
            if (time % p[i].period == 0) {
                p[i].remaining_bt = p[i].burst;
            }
            if (p[i].remaining_bt > 0 && p[i].period < min_period) {
                min_period = p[i].period;
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
    float totalcpu_util = 0;

    printf("Enter Burst Time and Period for each process:\n");
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d Burst Time: ", p[i].pid);
        scanf("%d", &p[i].burst);
        printf("Process %d Period: ", p[i].pid);
        scanf("%d", &p[i].period);

        float x = (float)p[i].burst / p[i].period;
        printf("CPU utilization for process %d is: %.2f\n", i + 1, x);
        totalcpu_util += x;
    }

    int sim_time = calculate_lcm_of_periods();
    printf("\nSimulation Time (LCM of periods): %d\n", sim_time);

    rate_monotonic(sim_time);

    float worstcaseCpuutil = n * (pow(2, 1.0 / n) - 1);

    printf("\nTotal CPU Utilization: %.2f\n", totalcpu_util);
    printf("Worst Case Utilization Bound: %.2f\n", worstcaseCpuutil);

    if (totalcpu_util <= worstcaseCpuutil) {
        printf("\nSince %.2f <= %.2f,\nScheduling is possible under Rate Monotonic Scheduling.\n", totalcpu_util, worstcaseCpuutil);
    } else {
        printf("\nSince %.2f > %.2f,\nScheduling is NOT guaranteed under Rate Monotonic Scheduling.\n", totalcpu_util, worstcaseCpuutil);
    }

    return 0;
}


/*
OUTPUT:
Enter the number of processes: 3
Enter Burst Time and Period for each process:
Process 1 Burst Time: 3
Process 1 Period: 3
CPU utilization for process 1 is: 1.00
Process 2 Burst Time: 6
Process 2 Period: 4
CPU utilization for process 2 is: 1.50
Process 3 Burst Time: 8
Process 3 Period: 5
CPU utilization for process 3 is: 1.60

Simulation Time (LCM of periods): 60

--- Rate Monotonic Scheduling ---
Time  0: Task 1
Time  1: Task 1
Time  2: Task 1
Time  3: Task 1
Time  4: Task 1
Time  5: Task 1
Time  6: Task 1
Time  7: Task 1
Time  8: Task 1
Time  9: Task 1
Time 10: Task 1
Time 11: Task 1
Time 12: Task 1
Time 13: Task 1
Time 14: Task 1
Time 15: Task 1
Time 16: Task 1
Time 17: Task 1
Time 18: Task 1
Time 19: Task 1
Time 20: Task 1
Time 21: Task 1
Time 22: Task 1
Time 23: Task 1
Time 24: Task 1
Time 25: Task 1
Time 26: Task 1
Time 27: Task 1
Time 28: Task 1
Time 29: Task 1
Time 30: Task 1
Time 31: Task 1
Time 32: Task 1
Time 33: Task 1
Time 34: Task 1
Time 35: Task 1
Time 36: Task 1
Time 37: Task 1
Time 38: Task 1
Time 39: Task 1
Time 40: Task 1
Time 41: Task 1
Time 42: Task 1
Time 43: Task 1
Time 44: Task 1
Time 45: Task 1
Time 46: Task 1
Time 47: Task 1
Time 48: Task 1
Time 49: Task 1
Time 50: Task 1
Time 51: Task 1
Time 52: Task 1
Time 53: Task 1
Time 54: Task 1
Time 55: Task 1
Time 56: Task 1
Time 57: Task 1
Time 58: Task 1
Time 59: Task 1

Total CPU Utilization: 4.10
Worst Case Utilization Bound: 0.78

Since 4.10 > 0.78,
Scheduling is NOT guaranteed under Rate Monotonic Scheduling.
*/