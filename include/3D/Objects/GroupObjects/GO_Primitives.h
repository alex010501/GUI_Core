#include <3D/Objects/GroupObjects/GroupObject.h>

class CubeGO : public GroupObject
{
public:
    CubeGO(const char* p_name, double a, double b, double c, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    ~CubeGO();
};

class CylinderGO : public GroupObject
{
public:
    CylinderGO(const char* p_name, double h, double r, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    ~CylinderGO();
};

class SphereGO : public GroupObject
{
public:
    SphereGO(const char* p_name, double r, osg::MatrixTransform* p_worldTransform, BaseObject* p_parent, osg::Vec4 p_color = osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    ~SphereGO();
};