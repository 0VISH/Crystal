#pragma once

struct FrameBuffer{
    u32 fbo;
    u32 rbo;
    u32 texture;

    void init(u32 x, u32 y);
    void uninit();
    void bind();
    void unbind();
};
