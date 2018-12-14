#include "SuperGraphicsEngine.h"
#include "Cat.h"
#include "Coin.h"
#include "PowerUp.h"
#include "Hero.h"
#include "Block.h"
#include "Spaceship.h"
#include "Spike.h"
#include "Obstacle.h"
#include "woodenBox.h"
#include "Villian.h"
SuperGraphicsEngine::SuperGraphicsEngine()
{
    this->windowWidth = 1200;
    this->windowHeight = 750;
    this->initialize();
}

void SuperGraphicsEngine::initialize() 
{   
    this->initializeGLFW();
    this->initializeGLEW();

    // Set the background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    this->initializeGLOptions();
    
    ResourceManager::initializeResources();
}

void SuperGraphicsEngine::initializeGLFW()
{
    if(!glfwInit()) {
		cerr << "Failed to initialize GLFW\n";
		throw "Failed to initialize GLFW";
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(windowWidth, windowHeight, "Super Graphics", NULL, NULL);
	if (window == NULL) {
		cerr << "Failed to open GLFW window.";
		glfwTerminate();
		throw "Failed to initialize GLFW";
	}
	glfwMakeContextCurrent(window);
}

void SuperGraphicsEngine::initializeGLEW()
{
    glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW\n";
		throw "Failed to initialize GLEW";
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); 
}

void SuperGraphicsEngine::initializeGLOptions() {
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);  
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

//Cat *q;
Skybox *skybox;
Coin *coin;
PowerUp *powerup;
Hero *hero;
Spaceship *spaceship;
Block *block;
Obstacle *block1;
woodenBox *box;
Spike *spikes;
Villian *villian;
Obstacle *o;
void SuperGraphicsEngine::start()
{
   // q = new Cat();
    skybox = new Skybox();
	coin = new Coin();
	powerup = new PowerUp();
	hero = new Hero();
	block = new Block();
	spaceship = new Spaceship();
	spikes = new Spike();
	block1 = new Obstacle();
	box = new woodenBox();
	villian = new Villian();
    double lastFrameDraw = 0;
    do {
        double now = glfwGetTime();
        double FPS = 1.0 / 120.0;
        if (now - lastFrameDraw < FPS) {
            continue;
        }
        lastFrameDraw = now;

        this->render();
        this->handleInput();

        glfwSwapBuffers(window);
		glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0);

    glfwTerminate();
}

void SuperGraphicsEngine::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    ResourceManager::bindCamera(&mainCamera);
    skybox->render();
	coin->render();
	coin->update();
	powerup->render();
	powerup->update();
	hero->render();
	hero->update();
	block->render();
	spaceship->render();
	spaceship->update();
	block1->render();
	box->render();
	box->update();
	spikes->render();
	villian->render();
	villian->update();

}

void SuperGraphicsEngine::handleInput()
{ 
    float step = 0.05f;
    float angle = 1.f;
	hero->handelInput(window);
	if (glfwGetKey(this->window, GLFW_KEY_M) == GLFW_PRESS) {
		hero->setDir(1);
	}
    if(glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS) {
        mainCamera.Walk(step);
    }
    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS) {
        mainCamera.Walk(-step);
    }
    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS) {
        mainCamera.Strafe(step);
    }
    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS) {
        mainCamera.Strafe(-step);
    }
    if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS) {
        mainCamera.Fly(step);
    }
    if (glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS) {
        mainCamera.Fly(-step);
    } 
    if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS) {
        mainCamera.Pitch(angle);
    }
    if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mainCamera.Pitch(-angle);
    }
    if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        mainCamera.Yaw(angle);
    }
    if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        mainCamera.Yaw(-angle);
    }

    mainCamera.UpdateViewMatrix();
}
