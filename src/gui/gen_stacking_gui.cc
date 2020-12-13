#include "gui/gen_stacking_gui.h"

using namespace ci;

namespace cas {
    GenStackingGui::GenStackingGui(int ruleset, ColorA& live_cell_color, ColorA& dead_cell_color, int& num_cells_per_gen,
                                   int starting_gen_selection, float top_left_cell_width_pct, float top_left_cell_height_pct, int min_cells_per_gen, int max_cells_per_gen) :
    live_cell_color_(&live_cell_color), dead_cell_color_(&dead_cell_color),
    live_cell_cycle_hue_(0.5f), dead_cell_cycle_hue_(0),
    top_left_cell_width_pct_(top_left_cell_width_pct), top_left_cell_height_pct_(top_left_cell_height_pct),
    num_cells_per_gen_(&num_cells_per_gen),
    num_cells_per_gen_cycle_(num_cells_per_gen), min_cells_per_gen_(min_cells_per_gen), max_cells_per_gen_(max_cells_per_gen),
    gen_stacking_(ruleset, num_cells_per_gen, starting_gen_selection),
    frame_count_(0) {
        srand((unsigned) time(nullptr));
        live_cell_cycle_color_= Color(CM_HSV,live_cell_cycle_hue_, 1, 1);
        dead_cell_cycle_color_ = Color(CM_HSV, dead_cell_cycle_hue_, 1, 1);
    }

    void GenStackingGui::UpdateGenerations(const int gui_width, const int gui_height, const bool is_paused, const bool is_reset, const bool is_in_cycle_mode) {
        if (is_in_cycle_mode) {
            if (!is_paused) {
                //Update Cycle Colors
                live_cell_cycle_hue_ += 0.006f;
                dead_cell_cycle_hue_ += 0.006f;
                if (live_cell_cycle_hue_ >= 0.99f) live_cell_cycle_hue_ = 0;
                if (dead_cell_cycle_hue_ >= 0.99f) dead_cell_cycle_hue_ = 0;
                live_cell_cycle_color_ = Color(CM_HSV, live_cell_cycle_hue_, 1, 1);
                dead_cell_cycle_color_ = Color(CM_HSV, dead_cell_cycle_hue_, 1, 1);
            }

            if (!is_paused && !is_reset) {
                frame_count_++;
                int max_gens = static_cast<int>((gui_height - (top_left_cell_height_pct_ * gui_height)) / static_cast<float>(gui_width / num_cells_per_gen_cycle_)) + 2;

                //Update Cycle Ruleset and Number of Cells per Generation
                if (frame_count_ == 50) {
                    int ruleset = rand() % 256;
                    gen_stacking_.SetRuleset(ruleset);
                    num_cells_per_gen_cycle_ = rand() % ((max_cells_per_gen_ - 20) - (min_cells_per_gen_ + 20) + 1) + (min_cells_per_gen_ + 20);
                    max_gens = static_cast<int>((gui_height - (top_left_cell_height_pct_ * gui_height)) / static_cast<float>(gui_width / num_cells_per_gen_cycle_)) + 2;
                    gen_stacking_.UpdateNumCellsPerGen(num_cells_per_gen_cycle_, is_reset, max_gens);
                    frame_count_ = 0;
                }
                gen_stacking_.UpdateGenerations(max_gens);
            }
        } else {
            if (!is_paused && !is_reset) {
                int max_gens = static_cast<int>((gui_height - (top_left_cell_height_pct_ * gui_height)) / static_cast<float>(gui_width / *num_cells_per_gen_)) + 2;
                gen_stacking_.UpdateGenerations(max_gens);
            }
        }
    }

    void GenStackingGui::DrawGenStackingGui(const int gui_width, const int gui_height, const Font& subtitle_font, const float subtitle_height_pct, const bool is_in_cycle_mode) {
        DrawSubtitle(gui_width, gui_height, subtitle_font, subtitle_height_pct);
        DrawCells(gui_width, gui_height, is_in_cycle_mode);
    }

    void GenStackingGui::DrawSubtitle(const int gui_width, const int gui_height, const Font& subtitle_font, const float subtitle_height_pct) {
        gl::drawStringCentered("1-D: Generation Stacking",
                               glm::vec2(gui_width / 2, gui_height * subtitle_height_pct),
                               Colorf(1, 1, 1), subtitle_font);
    }

    void GenStackingGui::DrawCells(const int gui_width, const int gui_height, const bool is_in_cycle_mode) {
        //top left of the first cell, gets updated for each subsequent cell
        glm::vec2 top_left = glm::vec2(top_left_cell_width_pct_ * gui_width, top_left_cell_height_pct_ * gui_height);
        const float original_top_left_x = top_left.x;

        for (auto& gen : gen_stacking_.GetGenerations()) {
            float cell_width = (gui_width + 0.0f) / gen.size();
            for (const Cell& cell : gen) {
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

    void GenStackingGui::UpdateRuleset(int ruleset) { gen_stacking_.SetRuleset(ruleset); }

    void GenStackingGui::UpdateNumCellsPerGen(int num_cells_per_gen, bool is_reset, int gui_width, int gui_height) {
        gen_stacking_.UpdateNumCellsPerGen(num_cells_per_gen, is_reset,static_cast<int>((gui_height - (top_left_cell_width_pct_
                                                                                                       * gui_height)) / static_cast<float>(gui_width / *num_cells_per_gen_)) + 2);
    }

    void GenStackingGui::UpdateStartingGen(int starting_gen_selection, int num_cells_in_gen) {
        gen_stacking_.SetStartingGeneration(starting_gen_selection, num_cells_in_gen, true);
    }

    void GenStackingGui::Clear() { gl::clear(); }
}