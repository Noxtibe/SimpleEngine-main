#include "Renderer.h"
void Renderer::initialize()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    FONT_LARGE = TTF_OpenFont("../res/fonts/DIGDUG.ttf", 100);
    FONT_SMALL = TTF_OpenFont("../res/fonts/barcadbold.ttf", 50);
    FONT_SCORE = TTF_OpenFont("../res/fonts/digital-7.ttf", 28);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cout << "Could not initialize SDL Images: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    if (window == nullptr) {
        std::cout << "Could not create window" << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
}

void Renderer::initializeMainMenu()
{

    menuItemOneWhite = TTF_RenderText_Solid(FONT_SMALL, "New Game", COLOR_WHITE);
    menuItemOneGreen = TTF_RenderText_Solid(FONT_SMALL, "New Game", COLOR_GREEN);

    menuItemTwoWhite = TTF_RenderText_Solid(FONT_SMALL, "Exit", COLOR_WHITE);
    menuItemTwoGreen = TTF_RenderText_Solid(FONT_SMALL, "Exit", COLOR_GREEN);

    menuItemOneWhiteTexture = SDL_CreateTextureFromSurface(renderer, menuItemOneWhite);
    menuItemOneGreenTexture = SDL_CreateTextureFromSurface(renderer, menuItemOneGreen);
    menuItemTwoGreenTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwoGreen);
    menuItemTwoWhiteTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwoWhite);

    titleSurface = TTF_RenderText_Solid(FONT_LARGE, "BRICKBREAKER", COLOR_WHITE);
    titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);

    SDL_QueryTexture(titleTexture, nullptr, nullptr, &titleWidth, &titleHeight);
    titlePosition = { WIDTH / 2 - titleSurface->w / 2, titleSurface->h - HEIGHT / 6, titleWidth, titleHeight };

    menuItemOneText = TTF_RenderText_Solid(FONT_SMALL, "New Game", COLOR_WHITE);
    menuItemOneTextTexture = SDL_CreateTextureFromSurface(renderer, menuItemOneText);

    menuItemTwoText = TTF_RenderText_Solid(FONT_SMALL, "Exit", COLOR_GREEN);
    menuItemTwoTextTexture = SDL_CreateTextureFromSurface(renderer, menuItemTwoText);

    int menuItemHeight = menuItemOneText->clip_rect.h;
    int positioningHeight = HEIGHT / 3;

    SDL_QueryTexture(menuItemOneTextTexture, nullptr, nullptr, &menuItems[0], &menuItems[0 + 1]);
    SDL_QueryTexture(menuItemTwoTextTexture, nullptr, nullptr, &menuItems[1], &menuItems[1 + 1]);

    firstOptionPosition = {
            WIDTH / 2 - menuItemOneText->clip_rect.w / 2,
            positioningHeight,
            menuItems[0],
            menuItems[0 + 1]
    };
    secondOptionPosition = {
            WIDTH / 2 - menuItemTwoText->clip_rect.w / 2,
            positioningHeight + menuItemHeight * 2,
            menuItems[1],
            menuItems[0 + 1]
    };

}

void Renderer::drawMenuItems(int highlightedItem)
{
    if (highlightedItem == 0)
    {
        SDL_RenderCopy(renderer, menuItemOneGreenTexture, nullptr, &firstOptionPosition);
        SDL_RenderCopy(renderer, menuItemTwoWhiteTexture, nullptr, &secondOptionPosition);
    }
    else {
        SDL_RenderCopy(renderer, menuItemOneWhiteTexture, nullptr, &firstOptionPosition);
        SDL_RenderCopy(renderer, menuItemTwoGreenTexture, nullptr, &secondOptionPosition);
    }
}

void Renderer::drawMenuTitle()
{
    SDL_RenderCopy(renderer, titleTexture, nullptr, &titlePosition);
}

void Renderer::initializeGame()
{
    ballSurface = IMG_Load("../res/images/ballBlue.png");
    paddleSurface = IMG_Load("../res/images/paddleRed.png");
    heartSurface = IMG_Load("../res/images/health.png");

    if (paddleSurface == nullptr || ballSurface == nullptr || heartSurface == nullptr)
    {
        std::cout << "SDL_Image Error: " << SDL_GetError() << std::endl;
        return;
    }

    brickSurfaceVector.push_back(IMG_Load("../res/images/rectGreen.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectBlue.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectYellow.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectRed.png"));
    brickSurfaceVector.push_back(IMG_Load("../res/images/rectPurple.png"));

    std::for_each(brickSurfaceVector.begin(), brickSurfaceVector.end(), [this](SDL_Surface* surface)
        {
            if (surface == nullptr)
            {
                std::cout << "SDL_Image Error: " << SDL_GetError() << std::endl;
                return;
            }
            brickTextureVector.push_back(SDL_CreateTextureFromSurface(renderer, surface));
        });

    paddleTexture = SDL_CreateTextureFromSurface(renderer, paddleSurface);
    ballTexture = SDL_CreateTextureFromSurface(renderer, ballSurface);
    heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurface);
}

void Renderer::drawBricks(Bricks& bricks)
{
    auto brickVector = bricks.getBricks();
    std::for_each(brickVector->begin(), brickVector->end(), [this](Brick brick)
        {
            SDL_Rect brickRect = brick.rect;

            if (brick.isHit())
            {
                brickRect.h = 0;
                brickRect.w = 0;
            }

            int health = brick.getHealth();
            drawBrick(health, brickRect);
        });
}


void Renderer::drawBrick(int health, SDL_Rect rect)
{
    SDL_RenderCopy(
        renderer,
        brickTextureVector.at((health <= 0) ? 0 : health - 1), //Make sure health is never less then 0
        nullptr,
        &rect
    );
}


void Renderer::drawPaddle(SDL_Rect rect)
{
    SDL_RenderCopy(renderer, paddleTexture, nullptr, &rect);
}

void Renderer::drawBall(SDL_Rect rect)
{
    SDL_RenderCopy(renderer, ballTexture, nullptr, &rect);
}

void Renderer::drawStatusBar(int health, int score, Status status)
{
    for (int i = 0; i < health; i++)
    {
        SDL_Rect rect = { WIDTH - (40 + (35 * i)) , 10, 22, 20 };
        SDL_RenderCopy(renderer, heartTexture, nullptr, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, 0, 43, WIDTH, 43);
        SDL_RenderDrawLine(renderer, 0, 44, WIDTH, 44);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    }

    std::string statusText;
    switch (status) {
    case INITIALIZED:
        statusText = "PRESS SPACE TO PLAY";
        break;
    case PAUSED:
        statusText = "GAME PAUSED - SPACE TO RESUME";
        break;
    case PLAYING:
        statusText = "GAME ACTIVE - SPACE TO PAUSE";
        break;
    case GAME_WON:
        statusText = "YOU WON! SPACE TO SEE MAIN MENU";
        break;
    case GAME_LOST:
        statusText = "YOU LOSE! SPACE TO SEE MAIN MENU";
        break;
    default:
        statusText = "";
        break;
    }

    scoreTxtSurface = TTF_RenderText_Solid(FONT_SCORE, std::to_string(score).c_str(), COLOR_GREEN);
    scoreTxtTexture = SDL_CreateTextureFromSurface(renderer, scoreTxtSurface);
    scoreTxtPosition = { 10, 10, scoreTxtSurface->clip_rect.w, scoreTxtSurface->clip_rect.h, };

    gameStatusTxtSurface = TTF_RenderText_Solid(FONT_SCORE, statusText.c_str(), COLOR_GREEN);
    gameStatusTxtTexture = SDL_CreateTextureFromSurface(renderer, gameStatusTxtSurface);
    gameStatusTxtPosition = { WIDTH / 2 - (gameStatusTxtSurface->clip_rect.w / 2) , 10, gameStatusTxtSurface->clip_rect.w, 				gameStatusTxtSurface->clip_rect.h, };

    SDL_RenderCopy(renderer, scoreTxtTexture, nullptr, &scoreTxtPosition);
    SDL_RenderCopy(renderer, gameStatusTxtTexture, nullptr, &gameStatusTxtPosition);

    SDL_DestroyTexture(scoreTxtTexture);
    SDL_DestroyTexture(gameStatusTxtTexture);
    SDL_FreeSurface(scoreTxtSurface);
    SDL_FreeSurface(gameStatusTxtSurface);
}

void Renderer::destroyGame()
{
    SDL_DestroyTexture(paddleTexture);
    SDL_DestroyTexture(ballTexture);
    SDL_DestroyTexture(heartTexture);

    std::for_each(brickTextureVector.begin(), brickTextureVector.end(), [](SDL_Texture* texture) {
        SDL_DestroyTexture(texture);
        });

    SDL_FreeSurface(ballSurface);
    SDL_FreeSurface(paddleSurface);
    SDL_FreeSurface(heartSurface);

    std::for_each(brickSurfaceVector.begin(), brickSurfaceVector.end(), [](SDL_Surface* surface) {
        SDL_FreeSurface(surface);
        });

    brickSurfaceVector.clear();
    brickTextureVector.clear();
}

void Renderer::destroyMainMenu()
{
    SDL_DestroyTexture(titleTexture);
    SDL_DestroyTexture(menuItemOneWhiteTexture);
    SDL_DestroyTexture(menuItemOneGreenTexture);
    SDL_DestroyTexture(menuItemTwoWhiteTexture);
    SDL_DestroyTexture(menuItemTwoGreenTexture);

    SDL_FreeSurface(titleSurface);
    SDL_FreeSurface(menuItemOneWhite);
    SDL_FreeSurface(menuItemOneGreen);
    SDL_FreeSurface(menuItemTwoWhite);
    SDL_FreeSurface(menuItemTwoGreen);
}

void Renderer::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}