#pragma once

#include "cinder/gl/gl.h"
#include "core/gen_stacking.h"

using namespace ci;

namespace cas {
    class GenStackingGui {
    public:
        /* Default Constructor */
        GenStackingGui() {};

        /* Parameterized Constructor: initializes member variables */
        GenStackingGui(int ruleset, ColorA& live_cell_color, ColorA& dead_cell_color, int& num_cells_per_gen, int starting_gen_selection,
                       float top_left_cell_width_pct, float top_left_cell_height_pct, int min_cells_per_gen, int max_cells_per_gen);

        /* Updates generations to be drawn based on current gui width and height; called every frame */
        void UpdateGenerations(int gui_width, int gui_height, bool is_paused, bool is_reset, bool is_in_cycle_mode);

        /* Draws Gen Stacking generations of cells; called every frame */
        void DrawGenStackingGui(int gui_width, int gui_height, const Font& subtitle_font, float subtitle_height_pct, bool is_in_cycle_mode);

        /* Updates the Gen Stacking ruleset */
        void UpdateRuleset(int ruleset);

        /* Updates the number of cells per generation */
        void UpdateNumCellsPerGen(int num_cells_per_gen, bool is_reset, int gui_width, int gui_height);

        /* Updates the starting generation */
        void UpdateStartingGen(int starting_gen_selection, int num_cells_in_gen);

        /* Clears the Gen Stacking GUI, called when menu button is clicked */
        void Clear();

    private:
        /* GenStacking object; stores and updates list of generations */
        GenStacking gen_stacking_;

        /* Cell colors */
        ColorA* live_cell_color_;
        ColorA* dead_cell_color_;

        /* Cycle mode cell colors */
        Color live_cell_cycle_color_;
        float live_cell_cycle_hue_;
        Color dead_cell_cycle_color_;
        float dead_cell_cycle_hue_;

        /* Number of cells per generation (row); controlled by user */
        int* num_cells_per_gen_;

        /* Number of cells per generation during cycle mode; updates randomly */
        int num_cells_per_gen_cycle_;

        /* Min and max number of cells per generation */
        int min_cells_per_gen_;
        int max_cells_per_gen_;

        /* Keeps track of frames for updating ruleset_ and num_cells_per_gen_ during cycle mode */
        int frame_count_;

        /* first top left cell is at x = gui_width * top left width pct, y = gui_height * top left height pct */
        float top_left_cell_width_pct_;
        float top_left_cell_height_pct_;

        /* Drawing helper methods */
        void DrawSubtitle(int gui_width, int gui_height, const Font& subtitle_font, float subtitle_height_pct);
        void DrawCells(int gui_width, int gui_height, bool is_in_cycle_mode);
    };
}