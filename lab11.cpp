#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function under test (contains the original fault: starting at i = 1 instead of i = 0)
bool fail_lecture(const vector<int>& attendance_records) {
    int absent_count = 0;
    for (int i = 1; i < attendance_records.size(); ++i) {
        absent_count += (attendance_records[i] == 0);
    }
    return absent_count >= 3;
}

// Helper function to print the attendance vector
void print_record(const vector<int>& record) {
    cout << "{ ";
    for (size_t i = 0; i < record.size(); ++i) {
        cout << record[i] << (i + 1 < record.size() ? ", " : " ");
    }
    cout << "}";
}

// Helper function to run and verify a test case
void run_test(int test_num, const vector<int>& record, int expected_absences, bool expected_fail) {
    // Calculate actual absences using the buggy function's logic
    int actual_absences = 0;
    for (size_t i = 1; i < record.size(); ++i) {
        if (record[i] == 0) actual_absences++;
    }
    bool actual_fail = fail_lecture(record);

    cout << "--- Test Case " << test_num << " ---\n";
    cout << "Attendance Record:     ";
    print_record(record);
    cout << "\nExpected Absence Count: " << expected_absences;
    cout << "\nActual Absence Count:   " << actual_absences;
    cout << "\nExpected Output (Fail): " << (expected_fail ? "true" : "false");
    cout << "\nActual Output (Fail):   " << (actual_fail ? "true" : "false");
    cout << "\n----------------------------------------\n\n";
}

int main() {
    cout << "=== EECS 348 Lab 11: Debugging and Testing ===\n\n";

    // Q3 Test Case: Executes the fault, but does not result in an error state
    // Explanation: All the  lectures attended (0 absences), so skipping index 0 does not alter the absence count.
    vector<int> tc3 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    run_test(3, tc3, 0, false);

    // Q4 Test Case: Results in an error state, but not a failure
    // Expanation: 1 absence at index 0. The fault skips it, resulting in an actual count of 0 instead of 1.
    // However, since 0 and 1 are both below the failure threshold of 3, the final output remains false (no failure).
    vector<int> tc4 = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    run_test(4, tc4, 1, false);

    // Q5 Test Case: Results in a failure
    // Explanation: 3 absencs total (indices 0, 1, and 2). The fault skips index 0, yielding an actual count of 2 insead of 3.
    // Expected output is true (fails), but actual output evaluates to false (passes), causing an observable failure.
    vector<int> tc5 = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1};
    run_test(5, tc5, 3, true);

    return 0;
}
