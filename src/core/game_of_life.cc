#include "core/game_of_life.h"
#include <ctime>

namespace cas {
    GameOfLife::GameOfLife(int num_cells_per_row, int num_rows_per_col, int starting_board_selection) :
            num_cells_per_row_(num_cells_per_row), num_rows_per_col_(num_rows_per_col),
            starting_board_selection_(starting_board_selection) {
        srand((unsigned) time(nullptr));
        SetBoard(starting_board_selection_);
    }

    GameOfLife::GameOfLife(vector<vector<Cell>> board) {
        prev_board_ = board;
        board_= board;
    }

    void GameOfLife::UpdateBoard() {
        //each cell's state changes or stays the same according to https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
        for (size_t y = 0; y < prev_board_.size(); ++y) {
            for (size_t x = 0; x < prev_board_[y].size(); ++x) {
                size_t num_live_neighbors = 0;
                //ignore edges
                if (!(x == 0 || y == 0 || x == prev_board_[y].size()-1 || y == prev_board_.size()-1)) {
                    if (prev_board_[y-1][x-1].state) num_live_neighbors++;
                    if (prev_board_[y-1][x].state) num_live_neighbors++;
                    if (prev_board_[y-1][x+1].state) num_live_neighbors++;
                    if (prev_board_[y][x-1].state) num_live_neighbors++;
                    if (prev_board_[y][x+1].state) num_live_neighbors++;
                    if (prev_board_[y+1][x-1].state) num_live_neighbors++;
                    if (prev_board_[y+1][x].state) num_live_neighbors++;
                    if (prev_board_[y+1][x+1].state) num_live_neighbors++;
                }
                /* - Any live cell with two or three live neighbours survives.
                   - Any dead cell with three live neighbours becomes a live cell.
                   - All other live cells die in the next generation. Similarly, all other dead cells stay dead. */
                if (board_[y][x].state && (num_live_neighbors == 2 || num_live_neighbors == 3)) {
                    board_[y][x].state = true;
                } else if (!board_[y][x].state && num_live_neighbors == 3) {
                    board_[y][x].state = true;
                } else {
                    board_[y][x].state = false;
                }
            }
        }
        prev_board_ = board_;
    }

    void GameOfLife::SetBoard(int starting_selection_) {
        board_.clear();
        prev_board_.clear();
        starting_board_selection_ = starting_selection_;
        //0 means default: square border
        if (starting_selection_ == 0) {
            for (int y = 0; y < num_rows_per_col_; ++y) {
                vector<Cell> cells;
                for (int x = 0; x < num_cells_per_row_; ++x) {
                    if (x >= (int) (.30f * num_cells_per_row_) && x <= (int) (.70f * num_cells_per_row_)
                        && (y >= (int) (.04f * num_rows_per_col_) && y <= (int) (.19f * num_rows_per_col_))) {
                        cells.emplace_back(Cell(false));
                    } else {
                        cells.emplace_back(Cell(true));
                    }
                }
                board_.push_back(cells);
                prev_board_.push_back(cells);
            }
        //1 means random: some alive, some dead    
        } else if (starting_selection_ == 1) {
            for (int y = 0; y < num_rows_per_col_; ++y) {
                vector<Cell> cells;
                for (int x = 0; x < num_cells_per_row_; ++x) {
                    int alive = rand() % 2;
                    alive == 1 ? cells.emplace_back(Cell(true)) : cells.emplace_back(Cell(false));
                }
                board_.push_back(cells);
                prev_board_.push_back(cells);
            }
        //else custom, so user will draw board (all start dead)    
        } else {
            for (int y = 0; y < num_rows_per_col_; ++y) {
                vector<Cell> cells;
                for (int x = 0; x < num_cells_per_row_; ++x) {
                    cells.emplace_back(Cell(false));
                }
                board_.push_back(cells);
                prev_board_.push_back(cells);
            }
        }
    }

    void GameOfLife::UpdateNumCellsPerRow(int num_cells_per_row) {
        //remove cells from each row of board
        if (num_cells_per_row < num_cells_per_row_) {
            size_t num_to_remove = num_cells_per_row_ - num_cells_per_row;
            for (size_t i = 0; i < board_.size(); ++i) {
                for (size_t j = 0; j < num_to_remove; ++j) {
                    board_[i].pop_back();
                    prev_board_[i].pop_back();
                }
            }
        //add cells to each row of board; randomly alive or dead
        } else {
            size_t num_to_add = num_cells_per_row - num_cells_per_row_;
            for (size_t i = 0; i < board_.size(); ++i) {
                for (size_t j = 0; j < num_to_add; ++j) {
                    int alive = rand() % 2;
                    if (alive == 1) {
                        board_[i].emplace_back(Cell(true));
                        prev_board_[i].emplace_back(Cell(true));
                    } else {
                        board_[i].emplace_back(Cell(false));
                        prev_board_[i].emplace_back(Cell(false));
                    }
                }
            }
        }
        num_cells_per_row_ = num_cells_per_row;
    }

    void GameOfLife::ReviveOrKillCells(const int row, const int col, const bool should_revive) {
        should_revive ? board_[row][col].state = true : board_[row][col].state = false;
        should_revive ? prev_board_[row][col].state = true : prev_board_[row][col].state = false;
    }

    const vector<vector<Cell>>& GameOfLife::GetBoard() { return board_; }
}