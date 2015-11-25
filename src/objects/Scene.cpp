//
// Created by Martin on 22. 11. 2015.
//

#include "src/objects/Scene.hpp"

Scene::Scene(nsMaterRenderer::MasterRenderer *masterRenderer, Light *light,
             glm::mat4 projection, nsThirdPersonCamera::ThirdPersonCamera *camera) {
    this->masterRenderer = masterRenderer;
    this->light = light;
    this->projection = projection;
    this->camera = camera;
}

void Scene::addObjectToScene(Mesh *mesh) {
    this->objects.push_back(mesh);
}

void Scene::addGroundToScene(nsGround::Ground *ground) {
    this->grounds.push_back(ground);
}

void Scene::animate(float delta) {
    for (auto objectLoop : this->objects) {
        objectLoop->animate(this, delta);
    }

    camera->move();
}

void Scene::render() {

    for (auto meshLoop : this->objects) {
        masterRenderer->processMesh(meshLoop);
    }

    for (auto groundLoop : this->grounds) {
        masterRenderer->processGround(groundLoop);
    }

    masterRenderer->render(this->projection, this->camera->getViewMatrix(), this->light);
}

void Scene::processWrapper(MeshWrapper *wrapper) {
    this->wrappers.push_back(wrapper);
    this->masterRenderer->processWrapper(wrapper);
}

void Scene::processGui(Gui *gui) {
    this->guis.push_back(gui);
    this->masterRenderer->processGui(gui);
}