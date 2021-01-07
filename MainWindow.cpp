#include "MainWindow.h"
#include "Bullet.h"
#include "WallBlock.h"
#include "Constants.h"

#include <iostream>

#include <future>
#include <thread>


MainWindow::MainWindow()
    : mAngelSlider(sf::Vector2f(Constants::WINDOW_WIDTH - Constants::WINDOW_MENU_WIDTH + Constants::WINDOW_MENU_PADDING, 30), Constants::ANGEL_SLIDER_LABEL),
      mSpeedSlider(sf::Vector2f(Constants::WINDOW_WIDTH - Constants::WINDOW_MENU_WIDTH + Constants::WINDOW_MENU_PADDING, 70), Constants::SPEED_SLIDER_LABEL),
      mDelaySlider(sf::Vector2f(Constants::WINDOW_WIDTH - Constants::WINDOW_MENU_WIDTH + Constants::WINDOW_MENU_PADDING, 110), Constants::DELAY_SLIDER_LABEL),
      mLifeTimeSlider(sf::Vector2f(Constants::WINDOW_WIDTH - Constants::WINDOW_MENU_WIDTH + Constants::WINDOW_MENU_PADDING, 150), Constants::LIFETIME_SLIDER_LABEL),
      mResetWallButton(sf::Vector2f(Constants::WINDOW_GAME_WIDTH + Constants::WINDOW_MENU_WIDTH / 2, Constants::WINDOW_HEIGHT - 40), Constants::BUTTON_RESET_LABEL),
      mBulletManager(),
      mWallManager(Constants::BLOCK_COUNT, Constants::BLOCK_WIDTH, Constants::BLOCK_HEIGHT),
      mThreadManager()
{
    mWindow.create(VideoMode(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT), Constants::WINDOW_LABEL);

    mResetWallButton.setClickCallback([&]() {
            mWallManager.reset();
        });
    
    mAngelSlider.create(Constants::MIN_ENGEL, Constants::MAX_ENGEL);
    mSpeedSlider.create(Constants::MIN_SPEED, Constants::MAX_SPEED);
    mDelaySlider.create(Constants::MIN_DELAYTIME, Constants::MAX_DELAYTIME);
    mLifeTimeSlider.create(Constants::MIN_LIFETIME, Constants::MAX_LIFETIME);
}

void MainWindow::start()
{
    Clock clock;

    while (mWindow.isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        input();
        update(dt);
        draw();
    }
}

void MainWindow::input()
{
    sf::Event event;
    while ( mWindow.pollEvent(event) )
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(mWindow);

        mAngelSlider.input(event, mousePosition);
        mSpeedSlider.input(event, mousePosition);
        mDelaySlider.input(event, mousePosition);
        mLifeTimeSlider.input(event, mousePosition);

        mResetWallButton.input(event, mousePosition);

        switch (event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (mousePosition.x > Constants::WINDOW_WIDTH - Constants::WINDOW_MENU_WIDTH)
                {
                    break;
                }

                mThreadManager.addTask( std::move(std::packaged_task<void()>( [&]() {
                        mBulletManager.fire( mousePosition.x - Constants::BULLET_RADIUS,
                                             mousePosition.y - Constants::BULLET_RADIUS,
                                             mAngelSlider.getValue(), 
                                             mSpeedSlider.getValue(),
                                             mDelaySlider.getValue(), 
                                             mLifeTimeSlider.getValue());
                    } ) ) );

                break;
        }
    }
}

void MainWindow::update(float dt)
{
    mBulletManager.update(dt);

    mBulletManager.checkColisions(mWallManager.getWallBlocks());
    mWallManager.checkColisions(mBulletManager.getBullets());
}

void MainWindow::draw()
{
    mWindow.clear(Constants::BACKGROUND_COLOR);

    sf::CircleShape bullet(Constants::BULLET_RADIUS);
    bullet.setFillColor(Constants::BULLET_COLOR);
    auto bullets = mBulletManager.getBullets();

    for (auto it = bullets.begin(); it != bullets.end(); ++it)
    {
        bullet.setPosition(it->getPosition());
        mWindow.draw(bullet);
    }

    sf::RectangleShape block(sf::Vector2f(Constants::BLOCK_WIDTH, Constants::BLOCK_HEIGHT));
    auto bloks = mWallManager.getWallBlocks();

    for (int i = 0; i < bloks.size(); ++i)
    {
        if (bloks[i].isBroken())
            continue;

        block.setFillColor(i % 2 == 0 ? Constants::BLOCK_COLOR_1 : Constants::BLOCK_COLOR_2);
        block.setPosition(bloks[i].getPosition());
        
        mWindow.draw(block);
    }

    sf::RectangleShape menuBackground(sf::Vector2f(Constants::WINDOW_MENU_WIDTH, Constants::WINDOW_HEIGHT));
    menuBackground.setPosition(Constants::WINDOW_GAME_WIDTH, 0);
    menuBackground.setFillColor(Constants::MENU_BACKGROUND_COLOR);

    mWindow.draw(menuBackground);

    mWindow.draw(mAngelSlider);
    mWindow.draw(mSpeedSlider);
    mWindow.draw(mDelaySlider);
    mWindow.draw(mLifeTimeSlider);

    mWindow.draw(mResetWallButton);

    mWindow.display();
}