/*

	Simple OBJ file parser to load models into openGL
	Author: Rytis Karpuška
			rytis@elektromotus.lt

*/

#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H


struct vertex {
	float x;
	float y;
	float z;
	float w;
};

struct face {
	struct vertex **vertices;
	struct vertex **normals;
	int vertex_count;
	int vertex_capacity;
};

struct object {
	struct vertex *vertices;
	int vertex_count;
	int vertex_capacity;
	struct vertex *normals;
	int normals_count;
	int normals_capacity;
	struct face *faces;
	int face_count;
	int face_capacity;
};


struct object *parse(char *filename);

void free_object(struct object *o);



#endif

