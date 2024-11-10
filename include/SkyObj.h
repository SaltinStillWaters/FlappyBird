#ifndef SKYOBJ_H
#define SKYOBJ_H

#include "DrawableObj.h"

class SkyObj : public DrawableObj {
  protected:
    static ArrayBuffer *skyVertices;

  private:
    class SkyObjInit {
      public:
        ~SkyObjInit() { SkyObj::cleanup(); }
    };
    static SkyObjInit initSkyObj;

  public:
    SkyObj();
    static void init();
    static void cleanup();
};

#endif