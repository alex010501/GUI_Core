#include <3D/BaseScene.h>

BaseScene::BaseScene()
{
	this->m_root = new osg::Group;

	this->m_floor = createFloor();
	this->m_XYZAxes = createAxes();

	this->m_root->addChild(this->m_floor);
	this->m_root->addChild(this->m_XYZAxes);

	osg::ref_ptr<osg::ShapeDrawable> sphere = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(2, 2, 5), 0.5));
	sphere->setColor(osg::Vec4(0.5, 1.0, 0.5, 1.0));

	this->m_root->addChild(sphere);
}

osg::ref_ptr<osg::ShapeDrawable> BaseScene::createFloor()
{
	osg::ref_ptr<osg::ShapeDrawable> floor = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0, 0, -0.005), 20.0, 20.0, 0.01));

	floor->setColor(osg::Vec4(0.0, 0.0, 0.0, 0.4));

	floor->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    floor->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

	return floor.release();
}

osg::ref_ptr<osg::Group> BaseScene::createAxes()
{
	osg::ref_ptr<osg::Group> axes = new osg::Group();

	osg::ref_ptr<osg::ShapeDrawable> sphere = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0, 0, 0), 0.05));
    sphere->setColor(osg::Vec4(1.0, 1.0, 1.0, 0.75));
	sphere->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    sphere->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	axes->addChild(sphere);

	double length = 1.0;

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

void BaseScene::update()
{

}