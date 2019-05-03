#pragma once
#ifndef SKELETON_H
#define SKELETON_H

#include "joint.h"
#include "vertex.h"
#include <string>
#include <fstream>
#include <glut.h>


class Skeleton
{
public:
	Skeleton();
	~Skeleton();

	void readSkeletonTGF(std::string filename);
	void readSkeletonInfo(std::string filename);
	void updateJoint();
	void updateMesh();
	void drawJoint();
	void drawMesh();

public:
	int JOINT_COUNT;
	std::vector<Joint*> joints;
	std::vector<Vertex> vertices;
	std::vector<std::vector<int>> surfaces;

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};



#endif