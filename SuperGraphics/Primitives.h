#pragma once
#include "Primitive.h"
#include "colors.h"

class Triangle : public Primitive {
public:
	Triangle(Texture *texture,
		vec3 position = vec3(0.f),
		vec3 rotation = vec3(0.f),
		vec3 scale = vec3(1.f)
	) : Primitive(texture, position, rotation, scale) {
		vertices = {
			{ vec3(-0.15f, 0.f, 0.f), vec3(GREY), vec2(0.f, 0.f) },
			{ vec3(0.f, 0.4f, 0.f), vec3(SILVER), vec2(0.f, 1.f) },
			{ vec3(0.15f, 0.f, 0.f), vec3(SILVER), vec2(1.f, 1.f) },
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
            { vec3(-0.5f, -0.5f, 0.f), vec3(RED), vec2(0.f, 0.f) },
            { vec3(-0.5f, 0.5f, 0.f), vec3(GREEN), vec2(0.f, 1.f) },
            { vec3(0.5f, 0.5f, 0.f), vec3(BLUE), vec2(1.f, 1.f) },
            { vec3(0.5f, -0.5f, 0.f), vec3(RED), vec2(1.f, 0.f) },
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
            { vec3(-0.5f, -0.5f, 0.5f), vec3(BLACK), vec2(0.f, 1.f) },
            { vec3(-0.5f, 0.5f, 0.5f), vec3(BLACK), vec2(0.f, 0.f) },
            { vec3(0.5f, 0.5f, 0.5f), vec3(BLACK), vec2(1.f, 0.f) },
            { vec3(0.5f, -0.5f, 0.5f), vec3(BLACK), vec2(1.f, 1.f) },

            { vec3(-0.5f, -0.5f, -0.5f), vec3(BLACK), vec2(0.f, 1.f) },
            { vec3(-0.5f, 0.5f, -0.5f), vec3(BLACK), vec2(0.f, 0.f) },
            { vec3(0.5f, 0.5f, -0.5f), vec3(BLACK), vec2(1.f, 0.f) },
            { vec3(0.5f, -0.5f, -0.5f), vec3(BLACK), vec2(1.f, 1.f) }
        };

        indices = {
            0, 1, 2,
            0, 2, 3,

            5, 6, 7,
            5, 4, 7,

            1, 0, 4,
            1, 5, 4,

            2, 3, 7,
            2, 6, 7,

            1, 2, 6,
            1, 5, 6,

            0, 3, 7,
            0, 4, 7,
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
			{ vec3(-0.5f, -0.5f, 0.5f), vec3(color), vec2(0.f, 1.f) },
		{ vec3(-0.5f, -0.5f, -0.5f), vec3(color), vec2(0.f, 0.f) },
		{ vec3(0.5f, -0.5f, -0.5f), vec3(color), vec2(1.f, 0.f) },
		{ vec3(0.5f, -0.5f, 0.5f), vec3(color), vec2(1.f, 1.f) },
		{ vec3(0.0f, 0.5f, 0.0f), vec3(color), vec2(1.f, 1.f) },
		};

		indices = {
			0, 1, 2,

			0, 2, 3,

			0, 1, 4,

			1, 2, 4,

			2, 3, 4,

			0, 3, 4,

			0, 1, 4,
		};

		init();
	}
};