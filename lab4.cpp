#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    const int n = 3844221 + 5;
    long double* arr = new long double[n];

 
    arr[0] = 1.0;


    __asm {
        finit 
        mov ebx, arr       // Указатель на начало массива
        mov ecx, 1         // Текущий индекс (начинаем с 1)

        loop_start:
        cmp ecx, n         // Проверяем, достигли ли конца массива
            jge loop_end

            // Определение знака (-1)^ecx
            mov eax, ecx
            and eax, 1
            jnz odd

            // Четный индекс: знак 1.0
            fld1
            jmp sign_done

            odd :
        // Нечетный индекс: знак -1.0
        fld1
            fchs              // Меняем знак на -1.0

            sign_done :
        // Вычисление (ecx + 1)^2
        mov eax, ecx
            inc eax           // eax = ecx + 1
           // imul eax, eax     // eax = (ecx + 1)^2

            
            push eax
            fild dword ptr[esp]
            add esp, 4        // Очистка стека

           
            fdivp st(1), st(0)
                                // ОЧЕНЬ ВАЖНО! ДЕЛИМ ДВА РАЗА А НЕ ДЕЛИМ НА КВАДРАТ
            push eax
            fild dword ptr[esp]
            add esp, 4        // Очистка стека


            fdivp st(1), st(0)

           
            mov edx, ecx
            dec edx
            fld qword ptr[ebx + edx * 8]

            
            faddp st(1), st(0)
            fstp qword ptr[ebx + ecx * 8]

           
            inc ecx
            jmp loop_start

            loop_end :
    }

   
    long double target = 0.8224670334241132; 
    int cur = 1;
   
    for (int i = 0; i < n; ++i) {
        if (cur > 16) {
            break;
       }
        if (fabs(target - arr[i]) <= pow(10.0, -cur - 1) ){
            std::cout << "precision is " << cur << '\n';
            std::cout<< "target is :" <<std::fixed<<std::setprecision(15)<< target << '\n';
            std::cout<< "iterations is: " << i + 1 << '\n';
            std::cout << "current is " << std::fixed << std::setprecision(15)<< arr[i] << '\n';
            std::cout << "=========\n";
            cur++;
        }
    }

    delete[] arr;
    return 0;
}
