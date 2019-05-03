#pragma once
#ifndef JOINT_H
#define JOINT_H

#include <Eigen/Dense>
#include <vector>
#include <glut.h>
#include <iostream>


class Joint
{
public:
	Joint(Eigen::Vector3d _position); //construct root
	Joint(Joint* _father, Eigen::Vector3d _offset);
	~Joint();

	void addChild(Joint* child);
	Eigen::Matrix4d getTransform();
	Eigen::Matrix4d getTransformL2W();
	Eigen::Matrix4d getTransformL2P();
	Eigen::Vector3d getWorldPosition();
	void draw();

public:
	Eigen::Vector3d offset;
	double angle_x, angle_y, angle_z;

	Eigen::Matrix4d transform; // may be deleted later
	Eigen::Matrix4d L2P;
	Eigen::Matrix4d L2W;

	Joint* father;
	std::vector<Joint*> children;

	Eigen::Vector3d position;
	Eigen::Vector3d mesh_position;

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


#endif