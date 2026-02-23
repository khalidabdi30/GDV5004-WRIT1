#include "Scene.h"

Scene::Scene() = default;

void Scene::setRoot(std::shared_ptr<SceneNode> root) {
    m_root = root;
}

std::shared_ptr<SceneNode> Scene::getRoot() const {
    return m_root;
}
