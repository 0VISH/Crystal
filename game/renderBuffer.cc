#include "renderer.hh"

void useMaterial(Renderer *r, Material *m){
    r->curMat = m;
};
void submitQuad(Renderer *r, glm::mat4 &mat){
    float quadVertices[] = {
	0.5f,  0.5f,
	0.5f, -0.5f,
	-0.5f, -0.5f,
	-0.5f,  0.5f,
    };
    Draw::Vertex &v1 = *r->watermark;
    v1.pos = mat * glm::vec4(quadVertices[0], quadVertices[1], 0.0, 1.0);
    v1.col = r->curMat->col;
    r->watermark += 1;

    Draw::Vertex &v2 = *r->watermark;
    v2.pos = mat * glm::vec4(quadVertices[2], quadVertices[3], 0.0, 1.0);
    v2.col = r->curMat->col;
    r->watermark += 1;

    Draw::Vertex &v3 = *r->watermark;
    v3.pos = mat * glm::vec4(quadVertices[4], quadVertices[5], 0.0, 1.0);
    v3.col = r->curMat->col;
    r->watermark += 1;

    Draw::Vertex &v4 = *r->watermark;
    v4.pos = mat * glm::vec4(quadVertices[6], quadVertices[7], 0.0, 1.0);
    v4.col = r->curMat->col;
    r->watermark += 1;
	    
    r->indexCount += 6;
};
