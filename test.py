# Run with:
#
# (Linux & Mac) python3.5 engine.py -m ./mygameengine.so
# (Windows) python3.6 engine.py -m ./mygameengine.pyd
#
# The program should also run with 'python2.7' but you will have
# to change the 3.5's to 2.7's in your respective build script as
# well as make sure you compiled with 3.5 or 2.7 load flags.
#
# You will see `python3.5-config --includes` for example which corresponds
# to which version of python you are building.
# (In fact, run `python3.5-config --includes` in the terminal to see what it does!)
import mygameengine
import sdl2

# Initialize SDL
screen_Width = 400
screen_Height = 400
paddle_Width = 20
paddle_Height = 100
ball_Width = 20
ball_Height = 20
offset = 10

global engine
# Init screen
engine = mygameengine.SDLGraphicsProgram(screen_Width,screen_Height)  

class GameObject:
    def __init__(self, x, y, width, height):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.speed = 1
        self.rect = sdl2.SDL_Rect(x, y, width, height)
    
    def get_rect(self):
        return self.rect
    
    def AddRectangle(self):
        engine.AddRectangle(self.x, self.y, self.width, self.height, 0, 0, 0)

    def move(self, index, dx, dy):
        self.x = dx
        self.y = dy
        self.rect = sdl2.SDL_Rect(self.x, self.y, self.width, self.height)
        engine.MoveRectangle(index, self.x, self.y)

    def setSpeed(self, speed):
        self.speed = speed
    

class Paddle(GameObject):
    def __init__(self, x, y, width, height):
        super().__init__(x, y, width, height)

    def check_collision(self, other_rect):
        return sdl2.SDL_HasIntersection(self.rect, other_rect)
    
    def move(self, index, dx, dy):
        return super().move(index, dx, dy)
    

class Ball(GameObject):
    def __init__(self, x, y, width, height, speed = 1):
        super().__init__(x, y, width, height)
        self.initXPos = x
        self.initYPos = y
        self.direction = 1
        self.ballXDirecion = 1
        self.ballYDirecion = 1
        self.speed = speed
        
    def move(self, index, dx, dy):
        self.x = dx
        self.y = dy
        self.rect = sdl2.SDL_Rect(self.x, self.y, self.width, self.height)
        engine.MoveRectangle(index, self.x, self.y)
    
    def resetBallPosition(self):
        self.x = self.initXPos
        self.y = self.initYPos
    
    def handleBallDirection(self):
        if(self.x >= screen_Width - paddle_Width - offset):
            self.direction = -1
        elif(self.x <= 0):
            self.direction = 1

    def handleBallMovement(self):
        self.x += self.speed * self.ballXDirecion
        self.y += self.speed * self.ballYDirecion
        self.move(2, self.x, self.y)

    def handleBallBoundary(self):
        # out of x boundary
        if(self.x > screen_Width - offset - left_paddle.width):
            self.ballXDirecion *= -1
            self.resetBallPosition()
        if(self.x < 0):
            self.ballXDirecion *= -1
            self.resetBallPosition()

        # out of y boundary
        if(self.y > screen_Height - offset):
            self.ballYDirecion *= -1
            # self.resetBallPosition()
        if(self.y < 0):
            self.ballYDirecion *= -1    
            # self.resetBallPosition()
    

# paddle 
left_paddle = Paddle(offset, screen_Height // 2 - paddle_Height // 2, 20, 100)
left_paddle.setSpeed(5)
left_paddle.AddRectangle()

right_paddle = Paddle(screen_Width - paddle_Width - offset, screen_Height // 2 - paddle_Height // 2, 20, 100)
right_paddle.setSpeed(5)
right_paddle.AddRectangle()

# ball
ball = Ball((screen_Width - ball_Width) // 2, (screen_Height - ball_Height) // 2, ball_Width, ball_Height)
ball.setSpeed(3)
ball.AddRectangle()

def handleCollision():
    ball_rect = ball.get_rect()
    print(ball_rect.x, ball_rect.y)

    if(ball.ballXDirecion == -1 and left_paddle.check_collision(ball_rect)):
        ball.ballXDirecion *= -1
        middlePoint = left_paddle.y + left_paddle.height / 2
        if(ball.y >= middlePoint):
            ball.ballYDirecion = -1
        else:
            ball.ballYDirecion = 1
        print("left Collision with ball", flush = True)

    if(ball.ballXDirecion == 1 and right_paddle.check_collision(ball_rect)):
        ball.ballXDirecion *= -1
        middlePoint = right_paddle.y + right_paddle.height / 2
        if(ball.y >= middlePoint):
            print(">=", flush = True)
            ball.ballYDirecion = -1
        else:
            print("<", flush = True)
            ball.ballYDirecion = 1
        print("Right Collision with ball", flush = True)


def Render():
    engine.DrawRectangle()

def Input():
    # print("detecting input")
    if engine.IsUpKeyDown(): 
        right_paddle.move(1, right_paddle.x, right_paddle.y - right_paddle.speed)
        
    elif engine.IsDownKeyDown():
        right_paddle.move(1, right_paddle.x, right_paddle.y + right_paddle.speed)

    if engine.IsWKeyDown():
        left_paddle.move(0, left_paddle.x, left_paddle.y - left_paddle.speed)

    elif engine.IsSKeyDown():
        left_paddle.move(0, left_paddle.x, left_paddle.y + left_paddle.speed)
       

def Update():
    # ball.move(2, -1, 0)
    handleCollision()
    ball.handleBallBoundary()
    ball.handleBallMovement()
    ball.handleBallDirection()

def main():
    while not engine.quit :
        if(engine.QuitGame()):
            engine.quit = True
        
        engine.clear()

        Render()
        Input()
        Update()

        engine.delay(16)
        engine.flip()

if __name__ == '__main__':
    main()