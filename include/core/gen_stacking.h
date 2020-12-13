#pragma once

#include "core/cell.h"
#include <vector>
#include <deque>
#include <string>

using std::vector;
using std::deque;
using std::string;

namespace cas {
    typedef vector<Cell> Generation1D; //each vector of cells is a Generation in 1-D Gen Stacking
    class GenStacking {
    public:
        /* Default constructor */
        GenStacking() {};

        /* Parameterized constructor: Initializes generations_ either with 1 live cell in center, randomly, or alternating */
        GenStacking(int ruleset, int num_cells_per_gen, int starting_gen_selection);

        /* Parameterized constructor: Initializes generations_ with the specific starting_generation */
        GenStacking(Generation1D& starting_generation);

        /* Updates deque of generations. if generations_.size() > max_gens, pop_front() */
        void UpdateGenerations(int max_gens);

        /* Getter */
        const deque<Generation1D>& GetGenerations();

        /* Sets the ruleset 8-digit binary string. rule_value is an int 0 - 255 */
        void SetRuleset(int rule_value);

        /* Updates the number of cells in a generation */
        void UpdateNumCellsPerGen(int num_cells_per_gen, bool is_reset, int max_gens);

        /* Sets the starting generation with 1 live cell in center (0), randomly (1), or alternating (2) */
        void SetStartingGeneration(int starting_gen_value, int num_cells_in_gen, bool should_clear);

    private:
        /* Deque of generations: each frame, insert new generation into back and pop front */
        deque<Generation1D> generations_;

        /* Ruleset which determines how generations change: 8 binary digits */
        string ruleset_;

        /* How the generation of cells starts: default, random, or alternating */
        int starting_gen_selection_;

        /* Computes the next generation based on the previous generation */
        void ComputeNextGen(Generation1D& prev_gen);
    };
}