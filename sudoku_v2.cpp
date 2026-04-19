#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Cell {
    private:
        int code;
        int x;
        int y;
        int value;
        int box;
        vector<int> possible_values;

    public:
        Cell(int Code) {
            code = Code;
            possible_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            value = 0;
            x = code % 10;
            y = code / 10;
            if (y < 3) {
                if (x < 3) {
                    box = 1;
                }
                else if (x < 6) {
                    box = 2;
                }
                else if (x < 9) {
                    box = 3;
                }
            }
            else if (y < 6) {
                if (x < 3) {
                    box = 4;
                }
                else if (x < 6) {
                    box = 5;
                }
                else if (x < 9) {
                    box = 6;
                }
            }
            else {
                if (x < 3) {
                    box = 7;
                }
                else if (x < 6) {
                    box = 8;
                }
                else if (x < 9) {
                    box = 9;
                }
            }
            code = box*100 + code;
        }

        Cell() : Cell(0) {}

        friend ostream& operator<<(ostream& os, const Cell& c);

        void update_possibles(vector<int> pos) {
            possible_values = pos;
        } 

        vector<int> get_possibles() {
            return possible_values;
        }

        void update_value(int val) {
            if (val != 0 and value == 0) {
                possible_values = {};
            }
            value = val;
        }

        // removes possible value if this value exist in possible_value table. 
        void remove_if_exists(int val) {
            if (find(possible_values.begin(), possible_values.end(), val) != possible_values.end()) {
                possible_values.erase(find(possible_values.begin(), possible_values.end(), val));
            }
        }

        int get_value() {
            return value;
        }

        int get_box() {
            return box;
        }

        int get_x() {
            return x;
        }
        
        int get_y() {
            return y;
        }

};

class Grid {
    private:
        vector<int> empty_codes = {};
         Cell grid[9][9];
    public:
        Grid() {
            for (int i = 0; i < 89; i++) {
                if (i % 10 == 9) continue;
                empty_codes.push_back(i);
                grid[i / 10][i % 10] = Cell(i);
            }
        }

        void display(int option) {
            switch (option) {
            case 1:
                for (unsigned int i = 0; i < empty_codes.size(); i++) {
                    cout << empty_codes[i] << " ";
                }
                break;
            case 2:
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        cout << grid[i][j] << " ";
                    }
                    cout << endl;
                }
                
            }
        }

        // returns true if a value can be placed on a specified cell, false otherwise
        bool is_possible(int code, int value) {
            vector<int> vec = grid[(code / 10) % 10][code % 10].get_possibles();
            return (find(vec.begin(), vec.end(), value) != vec.end());
        }

        /*
            tries to update a specified cell with a certain value
            to tell if a value is possible to update it checks if this value isn't in "possible_values" table
            if this cell cannot be updated with this value it returns true
            if it can, it updates it and changes every cell possible values 
            (f. e. if you put 1 in a row, every cell in this row is getting 1 erased from theirs possible_values table)
        */
        bool try_to_update(int code, int value) {
            if (!is_possible(code, value)) return false;
            
            cout << "broski?" << endl;
            int x = code % 10;
            int y = (code / 10) % 10;
            int box = code % 100;
            grid[(code / 10) % 10][code % 10].update_value(value);

            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (grid[i][j].get_x() == x or grid[i][j].get_y() == y or grid[i][j].get_box() == box) {
                        grid[i][j].remove_if_exists(value);
                    }
                }
            }
            return true;
        }
        
};

ostream& operator<<(ostream& os, const Cell& c) {
        os << c.code << "(" << c.value << ")";
        return os;
}

int main() {
    Grid sudoku;
    sudoku.display(2);
    sudoku.try_to_update(100,9);
    sudoku.try_to_update(781,9);
    cout << endl;
    sudoku.display(2);
}