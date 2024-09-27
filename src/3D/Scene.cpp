#include <3D/Scene.h>

Scene::Scene()
{
	//Set the space size of the world and limit the spatial range of rigid body motion
    btVector3 worldAabbMin(-10000, -10000, -10000);
    btVector3 worldAabbMax(10000, 10000, 10000);
    //Set the maximum number of rigid bodies
    int maxProxies = 1024;
    //Use the above configuration to create the parameters required for the rough test phase
    this->m_broadphase = new btAxisSweep3(worldAabbMin, worldAabbMax, maxProxies);

    //Create a collision configuration
    this->m_collisionConfiguration = new btDefaultCollisionConfiguration();
    this->m_dispatcher = new btCollisionDispatcher(this->m_collisionConfiguration);

    //Create solver
    this->m_solver = new btSequentialImpulseConstraintSolver();

    //Use the settings created above to create the physical world
    this->m_dynamicsWorld = new btDiscreteDynamicsWorld(this->m_dispatcher, this->m_broadphase, this->m_solver, this->m_collisionConfiguration);
    //Set the gravity of the physical world (here, the gravity on the y axis is set to 10N/kg)
    this->m_dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

	this->m_root = new osg::Group;

	this->m_floor = createFloor();
	this->m_XYZAxes = createAxes();
	this->m_groundbody = createGround();
    this->m_dynamicsWorld->addRigidBody(this->m_groundbody);

	this->m_root->addChild(this->m_floor);
	this->m_root->addChild(this->m_XYZAxes);

	osg::ref_ptr<osg::ShapeDrawable> sphere = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(2, 2, 5), 0.5));
	sphere->setColor(osg::Vec4(0.5, 1.0, 0.5, 1.0));

	this->m_root->addChild(sphere);
}

Scene::~Scene()
{
	// Free the memory used by the dynamics world
	this->m_dynamicsWorld->removeRigidBody(this->m_groundbody);
	delete this->m_groundbody;

	// World must be deleted first
	delete this->m_dynamicsWorld;

	// Free other memory
	delete this->m_broadphase;
	delete this->m_collisionConfiguration;
	delete this->m_dispatcher;
	delete this->m_solver;	
}

btRigidBody* Scene::createGround()
{
	// Set transform for the ground using matrix 3x3 + vector
	btTransform* lv_groundTransform = new btTransform(btMatrix3x3(1, 0, 0,
																  0, 1, 0,
																  0, 0, 1), btVector3(0, -1, 0));

	btDefaultMotionState* lv_groundMotionState = new btDefaultMotionState(*lv_groundTransform);
    
    btCollisionShape* lv_groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
	
    btRigidBody::btRigidBodyConstructionInfo lv_groundRigidBodyCI(0, lv_groundMotionState, lv_groundShape, btVector3(0, 0, 0));
    
    btRigidBody* groundbody = new btRigidBody(lv_groundRigidBodyCI);
    
    groundbody->setFriction(0.5f);

	return groundbody;
}

osg::ref_ptr<osg::ShapeDrawable> Scene::createFloor()
{
	osg::ref_ptr<osg::ShapeDrawable> floor = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0, 0, -0.005), 20.0, 20.0, 0.01));

	floor->setColor(osg::Vec4(0.0, 0.0, 0.0, 0.4));

	floor->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    floor->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

	return floor.release();
}

osg::ref_ptr<osg::Group> Scene::createAxes()
{
	osg::ref_ptr<osg::Group> axes = new osg::Group();

	osg::ref_ptr<osg::ShapeDrawable> sphere = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 0, 0), 0.05));
    sphere->setColor(osg::Vec4(1.0, 1.0, 1.0, 0.75));
	sphere->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    sphere->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	axes->addChild(sphere);

	double length = 0.5;

	osg::ref_ptr<osg::ShapeDrawable> axisZ = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0, 0, length/2), 0.01, length));
	axisZ->setColor(osg::Vec4(0.0, 0.0, 1.0, 0.5));
	axisZ->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	axisZ->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	axes->addChild(axisZ);

	osg::ref_ptr<osg::ShapeDrawable> axisY = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0, 0, length/2), 0.01, length));
	axisY->setColor(osg::Vec4(0.0, 1.0, 0.0, 0.5));
	axisY->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	axisY->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform;
	transform1->setMatrix(osg::Matrix::rotate(-osg::PI_2, osg::Vec3(1.0, 0.0, 0.0)));
	transform1->addChild(axisY);
	axes->addChild(transform1.get());

	osg::ref_ptr<osg::ShapeDrawable> axisX = new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(0, 0, length/2), 0.01, length));
	axisX->setColor(osg::Vec4(1.0, 0.0, 0.0, 0.5));
	axisX->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	axisX->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	osg::ref_ptr<osg::MatrixTransform> transform2 = new osg::MatrixTransform;
	transform2->setMatrix(osg::Matrix::rotate(osg::PI_2, osg::Vec3(0.0, 1.0, 0.0)));
	transform2->addChild(axisX);
	axes->addChild(transform2.get());

	return axes.release();
}

void Scene::initPhysics()
{
	for(auto& object : this->m_objectList)
	{
		object.initPhysics(this->m_dynamicsWorld);
	}
}

void Scene::update(double p_dt)
{
	this->m_dynamicsWorld->stepSimulation(p_dt, 10, 0.001);

	for (auto& object : this->m_objectList)
	{
		object.update();
	}
}