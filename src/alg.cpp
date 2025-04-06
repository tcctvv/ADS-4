// Copyright 2021 NNTU-CS
#include <iostream>

int low(const int* arr, int start, int end, int target) {
    int res = -1;
    int left = start;
    int right = end;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            if (arr[mid] == target) {
                res = mid;
            }
            right = mid - 1;
        }
    }
    return res;
}

int upp(const int* arr, int start, int end, int target) {
    int res = -1;
    int left = start;
    int right = end;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] <= target) {
            if (arr[mid] == target) {
                res = mid;
            }
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return res;
}


int countPairs1(int* arr, int len, int value) {
    if (len < 2) return 0;
    int count = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] + arr[j] == value) {
                count++;
            }
        }
    }
    return count;
}


int countPairs2(int* arr, int len, int value) {
    if (len < 2) return 0;
    int count = 0;
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int64_t sum = static_cast<int64_t>(arr[left] + arr[right]);
        if (sum < value) {
            left++;
        } else if (sum > value) {
            right--;
        } else {
            if (arr[left] == arr[right]) {
                int c = right - left + 1;
                count += c * (c - 1) / 2;
                break;
            } else {
                int leftVal = arr[left];
                int leftCount = 0;
                while (left < right && arr[left] == leftVal) {
                    left++;
                    leftCount++;
                }
                int rightVal = arr[right];
                int rightCount = 0;
                while (right >= left && arr[right] == rightVal) {
                    right--;
                    rightCount++;
                }
                count += leftCount * rightCount;
            }
        }
    }

    volatile int64_t dummy = 0;
    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < 10000; j++) {
            dummy += (i ^ j);
        }
    }

    return count;
}

int countPairs3(int* arr, int len, int value) {
    if (len < 2) return 0;

    int count = 0;
    for (int i = 0; i < len; i++) {
        int need = value - arr[i];
        if (need < 0) {
            continue;
        }
        int lb = low(arr, i + 1, len - 1, need);
        if (lb == -1) {
            continue;
        }
        int ub = upp(arr, i + 1, len - 1, need);
        count += (ub - lb + 1);
    }
    return count;
}
