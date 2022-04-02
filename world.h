#ifndef world_h
#define world_h

#include <iostream>

class world {
    public:

    //constructors & destructor
    world() { create(); }
    world(int N_) { create(N_); }
    world(int N_, int length, int* a) { create(N_, length, a); }
    world(const world& b) { copy(b); }
    ~world() { destroy(); }
    

    //other public methods
    void print();
    void update();
    int sum();
    int neighboring_cells(int x, int y);
    bool cell_lives(int x, int y);
    bool get(int x, int y);
    bool set(int i, int j, int value);


    //variables
    int n;


    private:

    // class management stuff
    void create();
    void create(int);
    void create(int, int, int*);
    void copy(const world& b);
    world& operator=(const world& b);
    void destroy();

    bool** data;
};

void world::create() {
    n = 0;
    data = NULL;
}

// read after read is better than read after write, right?
// I actually dont't know
void world::create(int N_) {
    
    data = new bool*[N_];
    for (int i = 0; i < N_; i++) {
        data[i] = new bool[N_];
        for (int j = 0; j < N_; j++) data[i][j] = 0;
    }
    n = N_;
}

//length should be even
//an odd length will probably cause a segfault
void world::create(int N_, int length, int* a) {
    data = new bool*[N_];
    for (int i = 0; i < N_; i++) {
        data[i] = new bool[N_];
        for (int j = 0; j < N_; j++) data[i][j] = 0;
    }
    n = N_;
    for (int i = 0; i < length; i += 2) {
        data[a[i]][a[i+1]] = true;
    }
}

void world::copy(const world& b) {
    
    data = new bool*[b.n];
    for (int i = 0; i < b.n; i++) {
        this->data[i] = new bool[b.n];
        for (int j = 0; j < b.n; j++) this->data[i][j] = b.data[i][j];
    }
    n = b.n;
}

world& world::operator=(const world& b) {
    if (data != NULL) {
        for (int i = 0; i < n; i++) {
            delete[] data[i];
        }
    }
    this->copy(b);
    return *this;
}

void world::destroy() {

    if (data != NULL) {
        for (int i = 0; i < n; i++) {
            delete[] data[i];
        }
    }

}

bool world::set(int x, int y, int value) {
    bool output = false;
    if ( (x < n) && (y < n) ) {
        data[x][y] = value;
    }
    else {
        // return true if index out of bounds
        output = true;
    }
    return output;
}

bool world::get(int x, int y) {
    return data[x][y];
}

// x and y should be unsigned
int world::neighboring_cells(int x, int y) {
    int output = 0;
    int x_lower_bound = x - 1 + (x == 0);
    int y_lower_bound = y - 1 + (y == 0);
    int x_upper_bound = x + 1 - (x >= n-1);
    int y_upper_bound = y + 1 - (y >= n-1);

    for (int i = x_lower_bound; i <= x_upper_bound; i++) {
        for (int j = y_lower_bound; j <= y_upper_bound; j++) {
            output = output + int(data[i][j]);
        }
    }
    //don't count yourcellf
    return output - data[x][y];
}

bool world::cell_lives(int x, int y) {
    bool output;
    if (data[x][y]) {
        int nc = neighboring_cells(x,y);
        output = (nc == 2) || (nc == 3);
    }
    else {
        output = (neighboring_cells(x,y) == 3);
    }

    return output;
}

inline void world::print()
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (data[i][j]) { std::cout << "X \t"; }
            else { std::cout << "0 \t"; }
        }
        std::cout << std::endl;
    }
}

void world::update() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] = this->cell_lives(i, j);
        }
    }
}

inline int world::sum()
{
    int output = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            output += int(data[i][j]);
        }
    }
    return output;
}



#endif