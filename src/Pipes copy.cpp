// #include "DrawableObj.h"
// #include "Hitbox.h"
// #include "ArrayBuffer.h"
// #include <deque>
// #include <string>
// #include <iostream>
// #include <random>

// /**
//  * Requires bird to be created first
//  */
// class Pipes {
//     public:
//     std::deque<DrawableObj*> pipes;
//     std::deque<Hitbox*> hitboxes;

//     ArrayBuffer* topPipeVBO;
//     ArrayBuffer* botPipeVBO;
//     GLfloat xDisplacement;
//     const GLfloat ySpace;
//     const float pipeWidth = .33814;

//     const unsigned int updatesNeeded = 120;
//     static unsigned int updateCount;

//     private:
//     std::mt19937* randMt;
//     std::uniform_int_distribution<int>* distrib;

//     public:
//     Pipes(const std::string& topPipeFilename, const std::string& botPipeFilename, GLfloat xDisplacement, const GLfloat& ySpace = 0.3)
//         : xDisplacement(xDisplacement), ySpace(ySpace) {
        
//         //AttribFormat may be moved to parameter list
//         AttribFormat* format = new AttribFormat();
//         format->addAttrib<GLfloat>(2, GL_VERTEX_ARRAY);
//         format->addAttrib<GLubyte>(3, GL_COLOR_ARRAY);
        
//         DrawableObj::type("botPipe", GL_QUADS, botPipeFilename, format, false);
//         DrawableObj::type("topPipe", GL_QUADS, topPipeFilename, format, false);

//         randMt = new std::mt19937 { std::random_device{}() };
//         distrib = new std::uniform_int_distribution<int> { 20, 80 }; //min height of pipes is 20% of the window's height
//     }

//     //Call alongside updatePipes()
//     void createPipe() {
//         if (Pipes::updateCount < updatesNeeded) {
//             ++Pipes::updateCount;
//             return;
//         }
//         Pipes::updateCount = 0;


//         GLfloat yOffset = (*distrib)(*randMt) / 50.f;

//         pipes.push_back(DrawableObj::create("botPipe"));
//         pipes.back()->setOffset(0, yOffset - 2 - ySpace / 2);

//         pipes.push_back(DrawableObj::create("topPipe"));
//         pipes.back()->setOffset(0, yOffset + ySpace / 2);

//         //bot pipe
//         hitboxes.push_back(new Hitbox(1, 1 + this->pipeWidth, ySpace / 2 + yOffset - 1, -1));

//         //top pipe
//         hitboxes.push_back(new Hitbox(1, 1 + this->pipeWidth, 1, ySpace / 2 + yOffset - 1));
//     }
    

//     // void reshape(int screenWidth, int screenHeight) {
//     //     for (Hitbox* hitbox : hitboxes) {
//     //         hitbox->updateX(this->xDisplacement);
//     //     }
//     // }

//     void updatePipes() {
//         for (DrawableObj* obj : pipes) {
//             obj->setOffset(obj->getXOffset() + this->xDisplacement, obj->getYOffset());
//             //std::cout << "PipeLeft: " << obj->getXOffset() << '\n';
//         }

//         for (Hitbox* hitbox : hitboxes) {
//             hitbox->updateX(this->xDisplacement);
//             //std::cout << "xLeft: " << hitbox->xLeft << '\n';
//         }

//         if (pipes.size() >= 2 && pipes[0]->getXOffset() < -2.f) {
//             delete pipes[0];
//             delete pipes[1];

//             pipes.pop_front();
//             pipes.pop_front();

//             delete hitboxes[0];
//             delete hitboxes[1];

//             hitboxes.pop_front();
//             hitboxes.pop_front();
//         }
//     }

//     void draw() {
//         for (DrawableObj* obj : pipes) {
//             obj->draw();
//         }
//     }
// };