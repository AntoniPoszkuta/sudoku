#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;



vector<int> get_new_numbers() {
    vector<int> v = {1,2,3,4,5,6,7,8,9};
    return v;
}

int get_group(int i) {
    
    if (i == 0 or i == 1 or i == 2) {
        return 0;
    }

    if (i == 3 or i == 4 or i == 5) {
        return 3;
    }

    if (i == 6 or i == 7 or i == 8) {
        return 6;
    }

}

void insert_box_random(int tab[9][9], int x, int y) {
    vector<int> numbers = get_new_numbers();

    int target_x = get_group(x);
    int target_y = get_group(y);
    int size = numbers.size();
    int new_number_index;
    

    for (int i = target_y; i < target_y + 3; i++) {
        for (int j = target_x; j < target_x + 3; j++) {
            new_number_index = rand() % size;
            
            tab[i][j] = numbers[new_number_index];
            numbers.erase(numbers.begin() + new_number_index);
            size--;
        }
    }
}

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

bool check_cell(int tab[9][9], int x, int y, int target) {
    return (check_col(tab,x,y,target) and check_row(tab,x,y,target) and check_box(tab,x,y,target));
}

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
    srand(time(0));
    insert_box_random(sudoku,0,0);
    insert_box_random(sudoku,3,3);
    insert_box_random(sudoku,7,7);
    display_grid(sudoku);
    return 0;
}