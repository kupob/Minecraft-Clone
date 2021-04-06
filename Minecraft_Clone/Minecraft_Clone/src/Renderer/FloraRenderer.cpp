#include "FloraRenderer.h"

#include "../Application.h"
#include "../Camera.h"
#include "../World/Block/BlockDatabase.h"
#include "../World/Chunk/ChunkMesh.h"

void FloraRenderer::add(const ChunkMesh &mesh)
{
    m_chunks.push_back(&mesh.getModel().getRenderInfo());
}

void FloraRenderer::render(const Camera &camera)
{
    if (m_chunks.empty()) {
        return;
    }

    //glDisable(GL_BLEND);
    //glEnable(GL_CULL_FACE);

    m_shader.useProgram();

	m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
	m_shader.loadProjectionMatrix(camera.getProjMatrix());
	m_shader.loadViewMatrix(camera.getViewMatrix());
	m_shader.loadTime(g_info.elapsedTime);
	m_shader.loadLight(g_info.lighting);

	m_shader.loadDTime(g_info.dayTime);

    for (auto mesh : m_chunks) {
        GL::bindVAO(mesh->vao);
        GL::drawElements(mesh->indicesCount);
    }

    m_chunks.clear();
}
