#include <iostream>
#include <cstring>
#include <stdint.h>
#include "base_convert.h"

#define MAX_LEN 64

using namespace std;

int main()
{
    uint32_t num{};
    uint16_t base_num{};

    while(true) {
        cout << "Input the number for convert (exit = 0) : ";
        if(!getNum(num))    continue;
        else if(num == 0)   goto _end;
_base:  cout << "Input base for convert (2 <= base <= 62) : ";
        if(!getNum(base_num) || (base_num > 62 || base_num < 2))
            goto _base;
        convert(num, base_num);
        cout << endl;
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

template <typename T, typename U>
void convert(T &op, U &base) {
    constexpr static char base_table[62]
                        {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                        'U', 'V', 'W', 'X', 'Y', 'Z',
                        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                        'u', 'v', 'w', 'x', 'y', 'z'
                       };
    static char result[MAX_LEN];
    static char tmp[MAX_LEN];
    int i{}, len{};

    for(i = 0; op; i++) {
        tmp[i] = base_table[op%base];
        op /= base;
    }

    len = --i;

    do {
        result[len - i] = tmp[i];
    } while(i--);

    cout << "Result : " << result << endl;

    memset(result, '\0', static_cast<uint64_t>(len + 1) * sizeof(char));
}

