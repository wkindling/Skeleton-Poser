#include "joint.h"


Joint::Joint(Eigen::Vector3d _position) //construct root
{
	offset = Eigen::Vector3d::Zero();
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
	transform = Eigen::Matrix4d::Identity();
	L2P = Eigen::Matrix4d::Identity();
	L2W = Eigen::Matrix4d::Identity();
	
	father = nullptr;
	position = _position;
	mesh_position = _position;
}

Joint::Joint(Joint* _father, Eigen::Vector3d _offset)
{
	offset = _offset;
	angle_x = 0;
	angle_y = 0;
	angle_z = 0;
	
	transform = Eigen::Matrix4d::Identity();
	L2P = Eigen::Matrix4d::Identity();
	L2W = Eigen::Matrix4d::Identity();

	father = _father;
	father->addChild(this);
	position = father->position + offset;
	mesh_position = father->mesh_position + offset;
}

Joint::~Joint() {}

void Joint::addChild(Joint* child)
{
	children.push_back(child);
}

Eigen::Matrix4d Joint::getTransform()//translate angles to Matrix4d
{
	Eigen::Matrix4d Rotx, Roty, Rotz;
	Rotx << 1, 0, 0, 0,
			0, cos(angle_x), -sin(angle_x), 0,
			0, sin(angle_x), cos(angle_x), 0,
			0, 0, 0, 1;
	Roty << cos(angle_y), 0, sin(angle_y), 0,
			0, 1, 0, 0,
			-sin(angle_y), 0, cos(angle_y), 0,
			0, 0, 0, 1;
	Rotz << cos(angle_z), -sin(angle_z), 0, 0,
			sin(angle_z), cos(angle_z), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1;

	transform = Roty * Rotx * Rotz; // zxy
	return transform;
}

Eigen::Matrix4d Joint::getTransformL2P() // translate local frame to parent frame
{
	if (father!=nullptr) // non root
	{
		Eigen::Matrix4d inverseRotate = getTransform().inverse();
		Eigen::Matrix4d inverseOffset;
		inverseOffset << 1, 0, 0, offset.x(),
			0, 1, 0, offset.y(),
			0, 0, 1, offset.z(),
			0, 0, 0, 1;

		L2P = inverseOffset * inverseRotate;
	}
	else  // root
	{
		Eigen::Matrix4d inverseRotate = getTransform().inverse();
		Eigen::Matrix4d inverseOffset;
		inverseOffset << 1, 0, 0, position.x(),
			0, 1, 0, position.y(),
			0, 0, 1, position.z(),
			0, 0, 0, 1;

		L2P = inverseOffset * inverseRotate;
	}
	return L2P;
}

Eigen::Matrix4d Joint::getTransformL2W()
{
	L2W = Eigen::Matrix4d::Identity();
	Joint* current = this;
	while (current != nullptr)
	{
		L2W = current->getTransformL2P()*L2W;
		current = current->father;
	}
	return L2W;
}

Eigen::Vector3d Joint::getWorldPosition()
{
	getTransformL2W();
	Eigen::Vector4d coordinate(0, 0, 0, 1);
	coordinate = L2W * coordinate;

	position = Eigen::Vector3d(coordinate(0), coordinate(1), coordinate(2));
	return position;
}

void Joint::draw()
{

	for (int i = 0; i < children.size(); i++)
	{
		glColor3d(1, 0, 0);
		glBegin(GL_LINES);
		glVertex3d(position.x(), position.y(), position.z());
		glVertex3d(children[i]->position.x(), children[i]->position.y(), children[i]->position.z());
		glEnd();

		children[i]->draw();
	}

}