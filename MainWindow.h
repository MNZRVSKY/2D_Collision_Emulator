#pragma once
#include <SFML/Graphics.hpp>
#include "BulletManager.h"
#include "WallManager.h"
#include "TaskManager.h"
#include "Slider.h"
#include "Button.h"

using namespace sf;


class MainWindow
{
public:
    MainWindow();

    void start();

private:
    RenderWindow mWindow;

    UI::Slider mAngelSlider;
    UI::Slider mSpeedSlider;
    UI::Slider mDelaySlider;
    UI::Slider mLifeTimeSlider;
    UI::Button mResetWallButton;

    BulletManager mBulletManager;
    WallManager mWallManager;
    TaskManager mThreadManager;

    void input();
    void update(float dt);
    void draw();

};
