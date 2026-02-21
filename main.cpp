#include <iostream>
#include <filesystem>
#include "tinyxml2.h"
#include "Scene.h"

using namespace tinyxml2;
namespace fs = std::filesystem;

std::shared_ptr<SceneNode> parseNode(XMLElement* xmlNode) {
    const char* nameAttr = xmlNode->Attribute("name");
    std::string nodeName = nameAttr ? nameAttr : "UnnamedNode";

    auto node = std::make_shared<SceneNode>(nodeName);

    // Look for attached entity
    XMLElement* entity = xmlNode->FirstChildElement("entity");
    if (entity) {
        const char* meshFile = entity->Attribute("meshFile");
        if (meshFile) {
            node->setMeshFile(meshFile);
        }
    }

    // Parse child nodes recursively
    XMLElement* child = xmlNode->FirstChildElement("node");
    while (child) {
        node->addChild(parseNode(child));
        child = child->NextSiblingElement("node");
    }

    return node;
}

void validateNode(const std::shared_ptr<SceneNode>& node) {
    if (!node->getMeshFile().empty()) {
        if (!fs::exists(node->getMeshFile())) {
            std::cout << "[ERROR] Missing mesh: "
                      << node->getMeshFile()
                      << " (Node: " << node->getName() << ")\n";
        }
    }

    for (const auto& child : node->getChildren()) {
        validateNode(child);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: SceneVerifier <scene_file.scene>\n";
        return 1;
    }

    XMLDocument doc;
    if (doc.LoadFile(argv[1]) != XML_SUCCESS) {
        std::cerr << "Failed to load scene file\n";
        return 1;
    }

    XMLElement* sceneElem = doc.FirstChildElement("scene");
    if (!sceneElem) {
        std::cerr << "Invalid scene file\n";
        return 1;
    }

    XMLElement* rootNodeElem = sceneElem->FirstChildElement("nodes")
                                         ->FirstChildElement("node");

    Scene scene;
    scene.setRoot(parseNode(rootNodeElem));

    std::cout << "Scene loaded. Validating...\n";
    validateNode(scene.getRoot());

    std::cout << "Validation complete.\n";
    return 0;
}
