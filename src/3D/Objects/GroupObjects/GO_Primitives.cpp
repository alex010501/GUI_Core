#include <3D/Objects/GroupObjects/GO_Primitives.h>

CubeGO::CubeGO(const char* p_name, double a, double b, double c, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
GroupObject(p_name, NULL, p_worldTransform, p_parent, p_color)
{
    this->m_mesh = ObjectsHelper::createCube(a, b, c);
    this->setColor(p_color);
}

CylinderGO::CylinderGO(const char* p_name, double h, double r, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
GroupObject(p_name, NULL, p_worldTransform, p_parent, p_color)
{
    this->m_mesh = ObjectsHelper::createCylinder(h, r);
    this->setColor(p_color);
}

SphereGO::SphereGO(const char* p_name, double r, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color):
GroupObject(p_name, NULL, p_worldTransform, p_parent, p_color)
{
    this->m_mesh = ObjectsHelper::createSphere(r);
    this->setColor(p_color);
}