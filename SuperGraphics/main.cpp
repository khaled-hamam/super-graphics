#include "SuperGraphicsEngine.h"

int main() {
    SuperGraphicsEngine *engine = new SuperGraphicsEngine();
    engine->start();
    delete engine;
    return 0;
}
