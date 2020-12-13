#include "gui/main_screen.h"

using namespace ci;

namespace cas {
    void MainScreen::DrawMainScreen(const int gui_width, const int gui_height, const Colorf& btn1_color, const Colorf& btn2_color) {
        DrawButtons(gui_width, gui_height, btn1_color, btn2_color);
    }

    void MainScreen::DrawButtons(const int gui_width, const int gui_height, const Colorf& btn1_color, const Colorf& btn2_color) {
        //Update button coordinates based on current gui width and height passed in from parent class
        top_left_1d_btn_ = glm::vec2(gui_width * kX1WidthPct, gui_height * kY1HeightPct);
        bottom_right_1d_btn_ = glm::vec2(gui_width * kX2WidthPct, gui_height * kY2HeightPct);
        top_left_2d_btn_ = glm::vec2(gui_width * (1 - kX2WidthPct), gui_height * kY1HeightPct);
        bottom_right_2d_btn_ = glm::vec2(gui_width * (1 - kX1WidthPct), gui_height * kY2HeightPct);

        Font btn_font("Roboto", (gui_width + gui_height) * .021f);

        //Draw first button
        gl::color(btn1_color);
        Rectf rect1(top_left_1d_btn_, bottom_right_1d_btn_);
        gl::drawStrokedRect(rect1, 5);
        gl::drawStringCentered("1-D",
                               glm::vec2(((gui_width * kX1WidthPct) + (gui_width * kX2WidthPct)) / 2,
                                         (gui_height * kY1HeightPct) + 20),
                               btn1_color, btn_font);
        gl::drawStringCentered("Generation",
                               glm::vec2(((gui_width * kX1WidthPct) + (gui_width * kX2WidthPct)) / 2,
                                         ((gui_height * kY1HeightPct) + (gui_height * kY2HeightPct)) / 2),
                               btn1_color, btn_font);
        gl::drawStringCentered("Stacking",
                               glm::vec2(((gui_width * kX1WidthPct) + (gui_width * kX2WidthPct)) / 2,
                                         (((gui_height * kY1HeightPct) + (gui_height * kY2HeightPct)) / 2) * 1.10f),
                               btn1_color, btn_font);

        //Draw second button
        gl::color(btn2_color);
        Rectf rect2(top_left_2d_btn_, bottom_right_2d_btn_);
        gl::drawStrokedRect(rect2, 5);
        gl::drawStringCentered("2-D",
                               glm::vec2(((gui_width * (1 - kX1WidthPct)) + (gui_width * (1 - kX2WidthPct))) / 2,
                                         (gui_height * kY1HeightPct) + 20),
                               btn2_color, btn_font);
        gl::drawStringCentered("Game of Life",
                               glm::vec2(((gui_width * (1 - kX1WidthPct)) + (gui_width * (1 - kX2WidthPct))) / 2,
                                         ((gui_height * kY1HeightPct) + (gui_height * kY2HeightPct)) / 2),
                               btn2_color, btn_font);
    }

    void MainScreen::Clear() { gl::clear(); }

    /* Getters */
    const glm::vec2& MainScreen::GetTopLeft1dBtn() { return top_left_1d_btn_; }
    const glm::vec2& MainScreen::GetBottomRight1dBtn() { return bottom_right_1d_btn_; }
    const glm::vec2& MainScreen::GetTopLeft2dBtn() { return top_left_2d_btn_; }
    const glm::vec2& MainScreen::GetBottomRight2dBtn() { return bottom_right_2d_btn_; }
}