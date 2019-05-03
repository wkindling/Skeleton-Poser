#include "vertex.h"


Vertex::Vertex(Eigen::Vector3d _mesh_position)
{
	mesh_position = _mesh_position;
	global_position = Eigen::Vector3d::Zero();
}

Vertex::~Vertex() {}

void Vertex::addRelatedJoint(Joint* joint, double weight)
{
	related_joints.push_back(joint);
	weights.push_back(weight);
}

void Vertex::blendVertex()
{
	Eigen::Vector4d sum = Eigen::Vector4d(0, 0, 0, 0);
	double sum_weight = 0;
	for (unsigned int i = 0; i < weights.size(); i++)
	{
		sum_weight += weights[i];
	}
	for (unsigned int i = 0; i < related_joints.size(); i++)
	{
		Eigen::Vector3d offset = mesh_position - related_joints[i]->mesh_position;
		Eigen::Vector4d coordinate(offset(0), offset(1), offset(2), 1);
		coordinate = related_joints[i]->L2W*coordinate;
		sum += coordinate * weights[i]/sum_weight;
	}
	global_position = Eigen::Vector3d(sum(0), sum(1), sum(2));
}