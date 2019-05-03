#include "skeleton.h"

extern int op;

Skeleton::Skeleton(): JOINT_COUNT(0) {}

Skeleton::~Skeleton() {}

void Skeleton::readSkeletonTGF(std::string filename)
{
	std::ifstream in(filename);

	int rows, cols;
	Eigen::MatrixXd C;

	in >> rows >> cols;
	C.resize(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			in >> C(i, j);
		}
	}
	for (int i = 0; i < C.rows(); i++)
	{
		Eigen::Vector3d position(C(i, 0), C(i, 1), C(i, 2));
		if (i == 0)
		{
			Joint* root = new Joint(position);
			joints.push_back(root);
			JOINT_COUNT++;
		}
		else
		{
			Eigen::Vector3d last_position(C(i - 1, 0), C(i - 1, 1), C(i - 1, 2));
			Eigen::Vector3d offset = position - last_position;
			Joint* joint = new Joint(joints[JOINT_COUNT - 1], offset);
			joints.push_back(joint);
			JOINT_COUNT++;
		}
	}

	std::cout << "Read TGF succeed!" << std::endl;
}

void Skeleton::readSkeletonInfo(std::string filename)
{
	using namespace Eigen;
	using namespace std;

	ifstream in(filename);
	Matrix<double, Dynamic, Dynamic> V, C, W;
	Matrix<int, Dynamic, Dynamic> F, E;

	int rows, cols;

	in >> rows >> cols;
	cout << "V " << rows << " " << cols << endl;
	V.resize(rows, cols);//Read V
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			in >> V(i, j);
		}
	}
	in >> rows >> cols;
	cout << "F" << rows << " " << cols << endl;
	F.resize(rows, cols);//Read F
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			in >> F(i, j);
		}
	}
	in >> rows >> cols;
	cout << "C " << rows << " " << cols << endl;
	C.resize(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			in >> C(i, j);
		}
	}
	in >> rows >> cols;
	cout << "E " << rows << " " << cols << endl;
	E.resize(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			in >> E(i, j);
		}
	}
	in >> rows >> cols;
	cout << "W " << rows << " " << cols << endl;
	W.resize(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			in >> W(i, j);
		}
	}
	cout << "Read Info Success!" << endl;
	/*-----------------------------------------------------------*/
	for (int i = 0; i < V.rows(); i++)
	{
		Vector3d mesh_position(V(i, 0), V(i, 1), V(i, 2));
		Vertex point(mesh_position);
		vertices.push_back(point);
	}
	cout << "Set V success£¡ " << endl;
	for (int i = 0; i < F.rows(); i++)
	{
		vector<int>	index;
		for (int j = 0; j < F.cols(); j++)
		{
			index.push_back(F(i, j));
		}
		surfaces.push_back(index);
	}
	cout << "Set F success! " << endl;

	JOINT_COUNT = C.rows();
	for (int i = 0; i < JOINT_COUNT; i++)
	{
		Vector3d position(C(i, 0), C(i, 1), C(i, 2));
		Joint* new_joint = new Joint(position);
		joints.push_back(new_joint);
	}
	for (int i = 0; i < E.rows(); i++)
	{
		int f_index = E(i, 0);
		int c_index = E(i, 1);
		Vector3d f_position(C(f_index, 0), C(f_index, 1), C(f_index, 2));
		Vector3d c_position(C(c_index, 0), C(c_index, 1), C(c_index, 2));
		Vector3d offset = c_position - f_position;
		delete joints[c_index];
		joints[c_index] = new Joint(joints[f_index], offset);
	}
	cout << "Set C success! " << endl;

	for (int i = 0; i < W.rows(); i++)
	{
		for (int j = 0; j < W.cols(); j++)
		{
			vertices[i].addRelatedJoint(joints[j], W(i, j));
		}
	}
	cout << "Set W success! " << endl;

	cout << "Config Success! " << endl;
}

void Skeleton::updateJoint()
{
	for (int i = 0; i < joints.size(); i++)
	{
		joints[i]->getWorldPosition();
	}
}

void Skeleton::updateMesh()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].blendVertex();
	}
}

void Skeleton::drawJoint()
{
	glColor3d(1, 1, 0);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	for (unsigned int i = 0; i < joints.size(); i++)
	{
		glVertex3d(joints[i]->position.x(), joints[i]->position.y(), joints[i]->position.z());
	}
	glEnd();

	glColor3d(0, 1, 1);
	glPointSize(15);
	glBegin(GL_POINTS);
	glVertex3d(joints[op]->position.x(), joints[op]->position.y(), joints[op]->position.z());
	glEnd();

	joints[0]->draw();
}

void Skeleton::drawMesh()
{
	glLineWidth(1.0);
	glColor3d(0, 0, 1);
	glBegin(GL_LINES);
	for (int i = 0; i < surfaces.size(); i++)
	{
		for (int j = 0; j < surfaces[i].size(); j++)
		{
			glVertex3d(vertices[surfaces[i][j]].global_position.x(), vertices[surfaces[i][j]].global_position.y(), vertices[surfaces[i][j]].global_position.z());
			glVertex3d(vertices[surfaces[i][(j + 1) % surfaces[i].size()]].global_position.x(), 
					   vertices[surfaces[i][(j + 1) % surfaces[i].size()]].global_position.y(), 
					   vertices[surfaces[i][(j + 1) % surfaces[i].size()]].global_position.z());
		}
	}
	glEnd();
}