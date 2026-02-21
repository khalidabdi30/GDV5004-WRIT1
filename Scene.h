#pragma once
#include "SceneNode.h"
#include <memory>

class Scene {
public:
    Scene();

    std::shared_ptr<SceneNode> getRoot() const;
    void setRoot(std::shared_ptr<SceneNode> root);

private:
    std::shared_ptr<SceneNode> m_root;
};
