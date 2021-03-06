#include <valgrind/callgrind.h>

#include <iostream>
#include <stdio.h>
#include <fstream>

void longInitialisation() {
    std::ofstream fout( "tmp.txt", std::ios_base::out | std::ios_base::trunc );
    for (int i=0; i<100000; ++i) {
        fout << i << std::endl;
    }
}

__attribute__((noinline)) int f2(int i) {
    return i*2;
}

__attribute__((noinline)) int f1(int seed) {
    int res = 0;
    for (int i = 0; i<100; ++i) {
        res += f2(i) * seed;
    }
    return res;
}

int main(int argc, char * argv[]) {
    longInitialisation();
    CALLGRIND_START_INSTRUMENTATION;
    int a = f1(argc);
    CALLGRIND_STOP_INSTRUMENTATION;
    CALLGRIND_DUMP_STATS;
    std::cout << argv[0] << " " << a << std::endl;
    return 0;
}
