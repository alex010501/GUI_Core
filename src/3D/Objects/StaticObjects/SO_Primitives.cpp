#include <3D/Objects/StaticObjects/SO_Primitives.h>

CubeSO::CubeSO(const char* p_name, double a, double b, double c, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
StaticObject(p_name, "primitive", p_worldTransform, p_parent, p_color)
{
    this->m_mesh = ObjectsHelper::createCube(a, b, c);
    this->setColor(p_color);

    this->m_rigidBody = ObjectsHelper::createStaticCubeBody(a, b, c, ObjectsHelper::getBTTransform(this->getWorldTransform()));
}

CylinderSO::CylinderSO(const char* p_name, double h, double r, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
StaticObject(p_name, "primitive", p_worldTransform, p_parent, p_color)
{
    this->m_mesh = ObjectsHelper::createCylinder(h, r);
    this->setColor(p_color);

    this->m_rigidBody = ObjectsHelper::createStaticCylinderBody(h, r, ObjectsHelper::getBTTransform(this->getWorldTransform()));
}

SphereSO::SphereSO(const char* p_name, double r, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
StaticObject(p_name, "primitive", p_worldTransform, p_parent, p_color)
{
    this->m_mesh = ObjectsHelper::createSphere(r);
    this->setColor(p_color);

    this->m_rigidBody = ObjectsHelper::createStaticSphereBody(r, ObjectsHelper::getBTTransform(this->getWorldTransform()));
}