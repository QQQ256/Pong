// Support Code written by Michael D. Shah
//
// You can modify this could however you like in order to implement your 'pong'
//
// Last Updated: 01/17/23
// Please do not redistribute without asking permission.


// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif
#undef main
#include <iostream>
#include <string>
#include "TexturedRectangle.hpp"
#include "SDLApp.hpp"
#include "GameEntity.hpp"
#include "ResourceManager.hpp"
#include "Sound.hpp"
#include "DynamicText.hpp"
using namespace std;

struct GameState {
    float movementSpeed;
    float ballSpeed;
    int ballXDirection;
    int ballYDirection;
    int leftScore;
    int rightScore;
    bool isFinished;
};

GameState* gameState;

// set app as a global variable to visit private members
SDLApp* app;    

GameEntity* leftPaddle;
GameEntity* rightPaddle;
GameEntity* ball;
GameEntity* middle;

void HandleLeftPaddleInputEvent() {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    int leftPaddleX = leftPaddle->GetTexturedRectangle().GetPositionX();
    int leftPaddleY = leftPaddle->GetTexturedRectangle().GetPositionY();
    if (state[SDL_SCANCODE_W])
    {
        leftPaddleY -= gameState->movementSpeed;
        leftPaddle->SetPosition(leftPaddleX, leftPaddleY);
    }
    if (state[SDL_SCANCODE_S])
    {
        leftPaddleY += gameState->movementSpeed;
        leftPaddle->SetPosition(leftPaddleX, leftPaddleY);
    }
}

void ResetBallPosition() {
    int ballXPosition = ball->GetTexturedRectangle().GetPositionX();
    int ballYPosition = ball->GetTexturedRectangle().GetPositionY();

    ballXPosition = app->GetWindowWidth() / 2 - ball->GetTexturedRectangle().GetWidth() / 2;
    ballYPosition = app->GetWindowHeight() / 2 - ball->GetTexturedRectangle().GetHeight() / 2;

    ball->SetPosition(ballXPosition, ballYPosition);
}

void RestartGame() {

    if (gameState->leftScore == 3)
    {
        cout << "Left Player wins!" << endl;
    }
    else if(gameState->rightScore == 3){
        cout << "Right Player wins!" << endl;
    }

    gameState->leftScore = 0;
    gameState->rightScore = 0;
    leftPaddle->SetPosition(10, 200);
    rightPaddle->SetPosition(610, 200);
    ResetBallPosition();
}

void HandleBallMovePosition() {
    int ballXPosition = ball->GetTexturedRectangle().GetPositionX();
    int ballYPosition = ball->GetTexturedRectangle().GetPositionY();

    // update position based on the ball's direction
    if (gameState->ballXDirection > 0)
    {
        ballXPosition += gameState->movementSpeed;
    }
    else {
        ballXPosition -= gameState->movementSpeed;
    }

    if (gameState->ballYDirection > 0)
    {
        ballYPosition += gameState->movementSpeed;
    }
    else {
        ballYPosition -= gameState->movementSpeed;
    }

    ball->SetPosition(ballXPosition, ballYPosition);
}

void HandleBoundaryForBall() {

    int ballXPosition = ball->GetTexturedRectangle().GetPositionX();
    int ballYPosition = ball->GetTexturedRectangle().GetPositionY();

    // set ball boundary
    if (ballXPosition > app->GetWindowWidth() + 100)
    {
        gameState->leftScore += 1;
        gameState->ballXDirection *= -1;

        ResetBallPosition();
    }
    if (ballXPosition < -80)
    {
        gameState->ballXDirection *= -1;
        gameState->rightScore += 1;

        ResetBallPosition();
    }

    if (ballYPosition > app->GetWindowHeight())
    {
        gameState->ballYDirection *= -1;
    }
    if (ballYPosition < 0)
    {
        gameState->ballYDirection *= -1;
    }

    if (gameState->leftScore == 3 || gameState->rightScore == 3)
    {
        gameState->isFinished = true;
        RestartGame();
    }
}

void HandleRightPaddleInputEvent() {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    int rightPaddleX = rightPaddle->GetTexturedRectangle().GetPositionX();
    int rightPaddleY = rightPaddle->GetTexturedRectangle().GetPositionY();
    if (state[SDL_SCANCODE_UP])
    {
        rightPaddleY -= gameState->movementSpeed;
        rightPaddle->SetPosition(rightPaddleX, rightPaddleY);
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        rightPaddleY += gameState->movementSpeed;
        rightPaddle->SetPosition(rightPaddleX, rightPaddleY);
    }
}

void HandleCollision() {

    int ballXPosition = ball->GetTexturedRectangle().GetPositionX();
    int ballYPosition = ball->GetTexturedRectangle().GetPositionY();

    // left paddle
    if (ballXPosition >= 20 && gameState->ballXDirection == -1 &&
        leftPaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    {
        gameState->ballXDirection *= -1;
        // leftPaddle->GetTexturedRectangle().SetDimention(20, 200);
        int middlePoint = leftPaddle->GetTexturedRectangle().GetPositionY() + 100;
        if (ballYPosition >= middlePoint)
        {
            gameState->ballYDirection = -1;
        }
        else {
            gameState->ballYDirection = 1;
        }
        cout << "Left paddle is colliding with ball" << endl;
    }

    if (ballXPosition <= 610 && gameState->ballXDirection == 1 &&
        rightPaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    {
        gameState->ballXDirection *= -1;
        int middlePoint = rightPaddle->GetTexturedRectangle().GetPositionY() + 100;
        if (ballYPosition >= middlePoint)
        {
            gameState->ballYDirection = -1;
        }
        else if (ballYPosition < middlePoint) {
            gameState->ballYDirection = 1;
        }
        cout << "Right paddle is colliding with ball!" << endl;
    }
}

//void WaitWinUIForSeconds(int ms) {
//    if (gameState->isFinished) {
//        static int currentTime = SDL_GetTicks();
//        static int lastTime = SDL_GetTicks();
//        currentTime = SDL_GetTicks();
//        if (currentTime > lastTime + ms)
//        {
//            gameState->isFinished = false;
//        }
//    }
//}

void HandleUpdate() {

    //WaitWinUIForSeconds(3000);

    HandleBallMovePosition();

    HandleCollision();

    HandleBoundaryForBall();

    leftPaddle->Update();
    rightPaddle->Update();
}

void HandleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            app->StopAppLoop();
            break;
        default:
            break;
        }
    }

    HandleLeftPaddleInputEvent();
    HandleRightPaddleInputEvent();
}

void HandleRendering() {

   /* cout << gameState->isFinished << endl;
    if (gameState->isFinished)
    {
        DynamicText winningText("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 24);
        string winText = gameState->leftScore >= 3 ? "Left Player Wins!" : "Right Player Wins!";
        winningText.DrawText(app->GetRenderer(), winText, 220, 210, 200, 30);
    }*/

    leftPaddle->Render();
    rightPaddle->Render();
    ball->Render();
    middle->Render();

    DynamicText leftScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 24);
    DynamicText rightScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf", 24);

    string lScore = "Left: " + to_string(gameState->leftScore);
    string rScore = "Right: " + to_string(gameState->rightScore);

    leftScore.DrawText(app->GetRenderer(), lScore, 140, 0, 80, 30);
    rightScore.DrawText(app->GetRenderer(), rScore, 410, 0, 80, 30);
    
}

int main() { 
    // init app
    app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO, "!PONG!", 20, 20, 640, 480);
    app->SetMaxFrameRate(60);

    // set gameState
    gameState = new GameState;
    gameState->movementSpeed    = 5.0f;
    gameState->ballSpeed        = 2.0f;
    gameState->ballXDirection   = 1;
    gameState->ballYDirection   = 1;
    gameState->leftScore        = 0;
    gameState->rightScore       = 0;
    gameState->isFinished       = false;

    leftPaddle = new GameEntity(app->GetRenderer());
    leftPaddle->AddTexturedRectangleComponent("./assets/images/leftpaddle.bmp");
    leftPaddle->AddBoxBoxCollider2D();    
    leftPaddle->GetTexturedRectangle().SetDimention(20, 100);
    leftPaddle->GetBoxCollider2D(0).SetDimention(
        leftPaddle->GetTexturedRectangle().GetWidth(),
        leftPaddle->GetTexturedRectangle().GetHeight());
    leftPaddle->SetPosition(10, 200);

    rightPaddle = new GameEntity(app->GetRenderer());
    rightPaddle->AddTexturedRectangleComponent("./assets/images/rightpaddle.bmp");
    rightPaddle->AddBoxBoxCollider2D();
    rightPaddle->GetTexturedRectangle().SetDimention(20, 100);
    rightPaddle->GetBoxCollider2D(0).SetDimention(
        rightPaddle->GetTexturedRectangle().GetWidth(),
        rightPaddle->GetTexturedRectangle().GetHeight());
    rightPaddle->SetPosition(610, 200);

    ball = new GameEntity(app->GetRenderer());
    ball->AddTexturedRectangleComponent("./assets/images/ball.bmp");
    ball->AddBoxBoxCollider2D();
    ball->GetTexturedRectangle().SetDimention(20, 20);
    ball->GetBoxCollider2D(0).SetDimention(
        ball->GetTexturedRectangle().GetWidth(),
        ball->GetTexturedRectangle().GetHeight());
    ball->SetPosition(app->GetWindowWidth() / 2, app->GetWindowHeight() / 2);

    middle = new GameEntity(app->GetRenderer());
    middle->AddTexturedRectangleComponent("./assets/images/rightpaddle.bmp");
    middle->SetPosition(app->GetWindowWidth() / 2, 0);
    middle->SetDimention(5, app->GetWindowHeight());

    // set callback function
    app->SetEventCallback(HandleEvents);
    app->SetRenderCallback(HandleRendering);
    app->SetUpdateCallback(HandleUpdate);
    app->RunLoop();

    delete app;
    delete leftPaddle;
    delete rightPaddle;
    delete ball;

    return 0;
}
