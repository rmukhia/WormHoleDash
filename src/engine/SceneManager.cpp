//
// Created by Raunak Mukhia on 11/4/18.
//


#include "Scene.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = 0;

SceneManager* SceneManager::instance() {
    if (!_instance) {
        _instance = new SceneManager();
    }
    return _instance;
}

std::vector<Scene*> *SceneManager::getScenes() {
    return &scenes;
}

int SceneManager::getCurrSceneIndex() const {
    return currSceneIndex;
}

void SceneManager::setCurrSceneIndex(int currSceneIndex) {
    SceneManager::currSceneIndex = currSceneIndex;
}

