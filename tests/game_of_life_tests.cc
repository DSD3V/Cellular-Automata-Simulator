#include "core/game_of_life.h"
#include <catch2/catch.hpp>

namespace cas {
    TEST_CASE("Game Of Life Updates Generations Correctly") {
        /* Each call to UpdateBoard represents one frame, or generation change 
           Each generation is a 5x5 grid of cells, edge cells are ignored */
        
        SECTION("Starting with all dead cells") {
            //Initialize board
            vector<vector<Cell>> board;
            for (size_t row = 0; row < 5; ++row) {
                vector<Cell> cells;
                for (size_t col = 0; col < 5; ++col) {
                    cells.emplace_back(Cell(false));
                }
                board.push_back(cells);
            }
            
            GameOfLife game_of_life(board);
    
            //Check if initialized correctly
            for (auto& row : game_of_life.GetBoard()) {
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == false);
                }
            }
    
            game_of_life.UpdateBoard();
    
            //All cells should still be dead
            for (auto& row : game_of_life.GetBoard()) {
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == false);
                }
            }
        }
    
        SECTION("Starting with all live cells") {
            //Initialize board
            vector<vector<Cell>> board;
            for (size_t row = 0; row < 5; ++row) {
                vector<Cell> cells;
                    for (size_t col = 0; col < 5; ++col) {
                        cells.emplace_back(Cell(true));
                    }
                board.push_back(cells);
            }
            
            GameOfLife game_of_life(board);
            
            //Check if initialized correctly
            for (auto& row : game_of_life.GetBoard()) {
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == true);
                }
            }
            
            game_of_life.UpdateBoard();
            
            //All cells should now be dead
            for (auto& row : game_of_life.GetBoard()) {
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == false);
                }
            }
        }
    
        SECTION("Starting with column of live cells in the middle") {
            //Initialize board
            vector<vector<Cell>> board;
            for (size_t row = 0; row < 5; ++row) {
                vector<Cell> cells;
                for (size_t col = 0; col < 5; ++col) {
                    if ((row == 1 && col == 2) ||
                        (row == 2 && col == 2) ||
                        (row == 3 && col == 2)) {
                            cells.emplace_back(Cell(true));
                        } else {
                            cells.emplace_back(Cell(false));
                        }
                }
                board.push_back(cells);
            }
            
            GameOfLife game_of_life(board);
            
            //Check if initialized correctly
            for (size_t row = 0; row < game_of_life.GetBoard().size(); ++row) {
                for (size_t col = 0; col < game_of_life.GetBoard()[row].size(); ++col) {
                    if ((row == 1 && col == 2) ||
                        (row == 2 && col == 2) ||
                        (row == 3 && col == 2)) {
                            REQUIRE(game_of_life.GetBoard()[row][col].state == true);
                    } else {
                        REQUIRE(game_of_life.GetBoard()[row][col].state == false);
                    }
                }
            }
            
            game_of_life.UpdateBoard();
            
            //Should now have a row of cells in the center of the board
            for (size_t row = 0; row < game_of_life.GetBoard().size(); ++row) {
                for (size_t col = 0; col < game_of_life.GetBoard()[row].size(); ++col) {
                    if ((row == 2 && col == 1) ||
                        (row == 2 && col == 2) ||
                        (row == 2 && col == 3)) {
                            REQUIRE(game_of_life.GetBoard()[row][col].state == true);
                    } else {
                        REQUIRE(game_of_life.GetBoard()[row][col].state == false);
                    }
                }
            }
        }
    }
    
    TEST_CASE("Game Of Life Updates Number of Cells per Row Correctly") {
        SECTION("Increasing number of cells per row") {
            //Initialize board
            vector<vector<Cell>> board;
            for (size_t row = 0; row < 5; ++row) {
                vector<Cell> cells;
                for (size_t col = 0; col < 5; ++col) {
                    cells.emplace_back(Cell(false));
                }
                board.push_back(cells);
            }
            
            GameOfLife game_of_life(board);
            
            //Check if initialized correctly
            for (auto& row : game_of_life.GetBoard()) {
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == false);
                }
            }
            
            game_of_life.UpdateNumCellsPerRow(7);
            
            //All cells should still be dead, but each row should now have length of 7
            for (auto& row : game_of_life.GetBoard()) {
                REQUIRE(row.size() == 7);
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == false);
                }
            }
        }
            
        SECTION("Decreasing number of cells per row") {
            //Initialize board
            vector<vector<Cell>> board;
            for (size_t row = 0; row < 7; ++row) {
                vector<Cell> cells;
                for (size_t col = 0; col < 7; ++col) {
                    cells.emplace_back(Cell(false));
                }
                board.push_back(cells);
            }
            
            GameOfLife game_of_life(board);
            
            //Check if initialized correctly
            for (auto& row : game_of_life.GetBoard()) {
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == false);
                }
            }
            
            game_of_life.UpdateNumCellsPerRow(5);
            
            //All cells should still be dead, but each row should now have length of 5
            for (auto& row : game_of_life.GetBoard()) {
                REQUIRE(row.size() == 5);
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == false);
                }
            }
        }
    }
            
    TEST_CASE("Game Of Life Revives and Kills Cells Correctly") {
        SECTION("A dead cell comes to life when revived") {
            //Initialize board
            vector<vector<Cell>> board;
            for (size_t row = 0; row < 5; ++row) {
                vector<Cell> cells;
                for (size_t col = 0; col < 5; ++col) {
                    cells.emplace_back(Cell(false));
                }
                board.push_back(cells);
            }
            
            GameOfLife game_of_life(board);
            
            //Check if initialized correctly
            for (auto& row : game_of_life.GetBoard()) {
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == false);
                }
            }
            
            game_of_life.ReviveOrKillCells(2, 2, true);
            
            //All cells should still be dead, but cell at 2, 2 should be alive
            for (size_t row = 0; row < game_of_life.GetBoard().size(); ++row) {
                for (size_t col = 0; col < game_of_life.GetBoard()[row].size(); ++col) {
                    if (row == 2 && col == 2) {
                        REQUIRE(game_of_life.GetBoard()[row][col].state == true);
                    } else {
                        REQUIRE(game_of_life.GetBoard()[row][col].state == false);
                    }
                }
            }
        }
            
        SECTION("A live cell dies when killed") {
            //Initialize board
            vector<vector<Cell>> board;
            for (size_t row = 0; row < 5; ++row) {
                vector<Cell> cells;
                for (size_t col = 0; col < 5; ++col) {
                    cells.emplace_back(Cell(true));
                }
                board.push_back(cells);
            }
            
            GameOfLife game_of_life(board);
            
            //Check if initialized correctly
            for (auto& row : game_of_life.GetBoard()) {
                for (const Cell& cell : row) {
                    REQUIRE(cell.state == true);
                }
            }
            
            game_of_life.ReviveOrKillCells(2, 2, false);
            
            //All cells should still be alive, but cell at 2, 2 should be dead
            for (size_t row = 0; row < game_of_life.GetBoard().size(); ++row) {
                for (size_t col = 0; col < game_of_life.GetBoard()[row].size(); ++col) {
                    if (row == 2 && col == 2) {
                        REQUIRE(game_of_life.GetBoard()[row][col].state == false);
                    } else {
                        REQUIRE(game_of_life.GetBoard()[row][col].state == true);
                    }
                }
            }
        }
    }
}