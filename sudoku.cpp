#include <iostream>
using namespace std;

int sudoku[9][9] = {0};

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
    wyswietl(sudoku);
    return 0;
}