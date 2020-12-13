#include "core/gen_stacking.h"
#include <bitset>
#include <ctime>

namespace cas {
    GenStacking::GenStacking(int ruleset, int num_cells_per_gen, int starting_gen_selection) :
            starting_gen_selection_(starting_gen_selection) {
        srand((unsigned) time(nullptr));
        SetRuleset(ruleset);
        SetStartingGeneration(starting_gen_selection, num_cells_per_gen, true);
    }

    void GenStacking::SetStartingGeneration(int starting_gen_value, int num_cells_in_gen, const bool should_clear) {
        starting_gen_selection_ = starting_gen_value;
        if (should_clear) generations_.clear();
        Generation1D cells;
        //0 means default: 1 live cell in the middle
        if (starting_gen_value == 0) {
            for (int i = 0; i < num_cells_in_gen; ++i) {
                i == floor(num_cells_in_gen / 2) ? cells.emplace_back(Cell(true)) : cells.emplace_back(Cell(false));
            }
            //1 means random: some alive, some dead    
        } else if (starting_gen_value == 1) {
            for (int i = 0; i < num_cells_in_gen; ++i) {
                int alive = rand() % 2;
                alive == 1 ? cells.emplace_back(Cell(true)) : cells.emplace_back(Cell(false));
            }
            //2 means alternating: dead->alive->dead->alive->etc.    
        } else if (starting_gen_value == 2) {
            for (int i = 0; i < num_cells_in_gen; ++i) {
                i % 2 == 0 ? cells.emplace_back(Cell(true)) : cells.emplace_back(Cell(false));
            }
        }
        generations_.emplace_back(cells);
    }

    GenStacking::GenStacking(Generation1D& starting_generation) {
        generations_.push_back(starting_generation);
    }

    void GenStacking::UpdateGenerations(const int max_gens) {
        ComputeNextGen(generations_.back());
        int size = generations_.size();
        if (size >= max_gens) generations_.pop_front();
    }

    void GenStacking::ComputeNextGen(Generation1D& prev_gen) {
        Generation1D cells;
        for (size_t i = 0; i < prev_gen.size(); ++i) {
            //handle edge cells
            if (i == 0) {
                cells.push_back(prev_gen[i+1]);
            } else if (i == prev_gen.size() - 1) {
                cells.push_back(prev_gen[i-1]);
            } else {
                //ruleset string is a 8-digit binary string, 1 means the cell should be alive, 0 means it should be dead
                //8 cases are fixed per rules at https://mathworld.wolfram.com/ElementaryCellularAutomaton.html
                if (prev_gen[i-1].state && prev_gen[i].state && prev_gen[i+1].state) {
                    cells.emplace_back(Cell(ruleset_[0] == '1'));
                } else if (prev_gen[i-1].state && prev_gen[i].state && !prev_gen[i+1].state) {
                    cells.emplace_back(Cell(ruleset_[1] == '1'));
                } else if (prev_gen[i-1].state && !prev_gen[i].state && prev_gen[i+1].state) {
                    cells.emplace_back(Cell(ruleset_[2] == '1'));
                } else if (prev_gen[i-1].state && !prev_gen[i].state && !prev_gen[i+1].state) {
                    cells.emplace_back(Cell(ruleset_[3] == '1'));
                } else if (!prev_gen[i-1].state && prev_gen[i].state && prev_gen[i+1].state) {
                    cells.emplace_back(Cell(ruleset_[4] == '1'));
                } else if (!prev_gen[i-1].state && prev_gen[i].state && !prev_gen[i+1].state) {
                    cells.emplace_back(Cell(ruleset_[5] == '1'));
                } else if (!prev_gen[i-1].state && !prev_gen[i].state && prev_gen[i+1].state) {
                    cells.emplace_back(Cell(ruleset_[6] == '1'));
                } else if (!prev_gen[i-1].state && !prev_gen[i].state && !prev_gen[i+1].state) {
                    cells.emplace_back(Cell(ruleset_[7] == '1'));
                }
            }
        }
        generations_.emplace_back(cells);
    }

    void GenStacking::UpdateNumCellsPerGen(int num_cells_per_gen, bool is_reset, int max_gens) {
        if (!is_reset) {
            Generation1D cells = generations_.back();
            int i = cells.size(), j = i;
            //if cell count is decreasing, remove cells
            while (num_cells_per_gen < i) {
                cells.pop_back();
                i--;
            }
            //if cell count has increased, add cells randomly alive or dead
            while (num_cells_per_gen > j) {
                int alive = rand() % 2;
                alive == 1 ? cells.emplace_back(Cell(true)) : cells.emplace_back(Cell(false));
                j++;
            }
            generations_.emplace_back(cells);
        } else {
            SetStartingGeneration(starting_gen_selection_, num_cells_per_gen, false);
        }
        //make sure new gen with new number of cells still fits on screen
        int size = generations_.size();
        if (size >= max_gens) generations_.pop_front();
    }

    /* Getters and Setters */
    const deque<Generation1D>& GenStacking::GetGenerations() { return generations_; }
    void GenStacking::SetRuleset(const int rule_value) { ruleset_ = std::bitset<8>(rule_value).to_string(); }
}