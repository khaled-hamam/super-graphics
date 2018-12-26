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
    
    this->initializeGLOptions();
	//glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
    
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

    skybox = new Skybox();
    hero = new Hero(vec3(0.f, 1.f, 0.f));
    mainCamera.bindHero(hero);
    level = generator.generateLevel();
    level.push_back(new SmartEnemy(hero, vec3(3.f, 1.f, 0.f)));
    sun = new DirectionalLight();
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

void SuperGraphicsEngine::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	
    ResourceManager::bindCamera(&mainCamera);

    for (auto &model : level) {
        double distanceFromHero = sqrt(
            pow(hero->position.x - model->position.x, 2) + 
            pow(hero->position.y - model->position.y, 2) +
            pow(hero->position.z - model->position.z, 2)
        );
        double distanceOnX = hero->position.x - model->position.x;

        if (distanceFromHero <= drawDistance && distanceOnX <= 4)
            model->render();
    }

    skybox->render();
	hero->render();

	hero->update();
    for (auto &model : level) {
        model->update();
    }

    textEngine->renderText("Lives: " + to_string(hero->lives), 5.f, 5.f, 1.0f, glm::vec3(BLACK));
    textEngine->renderText("Coins: " + to_string(hero->coins), 5.f, 60.f, 1.0f, glm::vec3(BLACK));
}

void SuperGraphicsEngine::checkCollision() {
    for (auto &model : level) {
        CollisionResult result = areColliding(hero, model);
        if (result.areColliding && !model->destroyed) {
            hero->direction = STATIC;
            model->collision(hero, result.direction, result.distance);
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
	hero->handelInput(window);
    mainCamera.handleInput(window);
}
