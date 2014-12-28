/*
	3D modelio atvaizdavimas judinamo paviršiaus pademonstravimui
	Author: Rytis Karpuška
			rytis@elektromotus.lt
*/


#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "obj_parser.h"
#include "connector.h"

#define GYRO_CALIB_COEF				20
#define GYRO_CALIB_THRES			0.2


struct object *obj = NULL;
float light_ambient[] = {0.2, 0.2, 0.2, 1.0};
float light_diffuse[] = {0.3, 0.3, 0.3, 1.0};
float light_specular[] = {0.5, 0.5, 0.5, 1.0};
float light_position[] = {0.8, 0.8, 0.8, 1.0};
float model_position[] = {0.0, 0.0, 0.0, 0.0};

float gyro_calib[] = {0.0, 0.0, 0.0};
float gyro_sensitivity = 1.0;
float model_angles[] = {0.0, 0.0, 0.0};
float model_angles_speed[] = {0.0, 0.0, 0.0};

static float length3f(float v[3])
{
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static void drawer_display()
{
	int i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);

	//Take care of rotation
	glRotatef(length3f(model_angles_speed),
					model_angles_speed[0],
					model_angles_speed[1],
					model_angles_speed[2]);

	glTranslatef(model_position[0], model_position[1], model_position[2]);
	model_position[0] = 0.0;
	model_position[1] = 0.0;
	model_position[2] = 0.0;

	for(i = 0; i < obj->face_count; i++){
		glBegin(GL_POLYGON);

		for(j = 0; j < obj->faces[i].vertex_count; j++){
			if(obj->faces[i].normals[j] != NULL)
				glNormal3f(obj->faces[i].normals[j]->x,
							obj->faces[i].normals[j]->y,
							obj->faces[i].normals[j]->z);
			glVertex3f(obj->faces[i].vertices[j]->x,
							obj->faces[i].vertices[j]->y,
							obj->faces[i].vertices[j]->z);
		}
		glEnd();
	}

	glutSwapBuffers();

	//Sleep a little
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 10000000;
	nanosleep(&ts, NULL);
	return;
}


static void drawing_keyboard(unsigned char key, int x, int y)
{
	switch(key){
	case 'j':
		light_position[0] -= 0.1;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;

	case 'l':
		light_position[0] += 0.1;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;

	case 'i':
		light_position[1] += 0.1;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;

	case 'k':
		light_position[1] -= 0.1;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;

	case 'u':
		light_position[2] += 0.1;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;

	case 'o':
		light_position[2] -= 0.1;
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		break;


	case 'a':
		model_position[0] -= 0.1;
		break;

	case 'd':
		model_position[0] += 0.1;
		break;

	case 'w':
		model_position[1] += 0.1;
		break;

	case 's':
		model_position[1] -= 0.1;
		break;

	case 'q':
		model_position[2] += 0.1;
		break;

	case 'e':
		model_position[2] -= 0.1;
		break;

	};


	return;
}

void angularVelocityCallback(union measurement *m)
{
	//only look at gyro
	if(m->floats.type != 1)
		return;

	//make slow-running average to compensate for gyroscope drift
	int i;
	for(i = 0; i < 3; i++)
		if(m->floats.value[i] < GYRO_CALIB_THRES)
			gyro_calib[i] = (m->floats.value[i] - gyro_calib[i]) / GYRO_CALIB_COEF;

	//calibrate
	for(i = 0; i < 3; i++)
		m->floats.value[i] -= gyro_calib[i];

	for(i = 0; i < 3; i++)
		model_angles_speed[i] = m->floats.value[i] * gyro_sensitivity;

	return;
}


static void drawing_init()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutDisplayFunc(drawer_display);
	glutIdleFunc(drawer_display);
	glutKeyboardFunc(drawing_keyboard);

	glMatrixMode(GL_PROJECTION);
	 gluPerspective(40.0, 1.0, 1.0, 10.0);
	gluLookAt(0.0, 0.0, 5.0,
			0.0, 0.0, 0.0,
			0.0, 1.0, 0.0);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	return;
}

void drawer_run(int argc, char *argv[])
{
	//Extract filename from arguments.
	//If not given - use default "cube.obj"
	char *filename = "cube.obj";
	if(argc > 1)
		filename = argv[argc - 1];
	argc--;

	//Parse obj file
	obj = parse(filename);
	if(obj == NULL){
		fprintf(stderr, "Could not parse object file\n");
		return;
	}

	//Print some statistics
	printf("Parsed: \n");
	printf("vertex count %d\n", obj->vertex_count);
	printf("normals count %d\n", obj->normals_count);
	printf("face count %d\n", obj->face_count);

	//Register angular velocity listener
	connector_register_notifier(angularVelocityCallback);

	//Init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 900);
	glutCreateWindow("Demonstration");
	drawing_init();
	glutMainLoop();

	return;
}
