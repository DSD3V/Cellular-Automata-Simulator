#include "gui/game_of_life_gui.h"

using namespace ci;

namespace cas {
    GameOfLifeGui::GameOfLifeGui(ColorA& live_cell_color, ColorA& dead_cell_color, int& num_cells_per_row, int num_rows_per_col,
                                 int starting_board_selection, float top_left_cell_width_pct, float top_left_cell_height_pct,
                                 int min_cells_per_row, int max_cells_per_row) :
    live_cell_color_(&live_cell_color), dead_cell_color_(&dead_cell_color),
    live_cell_cycle_hue_(0.5f), dead_cell_cycle_hue_(0),
    num_cells_per_row_cycle_(num_cells_per_row), min_cells_per_row_(min_cells_per_row), max_cells_per_row_(max_cells_per_row),
    top_left_cell_width_pct_(top_left_cell_width_pct), top_left_cell_height_pct_(top_left_cell_height_pct),
    game_of_life_(num_cells_per_row, num_rows_per_col, starting_board_selection),
    frame_count_(0) {
        srand((unsigned) time(nullptr));
        live_cell_cycle_color_ = Color(CM_HSV, live_cell_cycle_hue_, 1, 1);
        dead_cell_cycle_color_ = Color(CM_HSV, dead_cell_cycle_hue_, 1, 1);
    }

    void GameOfLifeGui::UpdateBoard(const bool is_paused, const bool is_reset, const bool cells_being_revived_or_killed, const bool is_in_cycle_mode) {
        if (is_in_cycle_mode) {
            if (!is_paused) {
                //Update Cycle Colors
                live_cell_cycle_hue_ += 0.008f;
                dead_cell_cycle_hue_ += 0.008f;
                if (live_cell_cycle_hue_ >= 0.99f) live_cell_cycle_hue_ = 0;
                if (dead_cell_cycle_hue_ >= 0.99f) dead_cell_cycle_hue_ = 0;
                live_cell_cycle_color_ = Color(CM_HSV, live_cell_cycle_hue_, 1, 1);
                dead_cell_cycle_color_ = Color(CM_HSV, dead_cell_cycle_hue_, 1, 1);
            }
            if (!is_paused && !is_reset && !cells_being_revived_or_killed) {
                frame_count_++;
                //Update Number of Cells per Row
                if (frame_count_ == 30) {
                    num_cells_per_row_cycle_ = rand() % ((max_cells_per_row_ - 10) - (min_cells_per_row_ + 10) + 1) + (min_cells_per_row_ + 10);
                    game_of_life_.UpdateNumCellsPerRow(num_cells_per_row_cycle_);
                    frame_count_ = 0;
                }
                game_of_life_.UpdateBoard();
            }
        } else {
            if (!is_paused && !is_reset && !cells_being_revived_or_killed) {
                game_of_life_.UpdateBoard();
            }
        }
    }

    void GameOfLifeGui::DrawGameOfLifeGui(const int gui_width, const int gui_height, const Font& subtitle_font, const float subtitle_height_pct, const bool is_in_cycle_mode) {
        DrawSubtitle(gui_width, gui_height, subtitle_font, subtitle_height_pct);
        DrawNote(gui_width, gui_height, subtitle_height_pct);
        DrawCells(gui_width, gui_height, is_in_cycle_mode);
    }

    void GameOfLifeGui::DrawSubtitle(const int gui_width, const int gui_height, const Font& subtitle_font, const float subtitle_height_pct) {
        gl::drawStringCentered("2-D: Game of Life",
                               glm::vec2(gui_width / 2, gui_height * subtitle_height_pct),
                               Colorf(1, 1, 1), subtitle_font);
    }

    void GameOfLifeGui::DrawNote(int gui_width, int gui_height, float subtitle_height_pct) {
        Font note_font("Roboto", (gui_width + gui_height) * .011f);
        gl::drawStringCentered("Left click to revive cells, right click to kill cells.",
                               glm::vec2(gui_width / 2, gui_height * (subtitle_height_pct + .07f)),
                               Colorf(1, 1, 1), note_font);
    }

    void GameOfLifeGui::DrawCells(const int gui_width, const int gui_height, const bool is_in_cycle_mode) {
        // top left of the first cell, gets updated for each subsequent cell
        glm::vec2 top_left = glm::vec2(top_left_cell_width_pct_ * gui_width, top_left_cell_height_pct_ * gui_height);
        const float original_top_left_x = top_left.x;

        for (auto& row : game_of_life_.GetBoard()) {
            float cell_width = (gui_width + 0.0f) / row.size();
            for (const Cell& cell : row) {
                if (is_in_cycle_mode) {
                    cell.state ? gl::color(live_cell_cycle_color_) : gl::color(dead_cell_cycle_color_);
                } else {
                    cell.state ? gl::color(*live_cell_color_) : gl::color(*dead_cell_color_);
                }
                Rectf rect(top_left, glm::vec2(top_left.x + cell_width, top_left.y + cell_width));
                gl::drawSolidRect(rect);
                top_left.x += cell_width;
            }
            top_left.x = original_top_left_x;
            top_left.y += cell_width;
        }
    }

    void GameOfLifeGui::ReviveOrKillCells(const int row, const int col, const bool should_revive) {
        game_of_life_.ReviveOrKillCells(row, col, should_revive);
    }

    void GameOfLifeGui::UpdateNumCellsPerRow(int num_cells_per_row) {
        game_of_life_.UpdateNumCellsPerRow(num_cells_per_row);
    }

    void GameOfLifeGui::UpdateStartingBoard(int starting_board_selection) {
        game_of_life_.SetBoard(starting_board_selection);
    }

    void GameOfLifeGui::Clear() { gl::clear(); }

    int GameOfLifeGui::GetNumCellsPerRowCycle() { return num_cells_per_row_cycle_; }
}