#include "gui/cas_app.h"

using cas::CasApp;

void prepareSettings(CasApp::Settings* settings) {
    settings->setWindowSize(1300, 900);
    settings->setFrameRate(60.0f);
}

CINDER_APP(CasApp, ci::app::RendererGl, prepareSettings)