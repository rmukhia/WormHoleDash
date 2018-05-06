//
// Created by Raunak Mukhia on 6/5/18.
//

#include "TextureBox.h"
#include "../../engine/getBMP.h"

void TextureBox::create() {
    loadTextures();
    glGenTextures(6, textures);

    for (int face = 0; face < 6; face++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[face]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageCube[face]->width, imageCube[face]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageCube[face]->data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

}

void TextureBox::updateMaterial() {
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat matSpec[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat matAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat matDiff[] = { 0.0, 0.0, 0,0, 1.0 };
    GLfloat matShine[] = { 0.0 };

    // emission
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

    // specular
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);

    // shine
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

    // ambient
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmb);


    // diffuse
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiff);
}

void TextureBox::draw() {
    glEnable(GL_TEXTURE_2D);

    GLfloat w = 1000.0;
    GLfloat h = 1000.0;
    GLfloat d = 1000.0;

    glEnable(GL_COLOR_MATERIAL);

    // face 1
    glPushMatrix();

    // back
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    updateMaterial();
    glTexCoord2f(0.0, 0.0); glVertex3f(-w, h, d);
    glTexCoord2f(1.0, 0.0); glVertex3f(w, h, d);
    glTexCoord2f(1.0, 1.0); glVertex3f(w, -h, d);
    glTexCoord2f(0.0, 1.0); glVertex3f(-w, -h, d);
    glEnd();

    // front
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glColor4f(1.0, 1.0, 1.0,1.0);
    glBegin(GL_POLYGON);
    updateMaterial();
    glTexCoord2f(0.0, 1.0); glVertex3f(-w, -h, -d);
    glTexCoord2f(1.0, 1.0); glVertex3f(w, -h, -d);
    glTexCoord2f(1.0, 0.0); glVertex3f(w, h, -d);
    glTexCoord2f(0.0, 0.0); glVertex3f(-w, h, -d);
    glEnd();

    // top
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glColor4f(1.0,1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    updateMaterial();
    glTexCoord2f(0.0, 0.0); glVertex3f(-w, h, -d);
    glTexCoord2f(1.0, 0.0); glVertex3f(w, h, -d);
    glTexCoord2f(1.0, 1.0); glVertex3f(w, h, d);
    glTexCoord2f(0.0, 1.0); glVertex3f(-w, h, d);
    glEnd();


    // bottom
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glColor4f(1.0,1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    updateMaterial();
    glTexCoord2f(0.0, 0.0); glVertex3f(-w, -h, d);
    glTexCoord2f(1.0, 0.0); glVertex3f(w, -h, d);
    glTexCoord2f(1.0, 1.0); glVertex3f(w, -h, -d);
    glTexCoord2f(0.0, 1.0); glVertex3f(-w, -h, -d);
    glEnd();

    // left
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glColor4f(1.0,1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    updateMaterial();
    glTexCoord2f(1.0, 1.0); glVertex3f(-w, -h, d);
    glTexCoord2f(0.0, 1.0); glVertex3f(-w, -h, -d);
    glTexCoord2f(0.0, 0.0); glVertex3f(-w, h, -d);
    glTexCoord2f(1.0, 0.0); glVertex3f(-w, h, d);
    glEnd();

    // right
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glColor4f(1.0,1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    updateMaterial();
    glTexCoord2f(1.0, 1.0); glVertex3f(w, -h, d);
    glTexCoord2f(0.0, 1.0); glVertex3f(w, -h, -d);
    glTexCoord2f(0.0, 0.0); glVertex3f(w, h, -d);
    glTexCoord2f(1.0, 0.0); glVertex3f(w, h, d);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
}

void TextureBox::update() {

}

void TextureBox::destroy() {

}

void TextureBox::act(Command *pCommand) {

}

void TextureBox::loadTextures() {
    imageCube[0] = getBMP("../resources/textures/background/back.bmp");
    imageCube[1] = getBMP("../resources/textures/background/front.bmp");
    imageCube[2] = getBMP("../resources/textures/background/top.bmp");
    imageCube[3] = getBMP("../resources/textures/background/bot.bmp");
    imageCube[4] = getBMP("../resources/textures/background/left.bmp");
    imageCube[5] = getBMP("../resources/textures/background/right.bmp");
}

GLfloat *TextureBox::getBuggyTransform() {
    return buggyTransform;
}

