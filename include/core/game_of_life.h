#pragma once

#include "core/cell.h"
#include <vector>

using std::vector;

namespace cas {
    class GameOfLife {
        public:
            /* Default Constructor */
            GameOfLife() {};
    
            /* Parameterized Constructor: initializes member variables */
            GameOfLife(int num_cells_per_row, int num_rows_per_col, int starting_board_selection);
    
            /* Parameterized Constructor: takes in a pre-constructed board; used for testing */
            GameOfLife(vector<vector<Cell>> board);
    
            /* Updates boards of cells based on Game of Life rules */
            void UpdateBoard();
    
            /* Sets the initial board */
            void SetBoard(int starting_board_selection_);
    
            /* Updates the number of cells on the board */
            void UpdateNumCellsPerRow(int num_cells_per_row);
    
            /* Called every time board is clicked. row, col is index of cell in board_ to revive or kill */
            void ReviveOrKillCells(int row, int col, bool should_revive);
    
            /* Getter */
            const vector<vector<Cell>>& GetBoard();
    
        private:
            /* 2D board of cells, changes each frame/generation */
            vector<vector<Cell>> board_;
    
            /* Stores the previous board; used for updating board_ */
            vector<vector<Cell>> prev_board_;
    
            /* Dimensions of board */
            int num_cells_per_row_;
            int num_rows_per_col_;
    
            /* How the generation of cells starts */
            int starting_board_selection_;
    };
}