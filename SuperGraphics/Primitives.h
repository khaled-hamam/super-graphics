#pragma once
#include "Primitive.h"
#include "colors.h"
#include "normals.h"

class Triangle : public Primitive {
public:
	Triangle(Texture *texture,
		vec3 position = vec3(0.f),
		vec3 rotation = vec3(0.f),
		vec3 scale = vec3(1.f)
	) : Primitive(texture, position, rotation, scale) {
		vertices = {
			{ vec3(0.5f, 0.f, 0.f), vec3(GREY), vec2(0.f, 0.f), vec3(NORMAL_ZPOS) },
			{ vec3(0.f, 0.5f, 0.f), vec3(SILVER), vec2(0.f, 1.f), vec3(NORMAL_ZPOS) },
			{ vec3(0.5f, 0.f, 0.f), vec3(SILVER), vec2(1.f, 1.f), vec3(NORMAL_ZPOS) },
		};

		indices = {
			0, 1, 2
		};

		init();
	}
};


class Quad : public Primitive {
public: 
    Quad(Texture *texture, 
        vec3 position = vec3(0.f),
        vec3 rotation = vec3(0.f),
        vec3 scale = vec3(1.f)
    ) : Primitive(texture, position, rotation, scale) {
        vertices = {
            { vec3(-0.5f, -0.5f, 0.f), vec3(RED), vec2(0.f, 0.f), vec3(NORMAL_ZPOS) },
            { vec3(-0.5f, 0.5f, 0.f), vec3(GREEN), vec2(0.f, 1.f), vec3(NORMAL_ZPOS) },
            { vec3(0.5f, 0.5f, 0.f), vec3(BLUE), vec2(1.f, 1.f), vec3(NORMAL_ZPOS) },
            { vec3(0.5f, -0.5f, 0.f), vec3(RED), vec2(1.f, 0.f), vec3(NORMAL_ZPOS) },
        };

        indices = {
            0, 1, 2,
            0, 2, 3
        };

        init();
    }
};

class Cube : public Primitive {
public: 
    Cube(Texture *texture, 
        vec3 position = vec3(0.f), 
        vec3 rotation = vec3(0.f), 
        vec3 scale = vec3(1.f)
    ) : Primitive(texture, position, rotation, scale) {
        vertices = {
            // FRONT FACE
            { vec3(-0.5f, -0.5f, 0.5f), vec3(), vec2(0.f, 0.f), vec3(NORMAL_ZPOS) },
            { vec3(-0.5f, 0.5f, 0.5f), vec3(), vec2(0.f, 1.f), vec3(NORMAL_ZPOS) },
            { vec3(0.5f, 0.5f, 0.5f), vec3(), vec2(1.f, 1.f), vec3(NORMAL_ZPOS) },
            { vec3(0.5f, -0.5f, 0.5f), vec3(), vec2(1.f, 0.f), vec3(NORMAL_ZPOS) },

            // BACK FACE
            { vec3(-0.5f, -0.5f, -0.5f), vec3(), vec2(0.f, 0.f), vec3(NORMAL_ZNEG) },
            { vec3(-0.5f, 0.5f, -0.5f), vec3(), vec2(0.f, 1.f), vec3(NORMAL_ZNEG) },
            { vec3(0.5f, 0.5f, -0.5f), vec3(), vec2(1.f, 1.f), vec3(NORMAL_ZNEG) },
            { vec3(0.5f, -0.5f, -0.5f), vec3(), vec2(1.f, 0.f), vec3(NORMAL_ZNEG) },

            // RIGHT FACE
            { vec3(0.5f, -0.5f, 0.5f), vec3(), vec2(0.f, 0.f), vec3(NORMAL_XPOS) },
            { vec3(0.5f, 0.5f, 0.5f), vec3(), vec2(0.f, 1.f), vec3(NORMAL_XPOS) },
            { vec3(0.5f, 0.5f, -0.5f), vec3(), vec2(1.f, 1.f), vec3(NORMAL_XPOS) },
            { vec3(0.5f, -0.5f, -0.5f), vec3(), vec2(1.f, 0.f), vec3(NORMAL_XPOS) },

            // LEFT FACE
            { vec3(-0.5f, -0.5f, -0.5f), vec3(), vec2(0.f, 0.f), vec3(NORMAL_XNEG) },
            { vec3(-0.5f, 0.5f, -0.5f), vec3(), vec2(0.f, 1.f), vec3(NORMAL_XNEG) },
            { vec3(-0.5f, 0.5f, 0.5f), vec3(), vec2(1.f, 1.f), vec3(NORMAL_XNEG) },
            { vec3(-0.5f, -0.5f, 0.5f), vec3(), vec2(1.f, 0.f), vec3(NORMAL_XNEG) },

            // TOP FACE
            { vec3(-0.5f, 0.5f, 0.5f), vec3(), vec2(0.f, 0.f), vec3(NORMAL_YPOS) },
            { vec3(-0.5f, 0.5f, -0.5f), vec3(), vec2(0.f, 1.f), vec3(NORMAL_YPOS) },
            { vec3(0.5f, 0.5f, -0.5f), vec3(), vec2(1.f, 1.f), vec3(NORMAL_YPOS) },
            { vec3(0.5f, 0.5f, 0.5f), vec3(), vec2(1.f, 0.f), vec3(NORMAL_YPOS) },

            // BOTTOM FACE
            { vec3(-0.5f, -0.5f, -0.5f), vec3(), vec2(0.f, 0.f), vec3(NORMAL_YNEG) },
            { vec3(-0.5f, -0.5f, 0.5f), vec3(), vec2(0.f, 1.f), vec3(NORMAL_YNEG) },
            { vec3(0.5f, -0.5f, 0.5f), vec3(), vec2(1.f, 1.f), vec3(NORMAL_YNEG) },
            { vec3(0.5f, -0.5f, -0.5f), vec3(), vec2(1.f, 0.f), vec3(NORMAL_YNEG) }
        };

        indices = {
            0, 1, 2,
            0, 2, 3,

            4, 5, 6,
            4, 6, 7,

            8, 9, 10,
            8, 10, 11,

            12, 13, 14,
            12, 14, 15,

            16, 17, 18,
            16, 18, 19,

            20, 21, 22,
            20, 22, 23
        };

        init();
    }
};

class Pyramid : public Primitive {
public: 
	Pyramid(Texture *texture,
		vec3 position = vec3(0.f),
		vec3 rotation = vec3(0.f),
		vec3 scale = vec3(1.f),
		vec3 color = vec3(BLACK)
	) : Primitive(texture, position, rotation, scale) {
		vertices = {
            // BASE FACE
            { vec3(-0.5f, -0.5f, -0.5f), vec3(color), vec2(0.f, 0.f), vec3(NORMAL_YNEG) },
            { vec3(-0.5f, -0.5f, 0.5f), vec3(color), vec2(0.f, 1.f), vec3(NORMAL_YNEG) },
            { vec3(0.5f, -0.5f, 0.5f), vec3(color), vec2(1.f, 1.f), vec3(NORMAL_YNEG) },
            { vec3(0.5f, -0.5f, -0.5f), vec3(color), vec2(1.f, 0.f), vec3(NORMAL_YNEG) },

            // FRONT FACE
            { vec3(-0.5f, -0.5f, 0.5f), vec3(color), vec2(0.f, 1.f), vec3(0.f, 1.f, 1.f) },
            { vec3(0.0f, 0.5f, 0.0f), vec3(color), vec2(0.5f, 0.5f), vec3(0.f, 1.f, 1.f) },
            { vec3(0.5f, -0.5f, 0.5f), vec3(color), vec2(1.f, 0.f), vec3(0.f, 1.f, 1.f) },

            // BACK FACE
            { vec3(-0.5f, -0.5f, -0.5f), vec3(color), vec2(0.f, 1.f), vec3(0.f, 1.f, -1.f) },
            { vec3(0.0f, 0.5f, 0.0f), vec3(color), vec2(0.5f, 0.5f), vec3(0.f, 1.f, -1.f) },
            { vec3(0.5f, -0.5f, -0.5f), vec3(color), vec2(1.f, 0.f), vec3(0.f, 1.f, -1.f) },

            // RIGHT FACE
            { vec3(0.5f, -0.5f, 0.5f), vec3(color), vec2(0.f, 1.f), vec3(1.f, 1.f, 0.f) },
            { vec3(0.0f, 0.5f, 0.0f), vec3(color), vec2(0.5f, 0.5f), vec3(1.f, 1.f, 0.f) },
            { vec3(0.5f, -0.5f, -0.5f), vec3(color), vec2(1.f, 0.f), vec3(1.f, 1.f, 0.f) },

            // LEFT FACE
            { vec3(-0.5f, -0.5f, -0.5f), vec3(color), vec2(0.f, 1.f), vec3(-1.f, 1.f, 0.f) },
            { vec3(0.0f, 0.5f, 0.0f), vec3(color), vec2(0.5f, 0.5f), vec3(-1.f, 1.f, 0.f) },
            { vec3(-0.5f, -0.5f, 0.5f), vec3(color), vec2(1.f, 0.f), vec3(-1.f, 1.f, 0.f) }
		};

		indices = {
			0, 1, 2,
            0, 2, 3,

            4, 5, 6,

            7, 8, 9,

            10, 11, 12,

            13, 14, 15
		};

		init();
	}
};