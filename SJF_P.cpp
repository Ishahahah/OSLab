#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Process {
    int pid; // Process ID
    int bt;  // Burst Time
    int art; // Arrival Time
};

// Function to find the waiting time for all processes
void findWaitingTime(vector<Process>& proc, vector<int>& wt) {
    vector<int> rt(proc.size());

    // Copy the burst time into rt[]
    for (size_t i = 0; i < proc.size(); i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    // Process until all processes get completed
    while (complete != proc.size()) {
        // Find the process with the minimum remaining time among the processes that arrive till the current time
        for (size_t j = 0; j < proc.size(); j++) {
            if (proc[j].art <= t && rt[j] < minm && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }

        // Reduce the remaining time by one
        rt[shortest]--;

        // Update the minimum
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completely executed
        if (rt[shortest] == 0) {
            // Increment complete
            complete++;
            check = false;

            // Find the finish time of the current process
            finish_time = t + 1;

            // Calculate the waiting time
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        // Increment time
        t++;
    }
}

// Function to calculate the turn around time
void findTurnAroundTime(const vector<Process>& proc, const vector<int>& wt, vector<int>& tat) {
    // Calculating the turnaround time by adding bt[i] + wt[i]
    for (size_t i = 0; i < proc.size(); i++)
        tat[i] = proc[i].bt + wt[i];
}

// Function to calculate the average time
void findAvgTime(vector<Process>& proc) {
    vector<int> wt(proc.size(), 0);
    vector<int> tat(proc.size(), 0);

    // Function to find the waiting time of all processes
    findWaitingTime(proc, wt);

    // Function to find the turn around time for all processes
    findTurnAroundTime(proc, wt, tat);

    // Display processes along with all details
    cout << " P\tBT\tWT\tTAT\n";

    // Calculate the total waiting time and total turnaround time
    int total_wt = 0, total_tat = 0;
    for (size_t i = 0; i < proc.size(); i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << " " << proc[i].pid << "\t" << proc[i].bt << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

    // Calculate and display the average waiting time and average turnaround time
    cout << "\nAverage waiting time = " << (float)total_wt / proc.size();
    cout << "\nAverage turn around time = " << (float)total_tat / proc.size();
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> proc(n);

    // Take input for process details
    for (int i = 0; i < n; i++) {
        cout << "Enter details for process " << i + 1 << ":" << endl;
        cout << "Process ID: ";
        cin >> proc[i].pid;
        cout << "Burst Time: ";
        cin >> proc[i].bt;
        cout << "Arrival Time: ";
        cin >> proc[i].art;
    }

    findAvgTime(proc);

  return 0;
}
/*Enter the number of processes: 4
Enter details for process 1:
Process ID: 1
Burst Time: 6
Arrival Time: 0
Enter details for process 2:
Process ID: 2
Burst Time: 4
Arrival Time: 1
Enter details for process 3:
Process ID: 3
Burst Time: 2
Arrival Time: 2
Enter details for process 4:
Process ID: 4
Burst Time: 3
Arrival Time: 3
 P      BT      WT      TAT
 1      6       9       15
 2      4       2       6
 3      2       0       2
 4      3       4       7

Average waiting time = 3.75
Average turn around time = 7.5*/