#include "core/gen_stacking.h"
#include <catch2/catch.hpp>

namespace cas {
    TEST_CASE("Generation Stacking Updates Generations Correctly") {
        /* Each call to UpdateGenerations represents one frame, or generation change 
           Each generation contains 5 cells and edge cells get same state as adjacent cell */
        
        SECTION("Starting with all dead cells, rule 30") {
            vector<Cell> cells;
            for (size_t i = 0; i < 5; ++i) {
                cells.emplace_back(Cell(false));
            }
            
            GenStacking gs(cells);
            gs.SetRuleset(30);
        
            //Check if initialized correctly
            for (auto& gen : gs.GetGenerations()) {
                for (const Cell& cell : gen) {
                    REQUIRE(!cell.state);
                }
            }
        
            gs.UpdateGenerations(3);
        
            //All cells should still be dead
            for (auto& gen : gs.GetGenerations()) {
                for (const Cell& cell : gen) {
                    REQUIRE(!cell.state);
                }
            }
        }
    
        SECTION("Starting with all live cells, rule 30") {
            vector<Cell> cells;
            for (size_t i = 0; i < 10; ++i) {
                cells.emplace_back(Cell(true));
            }
            
            GenStacking gs(cells);
            gs.SetRuleset(30);
            
            //Check if initialized correctly
            for (auto& gen : gs.GetGenerations()) {
                for (const Cell& cell : gen) {
                    REQUIRE(cell.state);
                }
            }
            
            gs.UpdateGenerations(3);
            
            //Previous generation should be unchanged
            for (const Cell& cell : gs.GetGenerations().front()) {
                REQUIRE(cell.state);
            }
            
            //Check new generation
            for (size_t i = 0; i < gs.GetGenerations().back().size(); ++i) {
                if (i == 0 || i == gs.GetGenerations().back().size() - 1) {
                    REQUIRE(gs.GetGenerations().back()[i].state);
                } else {
                    REQUIRE(!gs.GetGenerations().back()[i].state);
                }
            }
        }
    
        SECTION("Starting with 1 live cell in middle, rule 30") {
            GenStacking gs(30, 5, 0);
            
            //Check if initialized correctly
            for (size_t i = 0; i < gs.GetGenerations().front().size(); ++i) {
                if (i == 2) {
                    REQUIRE(gs.GetGenerations().front()[i].state);
                } else {
                    REQUIRE(!gs.GetGenerations().front()[i].state);
                }
            }
            
            gs.UpdateGenerations(3);
            
            //Previous generation should be unchanged
            for (size_t i = 0; i < gs.GetGenerations().front().size(); ++i) {
                if (i == 2) {
                    REQUIRE(gs.GetGenerations().front()[i].state);
                } else {
                    REQUIRE(!gs.GetGenerations().front()[i].state);
                }
            }
            
            //Check new generation
            for (size_t i = 0; i < gs.GetGenerations().back().size(); ++i) {
                if (i == 0 || i == gs.GetGenerations().back().size() - 1) {
                    REQUIRE(!gs.GetGenerations().back()[i].state);
                } else {
                    if (i == 1) {
                        REQUIRE(gs.GetGenerations().back()[i].state);
                    } else if (i == 2) {
                        REQUIRE(gs.GetGenerations().back()[i].state);
                    } else if (i == 3) {
                        REQUIRE(gs.GetGenerations().back()[i].state);
                    }
                }
            }
        }
    
        SECTION("Starting with random generation, rule 30") {
            vector<Cell> cells;
            cells.emplace_back(Cell(false));
            cells.emplace_back(Cell(false));
            cells.emplace_back(Cell(true));
            cells.emplace_back(Cell(false));
            cells.emplace_back(Cell(true));
            
            GenStacking gs(cells);
            
            gs.SetRuleset(30);
            
            //Check if initialized correctly
            for (size_t i = 0; i < gs.GetGenerations().front().size(); ++i) {
                if (i == 0 || i == 1 || i == 3) {
                    REQUIRE(!gs.GetGenerations().front()[i].state);
                } else {
                    REQUIRE(gs.GetGenerations().front()[i].state);
                }
            }
            
            gs.UpdateGenerations(3);
            
            //Previous generation should be unchanged
            for (size_t i = 0; i < gs.GetGenerations().front().size(); ++i) {
                if (i == 0 || i == 1 || i == 3) {
                    REQUIRE(!gs.GetGenerations().front()[i].state);
                } else {
                    REQUIRE(gs.GetGenerations().front()[i].state);
                }
            }
            
            //Check new generation
            for (size_t i = 0; i < gs.GetGenerations().back().size(); ++i) {
                if (i == 0) {
                    REQUIRE(!gs.GetGenerations().back()[i].state);
                } else if (i == gs.GetGenerations().back().size() - 1) {
                    REQUIRE(!gs.GetGenerations().back()[i].state);
                } else {
                    if (i == 1) {
                        REQUIRE(gs.GetGenerations().back()[i].state);
                    } else if (i == 2) {
                        REQUIRE(gs.GetGenerations().back()[i].state);
                    } else if (i == 3) {
                        REQUIRE(!gs.GetGenerations().back()[i].state);
                    }
                }
            }
        }
    
        SECTION("Works with different ruleset") {
            vector<Cell> cells;
            cells.emplace_back(Cell(false));
            cells.emplace_back(Cell(false));
            cells.emplace_back(Cell(true));
            cells.emplace_back(Cell(false));
            cells.emplace_back(Cell(true));
            
            GenStacking gs(cells);
            
            gs.SetRuleset(126);
            
            //Check if initialized correctly
            for (size_t i = 0; i < gs.GetGenerations().front().size(); ++i) {
                if (i == 0 || i == 1 || i == 3) {
                    REQUIRE(!gs.GetGenerations().front()[i].state);
                } else {
                    REQUIRE(gs.GetGenerations().front()[i].state);
                }
            }
            
            gs.UpdateGenerations(3);
            
            //Previous generation should be unchanged
            for (size_t i = 0; i < gs.GetGenerations().front().size(); ++i) {
                if (i == 0 || i == 1 || i == 3) {
                    REQUIRE(!gs.GetGenerations().front()[i].state);
                } else {
                    REQUIRE(gs.GetGenerations().front()[i].state);
                }
            }
            
            //Check new generation
            for (size_t i = 0; i < gs.GetGenerations().back().size(); ++i) {
                if (i == 0 || i == gs.GetGenerations().back().size() - 1) {
                    REQUIRE(!gs.GetGenerations().back()[i].state);
                } else {
                    if (i == 1) {
                        REQUIRE(gs.GetGenerations().back()[i].state);
                    } else if (i == 2) {
                        REQUIRE(gs.GetGenerations().back()[i].state);
                    } else if (i == 3) {
                        REQUIRE(gs.GetGenerations().back()[i].state);
                    }
                }
            }
        }
    }

    TEST_CASE("Generation Stacking Sets Up Starting Generations Correctly") {
        SECTION("Default starting generation is set correctly") {
            GenStacking gen_stacking;
            
            gen_stacking.SetStartingGeneration(0, 9, true);
            
            //Should have one live cell in the middle
            for (size_t i = 0; i < gen_stacking.GetGenerations().front().size(); ++i) {
                if (i == 4) {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == true);
                } else {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == false);
                }
            }
        }
    
        SECTION("Alternating starting generation is set correctly") {
            GenStacking gen_stacking;
            
            gen_stacking.SetStartingGeneration(2, 9, true);
            
            //Should have one live cell in the middle
            for (size_t i = 0; i < gen_stacking.GetGenerations().front().size(); ++i) {
                if (i % 2 == 0) {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == true);
                } else {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == false);
                }
            }
        }
    }

    TEST_CASE("Generation Stacking Updates Number of Cells per Generation Correctly") {
        SECTION("Increasing number of cells per generation") {
            GenStacking gen_stacking;
            
            gen_stacking.SetStartingGeneration(0, 9, true);
            
            //Check if initialized correctly: Should have one live cell in the middle
            for (size_t i = 0; i < gen_stacking.GetGenerations().front().size(); ++i) {
                if (i == 4) {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == true);
                } else {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == false);
                }
            }
            
            gen_stacking.UpdateNumCellsPerGen(13, true, 20);
            
            //Now only cell at index 6 should be alive
            for (size_t i = 0; i < gen_stacking.GetGenerations().back().size(); ++i) {
                if (i == 6) {
                    REQUIRE(gen_stacking.GetGenerations().back()[i].state == true);
                } else {
                    REQUIRE(gen_stacking.GetGenerations().back()[i].state == false);
                }
            }
            
            //Previous gen should still only have a cell alive at index 4
            for (size_t i = 0; i < gen_stacking.GetGenerations().front().size(); ++i) {
                if (i == 4) {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == true);
                } else {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == false);
                }
            }
        }
        
        SECTION("Decreasing number of cells per generation") {
            GenStacking gen_stacking;
            
            gen_stacking.SetStartingGeneration(0, 13, true);
            
            //Check if initialized correctly: Should have one live cell in the middle
            for (size_t i = 0; i < gen_stacking.GetGenerations().front().size(); ++i) {
                if (i == 6) {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == true);
                } else {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == false);
                }
            }
            
            gen_stacking.UpdateNumCellsPerGen(9, true, 20);
            
            //Now only cell at index 4 should be alive
            for (size_t i = 0; i < gen_stacking.GetGenerations().back().size(); ++i) {
                if (i == 4) {
                    REQUIRE(gen_stacking.GetGenerations().back()[i].state == true);
                } else {
                    REQUIRE(gen_stacking.GetGenerations().back()[i].state == false);
                }
            }
            
            //Previous gen should still only have a cell alive at index 6
            for (size_t i = 0; i < gen_stacking.GetGenerations().front().size(); ++i) {
                if (i == 6) {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == true);
                } else {
                    REQUIRE(gen_stacking.GetGenerations().front()[i].state == false);
                }
            }
        }
    }
}