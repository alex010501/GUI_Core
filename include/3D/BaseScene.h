#pragma once

#include <iostream>
#include <string>
#include <cstring>

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <BulletCollision/BroadphaseCollision/btDbvt.h>

#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osgGA/FirstPersonManipulator>
#include <osg/Texture2D>

#include <3D/BaseObject.h>

class BaseScene
{
private:
    osg::ref_ptr<osg::ShapeDrawable> createFloor();

    osg::ref_ptr<osg::Group> createAxes();

    osg::ref_ptr<osg::ShapeDrawable> m_floor;
    osg::ref_ptr<osg::Group> m_XYZAxes;

    std::vector<Base3DObject> m_objectList;
protected:
    osg::ref_ptr<osg::Group> m_root;

public:
    BaseScene();

    osg::ref_ptr<osg::Group> getSceneRoot(){return m_root.get();}

    void update();
};