#pragma once
#include <vector>


enum class cell_state { HIDDEN, REVEALED,FLAGGED};

struct Cell {
    bool is_mine;
    int num_adjacent_mines;
    cell_state state;
};


class Board {
    int size;
    int mines;
public:
    Board(int size, int mines);
    void initialize();
    int count_adjacent_mines(int x, int y);
    void update_adjacent_mines_count();
    void reveal_adjacent_cells(int x, int y);
    void display(bool show_mines= false) const;
    void plant_flag(int x, int y);
    bool is_game_over();
    
private:
    int board_size;
    int num_mines;
    std::vector<std::vector<Cell>> board;
};


