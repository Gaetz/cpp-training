#include "state_game.h"
#include "../core/state_manager.h"

State_Game::State_Game(StateManager *stateManager) : BaseState(stateManager) {}

State_Game::~State_Game() {}

void State_Game::onCreate()
{
    // View setup
    sf::Vector2u viewSize = mStateManager->getContext()->mWindow->getWindowSize();
    mView.setSize(viewSize.x, viewSize.y);
    mView.setCenter(viewSize.x / 2, viewSize.y / 2);
    mView.zoom(1.0f);
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

    evMgr->addCallback(StateType::Game, "Player_MoveLeft", &State_Game::playerMove, this);
    evMgr->addCallback(StateType::Game, "Player_MoveRight", &State_Game::playerMove, this);
    evMgr->addCallback(StateType::Game, "Player_MoveUp", &State_Game::playerMove, this);
    evMgr->addCallback(StateType::Game, "Player_MoveDown", &State_Game::playerMove, this);

    EntityManager* entities = mStateManager->getContext()->mEntityManager;
    //m_stateMgr->GetContext()->m_systemManager->GetSystem<S_Collision>(System::Collision)->SetMap(m_gameMap);
    mStateManager->getContext()->mSystemManager->getSystem<S_Movement>(System::Movement)->setMap(mGameMap);
    mPlayer = mGameMap->getPlayerId();
}

void State_Game::onDestroy()
{
    EventManager *evMgr = mStateManager->getContext()->mEventManager;
    evMgr->removeCallback(StateType::Game, "KeyEscape");
    evMgr->removeCallback(StateType::Game, "KeyP");
    evMgr->removeCallback(StateType::Game, "KeyO");

    evMgr->removeCallback(StateType::Game, "Player_MoveLeft");
    evMgr->removeCallback(StateType::Game, "Player_MoveRight");
    evMgr->removeCallback(StateType::Game, "Player_MoveUp");
    evMgr->removeCallback(StateType::Game, "Player_MoveDown");

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
    updateCamera();
    mGameMap->update(time.asSeconds());
    context->mSystemManager->update(time.asSeconds());
}

void State_Game::updateCamera()
{
    if(mPlayer == -1)
        return;
    SharedContext* context = mStateManager->getContext();
    C_Position* pos = mStateManager->getContext()->mEntityManager->getComponent<C_Position>(mPlayer, Component::Position);

    mView.setCenter(pos->getPosition());
    context->mWindow->getRenderWindow()->setView(mView);

    sf::FloatRect viewSpace = context->mWindow->getViewSpace();
    // View space right and left limits
    if(viewSpace.left <= 0) {
        mView.setCenter(viewSpace.width / 2, mView.getCenter().y);
        context->mWindow->getRenderWindow()->setView(mView);
    } else if(viewSpace.left + viewSpace.width > mGameMap->getMapSize().x * Sheet::TileSize) {
        mView.setCenter(mGameMap->getMapSize().x * Sheet::TileSize - viewSpace.width / 2, mView.getCenter().y);
        context->mWindow->getRenderWindow()->setView(mView);
    }
    // View space top and bottom limits
    if(viewSpace.top <= 0) {
        mView.setCenter(mView.getCenter().x, viewSpace.height / 2);
        context->mWindow->getRenderWindow()->setView(mView);
    } else if(viewSpace.top + viewSpace.height > mGameMap->getMapSize().y * Sheet::TileSize) {
        mView.setCenter(mView.getCenter().x, mGameMap->getMapSize().y * Sheet::TileSize - viewSpace.height / 2);
        context->mWindow->getRenderWindow()->setView(mView);
    }
}

void State_Game::playerMove(EventDetails *details)
{
    Message message((MessageType)EntityMessage::Move);
    if(details->mName == "Player_MoveLeft") {
        message.mInt = (int)Direction::Left;
    } else if(details->mName == "Player_MoveRight") {
        message.mInt = (int)Direction::Right;
    } else if(details->mName == "Player_MoveUp") {
        message.mInt = (int)Direction::Up;
    } else if(details->mName == "Player_MoveDown") {
        message.mInt = (int)Direction::Down;
    }
    message.mReceiver = mPlayer;
    mStateManager->getContext()->mSystemManager->getMessageHandler()->dispatch(message);
}

void State_Game::draw()
{
    for(unsigned int i = 0; i < Sheet::NumLayer; ++i)
    {
        mGameMap->draw(i);
        mStateManager->getContext()->mSystemManager->draw(mStateManager->getContext()->mWindow, i);
    }
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
