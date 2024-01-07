#include <math.h>
#include "renderer.hh"
#include "crystal.hh"
#include "componentID.hh"

void submitQuad(Renderer &r, const glm::mat4 &mat, Material &m){
    Draw::Vertex &v1 = *r.watermark;
    v1.pos = mat * glm::vec4(0.5f, 0.5f, 0.0, 1.0);
    v1.textPos = glm::vec2(1.0f, 1.0f);
    v1.col = m.col;
    v1.textID = m.textureId;
    r.watermark += 1;

    Draw::Vertex &v2 = *r.watermark;
    v2.pos = mat * glm::vec4(0.5f, -0.5f, 0.0, 1.0);
    v1.textPos = glm::vec2(1.0f, 0.0f);
    v2.col = m.col;
    v2.textID = m.textureId;
    r.watermark += 1;

    Draw::Vertex &v3 = *r.watermark;
    v3.pos = mat * glm::vec4(-0.5f, -0.5f, 0.0, 1.0);
    v1.textPos = glm::vec2(0.0f, 0.0f);
    v3.col = m.col;
    v3.textID = m.textureId;
    r.watermark += 1;

    Draw::Vertex &v4 = *r.watermark;
    v4.pos = mat * glm::vec4(-0.5f, 0.5f, 0.0, 1.0);
    v1.textPos = glm::vec2(0.0f, 1.0f);
    v4.col = m.col;
    v4.textID = m.textureId;
    r.watermark += 1;
    
    r.indexCount += 6;
};
void fillRenderBufferWithGivenMat(Renderer &r, Material &m){
    Draw::Vertex *info = r.watermark;
    info->shader = m.shader;
    r.watermark += 1;
    u32 submittedQuads = 0;
    for(u32 x=0; x<m.registeredEntities.count; x+=1){
	Entity e = m.registeredEntities[x];
	auto *transform = (Component::Transform*)getComponent(e, (u32)ComponentID::TRANSFORM);
	if(transform == nullptr){continue;};
	submitQuad(r, transform->genMatrix(), m);
	submittedQuads += 1;
    };
    if(submittedQuads == 0){
	r.watermark -= 1;
	return;
    };
    info->submittedQuads = submittedQuads;
};
void fillRenderBufferWithGivenMS(Renderer &r, MaterialSystem *ms){
    for(u32 x=0; x<ms->materials.count; x+=1){
	fillRenderBufferWithGivenMat(r, ms->materials[x]);
    };
};
void fillRenderBufferHeader(Renderer &r, const glm::mat4 &projectionView){
    r.watermark = r.renderBuffer;
    r.bufferEmpty = false;

    memcpy(r.watermark, &projectionView, sizeof(projectionView));
    r.watermark += (u32)ceil((f64)sizeof(glm::mat4)/(f64)sizeof(Draw::Vertex));
};
