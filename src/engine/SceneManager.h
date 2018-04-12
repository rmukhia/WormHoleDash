//
// Created by Raunak Mukhia on 11/4/18.
//

#ifndef CGPROJECT_SCENEMANAGER_H
#define CGPROJECT_SCENEMANAGER_H

#include<vector>
#include "Scene.h"

class SceneManager {
private:
    static SceneManager * _instance;

    std::vector<Scene*> scenes;

    int currSceneIndex;

protected:
    SceneManager() {};

public:
    static SceneManager * instance();

    std::vector<Scene*> getScenes();

    Scene getActiveScene() {
        return *scenes[currSceneIndex];
    }

    void setActiveScene(int index) {
        setCurrSceneIndex(index);
    }

    int getCurrSceneIndex() const;

    void setCurrSceneIndex(int currSceneIndex);
};


#endif //CGPROJECT_SCENEMANAGER_H
