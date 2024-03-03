#ifndef PAULENGINE_RENDERER_RENDERER_H_
#define PAULENGINE_RENDERER_RENDERER_H_

#include "Renderer/IRenderer.h"


#include <vector>

#include <SDL2/SDL.h>

#include "Renderer/Camera.h"
#include "Renderer/Clipping.h"
#include "Renderer/Display.h"
#include "Renderer/Light.h"
#include "Renderer/Mesh.h"
#include "Renderer/Triangle.h"

//////////////////////////////////////////////////////
///////// Implements Interface       /////////////////
/////////  means provides Interface //////////////////
/////////////////////////////////////////////////////

namespace renderer {
class Renderer  : public IRenderer {
  public:
    bool isRunning = true;

    display::Display* display = NULL;
    std::vector<Mesh> meshes;
    camera::Camera* camera;
    Light* light;
		
    glm::mat4 proj_matrix;		
    // refactor
    std::vector<Triangle> triangles_to_render;
    int triangles_to_render_count = 0;
		
  public:
    Renderer()= default;
    ~Renderer() = default;
		
    void init() override;
    void set_up() override;
    bool is_running() override;
    void process_input() override;
    void update() override;
    void render() override;
    void destroy() override;
    void pipeline(Mesh& mesh);
    glm::mat4 projection_matrix(float fov, float aspect, float znear, float zfar);
                		
};

} // namespace renderer

#endif
