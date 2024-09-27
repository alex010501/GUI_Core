#pragma once

#include <3D/Objects/ObejctsHelper.h>

class BaseObject
{
private:
    const char* m_name;

protected:
    // Hierarchy variables
    BaseObject* m_parent;

    // OSG variables
    osg::ref_ptr<osg::MatrixTransform> m_localTransform;
    osg::ref_ptr<osg::Geode> m_mesh;
    osg::Vec4 m_color;

public:
    BaseObject(const char* p_name, osg::ref_ptr<osg::MatrixTransform> p_worldTransform, BaseObject* p_parent = nullptr);

    virtual ~BaseObject() {};

    virtual void update() = 0;

    virtual void initPhysics(btDiscreteDynamicsWorld* p_dynamicsWorld);

    void setColor(osg::Vec4 p_color);

    const char* getName(){ return m_name; }

    BaseObject* getParent(){ return m_parent; }

    osg::ref_ptr<osg::MatrixTransform> getWorldTransform();

    osg::ref_ptr<osg::MatrixTransform> getLocalTransform();

    void moveObject(ObjectsHelper::moveOption p_moveOption, osg::Matrix p_transform);
};