#pragma once

#include <3D/Objects/BaseObject.h>

class StaticObject : public BaseObject
{
protected:
    // For physics objects
    // btCollisionShape* m_shape;
    // btDefaultMotionState* m_motionState;
    btRigidBody* m_rigidBody;

public:
    StaticObject(const char* p_name, const char* p_modelPath, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    ~StaticObject();

    void initPhysics(btDiscreteDynamicsWorld* p_dynamicsWorld) override;
};