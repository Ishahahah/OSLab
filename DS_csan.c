#include <stdio.h>

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;
    int ptr;
    int dir;
    printf("Enter the total requests: ");
    scanf("%d", &n);
    printf("Enter the header pointer: ");
    scanf("%d", &ptr);
    printf("Enter the direction (1 for clockwise, 0 for anticlockwise): ");
    scanf("%d", &dir);
    int arr[100];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    sort(arr, n);
    printf("\n");
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= ptr) {
            j = (dir == 1) ? i : i - 1;
            break;
        }
    }
    printf("The value of j: %d %d\n", j, arr[j]);
    int res[100];
    int temp = 0;
    if (dir) {
        while (j < n) {
            res[temp] = arr[j];
            j++;
            temp++;
        }
        j = 0;
        while (arr[j] < ptr) {
            res[temp] = arr[j];
            j++;
            temp++;
        }
        printf("The seek sequence is: ");
        for (int i = 0; i < temp; i++) {
            printf("%d ", res[i]);
        }
        printf("\n");
        int avg = abs(ptr - res[0]);
        printf("%d ", avg);
        for (int i = 0; i < (temp - 1); i++) {
            printf("%d ", abs(res[i] - res[i + 1]));
            avg += abs(res[i] - res[i + 1]);
        }
        printf("\n");
        printf("Seek track: %d\n", avg);
    } else {
        while (j >= 0) {
            res[temp] = arr[j];
            j--;
            temp++;
        }
        j = n - 1;
        while (arr[j] > ptr) {
            res[temp] = arr[j];
            j--;
            temp++;
        }
        printf("The seek sequence is: ");
        for (int i = 0; i < temp; i++) {
            printf("%d ", res[i]);
        }
        printf("\n");
        int avg = abs(ptr - res[0]);
        printf("%d ", avg);
        for (int i = 0; i < (temp - 1); i++) {
            printf("%d ", abs(res[i] - res[i + 1]));
            avg += abs(res[i] - res[i + 1]);
        }
        printf("\n");
        printf("Seek track: %d\n", avg);
    }
  return 0;
}