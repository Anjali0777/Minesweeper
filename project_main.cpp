// Project by Anjali Gupta and gurleen Kaur

#include "project.h"
#include <iostream>
#include <chrono> // For time measurements



int main() {
    const int board_size = 10;
    const int num_mines = 10;
    const int game_duration = 3000; // 30 seconds

    Board board(board_size, num_mines);
    board.initialize();
    board.update_adjacent_mines_count();

    int x, y;
    char action;
    bool game_over = false;
    std::chrono::time_point<std::chrono::system_clock> start, end; // Timer variables
    start = std::chrono::system_clock::now(); // Start the timer
    int remaining_seconds = game_duration;
    
    while (!game_over && remaining_seconds > 0)
    {
        system("cls");
        board.display();
        std::cout << "Time remaining: " << remaining_seconds << " seconds" << std::endl;
        std::cout << "Enter row and column (x y f/r) f for flagged,r for revealed (or -1 to quit): ";
        std::cin >> x;
        if (x == -1)
        {
            break;
        }
        std::cin >> y >> action;
        if (x < 0 || x >= board_size || y < 0 || y >= board_size)
        {
            std::cout << "Invalid input!" << std::endl;
            continue;
        }
        if (action == 'f' || action == 'F')
        {
            board.plant_flag(x, y);
        }
        else if (action == 'r' || action == 'R')
        {
            board.reveal_adjacent_cells(x, y);
        }
        else
        {
             // Only reveal adjacent cells if the player chose to reveal a cell
            if (board.is_game_over())
            {
                std::cout << "Congratulations!You won the game!" << std::endl;
                board.display(true);
                break;
            }
        }
        if (board.is_game_over())
        {
            std::cout << "Game over! You hit a mine!" << std::endl;
            board.display(true);
            break;
        }
    


        end = std::chrono::system_clock::now(); // Update the end time
        std::chrono::duration<double> elapsed_seconds = end - start;
        remaining_seconds = game_duration - (int)(elapsed_seconds.count());

        if (remaining_seconds <= 0) 
        {
            std::cout << "Time's up! Game over!" << std::endl;
            break;
        }

    }
    
    // Keep the console window open until user input
    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get();

    return 0;
}
