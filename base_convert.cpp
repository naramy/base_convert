#include <iostream>
#include <stdint.h>
#include "base_convert.h"

using namespace std;

template <typename T>
bool getNum(T &num);

int main()
{
    uint32_t num{};
    uint16_t base_num{};
    char result[MAX_LEN]{};

    while(true) {
        cout << "Input the number for convert (exit = 0) : ";
        if(!getNum(num))    continue;
        else if(num == 0)   goto _end;
_base:  cout << "Input base for convert (2 <= base <= 62) : ";
        if(!getNum(base_num) || (base_num > 62 || base_num < 2))
            goto _base;
        convert(num, base_num, result);

        cout << "Result : " << result << endl;
    }

_end:
    return 0;
}

template <typename T>
bool getNum(T &num) {
    cin >> num;

    if(cin.fail()) {
        cin.clear();
        cin.ignore(256, '\n');
        return false;
    }
    return true;
}

