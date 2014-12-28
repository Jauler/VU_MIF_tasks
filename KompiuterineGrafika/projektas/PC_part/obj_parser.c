/*

	Simple OBJ file parser to load models into openGL
	Author: Rytis Karpuška
			rytis@elektromotus.lt

*/


#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "obj_parser.h"

static void update_object_face(char *line, struct object *obj)
{
	char *new_line_pos, *curr_line_pos = line + 2;
	unsigned long int idx, vertex_idx, normal_idx;

	//First of all, we should check if we have enough space in faces array
	if(obj->face_count + 1 >= obj->face_capacity){
		obj->faces = realloc(obj->faces, sizeof(*obj->faces) * obj->face_capacity * 2);
		if(obj->faces == NULL){
			fprintf(stderr, "Out of memory 1\n");
			return;
		}
		obj->face_capacity *= 2;
	}

	//perpare face struct
	struct face *face = &obj->faces[obj->face_count];
	memset(face, 0, sizeof(*face));
	face->vertices = malloc(sizeof(*face->vertices) * 4);
	face->normals  = malloc(sizeof(*face->normals) * 4);
	if(face->vertices == NULL || face->normals == NULL){
		fprintf(stderr, "Out of memory 2\n");
		return;
	}
	memset(face->normals, 0, sizeof(*face->normals) * 4);
	memset(face->vertices, 0, sizeof(*face->vertices) * 4);
	face->vertex_count = 0;
	face->vertex_capacity = 4;


	//Go through the list and add it to the array
	while(1){
		vertex_idx = strtol(curr_line_pos, &new_line_pos, 10);
		if(new_line_pos == curr_line_pos)
			break;
		else
			curr_line_pos = new_line_pos;

		if(vertex_idx <= 0 || vertex_idx > obj->vertex_count){
			printf("Index out of bounds\n");
			continue;
		}

		//check if we have enough place for vertices
		if(face->vertex_count + 1 >= face->vertex_capacity){
			face->vertices = realloc(face->vertices,
							sizeof(*face->vertices) * face->vertex_capacity * 2);
			face->normals  = realloc(face->normals,
							sizeof(*face->normals) * face->vertex_capacity * 2);
			if(face->vertices == NULL || face->normals == NULL){
				fprintf(stderr, "Out of memory 3\n");
				return;
			}
			memset(&face->normals[face->vertex_count], 0, sizeof(face->normals[0]));
			face->vertex_capacity *= 2;
		}

		//Add actual pointer to vertex
		face->vertices[face->vertex_count] = (void *)vertex_idx;

		//check for normal values
		if(*curr_line_pos == '/'){
			//move away from first slash
			curr_line_pos++;

			//we do not care about texture now, only about normals
			while(*curr_line_pos != '/' && *curr_line_pos != 0 && *curr_line_pos != ' ')
					curr_line_pos++;

			//we should be at the index of normals
			if(*curr_line_pos == '/')
				curr_line_pos++;

			normal_idx = strtol(curr_line_pos, &new_line_pos, 10);
			if(new_line_pos == curr_line_pos)
				break;
			else
				curr_line_pos = new_line_pos;

			if(normal_idx <= 0 || normal_idx > obj->vertex_count){
				printf("Index out of bounds\n");
				continue;
			}

			face->normals[face->vertex_count] = (void *)normal_idx;
		}

		face->vertex_count++;
	}

	//Increment face count
	obj->face_count++;

	return;
}


static void update_object_normal(char *line, struct object *obj)
{
	int cnt, idx;

	//Check if we need more space in vertices array
	if(obj->normals_count + 1 >= obj->normals_capacity){
		//Double the capacity of vertices array
		obj->normals = realloc(obj->normals,
								sizeof(struct vertex) * obj->normals_capacity * 2);
		if(obj->normals == NULL){
			fprintf(stderr, "Out of memory 4\n");
			return;
		}
		obj->normals_capacity *= 2;
	}

	//save index value
	idx = obj->normals_count;

	//add new vertex to array
	cnt = sscanf(line, "vn %f %f %f %f\n", &obj->normals[idx].x,
												&obj->normals[idx].y,
												&obj->normals[idx].z,
												&obj->normals[idx].w);
	//If we did not have last element - it defaults to one
	if(cnt < 4)
		obj->normals[idx].w = 0.0;

	//Increment vertices count
	obj->normals_count++;

	return;
}


static void update_object_vertex(char *line, struct object *obj)
{
	int cnt, idx;

	//Check if we need more space in vertices array
	if(obj->vertex_count + 1 >= obj->vertex_capacity){
		//Double the capacity of vertices array
		obj->vertices = realloc(obj->vertices,
								sizeof(struct vertex) * obj->vertex_capacity * 2);
		if(obj->vertices == NULL){
			fprintf(stderr, "Out of memory 5\n");
			return;
		}
		obj->vertex_capacity *= 2;
	}

	//save index value
	idx = obj->vertex_count;

	//add new vertex to array
	cnt = sscanf(line, "v %f %f %f %f\n", &obj->vertices[idx].x,
												&obj->vertices[idx].y,
												&obj->vertices[idx].z,
												&obj->vertices[idx].w);
	//If we did not have last element - it defaults to one
	if(cnt < 4)
		obj->vertices[idx].w = 1.0;

	//Increment vertices count
	obj->vertex_count++;

	return;
}

static void update_object(char *line, struct object *obj)
{
	//Check for start of the line
	if(strncmp(line, "v ", 2) == 0)
		update_object_vertex(line, obj);
	else if(strncmp(line, "vn ", 2) == 0)
		update_object_normal(line, obj);
	else if(strncmp(line, "f ", 2) == 0)
		update_object_face(line, obj);

	return;
}


static struct object *read_file(FILE *f)
{
	char *line = NULL;
	int len;
	size_t tmp = 0;

	//prepare object
	struct object *obj = malloc(sizeof(struct object));
	if(obj == NULL){
		fprintf(stderr, "Out of memory 6\n");
		return NULL;
	}
	memset(obj, 0, sizeof(*obj));

	//	Allocate some memory for buffers
	//vertices
	obj->vertices = malloc(sizeof(*obj->vertices) * 4);
	if(obj->vertices == NULL){
		fprintf(stderr, "Out of memory 7\n");
		return NULL;
	}
	obj->vertex_count = 0;
	obj->vertex_capacity = 4;

	//normals
	obj->normals = malloc(sizeof(*obj->normals) * 4);
	if(obj->normals == NULL){
		fprintf(stderr, "Out of memory 8\n");
		return NULL;
	}
	obj->normals_count = 0;
	obj->normals_capacity = 4;

	//faces
	obj->faces = malloc(sizeof(*obj->faces) * 4);
	if(obj->faces == NULL){
		fprintf(stderr, "Out of memory 9\n");
		return NULL;
	}
	obj->face_count = 0;
	obj->face_capacity = 4;

	//read line by line
	while((len = getline(&line, &tmp, f)) > 0){
		update_object(line, obj);
		free(line);
		line = NULL;
		tmp = 0;
	}

	//Now indexes are stored instead of instance, so we have to account for that
	int i, j;
	for(i = 0; i < obj->face_count; i++){
		for(j = 0; j < obj->faces[i].vertex_count; j++){
			if(obj->faces[i].vertices[j] != 0)
				obj->faces[i].vertices[j] =
						&obj->vertices[((unsigned long int)obj->faces[i].vertices[j]) - 1];

			if(obj->faces[i].normals[j] != 0)
				obj->faces[i].normals[j] =
						&obj->normals[((unsigned long int)obj->faces[i].normals[j]) - 1];
		}
	}

	return obj;
}



struct object *parse(char *filename)
{
	FILE *f = fopen(filename, "r");
	if(!f){
		fprintf(stderr, "Could not open object file\n");
		return NULL;
	}

	return read_file(f);
}



void free_object(struct object *o)
{
	int i;

	//free vertices
	for(i = 0; i < o->vertex_count; i++)
		free(o->vertices);

	//free face count
	for(i = 0; i < o->face_count; i++)
		free(o->faces);

	//free object structure
	free(o);

	return;
}





