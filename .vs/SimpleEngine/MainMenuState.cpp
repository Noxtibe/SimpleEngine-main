#include "MainMenuState.h"
MainMenuState::MainMenuState(std::shared_ptr<Renderer> r)
{
    renderer = std::move(r);
    renderer->initializeMainMenu();
}

void MainMenuState::update() {
    // update is handled by handleEvent() mostly
}

void MainMenuState::display() {
    SDL_RenderClear(renderer->getRenderer());

    renderer->drawMenuTitle();
    renderer->drawMenuItems(highlightedPosition);

    SDL_RenderPresent(renderer->getRenderer());
}

void MainMenuState::handleEvent() {
    switch (inputManager.handle()) {
    case QUIT_GAME:
        active = false;
        break;
    case ENTER:
        selectedItem = highlightedPosition;
        break;
    case MOVE_DOWN:
        highlightedPosition = 1;
        break;
    case MOVE_UP:
        highlightedPosition = 0;
        break;
    default:
        return;
    }
}

std::unique_ptr<GameState> MainMenuState::nextState()
{
    if (selectedItem == 0)
    {
        std::unique_ptr<GameState> nextState(new PlayingState(renderer));
        renderer->destroyMainMenu();
        return nextState;
    }

    else if (selectedItem == 1)
    {
        active = false;
    }

    return nullptr;
}