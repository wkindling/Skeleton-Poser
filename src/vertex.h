#pragma once
#ifndef VERTEX_H
#define VERTEX_H

#include "joint.h"

class Vertex
{
public:
	Vertex(Eigen::Vector3d _mesh_position);
	~Vertex();

	void addRelatedJoint(Joint* joint, double weight);
	void blendVertex();
	
public:
	Eigen::Vector3d global_position;
	Eigen::Vector3d mesh_position;

	std::vector<Joint*> related_joints;
	std::vector<double> weights;

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};




#endif