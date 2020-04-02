#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager *stateManager) : BaseState(stateManager) {}

State_MainMenu::~State_MainMenu() {}

void State_MainMenu::onCreate()
{
    mFont.loadFromFile("arial.ttf");
    mText.setFont(mFont);
    mText.setString(sf::String("Menu principal"));
    mText.setCharacterSize(18);

    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    mText.setPosition(400, 100);
    mButtonSize = sf::Vector2f(300.0f, 32.0f);
    mButtonPosition = sf::Vector2f(400.0f, 200.0f);
    mButtonPadding = 4;

    std::string str[3];
    str[0] = "Jouer";
    str[1] = "Credits";
    str[2] = "Quitter";

    for (int i = 0; i < 3; ++i)
    {
        sf::Vector2f buttonPosition(mButtonPosition.x, mButtonPosition.y + (i * (mButtonSize.y + mButtonPadding)));
        mRects[i].setSize(mButtonSize);
        mRects[i].setFillColor(sf::Color::Yellow);
        mRects[i].setOrigin(mButtonSize.x / 2.0f, mButtonSize.y / 2.0f);
        mRects[i].setPosition(buttonPosition);

        mLabels[i].setFont(mFont);
        mLabels[i].setFillColor(sf::Color::Black);
        mLabels[i].setString(sf::String(str[i]));
        mLabels[i].setCharacterSize(18);
        sf::FloatRect rect = mLabels[i].getLocalBounds();
        mLabels[i].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
        mLabels[i].setPosition(buttonPosition);
    }

    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->addCallback(StateType::MainMenu, "mainmenu_mouseLeft", &State_MainMenu::mouseClick, this);
    evMgr->addCallback(StateType::MainMenu, "intro_carryOn", &State_MainMenu::quickStart, this);
}

void State_MainMenu::onDestroy()
{
    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->removeCallback(StateType::MainMenu, "mainmenu_mouseLeft");
    evMgr->removeCallback(StateType::MainMenu, "intro_carryOn");
}

void State_MainMenu::activate()
{
    // Change the first button name if Game state already exists
    if (mStateManager->hasState(StateType::Game) && mLabels[0].getString() == "Jouer")
    {
        mLabels[0].setString("Reprendre");
        // Origin is reset by modifying text
        sf::FloatRect rect = mLabels[0].getLocalBounds();
        mLabels[0].setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    }
}

void State_MainMenu::deactivate() {}

void State_MainMenu::mouseClick(EventDetails *details)
{
    sf::Vector2i mousePosition = details->mMouse;

    float halfX = mButtonSize.x / 2.0f;
    float halfY = mButtonSize.y / 2.0f;
    for (int i = 0; i < 3; ++i)
    {
        if (mousePosition.x >= mRects[i].getPosition().x - halfX &&
            mousePosition.x <= mRects[i].getPosition().x + halfX &&
            mousePosition.y >= mRects[i].getPosition().y - halfY &&
            mousePosition.y <= mRects[i].getPosition().y + halfY)
        {
            switch (i)
            {
            case 0:
                // Game
                mStateManager->switchTo(StateType::Game);
                break;
            case 1:
                // Credits
                break;
            case 2:
                // Quit
                mStateManager->getContext()->mWindow->close();
                break;
            }
        }
    }
}

void State_MainMenu::quickStart(EventDetails *details)
{
    mStateManager->switchTo(StateType::Game);
}

void State_MainMenu::quickResume(EventDetails *details)
{
    if (mStateManager->hasState(StateType::Game))
    {
        mStateManager->switchTo(StateType::Game);
    }
}

void State_MainMenu::update(const sf::Time &time) {}

void State_MainMenu::draw()
{
    sf::RenderWindow *window = mStateManager->getContext()->mWindow->getRenderWindow();
    window->draw(mText);
    for (int i = 0; i < 3; ++i)
    {
        window->draw(mRects[i]);
        window->draw(mLabels[i]);
    }
}