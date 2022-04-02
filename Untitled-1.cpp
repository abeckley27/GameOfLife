#include <iostream>
#include "world.h"

using namespace std;

int run_simulation(world& w, int genlimit = 1000) {

    int generation = 0;
    int output = 0;

    while (generation < genlimit) {
        w.update();
        w.print();
        cout << "---------------\n";
        generation++;
    }

    return generation;
}

int main(int argc, char* argv[]) {

    const int N = 100;
    int i, j;

    world b(N);
    b.set(10, 10, true);
    b.set(10, 11, true);
    b.set(11, 11, true);
/*
    world cpy = b;
    cout << b.get(10, 10) << endl;
    cout << cpy.get(10, 10) << endl;
    cout << b.neighboring_cells(10, 10) << endl;
    cout << cpy.neighboring_cells(10, 10) << endl;
    cout << "---------------\n";

    int test = 3;
    int generation = 0;
    while (generation < test) {
        b.update();
        cout << b.get(10, 10) << endl;
        cout << cpy.get(10, 10) << endl;
        cout << b.neighboring_cells(10, 10) << endl;
        cout << cpy.neighboring_cells(10, 10) << endl;
        cout << "---------------\n";
        generation++;
    }
*/

    const int printsizeN = 10;
    const int seedlength = 10;
    int seed[seedlength] = {5, 7, 8, 6, 6, 7, 7, 7, 7, 8};
    world test(printsizeN, seedlength, seed);
    run_simulation(test, 10);


    return 0;
}