#ifndef SCENES
#define SCENES

#include "core/InputManager.hpp"

class Scene 
{
public:
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void ProcessInput(const InputManager& input) = 0;
    virtual void Render() = 0;
    virtual void Destroy() = 0;
    virtual ~Scene() = default;
};

#endif