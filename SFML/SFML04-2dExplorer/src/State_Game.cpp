#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager *stateManager) : BaseState(stateManager) {}

State_Game::~State_Game() {}

void State_Game::onCreate()
{
    // View setup
    sf::Vector2u viewSize = mStateManager->getContext()->mWindow->getWindowSize();
    mView.setSize(viewSize.x, viewSize.y);
    mView.setCenter(viewSize.x / 2, 120); // viewSize.y / 2
    mView.zoom(0.6f);
    mStateManager->getContext()->mWindow->getRenderWindow()->setView(mView);

    // Map load
    mGameMap = new Map(mStateManager->getContext(), this);
    mGameMap->loadMap("assets/data/maps/map1.map");

    // Tutorail text
    mFont.loadFromFile("assets/arial.ttf");
    mText.setFont(mFont);
    mText.setFillColor(sf::Color(100, 100, 100));
    mText.setString({L"Shift gauche: contrôle souris | Echap: menu"});
    mText.setCharacterSize(18);
    sf::FloatRect textRect = mText.getLocalBounds();
    mText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    mText.setPosition(mStateManager->getContext()->mWindow->getWindowSize().x * 0.75f, mStateManager->getContext()->mWindow->getWindowSize().y - 20);

    // Callback setup
    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->addCallback(StateType::Game, "KeyEscape", &State_Game::stateMainMenu, this);
    evMgr->addCallback(StateType::Game, "KeyP", &State_Game::statePaused, this);
    evMgr->addCallback(StateType::Game, "KeyO", &State_Game::toggleOverlay, this);
}

void State_Game::onDestroy()
{
    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->removeCallback(StateType::Game, "KeyEscape");
    evMgr->removeCallback(StateType::Game, "KeyP");
    evMgr->removeCallback(StateType::Game, "KeyO");

    delete mGameMap;
    mGameMap = nullptr;
}

void State_Game::activate()
{

}

void State_Game::deactivate()
{

}

void State_Game::update(const sf::Time &time)
{
    SharedContext* context = mStateManager->getContext();
    EntityBase* player = context->mEntityManager->find("Player");
    if(!player) {
        /*std::cout << "Respawning player" << std::endl;
        context->mEntityManager->add(EntityType::Player, "Player");
        player = context->mEntityManager->find("Player");
        player->setPosition(mGameMap->getPlayerStart());*/
    } else {
        mView.setCenter(sf::Vector2f(player->getPosition().x, mView.getCenter().y)); // Formerly player->getPosition();
        context->mWindow->getRenderWindow()->setView(mView);
    }

    sf::FloatRect viewSpace = context->mWindow->getViewSpace();
    if(viewSpace.left <= 0){
        mView.setCenter(viewSpace.width / 2, mView.getCenter().y);
        context->mWindow->getRenderWindow()->setView(mView);
    } else if (viewSpace.left + viewSpace.width > (mGameMap->getMapSize().x + 1) * Sheet::TileSize){
        mView.setCenter(((mGameMap->getMapSize().x + 1) * Sheet::TileSize) - (viewSpace.width / 2), mView.getCenter().y);
        context->mWindow->getRenderWindow()->setView(mView);
    }

    mGameMap->update(time.asSeconds());
    mStateManager->getContext()->mEntityManager->update(time.asSeconds());
}

void State_Game::draw()
{
    mGameMap->draw();
    mStateManager->getContext()->mEntityManager->draw();
}

void State_Game::stateMainMenu(EventDetails *details)
{
    mStateManager->switchTo(StateType::MainMenu);
}

void State_Game::statePaused(EventDetails *details)
{
    mStateManager->switchTo(StateType::Paused);
}

void State_Game::toggleOverlay(EventDetails* details){
    mStateManager->getContext()->mDebugOverlay.setDebug(!mStateManager->getContext()->mDebugOverlay.debug());
}
