#include "SDL_image.h"

#include "loadingState.h"
#include "app.h"

#define BUTTON_X 50
#define BUTTON_Y 50
#define BUTTON_WIDTH 618
#define BUTTON_HEIGHT 205

LoadingState LoadingState::instance;

int LoadingState::init(App* game) {
  strStream << "Initializing loading state";
  view.printToFile(strStream.str());
  strStream.str(std::string());

  IMG_Init(IMG_INIT_PNG);

  renderer = SDL_CreateRenderer(game->getWindow(), -1, SDL_RENDERER_ACCELERATED);

  if(renderer == NULL) {
    strStream << "Error Creating Renderer: " << SDL_GetError();
    view.printToFile(strStream.str());
    strStream.str(std::string());

    return 1;
  }

  SDL_Surface *temp = IMG_Load("./Images/playButton.png");
  playButtonTexture = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);

  if(playButtonTexture == NULL) {
    strStream << "Error Loading playButtonTexture: " << SDL_GetError();
    view.printToFile(strStream.str());
    strStream.str(std::string());

    return 1;
  }

  temp = IMG_Load("./Images/playButtonClicked.png");
  playButtonPressedTexture = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);

  IMG_Quit();

  if(playButtonPressedTexture == NULL) {
    strStream << "Error Loading playButtonPressedTexture: " << SDL_GetError();
    view.printToFile(strStream.str());
    strStream.str(std::string());

    return 1;
  }

  return 0;
}

int LoadingState::cleanup() {
  strStream << "Closing loading state";
  view.printToFile(strStream.str());
  strStream.str(std::string());

  SDL_DestroyTexture(playButtonTexture);
  SDL_DestroyTexture(playButtonPressedTexture);
  SDL_DestroyRenderer(renderer);

  if(playButtonTexture == NULL || playButtonPressedTexture == NULL || renderer == NULL) {
    strStream << "Error Closing Loading Screen: " << SDL_GetError();
    view.printToFile(strStream.str());
    strStream.str(std::string());

    return 1;
  }

  return 0;
}

int LoadingState::pause() {
  return 0;
}

int LoadingState::resume() {
  return 0;
}

int LoadingState::handleEvents(App* game) {
  SDL_Event e;

  strStream << "Handling loading events";
  view.printToFile(strStream.str());
  strStream.str(std::string());

  while(SDL_PollEvent(&e)) {
    strStream << "Handling event: " << e.type;
    view.printToFile(strStream.str());
    strStream.str(std::string());

    switch(e.type) {
      case SDL_QUIT:
        game->quit();

      case SDL_MOUSEBUTTONDOWN:
        if(e.button.x > BUTTON_X && e.button.x < (BUTTON_X + BUTTON_WIDTH) && e.button.y > BUTTON_Y && e.button.y < (BUTTON_Y + BUTTON_HEIGHT)) {
          clickingPlay = true;
        }

      case SDL_MOUSEBUTTONUP:
        clickingPlay = false;
    }
  }

  strStream << "Finished handling loading events";
  view.printToFile(strStream.str());
  strStream.str(std::string());

  return 0;
}

int LoadingState::update(App* game) {
  return 0;
}

int LoadingState::draw(Uint32 timeBetweenFrames) {
  SDL_RenderClear(renderer);
  SDL_Rect DestR;
  DestR.x = BUTTON_X;
  DestR.y = BUTTON_Y;
  DestR.w = BUTTON_WIDTH;
  DestR.h = BUTTON_HEIGHT;

  if(clickingPlay) {
    SDL_RenderCopy(renderer, playButtonPressedTexture, NULL, &DestR);
  } else {
    SDL_RenderCopy(renderer, playButtonTexture, NULL, &DestR);
  }

  SDL_RenderPresent(renderer);
  return 0;
}
