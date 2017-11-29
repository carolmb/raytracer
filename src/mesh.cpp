#include "objs/mesh.h"
#include "objs/triangle.h"

void Mesh::setTransf(Transformation *t) {
	transf = t;
	for (int j = 0; j < mesh.Vertices.size(); j++) {
		Vec3 pos(mesh.Vertices[j].Position.X, 
			mesh.Vertices[j].Position.Y, 
			mesh.Vertices[j].Position.Z);
		pos = t->mat*pos;
		mesh.Vertices[j].Position.X = pos.x;
		mesh.Vertices[j].Position.Y = pos.y;
		mesh.Vertices[j].Position.Z = pos.z;
	}
}

Point3 Mesh::getVerticeInMesh(int index) {
	return Vec3(mesh.Vertices[index].Position.X, 
			mesh.Vertices[index].Position.Y, 
			mesh.Vertices[index].Position.Z);
}

bool Mesh::hit(Ray ray, HitRecord &hit, double &mint, double maxt) {
	Transformation *t = new Transformation();
	t->mat = Mat4::identity();
	t->inv = Mat4::identity();

	for(int j = 0; j < mesh.Indices.size(); j += 3) {
		Point3 p1 = getVerticeInMesh(mesh.Indices[j]);
		Point3 p2 = getVerticeInMesh(mesh.Indices[j + 1]); 
		Point3 p3 = getVerticeInMesh(mesh.Indices[j + 2]);
		Triangle triangle(p1, p2, p3, mat, false, t);
		if(triangle.hit(ray, hit, mint, maxt)) {
			return true;
		}
	}
	false;
}