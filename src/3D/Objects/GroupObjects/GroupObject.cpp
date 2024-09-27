#include <3D/Objects/GroupObjects/GroupObject.h>

GroupObject::GroupObject(const char* p_name, const char* p_modelPath, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
BaseObject(p_name, p_worldTransform, p_parent)
{
    if(p_modelPath)
    {
        this->m_mesh = ObjectsHelper::loadMesh(p_modelPath);
        this->setColor(p_color);
    }
}

GroupObject::~GroupObject()
{

}

void GroupObject::update()
{
    for(int i = 0; i < this->m_childrenObjects.size(); i++)
    {
        this->m_childrenObjects[i]->update();
    }
}

void GroupObject::initPhysics(btDiscreteDynamicsWorld* p_dynamicsWorld)
{
    for(int i = 0; i < this->m_childrenObjects.size(); i++)
    {
        this->m_childrenObjects[i]->initPhysics(p_dynamicsWorld);
    }
}

void GroupObject::addChildObject(BaseObject* p_object)
{
    this->m_childrenObjects.push_back(p_object);
}