#include <iostream>
#include <cstdint>
#include <map>
#include<algorithm>
#include<bitset>
std::map<int, char> mp;
std::string toHex(uint16_t x) { // принимаем беззнаковое, чтобы нормально брать остатки от деления
	std::string res;
	while (x > 0) {
		res.push_back(mp[x%16]);
		x /= 16;
	}
	while (res.size() < 4) {
		res.push_back('0');
	}
	std::reverse(res.begin(), res.end());
	return res;

}
int64_t toDec(int16_t x, uint16_t y, uint16_t z) {
	return 0;
}
int main() {
	for (int i = 0; i < 10; i++) {
		mp[i] = (char)(i + '0');
	}

	for (int i = 0;i<=5; i++) {
		mp[10+i] = 'A' + i;
	}
	uint16_t a1, a2;
	uint16_t b1, b2;
	uint16_t c1, c2;
	int16_t c3, a3, b3;
	//Если три эти числа, это три части 48 битного чисоа, то  a1,b1,a2,b2 - беззнаковые, а знак хранится только в старшей части - третьей
	
	c1 = c2 = c3 = 0;

	a1 = a2 = a3 = 0;

	b2 = b3 = 0;

	a1 = 1<<15;
	b1 = 1<<15;

	a2 = 1 << 15;
	b2 = 1 << 15;

	a3 = 1 <<14 ;
	b3 = 1 << 14;

	__asm {
		mov ax, a1
		add ax, b1
		mov c1, ax
		mov ax, 1
		mov c2, 1
		jo was_overflow_1
		sub c2, 1
		was_overflow_1:

		mov ax, a2
		add ax, c2 ; единичка переполнения
	    mov c3,1
		jo was_overflow_2_0
		sub c3,1
		was_overflow_2_0:


		add ax, b2
		mov c2, ax
		mov ax, 1
		mov c3, 1
		jo was_overflow_2_1
		sub c3, 1
		was_overflow_2_1:
		
		
		mov ax, c3
		add ax, a3
		add ax, b3

		mov c3, ax

		


	}
	
	std::cout  << toHex(c3) << ' ' << toHex(c2) << ' ' << toHex(c1) << '\n';
	uint64_t res = c1<<16;
	res += ((uint64_t)c2 << 32);
	res += ((uint64_t)c3 << 48);
	/*std::bitset<64> ress(res);
	ress = ~ress;
	for (int i = 16; i < 64; i++) {
		if (ress[i] == 1) {
			ress[i] = 0;
		}
		else {
			ress[i] = 1;
			break;
		}
	}
	for (int64_t i = 16; i < 64; i++) {
		std::cout << ress[i] << ' ';
	}
	std::cout << '\n';
	int64_t check = 0;
	for (int64_t i = 16; i < 64; i++) {
		check += (int64_t)((int64_t)1 << (i - (int64_t)16)) * ress[i];
	}
	std::cout << '\n';*/
	std::cout <<((int64_t)res >> 16 ) << '\n';
	return 0;
}
