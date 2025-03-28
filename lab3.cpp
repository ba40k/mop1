#include <iostream>
using namespace std;

int main() {
    // Task 1: Compute a^12 + a^8 + a
    cout << "=== TASK 1: Computing a^12 + a^8 + a ===" << endl;
    unsigned int a;
    cout << "Enter positive integer a: ";
    cin >> a;

    unsigned long long res1 = 0;
    __asm {
        mov eax, a

        ; Compute a ^ 12
        mov ecx, eax; a
        imul ecx, ecx; a ^ 2
        imul ecx, eax; a ^ 3
        imul ecx, ecx; a ^ 6
        imul ecx, ecx; a ^ 12
        mov ebx, ecx; store a ^ 12

        ; Compute a ^ 8
        mov ecx, eax; a
        imul ecx, ecx; a ^ 2
        imul ecx, ecx; a ^ 4
        imul ecx, ecx; a ^ 8

        ; Sum all parts
        add ebx, ecx; a ^ 12 + a ^ 8
        add ebx, eax; +a

        ; Store 64 - bit result
        mov dword ptr[res1], ebx
        mov dword ptr[res1 + 4], 0
    }
    cout << "Result: " << res1 << endl << endl;

    // Task 2: Find integer solutions to 2x + 3y = 50
    cout << "=== TASK 2: Finding solutions to 2x + 3y = 50 ===" << endl;
    int cnt = 0;

    for (int x = 1; x <= 50; x++) {
        int y = 0;
        int valid = 0;

        __asm {
            mov eax, 50
            mov ebx, x
            imul ebx, 2
            sub eax, ebx

            cmp eax, 0
            jle not_valid

            mov ebx, 3
            cdq
            idiv ebx

            cmp edx, 0
            jne not_valid

            mov y, eax
            mov valid, 1

            not_valid :
        }
        if (y <= 0 || x <= 0) {
            valid = 0;
        }
        if (valid ) {
            cnt++;
            cout << "Solution found: 2*" << x << " + 3*" << y << " = 50" << endl;
        }
    }

    cout << "Total solutions found: " << cnt << endl;

    return 0;
}
