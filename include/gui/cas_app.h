#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "main_screen.h"
#include "gen_stacking_gui.h"
#include "game_of_life_gui.h"

using namespace ci;
using namespace ci::app;

namespace cas {
    class CasApp : public App {
    public:
        /* Default constructor: initializes member variables */
        CasApp();

        /* Initializes simulation settings */
        void setup() override;

        /* Updates simulation every frame */
        void update() override;

        /* Draws simulation every frame */
        void draw() override;

        /* Mouse events track whether buttons are being hovered over or clicked */
        void mouseMove(MouseEvent event) override;
        void mouseDown(MouseEvent event) override;
        void mouseUp(MouseEvent event) override;
        void mouseDrag(MouseEvent event) override;

    private:
        /* Main member variables being updated and drawn */
        MainScreen main_screen_;
        GenStackingGui gen_stacking_gui_;
        GameOfLifeGui game_of_life_gui_;

        /* Booleans used to determine what should be displayed on GUI */
        bool show_main_screen_;
        bool show_gen_stacking_;
        bool show_game_of_life_;

        /* Booleans used to track when a button is pressed to update GUI accordingly */
        bool main_screen_btn1_is_pressed_;
        bool main_screen_btn2_is_pressed_;
        bool menu_btn_is_pressed_;
        bool gen_stacking_pause_btn_is_pressed_;
        bool game_of_life_pause_btn_is_pressed_;
        bool gen_stacking_reset_btn_is_pressed_;
        bool game_of_life_reset_btn_is_pressed_;
        bool gen_stacking_settings_btn_is_pressed_;
        bool game_of_life_settings_btn_is_pressed_;
        bool gen_stacking_cycle_btn_is_pressed_;
        bool game_of_life_cycle_btn_is_pressed_;

        /* Button colors: default is gray, white when hovered over */
        const Colorf kDefaultBtnColor;
        const Colorf kHoverBtnColor;

        /* Main screen button colors: btn1 is Gen Stacking, btn2 is Game of Life */
        Colorf main_screen_btn1_color_;
        Colorf main_screen_btn2_color_;

        /* Both Gen Stacking and Game of Life have a menu button to return to main menu */
        Colorf menu_btn_color_;

        /* Color of buttons; white when hovered, else light gray */
        Colorf gen_stacking_pause_btn_color_;
        Colorf game_of_life_pause_btn_color_;
        Colorf gen_stacking_reset_btn_color_;
        Colorf game_of_life_reset_btn_color_;
        Colorf gen_stacking_settings_btn_color_;
        Colorf game_of_life_settings_btn_color_;
        Colorf gen_stacking_cycle_btn_color_;
        Colorf game_of_life_cycle_btn_color_;

        /* Stores location of buttons to know when it is hovered over / clicked */
        glm::vec2 top_left_menu_btn_;
        glm::vec2 bottom_right_menu_btn_;

        glm::vec2 top_left_pause_btn_;
        glm::vec2 bottom_right_pause_btn_;

        glm::vec2 top_left_reset_btn_;
        glm::vec2 bottom_right_reset_btn_;

        glm::vec2 top_left_settings_btn_;
        glm::vec2 bottom_right_settings_btn_;

        glm::vec2 top_left_cycle_btn_;
        glm::vec2 bottom_right_cycle_btn_;

        /* Booleans to store whether simulation is paused/reset/in cycle mode or not */
        bool gen_stacking_is_paused_;
        bool game_of_life_is_paused_;
        bool gen_stacking_is_reset_;
        bool game_of_life_is_reset_;
        bool gen_stacking_is_showing_settings_;
        bool game_of_life_is_showing_settings_;
        bool gen_stacking_is_in_cycle_mode_;
        bool game_of_life_is_in_cycle_mode_;
        bool cells_being_revived_or_killed_;

        /* x1, x2 are percent of gui width for location of sides of buttons
         * y1, y2 are percent of gui height for location of top and bottom of buttons */
        const float kMenuX1WidthPct;
        const float kMenuX2WidthPct;
        const float kMenuY1HeightPct;
        const float kMenuY2HeightPct;

        const float kPauseX1WidthPct;
        const float kPauseX2WidthPct;
        const float kPauseY1HeightPct;
        const float kPauseY2HeightPct;

        const float kResetX1WidthPct;
        const float kResetX2WidthPct;
        const float kResetY1HeightPct;
        const float kResetY2HeightPct;

        const float kSettingsX1WidthPct;
        const float kSettingsX2WidthPct;
        const float kSettingsY1HeightPct;
        const float kSettingsY2HeightPct;

        const float kCycleX1WidthPct;
        const float kCycleX2WidthPct;
        const float kCycleY1HeightPct;
        const float kCycleY2HeightPct;

        /* Subtitle (for gen stacking and game of life) is drawn at gui height * kSubtitleHeightPct */
        const float kSubtitleHeightPct;

        /* Percent of width and height for top left (first) cell that gets drawn */
        float top_left_cell_width_pct_;
        float top_left_cell_height_pct_;

        /* Simulation settings; can be changed by user */
        params::InterfaceGlRef settings_;

        /* Dimensions of simulation settings box */
        glm::vec2 settings_box_dimensions_;

        /* Ruleset for gen stacking; can be changed by user */
        int ruleset_;

        /* Cell colors; can be changed by user */
        ColorA gen_stacking_live_cell_color_;
        ColorA gen_stacking_dead_cell_color_;
        ColorA game_of_life_live_cell_color_;
        ColorA game_of_life_dead_cell_color_;

        /* Gen stacking cell settings; can be changed by user */
        int num_cells_per_gen_;
        int min_cells_per_gen_;
        int max_cells_per_gen_;

        /* Game of Life cell settings; can be changed by user */
        int num_cells_per_row_;
        int num_rows_per_col_;
        int min_cells_per_row_;
        int max_cells_per_row_;

        /* Starting board options and selection for Gen Stacking; can be changed by user */
        vector<string> starting_gen_options_;
        int starting_gen_selection_;

        /* Starting board options and selection for Game of Life; can be changed by user */
        vector<string> starting_board_options_;
        int starting_board_selection_;

        /* Drawing Helper Methods */
        void DrawTitle(const Font& title_font);
        void DrawMenuBtn(int gui_width, int gui_height);
        void DrawPauseBtn(int gui_width, int gui_height, const Colorf& btn_color, bool paused);
        void DrawResetBtn(int gui_width, int gui_height, const Colorf& btn_color, bool is_reset);
        void DrawSettingsBtn(int gui_width, int gui_height, const Colorf& btn_color, bool is_showing_settings);
        void DrawCycleBtn(int gui_width, int gui_height, const Colorf& btn_color, bool is_in_cycle_mode);

        /* Display different settings depending on mode */
        void SetGenStackingSettings();
        void SetGameOfLifeSettings();

        /* Helper methods for mouse events: x, y are mouse coordinates */
        void MainScreenMouseMove(int x, int y);
        void MainScreenMouseDown(int x, int y);
        void MainScreenMouseUp(int x, int y);

        void GenStackMouseMove(int x, int y);
        void GenStackMouseDown(int x, int y);
        void GenStackMouseUp(int x, int y);

        void GameOfLifeMouseMove(int x, int y);
        void GameOfLifeMouseDown(int x, int y);
        void GameOfLifeMouseUp(int x, int y);

        /* Handles mouse clicks/drag for Game of Life board */
        void ReviveOrKillCells(int x, int y, const MouseEvent& event);
    };
}