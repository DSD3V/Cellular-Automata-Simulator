#pragma once

#include "cinder/gl/gl.h"

using namespace ci;

namespace cas {
    class MainScreen {
        public:
            /* Draws the main screen using parameters passed in from parent class */
            void DrawMainScreen(int gui_width, int gui_height, const Colorf& btn1_color, const Colorf& btn2_color);
    
            /* Clears the main screen; called when GUI needs to display a different screen */
            void Clear();
    
            /* Getters */
            const glm::vec2& GetTopLeft1dBtn();
            const glm::vec2& GetBottomRight1dBtn();
            const glm::vec2& GetTopLeft2dBtn();
            const glm::vec2& GetBottomRight2dBtn();
    
        private:
            /* Drawing Helper Methods */
            void DrawButtons(int gui_width, int gui_height, const Colorf& btn1_color, const Colorf& btn2_color);
    
            /* Stores positions of top left and bottom right of each of main screen buttons, stored so parent
             * knows when button is being hovered over / clicked */
            glm::vec2 top_left_1d_btn_;
            glm::vec2 bottom_right_1d_btn_;
            glm::vec2 top_left_2d_btn_;
            glm::vec2 bottom_right_2d_btn_;
    
            /* x1, x2 are percent of gui width for location of sides of main screen button 1
             * y1, y2 are percent of gui height for location of top and bottom of main screen button 1 */
            const float kX1WidthPct = .15f;
            const float kX2WidthPct = .40f;
            const float kY1HeightPct = .25f;
            const float kY2HeightPct = .80f;
    };
}