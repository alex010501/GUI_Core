#pragma once

#include <iostream>
#include <string>
#include <cstring>

#include <stb_image.h>
#include <assimp/Importer.hpp>

#include <osgViewer/Viewer>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osgGA/FirstPersonManipulator>
#include <osg/Texture2D>

#include <btBulletDynamicsCommon.h>

#include <3D/Objects/BaseObject.h>

class Scene
{
private:
    // Bullet Physics
    btDiscreteDynamicsWorld* m_dynamicsWorld;
    btAxisSweep3* m_broadphase;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btSequentialImpulseConstraintSolver* m_solver;
    
    // Base Visualization
    osg::ref_ptr<osg::ShapeDrawable> m_floor;
    osg::ref_ptr<osg::Group> m_XYZAxes;
    osg::ref_ptr<osg::ShapeDrawable> createFloor();
    osg::ref_ptr<osg::Group> createAxes();

    // Base physics
    btRigidBody* m_groundbody;
    btRigidBody* createGround();

    // Object List
    std::vector<BaseObject> m_objectList;
    
protected:
    osg::ref_ptr<osg::Group> m_root;

public:
    Scene();
    ~Scene();

    osg::ref_ptr<osg::Group> getSceneRoot(){return m_root.get();}

    void initPhysics();

    void update(double p_dt);
};