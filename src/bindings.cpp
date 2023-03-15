#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

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
#else // This works for Mac
    #include <SDL.h>
#endif

// The glad library helps setup OpenGL extensions.
#include <glad/glad.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

const int FPS = 30;
const float Delta = 1000 / FPS;
const int FRAME = 6;

class SDLGraphicsProgram{
public:

    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Destructor
    ~SDLGraphicsProgram();
    // Setup OpenGL
    bool initGL();
    // Clears the screen
    void clear();
    // Flips to new buffer
    void flip();
    // Delay rendering
    void delay(int milliseconds);
    // loop that runs forever
    void loop();
    // Get Pointer to Window
    SDL_Window* getSDLWindow();
    // Draw a simple rectangle
    void DrawRectangle();

    // void DrawRectangle(SDL_Rect rect, SDL_Color color);

    void AddRectangle(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);

    void MoveRectangle(int id, int x, int y);

    bool IsUpKeyDown();

    bool IsDownKeyDown();

    bool IsWKeyDown();

    bool IsSKeyDown();

    void PrintRectangle();

    void SetFrameRate(int frame);

    bool QuitGame();

    // void MoveRect(SDLGraphicsProgram& program, int i, int x, int y);

    bool quit; // for python useage
    
    vector<SDL_Rect>    m_Rect; // for add rectangles in python
    
private:
    vector<SDL_Color>   m_Color;
    vector<bool>        m_MovingRect;
    // Screen dimension constants
    int screenHeight;
    int screenWidth;
    // The window we'll be rendering to
    SDL_Window* gWindow ;
    // Our renderer
    SDL_Renderer* gRenderer;

};

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h):screenWidth(w),screenHeight(h){
	// Initialization flag
	bool success = true;
	// String to hold any errors that occur.
	std::stringstream errorStream;
	// The window we'll be rendering to
	gWindow = NULL;
	// Render flag

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{
        errorStream << "Successfully Init SDL " << "\n";
	    //Create window
    	gWindow = SDL_CreateWindow( "Lab", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN );

        // Check if Window did not create.
        if( gWindow == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create a Renderer to draw on
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        // Check if Renderer did not create.
        if( gRenderer == NULL ){
            errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }
  	}

    // If initialization did not work, then print out a list of errors in the constructor.
    if(!success){
        errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
        std::string errors=errorStream.str();
        SDL_Log("%s\n",errors.c_str());
    }else{
        SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
    }

    // start game loop
    // this->loop();
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    //Destroy window
	SDL_DestroyWindow( gWindow );
	// Point gWindow to NULL to ensure it points to nothing.
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}


// Initialize OpenGL
// Setup any of our shaders here.
bool SDLGraphicsProgram::initGL(){
	//Success flag
	bool success = true;

	return success;
}


// clear
// Clears the screen
void SDLGraphicsProgram::clear(){
	// Nothing yet!
    SDL_SetRenderDrawColor(gRenderer, 0x44,0x44,0x4,0xFF);
    SDL_RenderClear(gRenderer);   
}
// Flip
// The flip function gets called once per loop
// It swaps out the previvous frame in a double-buffering system
void SDLGraphicsProgram::flip(){
	// Nothing yet!
    SDL_RenderPresent(gRenderer);
}


void SDLGraphicsProgram::delay(int milliseconds){
    SDL_Delay(milliseconds); 
}


//Loops forever!
void SDLGraphicsProgram::loop(){
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    // While application is running
    while(!quit){
     	 //Handle events on queue
		while(SDL_PollEvent( &e ) != 0){
        	// User posts an event to quit
	        // An example is hitting the "x" in the corner of the window.
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
            }
      	} // End SDL_PollEvent loop.
        SDL_GL_SwapWindow(getSDLWindow());
    }

    //Disable text input
    SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::getSDLWindow(){
  return gWindow;
}



void SDLGraphicsProgram::SetFrameRate(int frame){
    int startTime = SDL_GetTicks();

    int curDelta = SDL_GetTicks() - startTime;

    // 1000 / 60 = 16.67, which means that we should refreash 1 frame per 16.67 ms
    // if curDelta is less than 16.67, it means that the refresh speed is so fast
    // so we should delay the difference to enable next frame 
    if (curDelta < Delta)
    {
        SDL_Delay(Delta - curDelta);
    }
}



void SDLGraphicsProgram::PrintRectangle(){
    for (auto it = m_Rect.begin(); it != m_Rect.end(); ++it) {
        std::cout << "Rect x: " << it->x << ", y: " << it->y << ", w: " << it->w << ", h: " << it->h << std::endl;
    }
}


void SDLGraphicsProgram::AddRectangle(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b){
    SDL_Rect fillRect = {x, y, w, h};
    m_Rect.push_back(fillRect);
    m_MovingRect.push_back(false); // 添加矩形时，设置其移动状态为 true
    SDL_Color color = {r, g, b};
    m_Color.push_back(color);
}


void SDLGraphicsProgram::MoveRectangle(int i, int x, int y){
    m_Rect[i].x = x;
    m_Rect[i].y = y;
}

// void SDLGraphicsProgram::MoveRect(SDLGraphicsProgram& program, int i, int x, int y){
//     program.MoveRectangle(i, x, y);
// }



// Okay, render our rectangles!
void SDLGraphicsProgram::DrawRectangle(){
    for(int i = 0; i < m_Rect.size(); i++){
        SDL_SetRenderDrawColor(gRenderer, m_Color[i].r, m_Color[i].g, m_Color[i].b, 0xFF);
        SDL_RenderDrawRect(gRenderer, &m_Rect[i]); 
    }
}

// void SDLGraphicsProgram::DrawRectangle(SDL_Rect rect, SDL_Color color){
//     SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
//     SDL_RenderFillRect(gRenderer, &rect);
// }

bool SDLGraphicsProgram::IsUpKeyDown(){
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[SDL_SCANCODE_UP];
}

bool SDLGraphicsProgram::IsDownKeyDown(){
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[SDL_SCANCODE_DOWN];
}   

bool SDLGraphicsProgram::IsWKeyDown(){
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[SDL_SCANCODE_W];
}

bool SDLGraphicsProgram::IsSKeyDown(){
    const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[SDL_SCANCODE_S];
}

bool SDLGraphicsProgram::QuitGame(){
    SDL_Event e;
    if (SDL_PollEvent( &e ) != 0) {
        if (e.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

// Include the pybindings
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;


// Creates a macro function that will be called
// whenever the module is imported into python
// 'mygameengine' is what we 'import' into python.
// 'm' is the interface (creates a py::module object)
//      for which the bindings are created.
//  The magic here is in 'template metaprogramming'



PYBIND11_MODULE(mygameengine, m){
    m.doc() = "our game engine as a library"; // Optional docstring

    py::class_<SDLGraphicsProgram>(m, "SDLGraphicsProgram")
            // .def(py::init<SDL_Renderer*>())
            .def(py::init<int,int>(), py::arg("w"), py::arg("h"))   // our constructor
            .def_readwrite("quit", &SDLGraphicsProgram::quit)
            .def_readonly("m_Rect", &SDLGraphicsProgram::m_Rect)
            .def("SetFrameRate", &SDLGraphicsProgram::SetFrameRate)
            .def("clear", &SDLGraphicsProgram::clear) // Expose member methods
            .def("delay", &SDLGraphicsProgram::delay) 
            .def("flip", &SDLGraphicsProgram::flip) 
            .def("loop", &SDLGraphicsProgram::loop) 
            .def("DrawRectangle", &SDLGraphicsProgram::DrawRectangle)
            .def("IsUpKeyDown", &SDLGraphicsProgram::IsUpKeyDown)
            .def("IsDownKeyDown", &SDLGraphicsProgram::IsDownKeyDown)
            .def("IsWKeyDown", &SDLGraphicsProgram::IsWKeyDown)
            .def("IsSKeyDown", &SDLGraphicsProgram::IsSKeyDown)
            .def("AddRectangle", &SDLGraphicsProgram::AddRectangle)
            .def("PrintRectangle", &SDLGraphicsProgram::PrintRectangle)
            .def("MoveRectangle", &SDLGraphicsProgram::MoveRectangle)
            .def("QuitGame", &SDLGraphicsProgram::QuitGame);

    // m.def("MoveRect", &SDLGraphicsProgram::MoveRect); 
// We do not need to expose everything to our users! MoveRectangle QuitGame
//            .def("getSDLWindow", &SDLGraphicsProgram::getSDLWindow, py::return_value_policy::reference) 
}











#endif
