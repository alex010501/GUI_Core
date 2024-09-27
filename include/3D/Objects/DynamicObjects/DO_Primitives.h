#include <3D/Objects/DynamicObjects/DynamicObject.h>

class CubeDO : public DynamicObject
{
public:
    CubeDO(const char* p_name, double a, double b, double c, double p_mass, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
};

class CylinderDO : public DynamicObject
{
public:
    CylinderDO(const char* p_name, double h, double r, double p_mass, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
};

class SphereDO : public DynamicObject
{
public:
    SphereDO(const char* p_name, double r, double p_mass, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
};