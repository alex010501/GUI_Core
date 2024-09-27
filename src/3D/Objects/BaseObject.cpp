#include <3D/Objects/BaseObject.h>

BaseObject::BaseObject(const char* p_name, osg::ref_ptr<osg::MatrixTransform> p_worldTransform, BaseObject* p_parent):
m_name(p_name), m_parent(p_parent)
{
    if(this->m_parent)
    {
        osg::ref_ptr<osg::MatrixTransform> lv_parentTransform = this->m_parent->getWorldTransform();
        osg::Matrix lv_localTransformMatrix = lv_parentTransform->getInverseMatrix() * p_worldTransform->getMatrix();
        this->m_localTransform = new osg::MatrixTransform(lv_localTransformMatrix);
    }
    else
        this->m_localTransform = p_worldTransform;
}

void BaseObject::setColor(osg::Vec4 p_color)
{
    this->m_color = p_color;
    if(this->m_mesh)
        ObjectsHelper::setColor(this->m_mesh, this->m_color);
}

osg::ref_ptr<osg::MatrixTransform> BaseObject::getWorldTransform()
{
    if(this->m_parent)
    {
        osg::ref_ptr<osg::MatrixTransform> lv_parentTransform = this->m_parent->getWorldTransform();
        osg::Matrix lv_worldTransformMatrix = lv_parentTransform->getMatrix() * this->getLocalTransform()->getMatrix();
        return new osg::MatrixTransform(lv_worldTransformMatrix);
    }
    else
        return this->m_localTransform;
}

osg::ref_ptr<osg::MatrixTransform> BaseObject::getLocalTransform()
{
    return this->m_localTransform;
}

void BaseObject::moveObject(ObjectsHelper::moveOption p_moveOption, osg::Matrix p_transform)
{
    using namespace ObjectsHelper;

    switch (p_moveOption)
    {
    case LOCAL_REL:
        this->m_localTransform->postMult(p_transform);
        break;

    case LOCAL_ABS:
        this->m_localTransform->setMatrix(p_transform);
        break;

    case WORLD_REL:
        if(this->m_parent)
            this->m_localTransform->postMult(this->m_parent->getWorldTransform()->getInverseMatrix() * p_transform);
        else
            this->m_localTransform->postMult(p_transform);
        break;

    case WORLD_ABS:
        if(this->m_parent)
            this->m_localTransform->setMatrix(this->m_parent->getWorldTransform()->getInverseMatrix() * p_transform);
        else
            this->m_localTransform->setMatrix(p_transform);
        break;
    
    default:
        break;
    }
}