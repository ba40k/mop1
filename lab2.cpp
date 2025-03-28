#include <iostream>
using namespace std;

int main() {
    double x;
    std::cout << "FIRST SUBTASK BEGIN\n";
    cout << "Enter x: ";
    cin >> x;


    double result;
    double three = 3.0;
    __asm {
        fld qword ptr[x]
        fadd st, st(0)
        fld1
        fsubp st(1), st

        fld qword ptr[x]
        fadd st, st(0)
        fld1
        faddp st(1), st

        fld qword ptr[x]
        fld qword ptr[three]
        faddp st(1), st

        fmulp st(2), st(0)
        fmulp st(1), st(0)

        fld qword ptr[x]
        fadd st, st(0)

        fdivp st(1), st(0)

        fstp qword ptr[result]
    }

    int intResult = static_cast<int>(result);
    long double res = (long double)(2 * x - 1) * (2 * x + 1) * (x + 3) / (2 * x);
    cout << "RES INT PART ASM: " << intResult <<" | C++: "<<(int)res<<endl;
    std::cout << "FIRST SUBTASK END\n";

    std::cout << "SECOND SUBTASK BEGIN\n";

    uint32_t number;
    std::cout << "Enter number: ";
    std::cin >> number;
    int count = 0;

    __asm {
        mov eax, number
        bsr ecx, eax
        jz zero_case
        inc ecx
        mov count, ecx
        jmp done
        zero_case :
        mov count, 1
            done :
    }
    std::cout<<count;
    return 0;
}
