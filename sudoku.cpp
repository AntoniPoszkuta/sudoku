#include <iostream>
using namespace std;

int get_group(int i) {
    
    if (i == 0 or i == 1 or i == 2) {
        return 0;
    }

    if (i == 3 or i == 4 or i == 5) {
        return 3;
    }

    if (i == 6 or i == 7 or i == 8) {
        return 5;
    }

}

int sudoku[9][9] = {0};

bool check_box(int tab[9][9], int x, int y, int target) {
    int target_x = get_group(x);
    int target_y = get_group(y);
    
    for (int i = target_y; i < target_y + 3; i++) {
        for (int j = target_x; j < target_x + 3; j++) {
            if (j == x and i == y) continue;
            if (tab[y][x] == target) return false;  
        }
    }
    
    return true;
}   

bool check_row(int tab[9][9], int x, int y, int target) {
    for (int i = 0; i < 9; i++) {
        if (i == x) continue;
        if (tab[y][i] == target) return false;
    }
    return true;
}

bool check_col(int tab[9][9], int x, int y, int target) {
    for (int i = 0; i < 9; i++) {
        if (i == y) continue;
        if (tab[i][x] == target) return false;
    }
    return true;
}

bool check_box(int tab[9][9], int x, int y, int target)

int sudoku[9][9] = {0};

void display_grid(int tab[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 and j!= 0) {
                cout << "| ";
            }
            cout << tab[i][j] << " ";
        }
        cout << endl;
        if ((i+1) % 3 == 0 and i != 8) {
                cout << "------+-------+------";
                cout << endl;
            }
    }
}

int main() {
    display_grid(sudoku);
    return 0;
}