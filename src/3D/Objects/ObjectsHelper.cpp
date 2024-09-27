#include <3D/Objects/ObejctsHelper.h>

using namespace ObjectsHelper;

void setColor(osg::ref_ptr<osg::Geode> p_geode, osg::Vec4 p_color)
{
    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setDiffuse(osg::Material::FRONT_AND_BACK, p_color);
    p_geode->getOrCreateStateSet()->setAttributeAndModes(material.get());
    p_geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);
}

osg::ref_ptr<osg::Geode> createSphere(double p_radius)
{
    osg::ref_ptr<osg::Geode> lv_geode = new osg::Geode;
    lv_geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 0, 0), p_radius)));
    return lv_geode;
}

osg::ref_ptr<osg::Geode> createCube(double p_a, double p_b, double p_c)
{
    osg::ref_ptr<osg::Geode> lv_geode = new osg::Geode;
    lv_geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0, 0, 0), p_a, p_b, p_c)));
    return lv_geode;
}

osg::ref_ptr<osg::Geode> createCylinder(double p_radius, double p_height)
{
    osg::ref_ptr<osg::Geode> lv_geode = new osg::Geode;
    lv_geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0, 0, 0), p_radius, p_height)));
    return lv_geode;
}

osg::ref_ptr<osg::Geode> loadMesh(const char* p_path)
{
    osg::ref_ptr<osg::Node> lv_node = osgDB::readNodeFile(p_path);
    if (lv_node)
    {
        osg::ref_ptr<osg::Geode> lv_geode = new osg::Geode;
        lv_geode->addChild(lv_node);
        return lv_geode;
    }
    return nullptr;
}

btTransform getBTTransform(osg::ref_ptr<osg::MatrixTransform> p_transform)
{
    osg::Matrix lv_matrix = p_transform->getMatrix();
    btMatrix3x3 lv_rotation = btMatrix3x3(lv_matrix(0, 0), lv_matrix(0, 1), lv_matrix(0, 2),
                                          lv_matrix(1, 0), lv_matrix(1, 1), lv_matrix(1, 2),
                                          lv_matrix(2, 0), lv_matrix(2, 1), lv_matrix(2, 2));
    btVector3 lv_position = btVector3(lv_matrix(0, 3), lv_matrix(1, 3), lv_matrix(2, 3));
    btTransform lv_transform(lv_rotation, lv_position);
    return lv_transform;
}

osg::Matrix getOSGTransform(btTransform p_transform)
{
    btMatrix3x3 lv_rotation = btMatrix3x3(p_transform.getBasis());
    btVector3 lv_position = p_transform.getOrigin();
    osg::Matrix lv_matrix = osg::Matrix(lv_rotation[0][0], lv_rotation[0][1], lv_rotation[0][2], lv_position[0],
                                        lv_rotation[1][0], lv_rotation[1][1], lv_rotation[1][2], lv_position[1],
                                        lv_rotation[2][0], lv_rotation[2][1], lv_rotation[2][2], lv_position[2],
                                                        0,                 0,                 0,              1);
    return lv_matrix;
}

btRigidBody* createStaticSphereBody(double p_radius, btTransform p_transform)
{
    btCollisionShape* lv_shape = new btSphereShape(p_radius);
    btDefaultMotionState* lv_motionState = new btDefaultMotionState(p_transform);
    btRigidBody::btRigidBodyConstructionInfo lv_info(0, lv_motionState, lv_shape, btVector3(0, 0, 0));
    return new btRigidBody(lv_info);
}

btRigidBody* createDynamicSphereBody(double p_radius, btTransform p_transform, double p_mass)
{
    btCollisionShape* lv_shape = new btSphereShape(p_radius);
    btDefaultMotionState* lv_motionState = new btDefaultMotionState(p_transform);
    btVector3 lv_inertia;
    lv_shape->calculateLocalInertia(p_mass, lv_inertia);
    btRigidBody::btRigidBodyConstructionInfo lv_info(p_mass, lv_motionState, lv_shape, lv_inertia);
    return new btRigidBody(lv_info);
}

btRigidBody* createStaticCylinderBody(double p_radius, double p_height, btTransform p_transform)
{
    btCollisionShape* lv_shape = new btCylinderShape(btVector3(p_radius, p_radius, p_height));
    btDefaultMotionState* lv_motionState = new btDefaultMotionState(p_transform);
    btRigidBody::btRigidBodyConstructionInfo lv_info(0, lv_motionState, lv_shape, btVector3(0, 0, 0));
    return new btRigidBody(lv_info);
}

btRigidBody* createDynamicCylinderBody(double p_radius, double p_height, btTransform p_transform, double p_mass)
{
    btCollisionShape* lv_shape = new btCylinderShape(btVector3(p_radius, p_radius, p_height));
    btDefaultMotionState* lv_motionState = new btDefaultMotionState(p_transform);
    btVector3 lv_inertia;
    lv_shape->calculateLocalInertia(p_mass, lv_inertia);
    btRigidBody::btRigidBodyConstructionInfo lv_info(p_mass, lv_motionState, lv_shape, lv_inertia);
    return new btRigidBody(lv_info);
}

btRigidBody* createStaticCubeBody(double p_a, double p_b, double p_c, btTransform p_transform)
{
    btCollisionShape* lv_shape = new btBoxShape(btVector3(p_a, p_b, p_c));
    btDefaultMotionState* lv_motionState = new btDefaultMotionState(p_transform);
    btRigidBody::btRigidBodyConstructionInfo lv_info(0, lv_motionState, lv_shape, btVector3(0, 0, 0));
    return new btRigidBody(lv_info);
}

btRigidBody* createDynamicCubeBody(double p_a, double p_b, double p_c, btTransform p_transform, double p_mass)
{
    btCollisionShape* lv_shape = new btBoxShape(btVector3(p_a, p_b, p_c));
    btDefaultMotionState* lv_motionState = new btDefaultMotionState(p_transform);
    btVector3 lv_inertia;
    lv_shape->calculateLocalInertia(p_mass, lv_inertia);
    btRigidBody::btRigidBodyConstructionInfo lv_info(p_mass, lv_motionState, lv_shape, lv_inertia);
    return new btRigidBody(lv_info);
}

btRigidBody* createStaticMeshBody(const char* p_path, btTransform p_transform)
{
    // Load .obj file using Assimp
    Assimp::Importer lv_importer;
    const aiScene* lv_scene = lv_importer.ReadFile(p_path, aiProcess_Triangulate);

    // Convert mesh data to Bullet format
    btTriangleMesh* lv_triangleMesh = new btTriangleMesh();
    aiMesh* lv_mesh = lv_scene->mMeshes[0];
    for (unsigned int i = 0; i < lv_mesh->mNumFaces; i++)
    {
        aiFace lv_face = lv_mesh->mFaces[i];
        btVector3 v1 = btVector3(lv_mesh->mVertices[lv_face.mIndices[0]].x, lv_mesh->mVertices[lv_face.mIndices[0]].y, lv_mesh->mVertices[lv_face.mIndices[0]].z);
        btVector3 v2 = btVector3(lv_mesh->mVertices[lv_face.mIndices[1]].x, lv_mesh->mVertices[lv_face.mIndices[1]].y, lv_mesh->mVertices[lv_face.mIndices[1]].z);
        btVector3 v3 = btVector3(lv_mesh->mVertices[lv_face.mIndices[2]].x, lv_mesh->mVertices[lv_face.mIndices[2]].y, lv_mesh->mVertices[lv_face.mIndices[2]].z);
        lv_triangleMesh->addTriangle(v1, v2, v3);
    }

    btCollisionShape* lv_shape = new btBvhTriangleMeshShape(lv_triangleMesh, true);

    btDefaultMotionState* lv_motionState = new btDefaultMotionState(p_transform);
    btRigidBody::btRigidBodyConstructionInfo lv_info(0, lv_motionState, lv_shape, btVector3(0, 0, 0));
    return new btRigidBody(lv_info);
}

btRigidBody* createDynamicMeshBody(const char* p_path, btTransform p_transform, double p_mass)
{
    // Load .obj file using Assimp
    Assimp::Importer lv_importer;
    const aiScene* lv_scene = lv_importer.ReadFile(p_path, aiProcess_Triangulate);

    // Convert mesh data to Bullet format
    btTriangleMesh* lv_triangleMesh = new btTriangleMesh();
    aiMesh* lv_mesh = lv_scene->mMeshes[0];
    for (unsigned int i = 0; i < lv_mesh->mNumFaces; i++)
    {
        aiFace lv_face = lv_mesh->mFaces[i];
        btVector3 v1 = btVector3(lv_mesh->mVertices[lv_face.mIndices[0]].x, lv_mesh->mVertices[lv_face.mIndices[0]].y, lv_mesh->mVertices[lv_face.mIndices[0]].z);
        btVector3 v2 = btVector3(lv_mesh->mVertices[lv_face.mIndices[1]].x, lv_mesh->mVertices[lv_face.mIndices[1]].y, lv_mesh->mVertices[lv_face.mIndices[1]].z);
        btVector3 v3 = btVector3(lv_mesh->mVertices[lv_face.mIndices[2]].x, lv_mesh->mVertices[lv_face.mIndices[2]].y, lv_mesh->mVertices[lv_face.mIndices[2]].z);
        lv_triangleMesh->addTriangle(v1, v2, v3);
    }

    btCollisionShape* lv_shape = new btBvhTriangleMeshShape(lv_triangleMesh, true);

    btDefaultMotionState* lv_motionState = new btDefaultMotionState(p_transform);
    btVector3 lv_inertia;
    lv_shape->calculateLocalInertia(p_mass, lv_inertia);
    btRigidBody::btRigidBodyConstructionInfo lv_info(p_mass, lv_motionState, lv_shape, lv_inertia);
    return new btRigidBody(lv_info);
}