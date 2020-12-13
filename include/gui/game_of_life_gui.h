#pragma once

#include "cinder/gl/gl.h"
#include "core/game_of_life.h"

using namespace ci;

namespace cas {
    class GameOfLifeGui {
        public:
            /* Default Constructor */
            GameOfLifeGui() {};
    
            /* Parameterized Constructor: initializes member variables */
            GameOfLifeGui(ColorA& live_cell_color, ColorA& dead_cell_color, int& num_cells_per_row, int num_rows_per_col,
                          int starting_board_selection, float top_left_cell_width_pct, float top_left_cell_height_pct,
                          int min_cells_per_row, int max_cells_per_row);
    
            /* Updates the board of cells; called every frame */
            void UpdateBoard(bool is_paused, bool is_reset, bool cells_being_revived_or_killed, bool is_in_cycle_mode);
    
            /* Draws Game of Life board of cells; called every frame */
            void DrawGameOfLifeGui(int gui_width, int gui_height, const Font& subtitle_font, float subtitle_height_pct, bool is_in_cycle_mode);
    
            /* Updates the number of cells displayed on each row of Game of Life board */
            void UpdateNumCellsPerRow(int num_cells_per_row);
    
            /* Updates the starting board */
            void UpdateStartingBoard(int starting_board_selection);
    
            /* Revives or kills cells at row, col */
            void ReviveOrKillCells(int row, int col, bool should_revive);
    
            /* Clears the Game of Life GUI, called when menu button is clicked */
            void Clear();
    
            /* Getter */
            int GetNumCellsPerRowCycle();
    
        private:
            /* GameOfLife object; stores and updates 2d board of cells */
            GameOfLife game_of_life_;
    
            /* Cell colors */
            ColorA* live_cell_color_;
            ColorA* dead_cell_color_;
    
            /* Cycle mode cell colors */
            Color live_cell_cycle_color_;
            float live_cell_cycle_hue_;
            Color dead_cell_cycle_color_;
            float dead_cell_cycle_hue_;
    
            /* Number of cells per row during cycle mode */
            int num_cells_per_row_cycle_;
    
            /* Min and max number of cells per row */
            int min_cells_per_row_;
            int max_cells_per_row_;
    
            /* Keeps track of frames for updating num_cells_per_row_cycle_ during cycle mode */
            int frame_count_;
    
            /* first top left cell is at x = gui_width * top left width pct, y = gui_height * top left height pct */
            float top_left_cell_width_pct_;
            float top_left_cell_height_pct_;
    
            /* Drawing helper methods */
            void DrawSubtitle(int gui_width, int gui_height, const Font& subtitle_font, float subtitle_height_pct);
            void DrawNote(int gui_width, int gui_height, float subtitle_height_pct);
            void DrawCells(int gui_width, int gui_height, bool is_in_cycle_mode);
    };
}