#include "project.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


Board::Board(int size, int mines) 
{
    board_size = size;
    num_mines = mines;
    board = std::vector<std::vector<Cell>>(board_size, std::vector<Cell>(board_size, { false, 0, cell_state::HIDDEN }));
}

void Board::initialize() 
{
    srand(time(NULL));
    int minesPlaced = 0;
    while (minesPlaced < num_mines) 
    {
        int x = rand() % board_size;
        int y = rand() % board_size;
        if (!board[x][y].is_mine) 
        {
            board[x][y].is_mine = true;
            minesPlaced++;
        }
    }
}

int Board::count_adjacent_mines(int x, int y) 
{
    int count = 0;
    for (int i = std::max(0, x - 1); i <= std::min(board_size - 1, x + 1); i++) 
    {
        for (int j = std::max(0, y - 1); j <= std::min(board_size - 1, y + 1); j++) 
        {
            if (board[i][j].is_mine) 
            {
                count++;
            }
        }
    }
    return count;
}

void Board::update_adjacent_mines_count() 
{
    for (int i = 0; i < board_size; i++) 
    {
        for (int j = 0; j < board_size; j++) 
        {
            if (!board[i][j].is_mine) 
            {
                board[i][j].num_adjacent_mines = count_adjacent_mines(i, j);
            }
        }
    }
}

void Board::reveal_adjacent_cells(int x, int y) 
{
    if (x < 0 || x >= board_size || y < 0 || y >= board_size || board[x][y].state != cell_state::HIDDEN) 
    {
        return;
    }
    board[x][y].state = cell_state::REVEALED;
    if (board[x][y].num_adjacent_mines == 0) 
    {
        for (int i = std::max(0, x - 1); i <= std::min(board_size - 1, x + 1); i++) 
        {
            for (int j = std::max(0, y - 1); j <= std::min(board_size - 1, y + 1); j++) 
            {
                if (i != x || j != y) 
                {
                    reveal_adjacent_cells(i, j);
                }
            }
        }
    }
}

void Board::display(bool show_mines) const 
{
    std::cout << "   ";
    for (int i = 0; i < board_size; i++) 
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "  ";
    for (int i = 0; i < board_size * 2 - 1; i++) 
    {
        std::cout << "-";
    }
    std::cout << std::endl;
    for (int i = 0; i < board_size; i++) 
    {
        std::cout << i << "| ";
        for (int j = 0; j < board_size; j++) 
        {
            if (board[i][j].state == cell_state::REVEALED)
            {
                if (board[i][j].is_mine && show_mines) 
                {
                    std::cout << "\033[1;31m*\033[0m "; // Display mines in red using ANSI escape codes
                }
                else {
                    std::cout << board[i][j].num_adjacent_mines << " ";
                }
            }
            else if (board[i][j].state == cell_state::FLAGGED)
            {
                std::cout << "! "; // Display flagged cells as !
            }
            else if (board[i][j].is_mine && show_mines) 
            {
                std::cout << "\033[1;31m*\033[0m "; // Display unrevealed mines at the end of the game
            }
            else 
            {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

void Board::plant_flag(int x, int y)
{
    if (x < 0 || x >= board_size || y < 0 || y >= board_size)
    {
        return;
    }
    if (board[x][y].state == cell_state::HIDDEN)
    {
        board[x][y].state = cell_state::FLAGGED;
        
    }
    else if (board[x][y].state == cell_state::FLAGGED)
    {
        board[x][y].state = cell_state::HIDDEN;
    }
}

bool Board::is_game_over() 
{
    for (int i = 0; i < board_size; i++) 
    {
        for (int j = 0; j < board_size; j++) 
        {
            if (board[i][j].state == cell_state::REVEALED && board[i][j].is_mine) 
            {

                return true;
            }
        }
    }
    int revealedCount = 0;
    for (int i = 0; i < board_size; i++) 
    {
        for (int j = 0; j < board_size; j++) 
        {
            if (board[i][j].state == cell_state::REVEALED) 
            {
                revealedCount++;
            }
        }
    }
    return revealedCount == board_size * board_size - num_mines;
}
