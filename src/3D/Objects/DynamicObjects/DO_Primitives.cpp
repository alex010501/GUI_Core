#include <3D/Objects/DynamicObjects/DO_Primitives.h>

CubeDO::CubeDO(const char* p_name, double a, double b, double c, double p_mass, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
DynamicObject(p_name, "primitive", p_mass, p_worldTransform, p_parent, p_color)
{
    this->m_mesh = ObjectsHelper::createCube(a, b, c);
    this->setColor(p_color);

    this->m_rigidBody = ObjectsHelper::createDynamicCubeBody(a, b, c, ObjectsHelper::getBTTransform(this->getWorldTransform()), p_mass);
}

CylinderDO::CylinderDO(const char* p_name, double h, double r, double p_mass, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
DynamicObject(p_name, "primitive", p_mass, p_worldTransform, p_parent, p_color)
{
    this->m_mesh = ObjectsHelper::createCylinder(h, r);
    this->setColor(p_color);

    this->m_rigidBody = ObjectsHelper::createDynamicCylinderBody(h, r, ObjectsHelper::getBTTransform(this->getWorldTransform()), p_mass);
}

SphereDO::SphereDO(const char* p_name, double r, double p_mass, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
DynamicObject(p_name, "primitive", p_mass, p_worldTransform, p_parent, p_color)
{
    this->m_mesh = ObjectsHelper::createSphere(r);
    this->setColor(p_color);

    this->m_rigidBody = ObjectsHelper::createDynamicSphereBody(r, ObjectsHelper::getBTTransform(this->getWorldTransform()), p_mass);
}