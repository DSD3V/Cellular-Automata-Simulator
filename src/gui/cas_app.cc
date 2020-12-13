#include "gui/cas_app.h"

namespace cas {
    CasApp::CasApp() :
    //Initialize booleans
    show_main_screen_(true),
    show_gen_stacking_(false),
    show_game_of_life_(false),
    main_screen_btn1_is_pressed_(false), main_screen_btn2_is_pressed_(false),
    menu_btn_is_pressed_(false),
    gen_stacking_pause_btn_is_pressed_(false), game_of_life_pause_btn_is_pressed_(false),
    gen_stacking_reset_btn_is_pressed_(false), game_of_life_reset_btn_is_pressed_(false),
    gen_stacking_settings_btn_is_pressed_(false), game_of_life_settings_btn_is_pressed_(false),
    gen_stacking_cycle_btn_is_pressed_(false), game_of_life_cycle_btn_is_pressed_(false),
    gen_stacking_is_paused_(false), game_of_life_is_paused_(false),
    gen_stacking_is_reset_(true), game_of_life_is_reset_(true),
    gen_stacking_is_showing_settings_(true), game_of_life_is_showing_settings_(true),
    cells_being_revived_or_killed_(false),
    gen_stacking_is_in_cycle_mode_(false), game_of_life_is_in_cycle_mode_(false),

    //Initialize button colors
    kDefaultBtnColor(.65f, .65f, .65f), kHoverBtnColor(1, 1, 1),
    main_screen_btn1_color_(kDefaultBtnColor), main_screen_btn2_color_(kDefaultBtnColor),
    menu_btn_color_(kDefaultBtnColor),
    gen_stacking_pause_btn_color_(kDefaultBtnColor), game_of_life_pause_btn_color_(kDefaultBtnColor),
    gen_stacking_reset_btn_color_(kDefaultBtnColor), game_of_life_reset_btn_color_(kDefaultBtnColor),
    gen_stacking_settings_btn_color_(kDefaultBtnColor), game_of_life_settings_btn_color_(kDefaultBtnColor),
    gen_stacking_cycle_btn_color_(kDefaultBtnColor), game_of_life_cycle_btn_color_(kDefaultBtnColor),

    //Initialize percentages used for locations of buttons / subtitle / cells
    kMenuX1WidthPct(.04f), kMenuX2WidthPct(.15f), kMenuY1HeightPct(.03f), kMenuY2HeightPct(.10f),
    kPauseX1WidthPct(.67f), kPauseX2WidthPct(.75f), kPauseY1HeightPct(.12f), kPauseY2HeightPct(.18f),
    kResetX1WidthPct(.77f), kResetX2WidthPct(.84f), kResetY1HeightPct(.12f), kResetY2HeightPct(.18f),
    kSettingsX1WidthPct(.86f), kSettingsX2WidthPct(.99f), kSettingsY1HeightPct(.10f), kSettingsY2HeightPct(.18f),
    kCycleX1WidthPct(.73f), kCycleX2WidthPct(.88f), kCycleY1HeightPct(.02f), kCycleY2HeightPct(.09f),
    kSubtitleHeightPct(.09f),
    top_left_cell_width_pct_(0), top_left_cell_height_pct_(.20f),

    //Initialize default settings
    settings_box_dimensions_(glm::vec2(370, 325)),
    ruleset_(126),
    gen_stacking_live_cell_color_(ColorA(0, 0, 1)), gen_stacking_dead_cell_color_(ColorA(0, 0, .16f)),
    game_of_life_live_cell_color_(ColorA(0, 0, 1)), game_of_life_dead_cell_color_(ColorA(0, 0, .16f)),
    num_cells_per_gen_(51), num_cells_per_row_(51), num_rows_per_col_(100),
    min_cells_per_gen_(10), max_cells_per_gen_(100), min_cells_per_row_(10), max_cells_per_row_(100),
    starting_gen_options_({"Default (one live cell in the center)", "Random", "Alternating (dead->alive->dead->alive->etc.)"}),
    starting_board_options_({"Default (square)", "Random", "Custom (draw your own)"}),
    starting_gen_selection_(0), starting_board_selection_(0) {
        //Construct GUI objects with default values
        gen_stacking_gui_ = GenStackingGui(ruleset_, gen_stacking_live_cell_color_, gen_stacking_dead_cell_color_, num_cells_per_gen_,
                                           starting_gen_selection_, top_left_cell_width_pct_, top_left_cell_height_pct_, min_cells_per_gen_, max_cells_per_gen_);
        game_of_life_gui_ = GameOfLifeGui(game_of_life_live_cell_color_, game_of_life_dead_cell_color_, num_cells_per_row_, num_rows_per_col_,
                                          starting_board_selection_, top_left_cell_width_pct_, top_left_cell_height_pct_, min_cells_per_row_, max_cells_per_row_);
    }

    void CasApp::setup() {
        //Initialize simulation settings
        settings_ = params::InterfaceGl::create(getWindow(), "Simulation Settings", settings_box_dimensions_,
                                                ColorA(0.2f, 0.2f, 0.2f, 0.2f));
        settings_->setPosition(glm::vec2((getWindowWidth() / 2) - (settings_box_dimensions_.x / 2), getWindowHeight() * .34f));
    }

    void CasApp::update() {
        if (show_gen_stacking_) {
            gen_stacking_gui_.UpdateGenerations(getWindowWidth(), getWindowHeight(), gen_stacking_is_paused_, gen_stacking_is_reset_, gen_stacking_is_in_cycle_mode_);
        } else if (show_game_of_life_) {
            game_of_life_gui_.UpdateBoard(game_of_life_is_paused_, game_of_life_is_reset_, cells_being_revived_or_killed_, game_of_life_is_in_cycle_mode_);
        }
    }

    void CasApp::draw() {
        int gui_width = getWindowWidth();
        int gui_height = getWindowHeight();

        //Update fonts based on current width and height each frame
        const Font title_font = Font("Roboto", (gui_width + gui_height) * .026f);
        const Font subtitle_font = Font("Roboto",(gui_width + gui_height) * .018f);

        //Draw Main Screen
        if (show_main_screen_) {
            gen_stacking_gui_.Clear();
            game_of_life_gui_.Clear();
            DrawTitle(title_font);
            main_screen_.DrawMainScreen(gui_width, gui_height, main_screen_btn1_color_, main_screen_btn2_color_);

        //Draw Gen Stacking    
        } else if (show_gen_stacking_) {
            main_screen_.Clear();
            DrawTitle(title_font);
            DrawMenuBtn(gui_width, gui_height);
            DrawPauseBtn(gui_width, gui_height, gen_stacking_pause_btn_color_, gen_stacking_is_paused_);
            DrawResetBtn(gui_width, gui_height, gen_stacking_reset_btn_color_, gen_stacking_is_reset_);
            DrawSettingsBtn(gui_width, gui_height, gen_stacking_settings_btn_color_, gen_stacking_is_showing_settings_);
            DrawCycleBtn(gui_width, gui_height, gen_stacking_cycle_btn_color_, gen_stacking_is_in_cycle_mode_);
            gen_stacking_gui_.DrawGenStackingGui(gui_width, gui_height, subtitle_font, kSubtitleHeightPct, gen_stacking_is_in_cycle_mode_);
            gen_stacking_is_showing_settings_ ? settings_->show() : settings_->hide();
            settings_->draw();

        //Draw Game of Life    
        } else if (show_game_of_life_) {
            main_screen_.Clear();
            DrawTitle(title_font);
            DrawMenuBtn(gui_width, gui_height);
            DrawPauseBtn(gui_width, gui_height, game_of_life_pause_btn_color_, game_of_life_is_paused_);
            DrawResetBtn(gui_width, gui_height, game_of_life_reset_btn_color_, game_of_life_is_reset_);
            DrawSettingsBtn(gui_width, gui_height, game_of_life_settings_btn_color_, game_of_life_is_showing_settings_);
            DrawCycleBtn(gui_width, gui_height, game_of_life_cycle_btn_color_, game_of_life_is_in_cycle_mode_);
            game_of_life_gui_.DrawGameOfLifeGui(gui_width, gui_height, subtitle_font, kSubtitleHeightPct, game_of_life_is_in_cycle_mode_);
            game_of_life_is_showing_settings_ ? settings_->show() : settings_->hide();
            settings_->draw();
        }
    }

    void CasApp::DrawTitle(const Font& title_font) {
        gl::drawStringCentered("Cellular Automata Simulator",
                               glm::vec2(getWindowWidth() / 2, 20),
                               Colorf(1, 1, 1), title_font);
    }

    void CasApp::DrawMenuBtn(const int gui_width, const int gui_height) {
        top_left_menu_btn_ = glm::vec2(gui_width * kMenuX1WidthPct, gui_height * kMenuY1HeightPct);
        bottom_right_menu_btn_ = glm::vec2(gui_width * kMenuX2WidthPct, gui_height * kMenuY2HeightPct);

        Font btn_font("Roboto", (gui_width + gui_height) * .013f);

        gl::color(menu_btn_color_);
        Rectf rect1(top_left_menu_btn_, bottom_right_menu_btn_);
        gl::drawStrokedRect(rect1, 2);
        gl::drawStringCentered("Main Menu",
                               glm::vec2(((gui_width * kMenuX1WidthPct) + (gui_width * kMenuX2WidthPct)) / 2,
                                         (((gui_height * kMenuY1HeightPct) + (gui_height * kMenuY2HeightPct)) / 2) - 11),
                               menu_btn_color_, btn_font);
    }

    void CasApp::DrawPauseBtn(const int gui_width, const int gui_height, const Colorf& btn_color, const bool is_paused) {
        top_left_pause_btn_ = glm::vec2(gui_width * kPauseX1WidthPct, gui_height * kPauseY1HeightPct);
        bottom_right_pause_btn_ = glm::vec2(gui_width * kPauseX2WidthPct, gui_height * kPauseY2HeightPct);

        Font btn_font("Roboto", (gui_width + gui_height) * .012f);

        gl::color(btn_color);
        Rectf rect1(top_left_pause_btn_, bottom_right_pause_btn_);
        gl::drawStrokedRect(rect1, 2);
        std::string btn_string = is_paused ? "Resume" : "Pause";
        gl::drawStringCentered(btn_string,
                               glm::vec2(((gui_width * kPauseX1WidthPct) + (gui_width * kPauseX2WidthPct)) / 2,
                                         (((gui_height * kPauseY1HeightPct) + (gui_height * kPauseY2HeightPct)) / 2) - 11),
                               btn_color, btn_font);
    }

    void CasApp::DrawResetBtn(const int gui_width, const int gui_height, const Colorf& btn_color, const bool is_reset) {
        top_left_reset_btn_ = glm::vec2(gui_width * kResetX1WidthPct, gui_height * kResetY1HeightPct);
        bottom_right_reset_btn_ = glm::vec2(gui_width * kResetX2WidthPct, gui_height * kResetY2HeightPct);

        Font btn_font("Roboto", (gui_width + gui_height) * .012f);

        gl::color(btn_color);
        Rectf rect1(top_left_reset_btn_, bottom_right_reset_btn_);
        gl::drawStrokedRect(rect1, 2);
        std::string btn_string = is_reset ? "Begin" : "Reset";
        gl::drawStringCentered(btn_string,
                               glm::vec2(((gui_width * kResetX1WidthPct) + (gui_width * kResetX2WidthPct)) / 2,
                                         (((gui_height * kResetY1HeightPct) + (gui_height * kResetY2HeightPct)) / 2) - 11),
                               btn_color, btn_font);
    }

    void CasApp::DrawSettingsBtn(const int gui_width, const int gui_height, const Colorf& btn_color, const bool is_showing_settings) {
        top_left_settings_btn_ = glm::vec2(gui_width * kSettingsX1WidthPct, gui_height * kSettingsY1HeightPct);
        bottom_right_settings_btn_ = glm::vec2(gui_width * kSettingsX2WidthPct, gui_height * kSettingsY2HeightPct);

        Font btn_font("Roboto", (gui_width + gui_height) * .012f);

        gl::color(btn_color);
        Rectf rect1(top_left_settings_btn_, bottom_right_settings_btn_);
        gl::drawStrokedRect(rect1, 2);

        std::string btn_string, note_string;
        if (is_showing_settings) {
            btn_string = "Close Settings";
            note_string = "    If already closed, toggle \n button in bottom left corner";
            gl::drawStringCentered(btn_string,
                                   glm::vec2(((gui_width * kSettingsX1WidthPct) + (gui_width * kSettingsX2WidthPct)) / 2,
                                             (((gui_height * kSettingsY1HeightPct) + (gui_height * kSettingsY2HeightPct)) / 2) - 31),
                                   btn_color, btn_font);
            gl::drawStringCentered(note_string,
                                   glm::vec2(((gui_width * kSettingsX1WidthPct) + (gui_width * kSettingsX2WidthPct)) / 2,
                                             (((gui_height * kSettingsY1HeightPct) + (gui_height * kSettingsY2HeightPct)) / 2) - 2),
                                   btn_color, Font("Roboto", (gui_width + gui_height) * .008f));
        } else {
            btn_string = "Open Settings";
            gl::drawStringCentered(btn_string,
                                   glm::vec2(((gui_width * kSettingsX1WidthPct) + (gui_width * kSettingsX2WidthPct)) / 2,
                                             (((gui_height * kSettingsY1HeightPct) + (gui_height * kSettingsY2HeightPct)) / 2) - 11),
                                   btn_color, btn_font);
        }
    }

    void CasApp::DrawCycleBtn(const int gui_width, const int gui_height, const Colorf& btn_color, const bool is_in_cycle_mode) {
        top_left_cycle_btn_ = glm::vec2(gui_width * kCycleX1WidthPct, gui_height * kCycleY1HeightPct);
        bottom_right_cycle_btn_ = glm::vec2(gui_width * kCycleX2WidthPct, gui_height * kCycleY2HeightPct);

        Font btn_font("Roboto", (gui_width + gui_height) * .012f);

        gl::color(btn_color);
        Rectf rect1(top_left_cycle_btn_, bottom_right_cycle_btn_);
        gl::drawStrokedRect(rect1, 2);

        std::string btn_string, note_string;
        if (is_in_cycle_mode) {
            btn_string = "Turn Off Cycle Mode";
            gl::drawStringCentered(btn_string,
                                   glm::vec2(((gui_width * kCycleX1WidthPct) + (gui_width * kCycleX2WidthPct)) / 2,
                                             (((gui_height * kCycleY1HeightPct) + (gui_height * kCycleY2HeightPct)) / 2) - 11),
                                   btn_color, btn_font);
        } else {
            btn_string = "Turn On Cycle Mode";
            gl::drawStringCentered(btn_string,
                                   glm::vec2(((gui_width * kCycleX1WidthPct) + (gui_width * kCycleX2WidthPct)) / 2,
                                             (((gui_height * kCycleY1HeightPct) + (gui_height * kCycleY2HeightPct)) / 2) - 11),
                                   btn_color, btn_font);
        }
        if (show_gen_stacking_) {
            note_string = "Cycles through different \n rulesets, cell colors, \n and generation sizes.";
        } else if (show_game_of_life_) {
            note_string = "Cycles through different \n cell colors and \n generation sizes.";
        }
        gl::drawStringCentered(note_string,
                               glm::vec2(.94f * gui_width,(gui_height * kCycleY1HeightPct) + 7),
                               kDefaultBtnColor, Font("Roboto", (gui_width + gui_height) * .008f));
    }

    void CasApp::SetGenStackingSettings() {
        //Setup simulation parameters for Gen Stacking
        settings_->clear();

        settings_->addParam("Ruleset (0 - 255)", &ruleset_).min(0).max(255).step(1).updateFn([this] {
            gen_stacking_gui_.UpdateRuleset(ruleset_);
            gen_stacking_is_in_cycle_mode_ = false;
        });
        settings_->addSeparator();

        settings_->addParam("Live Cell Color", &gen_stacking_live_cell_color_).updateFn([this] {
            gen_stacking_is_in_cycle_mode_  = false;
        });
        settings_->addParam("Dead Cell Color", &gen_stacking_dead_cell_color_).updateFn([this] {
            gen_stacking_is_in_cycle_mode_ = false;
        });
        settings_->addSeparator();

        settings_->addParam("Cells Per Generation (" + std::to_string(min_cells_per_gen_) + " - " + std::to_string(max_cells_per_gen_) + ")",
                            &num_cells_per_gen_).min(min_cells_per_gen_ + 0.0f).max(max_cells_per_gen_ + 0.0f).step(1).updateFn([this] {
            gen_stacking_gui_.UpdateNumCellsPerGen(num_cells_per_gen_, gen_stacking_is_reset_, getWindowWidth(), getWindowHeight());
            gen_stacking_is_in_cycle_mode_ = false;
        });
        settings_->addText("Note 1", "label=`Note: A large change will take a moment to appear.`");
        settings_->addSeparator();

        settings_->addParam("Starting Generation (select one)", starting_gen_options_, &starting_gen_selection_)
                .updateFn([this] {
                    starting_gen_options_[starting_gen_selection_];
                    gen_stacking_gui_.UpdateStartingGen(starting_gen_selection_, num_cells_per_gen_);
                    gen_stacking_is_reset_ = true;
                    gen_stacking_is_in_cycle_mode_ = false;
                });
        settings_->addText("Note 2", "label=`Note: Changing this causes the simulation to reset.`");
        settings_->addSeparator();

        settings_->addText("Note 3", "label=`Note: Changing any settings deactivates cycle mode.`");
    }

    void CasApp::SetGameOfLifeSettings() {
        //Setup simulation parameters for Game of Life
        settings_->clear();

        settings_->addParam("Live Cell Color", &game_of_life_live_cell_color_).updateFn([this] {
            game_of_life_is_in_cycle_mode_ = false;
        });
        settings_->addParam("Dead Cell Color", &game_of_life_dead_cell_color_).updateFn([this] {
            game_of_life_is_in_cycle_mode_ = false;
        });
        settings_->addSeparator();

        settings_->addParam("Cells Per Row (" + std::to_string(min_cells_per_row_) + " - "
                            + std::to_string(max_cells_per_row_) + ")",
                            &num_cells_per_row_).min(min_cells_per_row_ + 0.0f)
                .max(max_cells_per_row_ + 0.0f).step(1).updateFn([this] {
                    game_of_life_gui_.UpdateNumCellsPerRow(num_cells_per_row_);
                    game_of_life_is_in_cycle_mode_ = false;
                });
        settings_->addText("Note 1", "label=`Note: Adds or removes cells from every row of the board.`");
        settings_->addSeparator();

        settings_->addParam("Starting Generation (select one)", starting_board_options_, &starting_board_selection_)
                .updateFn([this] {
                    starting_board_options_[starting_board_selection_];
                    game_of_life_gui_.UpdateStartingBoard(starting_board_selection_);
                    game_of_life_is_reset_ = true;
                    game_of_life_is_in_cycle_mode_ = false;
                });
        settings_->addText("Note 2", "label=`Note: Changing this causes the simulation to reset.`");
        settings_->addSeparator();

        settings_->addText("Note 3", "label=`Note: Changing any settings deactivates cycle mode.`");
    }

    void CasApp::mouseMove(MouseEvent event) {
        int x = event.getPos().x;
        int y = event.getPos().y;

        if (show_main_screen_) {
            MainScreenMouseMove(x, y);
        } else if (show_gen_stacking_) {
            GenStackMouseMove(x, y);
        } else if (show_game_of_life_) {
            GameOfLifeMouseMove(x, y);
        }
    }

    void CasApp::mouseDown(MouseEvent event) {
        int x = event.getPos().x;
        int y = event.getPos().y;

        if (show_main_screen_) {
            MainScreenMouseDown(x, y);
        } else if (show_gen_stacking_) {
            GenStackMouseDown(x, y);
        } else if (show_game_of_life_) {
            GameOfLifeMouseDown(x, y); //handles buttons
            ReviveOrKillCells(x, y, event); //handles board
        }
    }

    void CasApp::mouseUp(MouseEvent event) {
        int x = event.getPos().x;
        int y = event.getPos().y;

        if (show_main_screen_) {
            MainScreenMouseUp(x, y);
        } else if (show_gen_stacking_) {
            GenStackMouseUp(x, y);
        } else if (show_game_of_life_) {
            GameOfLifeMouseUp(x, y);
        }
    }

    void CasApp::mouseDrag(MouseEvent event) {
        int x = event.getPos().x;
        int y = event.getPos().y;

        if (show_game_of_life_) {
            ReviveOrKillCells(x, y, event);
        }
    }

    /* Mouse event helper methods: x, y are mouse coordinates */

    void CasApp::MainScreenMouseMove(const int x, const int y) {
        //if mouse is within bounds of either button, change btn color to hover color, else default
        if (x > main_screen_.GetTopLeft1dBtn().x && x < main_screen_.GetBottomRight1dBtn().x
            && y > main_screen_.GetTopLeft1dBtn().y && y < main_screen_.GetBottomRight1dBtn().y) {
            main_screen_btn1_color_ = kHoverBtnColor;
            main_screen_btn2_color_ = kDefaultBtnColor;
        } else if (x > main_screen_.GetTopLeft2dBtn().x && x < main_screen_.GetBottomRight2dBtn().x
                   && y > main_screen_.GetTopLeft2dBtn().y && y < main_screen_.GetBottomRight2dBtn().y) {
            main_screen_btn2_color_ = kHoverBtnColor;
            main_screen_btn1_color_ = kDefaultBtnColor;
        } else {
            main_screen_btn1_color_ = kDefaultBtnColor;
            main_screen_btn2_color_ = kDefaultBtnColor;
        }
    }

    void CasApp::MainScreenMouseDown(const int x, const int y) {
        //if mouse is clicked within bounds of either button, change boolean for that button to true
        if (x > main_screen_.GetTopLeft1dBtn().x && x < main_screen_.GetBottomRight1dBtn().x
            && y > main_screen_.GetTopLeft1dBtn().y && y < main_screen_.GetBottomRight1dBtn().y) {
            main_screen_btn1_is_pressed_ = true;
            main_screen_btn2_is_pressed_ = false;
        } else if (x > main_screen_.GetTopLeft2dBtn().x && x < main_screen_.GetBottomRight2dBtn().x
                   && y > main_screen_.GetTopLeft2dBtn().y && y < main_screen_.GetBottomRight2dBtn().y) {
            main_screen_btn2_is_pressed_ = true;
            main_screen_btn1_is_pressed_ = false;
        } else {
            main_screen_btn1_is_pressed_ = false;
            main_screen_btn2_is_pressed_ = false;
        }
    }

    void CasApp::MainScreenMouseUp(const int x, const int y) {
        //if mouse is released within bounds of either button, change screen being shown
        if (main_screen_btn1_is_pressed_ && x > main_screen_.GetTopLeft1dBtn().x && x < main_screen_.GetBottomRight1dBtn().x
            && y > main_screen_.GetTopLeft1dBtn().y && y < main_screen_.GetBottomRight1dBtn().y) {
            show_gen_stacking_ = true;
            show_main_screen_ = false;
            SetGenStackingSettings();
        } else if (main_screen_btn2_is_pressed_ && x > main_screen_.GetTopLeft2dBtn().x &&
                   x < main_screen_.GetBottomRight2dBtn().x
                   && y > main_screen_.GetTopLeft2dBtn().y && y < main_screen_.GetBottomRight2dBtn().y) {
            show_game_of_life_ = true;
            show_main_screen_ = false;
            SetGameOfLifeSettings();
        }
        main_screen_btn1_is_pressed_ = false;
        main_screen_btn2_is_pressed_ = false;
    }

    void CasApp::GenStackMouseMove(const int x, const int y) {
        //if mouse is within bounds of menu button, change btn color to hover color, else default
        if (x > top_left_menu_btn_.x && x < bottom_right_menu_btn_.x
            && y > top_left_menu_btn_.y && y < bottom_right_menu_btn_.y) {
            menu_btn_color_ = kHoverBtnColor;
        } else {
            menu_btn_color_ = kDefaultBtnColor;
        }

        //if mouse is within bounds of pause button, change btn color to hover color, else default
        if (x > top_left_pause_btn_.x && x < bottom_right_pause_btn_.x
            && y > top_left_pause_btn_.y && y < bottom_right_pause_btn_.y) {
            gen_stacking_pause_btn_color_ = kHoverBtnColor;
        } else {
            gen_stacking_pause_btn_color_ = kDefaultBtnColor;
        }

        //if mouse is within bounds of reset button, change btn color to hover color, else default
        if (x > top_left_reset_btn_.x && x < bottom_right_reset_btn_.x
            && y > top_left_reset_btn_.y && y < bottom_right_reset_btn_.y) {
            gen_stacking_reset_btn_color_ = kHoverBtnColor;
        } else {
            gen_stacking_reset_btn_color_ = kDefaultBtnColor;
        }

        //if mouse is within bounds of settings button, change btn color to hover color, else default
        if (x > top_left_settings_btn_.x && x < bottom_right_settings_btn_.x
            && y > top_left_settings_btn_.y && y < bottom_right_settings_btn_.y) {
            gen_stacking_settings_btn_color_ = kHoverBtnColor;
        } else {
            gen_stacking_settings_btn_color_ = kDefaultBtnColor;
        }

        //if mouse is within bounds of cycle button, change btn color to hover color, else default
        if (x > top_left_cycle_btn_.x && x < bottom_right_cycle_btn_.x
            && y > top_left_cycle_btn_.y && y < bottom_right_cycle_btn_.y) {
            gen_stacking_cycle_btn_color_ = kHoverBtnColor;
        } else {
            gen_stacking_cycle_btn_color_ = kDefaultBtnColor;
        }
    }

    void CasApp::GenStackMouseDown(const int x, const int y) {
        //if mouse is clicked within bounds of menu or pause button, change menu_btn_is_pressed_ or pause_btn_is_pressed_ to true
        if (x > top_left_menu_btn_.x && x < bottom_right_menu_btn_.x
            && y > top_left_menu_btn_.y && y < bottom_right_menu_btn_.y) {
            menu_btn_is_pressed_ = true;
        } else {
            menu_btn_is_pressed_ = false;
        }

        //if mouse is clicked within bounds of pause button, change gen_stacking_pause_btn_is_pressed_ to true
        if (x > top_left_pause_btn_.x && x < bottom_right_pause_btn_.x
            && y > top_left_pause_btn_.y && y < bottom_right_pause_btn_.y) {
            gen_stacking_pause_btn_is_pressed_ = true;
        } else {
            gen_stacking_pause_btn_is_pressed_ = false;
        }

        //if mouse is clicked within bounds of reset button, change gen_stacking_reset_btn_is_pressed_ to true
        if (x > top_left_reset_btn_.x && x < bottom_right_reset_btn_.x
            && y > top_left_reset_btn_.y && y < bottom_right_reset_btn_.y) {
            gen_stacking_reset_btn_is_pressed_ = true;
        } else {
            gen_stacking_reset_btn_is_pressed_ = false;
        }

        //if mouse is clicked within bounds of settings button, change gen_stacking_settings_btn_is_pressed_ to true
        if (x > top_left_settings_btn_.x && x < bottom_right_settings_btn_.x
            && y > top_left_settings_btn_.y && y < bottom_right_settings_btn_.y) {
            gen_stacking_settings_btn_is_pressed_ = true;
        } else {
            gen_stacking_settings_btn_is_pressed_ = false;
        }

        //if mouse is clicked within bounds of cycle button, change gen_stacking_cycle_btn_is_pressed_ to true
        if (x > top_left_cycle_btn_.x && x < bottom_right_cycle_btn_.x
            && y > top_left_cycle_btn_.y && y < bottom_right_cycle_btn_.y) {
            gen_stacking_cycle_btn_is_pressed_ = true;
        } else {
            gen_stacking_cycle_btn_is_pressed_ = false;
        }
    }

    void CasApp::GenStackMouseUp(const int x, const int y) {
        //if mouse is released within bounds of menu button, change screen to main menu and pause gen stacking
        if (menu_btn_is_pressed_ && x > top_left_menu_btn_.x && x < bottom_right_menu_btn_.x
            && y > top_left_menu_btn_.y && y < bottom_right_menu_btn_.y) {
            show_main_screen_ = true;
            show_gen_stacking_ = false;
            gen_stacking_is_paused_ = true;
        }
        menu_btn_is_pressed_ = false;

        //if mouse is released within bounds of pause button, toggle pause button
        if (gen_stacking_pause_btn_is_pressed_ && x > top_left_pause_btn_.x && x < bottom_right_pause_btn_.x
            && y > top_left_pause_btn_.y && y < bottom_right_pause_btn_.y) {
            gen_stacking_is_paused_ = !gen_stacking_is_paused_;
        }
        gen_stacking_pause_btn_is_pressed_ = false;

        //if mouse is released within bounds of reset button, toggle reset button and reset simulation
        if (gen_stacking_reset_btn_is_pressed_ && x > top_left_reset_btn_.x && x < bottom_right_reset_btn_.x
            && y > top_left_reset_btn_.y && y < bottom_right_reset_btn_.y) {
            if (!gen_stacking_is_reset_) gen_stacking_gui_.UpdateStartingGen(starting_gen_selection_, num_cells_per_gen_);
            gen_stacking_is_reset_ = !gen_stacking_is_reset_;
        }
        gen_stacking_reset_btn_is_pressed_ = false;

        //if mouse is released within bounds of settings button, toggle settings
        if (gen_stacking_settings_btn_is_pressed_ && x > top_left_settings_btn_.x && x < bottom_right_settings_btn_.x
            && y > top_left_settings_btn_.y && y < bottom_right_settings_btn_.y) {
            gen_stacking_is_showing_settings_ = !gen_stacking_is_showing_settings_;
        }
        gen_stacking_settings_btn_is_pressed_ = false;

        //if mouse is released within bounds of cycle button, toggle cycle mode
        if (gen_stacking_cycle_btn_is_pressed_ && x > top_left_cycle_btn_.x && x < bottom_right_cycle_btn_.x
            && y > top_left_cycle_btn_.y && y < bottom_right_cycle_btn_.y) {
            gen_stacking_is_in_cycle_mode_ = !gen_stacking_is_in_cycle_mode_;
        }
        gen_stacking_cycle_btn_is_pressed_ = false;
    }

    void CasApp::GameOfLifeMouseMove(const int x, const int y) {
        //if mouse is within bounds of main menu button, change btn color to hover color, else default
        if (x > top_left_menu_btn_.x && x < bottom_right_menu_btn_.x
            && y > top_left_menu_btn_.y && y < bottom_right_menu_btn_.y) {
            menu_btn_color_ = kHoverBtnColor;
        } else {
            menu_btn_color_ = kDefaultBtnColor;
        }

        //if mouse is within bounds of pause button, change btn color to hover color, else default
        if (x > top_left_pause_btn_.x && x < bottom_right_pause_btn_.x
            && y > top_left_pause_btn_.y && y < bottom_right_pause_btn_.y) {
            game_of_life_pause_btn_color_ = kHoverBtnColor;
        } else {
            game_of_life_pause_btn_color_ = kDefaultBtnColor;
        }

        //if mouse is within bounds of reset button, change btn color to hover color, else default
        if (x > top_left_reset_btn_.x && x < bottom_right_reset_btn_.x
            && y > top_left_reset_btn_.y && y < bottom_right_reset_btn_.y) {
            game_of_life_reset_btn_color_ = kHoverBtnColor;
        } else {
            game_of_life_reset_btn_color_ = kDefaultBtnColor;
        }

        //if mouse is within bounds of settings button, change btn color to hover color, else default
        if (x > top_left_settings_btn_.x && x < bottom_right_settings_btn_.x
            && y > top_left_settings_btn_.y && y < bottom_right_settings_btn_.y) {
            game_of_life_settings_btn_color_ = kHoverBtnColor;
        } else {
            game_of_life_settings_btn_color_ = kDefaultBtnColor;
        }

        //if mouse is within bounds of cycle button, change btn color to hover color, else default
        if (x > top_left_cycle_btn_.x && x < bottom_right_cycle_btn_.x
            && y > top_left_cycle_btn_.y && y < bottom_right_cycle_btn_.y) {
            game_of_life_cycle_btn_color_ = kHoverBtnColor;
        } else {
            game_of_life_cycle_btn_color_ = kDefaultBtnColor;
        }
    }

    void CasApp::GameOfLifeMouseDown(const int x, const int y) {
        //if mouse is clicked within bounds of main menu button, change menu_btn_is_pressed_ to true
        if (x > top_left_menu_btn_.x && x < bottom_right_menu_btn_.x
            && y > top_left_menu_btn_.y && y < bottom_right_menu_btn_.y) {
            menu_btn_is_pressed_ = true;
        } else {
            menu_btn_is_pressed_ = false;
        }

        //if mouse is clicked within bounds of pause button, change game_of_life_pause_btn_is_pressed_ to true
        if (x > top_left_pause_btn_.x && x < bottom_right_pause_btn_.x
            && y > top_left_pause_btn_.y && y < bottom_right_pause_btn_.y) {
            game_of_life_pause_btn_is_pressed_ = true;
        } else {
            game_of_life_pause_btn_is_pressed_ = false;
        }

        //if mouse is clicked within bounds of reset button, change game_of_life_reset_btn_is_pressed_ to true
        if (x > top_left_reset_btn_.x && x < bottom_right_reset_btn_.x
            && y > top_left_reset_btn_.y && y < bottom_right_reset_btn_.y) {
            game_of_life_reset_btn_is_pressed_ = true;
        } else {
            game_of_life_reset_btn_is_pressed_ = false;
        }

        //if mouse is clicked within bounds of settings button, change game_of_life_settings_btn_is_pressed_ to true
        if (x > top_left_settings_btn_.x && x < bottom_right_settings_btn_.x
            && y > top_left_settings_btn_.y && y < bottom_right_settings_btn_.y) {
            game_of_life_settings_btn_is_pressed_ = true;
        } else {
            game_of_life_settings_btn_is_pressed_ = false;
        }

        //if mouse is clicked within bounds of cycle button, change game_of_life_cycle_btn_is_pressed_ to true
        if (x > top_left_cycle_btn_.x && x < bottom_right_cycle_btn_.x
            && y > top_left_cycle_btn_.y && y < bottom_right_cycle_btn_.y) {
            game_of_life_cycle_btn_is_pressed_ = true;
        } else {
            game_of_life_cycle_btn_is_pressed_ = false;
        }

        glm::vec2 top_left = glm::vec2(top_left_cell_width_pct_ * getWindowWidth(), top_left_cell_height_pct_ * getWindowHeight());
        //if mouse is being clicked/dragged within bounds of board, temporarily stop updating
        if (x > top_left.x && x < getWindowWidth() && y > top_left.y && y < getWindowHeight()) {
            cells_being_revived_or_killed_ = true;
        }
    }

    void CasApp::GameOfLifeMouseUp(const int x, const int y) {
        //if mouse is released within bounds of menu button, change screen to main menu and pause game of life
        if (menu_btn_is_pressed_ && x > top_left_menu_btn_.x && x < bottom_right_menu_btn_.x
            && y > top_left_menu_btn_.y && y < bottom_right_menu_btn_.y) {
            show_main_screen_ = true;
            show_game_of_life_ = false;
            game_of_life_is_paused_ = true;
        }
        menu_btn_is_pressed_ = false;

        //if mouse is released within bounds of pause button, toggle pause button
        if (game_of_life_pause_btn_is_pressed_ && x > top_left_pause_btn_.x && x < bottom_right_pause_btn_.x
            && y > top_left_pause_btn_.y && y < bottom_right_pause_btn_.y) {
            game_of_life_is_paused_ = !game_of_life_is_paused_;
        }
        game_of_life_pause_btn_is_pressed_ = false;

        //if mouse is released within bounds of reset button, toggle reset button
        if (game_of_life_reset_btn_is_pressed_ && x > top_left_reset_btn_.x && x < bottom_right_reset_btn_.x
            && y > top_left_reset_btn_.y && y < bottom_right_reset_btn_.y) {
            if (!game_of_life_is_reset_) game_of_life_gui_.UpdateStartingBoard(starting_board_selection_);
            game_of_life_is_reset_ = !game_of_life_is_reset_;
        }
        game_of_life_reset_btn_is_pressed_ = false;

        //if mouse is released within bounds of settings button, toggle settings
        if (game_of_life_settings_btn_is_pressed_ && x > top_left_settings_btn_.x && x < bottom_right_settings_btn_.x
            && y > top_left_settings_btn_.y && y < bottom_right_settings_btn_.y) {
            game_of_life_is_showing_settings_ = !game_of_life_is_showing_settings_;
        }
        game_of_life_settings_btn_is_pressed_ = false;

        //if mouse is released within bounds of cycle button, toggle cycle mode
        if (game_of_life_cycle_btn_is_pressed_ && x > top_left_cycle_btn_.x && x < bottom_right_cycle_btn_.x
            && y > top_left_cycle_btn_.y && y < bottom_right_cycle_btn_.y) {
            game_of_life_is_in_cycle_mode_ = !game_of_life_is_in_cycle_mode_;
        }
        game_of_life_cycle_btn_is_pressed_ = false;

        glm::vec2 top_left = glm::vec2(top_left_cell_width_pct_ * getWindowWidth(), top_left_cell_height_pct_ * getWindowHeight());
        //if mouse is released within bounds of board, can update again
        if (x > top_left.x && x < getWindowWidth() && y > top_left.y && y < getWindowHeight()) {
            cells_being_revived_or_killed_ = false;
        }
    }

    void CasApp::ReviveOrKillCells(int x, int y, const MouseEvent& event) {
        // Handles reviving/killing of cells
        glm::vec2 top_left = glm::vec2(top_left_cell_width_pct_ * getWindowWidth(), top_left_cell_height_pct_ * getWindowHeight());
        float cell_width;
        if (game_of_life_is_in_cycle_mode_) {
            cell_width = (getWindowWidth() + 0.0f) / game_of_life_gui_.GetNumCellsPerRowCycle();
        } else {
            cell_width = (getWindowWidth() + 0.0f) / num_cells_per_row_;
        }

        //if mouse is being clicked/dragged within bounds of board
        if (x > top_left.x && x < getWindowWidth() && y > top_left.y && y < getWindowHeight()) {
            //mouse coords -> board index = mouse coords / cell width
            int row_index = (int) ((y - top_left.y) / cell_width);
            int col_index = (int) (x / cell_width);
            if (event.isLeftDown()) {
                game_of_life_gui_.ReviveOrKillCells(row_index, col_index, true);
            } else if (event.isRightDown()) {
                game_of_life_gui_.ReviveOrKillCells(row_index, col_index, false);
            }
        }
    }
}