#pragma once

#include "material.hh"

namespace Draw{
    struct Vertex{
	union{
	    glm::vec4 col;
	    u32 submittedQuads;
	};
	union{
	    glm::vec3 pos;
	    u16 shader;
	};
	glm::vec2 textPos;
	u32 textID;
    };

    const u32 maxQuadCount   = 1000;
    const u32 maxVertexCount = maxQuadCount * 4;
    const u32 maxIndexCount  = maxQuadCount * 6;
};

struct Renderer{
    Draw::Vertex *renderBuffer;
    Draw::Vertex *watermark;

    bool bufferEmpty;
    u32 qvbo;
    u32 qvao;
    u32 qibo;
    u32 indexCount;
    u32 drawCalls;
};
