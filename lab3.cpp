#include <iostream>
#include <cstdint>
using namespace std;

int main() {
    
    cout << "=== TASK 1: Computing a^12 + a^8 + a ===" << endl;
    uint32_t a;
    cout << "Enter positive integer a: ";
    cin >> a;

    uint64_t res1 = 0; // насколько я знаю лонг лонг модет меняться в зависимости от битности системы
    __asm {
        mov eax, a

        mov ecx, eax; считаем a в 12
        imul ecx, ecx; a ^ 2
        imul ecx, eax; a ^ 3
        imul ecx, ecx; a ^ 6
        imul ecx, ecx; a ^ 12
        mov ebx, ecx

        
        mov ecx, eax; ну тут тоже самое но для а в 8
        imul ecx, ecx; a ^ 2
        imul ecx, ecx; a ^ 4
        imul ecx, ecx; a ^ 8

        add ebx, ecx; a ^ 12 + a ^ 8
        add ebx, eax; +a

        
        mov dword ptr[res1], ebx
        mov dword ptr[res1 + 4], 0
    }
    cout << "Result: " << res1 << "\n\n";

   
    cout << "=== TASK 2: Finding solutions to 2x + 3y = 50 ===" << endl;

    const int MAX_SOLUTIONS = 51;  // логично что если числа положительные то ответов максимум 51 (спойлер - 8)
    int solutionsX[MAX_SOLUTIONS];
    int solutionsY[MAX_SOLUTIONS];
    int cnt = 0;
    int x;
    __asm {
        mov x, 1; x начинается с 1
        jmp start_loop





        loop_body :
       
        mov eax, 50; 50 которое ответ, а не 51 которое макс число решений
            
            
            
            mov ebx, x
            imul ebx, 2
            sub eax, ebx; eax = 50 - 2x

            ; Проверяем, что(50 - 2x) > 0 и делится на 3 без остатка

           
            cmp eax, 0
            jle not_valid

            mov ebx, 3
            cdq
            idiv ebx

            cmp edx, 0
            jne not_valid

            
            cmp eax, 0
            jle not_valid

            
            mov edi, cnt
            shl edi, 2
            mov ebx, x
            mov solutionsX[edi], ebx
            mov solutionsY[edi], eax

            
            inc cnt

            not_valid :
        inc x

            start_loop:
        cmp x, 51
            jle loop_body
    }

    
    if (cnt > 0) {
        cout << "Found solutions:" << endl;
        for (int i = 0; i < cnt; i++) {
            cout << "2*" << solutionsX[i] << " + 3*" << solutionsY[i] << " = 50" << endl;
        }
    }
    else {
        cout << "No solutions found.\n";
    }
    cout << "Total solutions found: " << cnt << '\n';

}
