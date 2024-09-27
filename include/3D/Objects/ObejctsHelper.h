#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <osg/Geode>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
// #include <osg/PositionAttitudeTransform>

#include <btBulletDynamicsCommon.h>


namespace ObjectsHelper
{
    enum moveOption
    {
        LOCAL_ABS = 0,
        LOCAL_REL = 1,
        WORLD_ABS = 2,
        WORLD_REL = 3
    };

    void setColor(osg::ref_ptr<osg::Geode> p_geode, osg::Vec4 p_color);

    osg::ref_ptr<osg::Geode> createSphere(double p_radius);

    osg::ref_ptr<osg::Geode> createCube(double p_a, double p_b, double p_c);

    osg::ref_ptr<osg::Geode> createCylinder(double p_radius, double p_height);

    osg::ref_ptr<osg::Geode> loadMesh(const char* p_path);

    btTransform getBTTransform(osg::ref_ptr<osg::MatrixTransform> p_transform);

    osg::Matrix getOSGTransform(btTransform p_transform);

    btRigidBody* createStaticSphereBody(double p_radius, btTransform p_transform);

    btRigidBody* createStaticCylinderBody(double p_radius, double p_height, btTransform p_transform);

    btRigidBody* createStaticCubeBody(double p_a, double p_b, double p_c, btTransform p_transform);

    btRigidBody* createStaticMeshBody(const char* p_path, btTransform p_transform);

    btRigidBody* createDynamicSphereBody(double p_radius, btTransform p_transform, double p_mass);

    btRigidBody* createDynamicCylinderBody(double p_radius, double p_height, btTransform p_transform, double p_mass);

    btRigidBody* createDynamicCubeBody(double p_a, double p_b, double p_c, btTransform p_transform, double p_mass);

    btRigidBody* createDynamicMeshBody(const char* p_path, btTransform p_transform, double p_mass);
}
