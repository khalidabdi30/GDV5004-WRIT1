#include "SceneNode.h"

SceneNode::SceneNode(const std::string& name)
    : m_name(name) {}

void SceneNode::addChild(std::shared_ptr<SceneNode> child) {
    m_children.push_back(child);
}

void SceneNode::setMeshFile(const std::string& mesh) {
    m_meshFile = mesh;
}

const std::string& SceneNode::getName() const {
    return m_name;
}

const std::string& SceneNode::getMeshFile() const {
    return m_meshFile;
}

const std::vector<std::shared_ptr<SceneNode>>& SceneNode::getChildren() const {
    return m_children;
}
