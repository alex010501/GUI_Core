#include <3D/Objects/StaticObjects/StaticObject.h>

class CubeSO : public StaticObject
{
public:
    CubeSO(const char* p_name, double a, double b, double c, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
};

class CylinderSO : public StaticObject
{
public:
    CylinderSO(const char* p_name, double h, double r, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
};

class SphereSO : public StaticObject
{
public:
    SphereSO(const char* p_name, double r, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
};