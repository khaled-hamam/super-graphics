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
#include "Lights.h"

SuperGraphicsEngine::SuperGraphicsEngine()
{
    windowWidth = 1200;
    windowHeight = 750;
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

/*    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT); */ 
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

Light *sun;

void SuperGraphicsEngine::start()
{
    LevelGenerator generator;
    this->level = generator.generateLevel();

    mainCamera.bindHero(level->hero);
	textEngine = new TextRenderer(windowWidth, windowHeight);
	textEngine->loadFont("Assets/Fonts/arial.ttf", 48);
	ResourceManager::playBackgroundMusic();

    double lastFrameDraw = 0;
    do {
        double now = glfwGetTime();
        double FPS = 1.0 / 120.0;
        if (now - lastFrameDraw < FPS) {
            continue;
        }
        lastFrameDraw = now;
        
        this->handleInput();
        this->render();
        this->checkCollision();
        glfwSwapBuffers(window);
		glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0);

    glfwTerminate();
}

void SuperGraphicsEngine::render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    switch (this->gameState)
    {
    case RUNNING:
        this->renderRunningScreen();
        break;
    case READY:
        this->renderReadyScreen();
        break;
    case GAME_OVER:
        this->renderGameOverScreen();
        break;
    }
}

void SuperGraphicsEngine::renderRunningScreen()
{
    ResourceManager::bindCamera(&mainCamera);

    for (auto &model : level->world) {
        double distanceFromHero = sqrt(
            pow(level->hero->position.x - model->position.x, 2) +
            pow(level->hero->position.y - model->position.y, 2) +
            pow(level->hero->position.z - model->position.z, 2)
        );
        double distanceOnX = level->hero->position.x - model->position.x;

        if (distanceFromHero <= drawDistance && distanceOnX <= 4)
            model->render();
    }

    level->skybox->render();
    level->hero->render();

    level->hero->update();
    for (auto &model : level->world) {
        model->update();
    }

    textEngine->renderText("Lives: " + to_string(level->hero->lives), 5.f, 5.f, 1.0f, glm::vec3(BLACK));
    textEngine->renderText("Coins: " + to_string(level->hero->coins), 5.f, 60.f, 1.0f, glm::vec3(BLACK));

    if (level->hero->lives <= 0) {
        this->gameState = GAME_OVER;
    }
}

void SuperGraphicsEngine::renderReadyScreen() {
    textEngine->renderText("Super Graphics Game", 600, 375, 1.0f, glm::vec3(BLACK));
    textEngine->renderText("Press Enter to Start", 600, 450, 0.5f, glm::vec3(BLACK));
}

void SuperGraphicsEngine::renderGameOverScreen() {
    textEngine->renderText("Game Over", 600, 375, 1.0f, glm::vec3(BLACK));
    textEngine->renderText("Press Enter to Retry", 600, 450, 0.5f, glm::vec3(BLACK));
}

void SuperGraphicsEngine::checkCollision() {
    for (auto &model : level->world) {
        CollisionResult result = areColliding(level->hero, model);
        if (result.areColliding && !model->destroyed) {
            level->hero->direction = STATIC;
            model->collision(level->hero, result.direction, result.distance);
        }
    }
}

CollisionResult SuperGraphicsEngine::areColliding(Hero *hero, Model *model) {
	float distanceX = hero->position.x - model->position.x;
	float distanceY = hero->position.y - model->position.y;
    float distanceZ = hero->position.z - model ->position.z;

	float scaleX = (model->scale.x / 2) + (hero->scale.x / 2);
	float scaleY = (model->scale.y / 2) + (hero->scale.y / 2);
	float scaleZ = (model->scale.z / 2) + (hero->scale.z / 2);

    CollisionResult result { false };
	if (abs(distanceX) < scaleX && abs(distanceY) < scaleY && hero->position.z == model->position.z) {
        result.areColliding = true;
	    float wy = scaleX * distanceY;
        float hx = scaleY * distanceX;

        if (wy > hx) {
            if (wy > -hx) {
                result.direction = UP;
                result.distance = scaleY - abs(distanceY);
            } else {
                result.direction = LEFT;
                result.distance = scaleX - abs(distanceX);
            }
        } else {
            if (wy > -hx) {
                result.direction = RIGHT;
                result.distance = scaleX - abs(distanceX);
            } else {
                result.direction = DOWN;
                result.distance = scaleY - abs(distanceY);
            }
        }
	}
    return result;
}

void SuperGraphicsEngine::handleInput()
{
    switch (this->gameState)
    {
    case RUNNING:
        level->hero->handelInput(window);
        mainCamera.handleInput(window);
        break;
    case READY:
        if (glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            this->gameState = RUNNING;
        }
        break;
    case GAME_OVER:
        if (glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            this->gameState = RUNNING;
        }
        break;
    }
}
