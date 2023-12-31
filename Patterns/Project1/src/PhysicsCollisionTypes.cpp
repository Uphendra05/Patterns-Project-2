#include "PhysicsCollisionTypes.h"



//void CollisionAABBvsHAABB(const cAABB& sphereAabb, BvhNode* rootNode, std::set<int>& triangleIndices)
//{
//	if (CheckCOllisionAABBvsAABB(sphereAabb, rootNode->UpdateAABB()))
//	{
//		if (rootNode->trianglesIndex.empty())
//		{
//			if (rootNode->leftChild != nullptr)
//			{
//				CollisionAABBvsHAABB(sphereAabb, rootNode->leftChild, triangleIndices);
//				CollisionAABBvsHAABB(sphereAabb, rootNode->rightChild, triangleIndices);
//			}
//		}
//		else
//		{
//			triangleIndices.insert(rootNode->trianglesIndex.begin(), rootNode->trianglesIndex.end());
//		}
//	}
//}


bool CollisionSphereVsMeshOfTriangles(const cAABB& sphereAabb, cSphere* sphere, BvhNode* rootNode,
	const glm::mat4 transformMatrix, const std::vector<Triangle>& triangles,
	std::vector<glm::vec3>& collisionPoints,
	std::vector<glm::vec3>& collisionNormals)


{

	std::set<int> triangleIndices;

	//CollisionAABBvsHAABB(sphereAabb, rootNode, triangleIndices);

	if (triangleIndices.empty()) return false;

	for (int i : triangleIndices)
	{
		glm::vec3 collisionPt;

		Triangle triangle;

		triangle.v1 = transformMatrix * glm::vec4(triangles[i].v1, 1.0f);
		triangle.v2 = transformMatrix * glm::vec4(triangles[i].v2, 1.0f);
		triangle.v3 = transformMatrix * glm::vec4(triangles[i].v3, 1.0f);
		triangle.normal = transformMatrix * glm::vec4(triangles[i].normal, 0.0f);

		if (CollisionSphereVsTriangle(sphere, triangle, collisionPt))
		{
			collisionPoints.push_back(collisionPt);
			collisionNormals.push_back(triangle.normal);
		}
	}

	std::cout << "Hit true" << std::endl;
	return true;

}




bool CollisionAABBVsMeshOfTriangles(const cAABB& aabb, BvhNode* rootNode, const glm::mat4 transformMatrix,
	const std::vector<Triangle>& triangles,
	std::vector<glm::vec3>& collisionPoints, 
	std::vector<glm::vec3>& collisionNormals)
{

	std::set<int> triangleIndices;

	//CollisionAABBvsHAABB(aabb, rootNode, triangleIndices);

	if (triangleIndices.empty()) return false;

	for (int i : triangleIndices)
	{
		glm::vec3 collisionPt;

		Triangle triangle;

		triangle.v1 = transformMatrix * glm::vec4(triangles[i].v1, 1.0f);
		triangle.v2 = transformMatrix * glm::vec4(triangles[i].v2, 1.0f);
		triangle.v3 = transformMatrix * glm::vec4(triangles[i].v3, 1.0f);
		triangle.normal = transformMatrix * glm::vec4(triangles[i].normal, 0.0f);

		if (CollisionAABBVsTriangle(aabb, triangle, collisionPt))
		{
			collisionPoints.push_back(collisionPt);
			collisionNormals.push_back(triangle.normal);
		}

	}

	return true;
}