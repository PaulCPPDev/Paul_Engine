#ifndef PAULENGINE_RENDERER_IRENDERER_H_
#define PAULENGINE_RENDERER_IRENDERER_H_




//////////////////////////////////////////////////////
///////// Provided Interface /////////////////////////
/////////////////////////////////////////////////////

namespace renderer {
class IRenderer {	
  public:
    
    virtual ~IRenderer() {
    
    }
    
    virtual void init() = 0;
    virtual void set_up() = 0;
    virtual bool is_running() = 0;
    virtual void process_input() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void destroy() = 0;             		
};

} // namespace renderer

#endif
