#include "DrawableObj.h"
#include "Hitbox.h"
#include "ArrayBuffer.h"
#include <deque>
#include <string>
#include <iostream>
#include <random>

class Pipes {
    public:
    std::deque<DrawableObj*> pipes;
    std::deque<Hitbox*> hitboxes;

    ArrayBuffer* topPipeVBO;
    ArrayBuffer* botPipeVBO;
    GLfloat xDisplacement;
    const GLfloat ySpace;
    
    private:
    std::mt19937* randMt;
    std::uniform_int_distribution<int>* distrib;

    public:
    /*
    methods:
        checkCollision    
    */
    Pipes(const std::string& topPipeFilename, const std::string& botPipeFilename, GLfloat xDisplacement, const GLfloat& ySpace = 0.3/*, AttribFormat* format*/)
        : xDisplacement(xDisplacement), ySpace(ySpace) {
        
        //AttribFormat here is for testing only
        AttribFormat* format = new AttribFormat();
        format->addAttrib<GLfloat>(2, GL_VERTEX_ARRAY);
        format->addAttrib<GLubyte>(3, GL_COLOR_ARRAY);
        
        DrawableObj::type("botPipe", GL_QUADS, botPipeFilename, format, false);

        randMt = new std::mt19937 { std::random_device{}() };
        distrib = new std::uniform_int_distribution<int> { 20, 80 }; //min height of pipes is 20% of the window's height
    }

    void createPipe() {
        GLfloat yOffset = (*distrib)(*randMt) / 50.f;

        pipes.push_back(DrawableObj::create("botPipe"));
        hitboxes.push_back(new Hitbox(1, 1.388, -1, 1));
    }

    void reshape(int screenWidth, int screenHeight) {
        for (Hitbox* hitbox : hitboxes) {
            hitbox->updateX(this->xDisplacement);
        }
    }

    void updatePipes() {
        for (DrawableObj* obj : pipes) {
            obj->setOffset(obj->getXOffset() + this->xDisplacement, obj->getYOffset());
        }

        for (Hitbox* hitbox : hitboxes) {
            hitbox->updateX(this->xDisplacement);
            std::cout << "xLeft=" << hitbox->xLeft << ", "
              << "xRight=" << hitbox->xRight << ", "
              << "yTop=" << hitbox->yTop << ", "
              << "yBot=" << hitbox->yBot << std::endl << std::endl;
        }

        // if (pipes.size() >= 2 && pipes[0]->getXOffset() < -3.5f) {
        //     delete pipes[0];
        //     delete pipes[1];

        //     pipes.pop_front();
        //     pipes.pop_front();

        // }

    }

    void draw() {
        for (DrawableObj* obj : pipes) {
            obj->draw();
        }
    }
};