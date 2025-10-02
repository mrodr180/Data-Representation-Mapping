#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sub_convert(uint32_t n, int base, char *out) { //took it from assignment 1
    int temp[64]; //temp buffer
    int arrayIndex = 0;

    //finding the biggest power
    uint64_t value = 1; //would overflow when assigned as int
    while (value <= n) {
        temp[arrayIndex ++] = value; //stores value in a numbered "slot" within the array
        value *= base;
    }

    int outLength = 0;
    for (int i = arrayIndex - 1; i >= 0; i-- ) {
        int arrayMove = 0;
        while (n >= temp[i]) { //goes thru arraylist
            n -= temp[i]; // subtract from n
            arrayMove++; //moves down the arraylist
        }

        if (arrayMove < 10)   // out[] is what gets spat out from the function
            out[outLength++] = '0' + arrayMove; // from numbers 0-9
        else
            out[outLength++] = 'A' + (arrayMove - 10); //from numbers a - f

    }
    out[outLength] = '\0'; //ends
}

void oct_to_bin(const char* oct, char* out) {
    const char *octTable[] = {  //this table will assign a binary value for every num
        "000", "001", "010", "011", "100", "101", "110", "111"
    };

    int outLength = 0;
    for (int i = 0; oct[i] != '\0'; i++) { //as long as oct[] != '0\' it keeps moving
        int num = oct[i] - '0'; //convert into a int
        const char *binNum = octTable[num]; //looks up in table

        for (int j = 0; j < 3; j++) {
            out[outLength++] = binNum[j]; // stores
        }
    }
    out[outLength] = '\0'; //ends
}

void hex_to_bin(const char* hex, char* out) {
    const char *hexTable[] = {
        "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
    };

    int outLength = 0;
    for (int i = 0; hex[i] != '\0'; ++i) {
        int num;
        char hexNum = hex[i];

        if (hexNum >= '0' && hexNum <= '9') {
            num = hexNum - '0';
        }else if (hexNum >= 'a' && hexNum <= 'f') {
            num = hexNum - 'a' + 10;
        }else if (hexNum >= 'A' && hexNum <= 'F') {
            num = hexNum - 'A' + 10;
        }else {
            continue;
        }

        const char *binNum = hexTable[num]; //looks up in table
        for (int j = 0; j < 4; j++) {
            out[outLength++] = binNum[j]; // stores
        }
    }
    out[outLength] = '\0';
}

void oct_to_hex(const char* oct, char* hex) {
    uint32_t n = 0;

    while (*oct) {
        n = n * 8 + (*oct - '0');
        oct++;
    }
    sub_convert(n, 16, hex);
}

void to_sign_magnitude(int n, char *out) {
    uint32_t num;

    if (n >= 0) { //positive case
        num = (uint32_t)n;
    }else {
        num = (uint32_t)-n;
        num |= 0x80000000;
    }
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (num & (1u << i)) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_ones_complement(int n, char *out) {
    uint32_t num;

    if (n >= 0) { //positive case
        num = (uint32_t)n;
    }else {
        num = (uint32_t)(-n);
        num = ~num;
    }
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (num & (1u << i)) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_twos_compliment(int n, char *out) {
    uint32_t num;

    if (n >= 0) { //positive case
        num = (uint32_t)n;
    }else {
        num = (uint32_t)(-n);
        num = ~num;
        num = num + 1;
    }
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = (num & (1u << i)) ? '1' : '0';
    }
    out[32] = '\0';
}
//this stumped me or a while then i reread that i just needed to add +one ;(