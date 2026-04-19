#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;


// class cell {
//     private:
//         int row;
//         int column;
//         int box_row;
//         int box_column;
//         vector<int> possible_values;
//         int number_of_possible_values;
//         int value;
//     public:
//         cell(int X, int Y, int BOX_X, int BOX_Y) : column(X), row(Y), box_column(BOX_X), box_row(BOX_Y) {
//             value = -1;
//             possible_values = get_new_numbers();
//             number_of_possible_values = get_new_numbers.size();
//         }
// } 

// gives vector of ordered numbers form 1 to 9
vector<int> get_new_numbers() {
    vector<int> v = {1,2,3,4,5,6,7,8,9};
    return v;
}


// returns 0 for 0, 1, 2 ; 3 for 3, 4, 5 etc (useful for box categorisation)
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

    return -1;
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

void display_numbers(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

bool check_col(int tab[9][9], int x, int y, int target) {
    for (int i = 0; i < 9; i++) {
        if (i == y) continue;
        if (tab[i][x] == target) return false;
    }
    return true;
}

bool check_cell(int tab[9][9], int x, int y, int target) {
    if (x > 8 or x < 0 or y > 8 or y < 0 or target > 9 or target < 1) return false;
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

// inserts random numbers 1 to 9 into given box (respects sudoku rules)
void insert_box(int tab[9][9], int x, int y) {
    vector<int> numbers = get_new_numbers();
    vector<int> current_numbers = get_new_numbers();

    int target_x = get_group(x);
    int target_y = get_group(y);
    unsigned int size = numbers.size();
    unsigned int new_number_index;
    

    for (int i = target_y; i < target_y + 3; i++) {
        for (int j = target_x; j < target_x + 3; j++) {
            do
            {
                new_number_index = rand() % size;
                current_numbers.erase(current_numbers.begin() + new_number_index);
                size--;
                cout << "HEJ! chce uzyc teraz " << numbers[new_number_index] << "a moj size to  " << size << "oraz dostepne numery to "; 
                display_numbers(current_numbers);
            } while (!check_cell(tab, j, i, current_numbers[new_number_index]));
            
            tab[i][j] = current_numbers[new_number_index];
            display_grid(tab);
            // numbers.erase(numbers.begin() + new_number_index);
            numbers.erase(remove(numbers.begin(), numbers.end(), current_numbers[new_number_index]), numbers.end());
            size = numbers.size();
            current_numbers = numbers;
        }
    }
}

// inserts random numbers from 1 to 9 into given box (doesn't expect sudoku rules / fully random) 
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

int main() {
    srand(time(0));
    insert_box_random(sudoku,0,0);
    insert_box_random(sudoku,3,3);
    insert_box_random(sudoku,7,7);
    insert_box(sudoku,3,7);
    display_grid(sudoku);
    return 0;
}