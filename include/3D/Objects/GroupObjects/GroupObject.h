#pragma once
#include <3D/Objects/BaseObject.h>

class GroupObject: public BaseObject
{
private:
    // For group objects
    std::vector<BaseObject*> m_childrenObjects;    

protected:

public:
    GroupObject(const char* p_name, const char* p_modelPath, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    ~GroupObject();

    void update() override;

    void initPhysics(btDiscreteDynamicsWorld* p_dynamicsWorld) override;

    void addChildObject(BaseObject* p_object);
};