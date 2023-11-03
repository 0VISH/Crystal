#include <math.h>
#include "renderer.hh"
#include "crystal.hh"
#include "componentID.hh"

void submitQuad(Renderer &r, const glm::mat4 &mat){
    float quadVertices[] = {
	0.5f,  0.5f,
	0.5f, -0.5f,
	-0.5f, -0.5f,
	-0.5f,  0.5f,
    };
    Draw::Vertex &v1 = *r.watermark;
    v1.pos = mat * glm::vec4(quadVertices[0], quadVertices[1], 0.0, 1.0);
    v1.col = r.curMat->col;
    r.watermark += 1;

    Draw::Vertex &v2 = *r.watermark;
    v2.pos = mat * glm::vec4(quadVertices[2], quadVertices[3], 0.0, 1.0);
    v2.col = r.curMat->col;
    r.watermark += 1;

    Draw::Vertex &v3 = *r.watermark;
    v3.pos = mat * glm::vec4(quadVertices[4], quadVertices[5], 0.0, 1.0);
    v3.col = r.curMat->col;
    r.watermark += 1;

    Draw::Vertex &v4 = *r.watermark;
    v4.pos = mat * glm::vec4(quadVertices[6], quadVertices[7], 0.0, 1.0);
    v4.col = r.curMat->col;
    r.watermark += 1;
	    
    r.indexCount += 6;
};
void fillRenderBufferWithGivenMat(Renderer &r, Material &m){
    r.curMat = &m;
    Draw::Vertex *info = r.watermark;
    info->pos.x = m.shader;
    r.watermark += 1;
    u32 submittedQuads = 0;
    for(u32 x=0; x<m.registeredEntities.count; x+=1){
	Entity e = m.registeredEntities[x];
	auto *transform = (Component::Transform*)getComponent(e, (u32)ComponentID::TRANSFORM);
	if(transform == nullptr){continue;};
	submitQuad(r, transform->genMatrix());
	submittedQuads += 1;
    };
    if(submittedQuads == 0){
	r.watermark -= 1;
	return;
    };
    info->pos.y = submittedQuads;
    print("qua: %d", submittedQuads);
};
void fillRenderBufferWithGivenMS(Renderer &r, MaterialSystem *ms){
    for(u32 x=0; x<ms->materials.count; x+=1){
	fillRenderBufferWithGivenMat(r, ms->materials[x]);
    };
};
void fillRenderBufferHeader(Renderer &r, const glm::mat4 &projectionView){
    r.watermark = r.renderBuffer;
    r.bufferEmpty = false;

    glm::mat4 *mat = (glm::mat4*)r.watermark;
    *mat = projectionView;
    r.watermark += (u32)ceil((f64)sizeof(glm::mat4)/(f64)sizeof(Draw::Vertex));
};
