#include <3D/Objects/StaticObjects/StaticObject.h>

StaticObject::StaticObject(const char* p_name, const char* p_modelPath, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
BaseObject(p_name, p_worldTransform, p_parent)
{
    if(p_modelPath)
    {
        this->m_mesh = ObjectsHelper::loadMesh(p_modelPath);
        this->setColor(p_color);

        this->m_rigidBody = ObjectsHelper::createStaticMeshBody(p_modelPath, ObjectsHelper::getBTTransform(this->getWorldTransform()));
    }
}

StaticObject::~StaticObject()
{
    delete this->m_rigidBody;

    // delete this->m_shape;
    // delete this->m_motionState;
}

void StaticObject::initPhysics(btDiscreteDynamicsWorld* p_dynamicsWorld)
{
    p_dynamicsWorld->addRigidBody(this->m_rigidBody);
}