#include <3D/Objects/DynamicObjects/DynamicObject.h>

DynamicObject::DynamicObject(const char* p_name, const char* p_modelPath, double p_mass, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
BaseObject(p_name, p_worldTransform, p_parent)
{
    if(p_modelPath)
    {
        this->m_mesh = ObjectsHelper::loadMesh(p_modelPath);
        this->setColor(p_color);

        this->m_rigidBody = ObjectsHelper::createDynamicMeshBody(p_modelPath, ObjectsHelper::getBTTransform(this->getWorldTransform()), p_mass);
    }
}

DynamicObject::~DynamicObject()
{
    delete this->m_rigidBody;

    // delete this->m_shape;
    // delete this->m_motionState;
}

void DynamicObject::update()
{
    this->moveObject(ObjectsHelper::moveOption::WORLD_ABS, ObjectsHelper::getOSGTransform(this->m_rigidBody->getWorldTransform()));
}

void DynamicObject::initPhysics(btDiscreteDynamicsWorld* p_dynamicsWorld)
{
    p_dynamicsWorld->addRigidBody(this->m_rigidBody);
}