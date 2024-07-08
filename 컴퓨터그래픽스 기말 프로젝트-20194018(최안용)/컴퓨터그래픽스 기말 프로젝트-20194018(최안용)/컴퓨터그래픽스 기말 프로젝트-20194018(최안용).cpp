//����: OpenGL�� �̿��� �¾�� ����
//�ۼ���: �־ȿ�
//���� ������: 2023.06.14

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>

GLfloat ratio;//ȭ������� ������ ����

typedef struct color {//rgb���� ������ color����ü
	float r, g, b;
}color;
float speed[9] = { 0.0 };//�ӵ� ������ ���Ҹ� ��Ű�� ���� �ӵ� ����
float revolution[9] = { 0.0 };//�� �༺�� ���� �ӵ��� ������ �迭
int Rotation = 1;//ȸ�� ���θ� Ȯ���� ���� 1�̸� ȸ�� 0�̸� ����
//�⺻ ����, �� ����, �� ����, �� ������ ������ �迭
double camera[4][9] = { {0.1,0.1,0.1,0.1,0.0,0.0,1.0,1.5,0.0},{0.1,0.1,0.0,0.1,0.0,0.0,0.0,0.0,-1.0},{0.0,0.0,0.0,0.1,0.0,0.0,0.0,1.0,0.0},{0.1,0.0,0.1,0.1,0.0,0.0,0.0,1.0,0.0} };
int index = 0;//���� ������ �����ϱ� ���� ����
double angle[4] = { 0.0,0.0,0.0,0.0 };//������ ī�޶� ȸ�� ����
//�¾�~�ؿռ� �ʱ� ���� ����
color list[10] = {
	{1.0,0.0,0.0},
	{1.0,1.0,1.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{0.5,0.4,0.6},
	{0.1,0.3,0.1},
	{0.9,0.2,0.4},
	{0.3,0.8,0.9},
	{0.1,0.2,0.3},
	{0.6,0.25,0.31}
};
double center[3] = { 0.1,0.0,0.0 };//�¾� �߽�

//�ʱ� �����Լ�
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);//����� ���������� ����
	glShadeModel(GL_SMOOTH);//���ؽ����� ������ ���� �����￡ �ε巴�� ���̵��ǵ��� ����
	srand(time(NULL));//seed�� ����
}

//���� �� ������ �Ÿ� ���ϴ� �Լ�
double getDistance(double x, double y, double z) {
	return sqrt(pow(x - center[0], 2.0) + pow(y - center[1], 2.0) + pow(z - center[2], 2.0));
}

//�༺ �׸��� �Լ�
void draw() {
	glLoadIdentity();//��� �ʱ�ȭ

	glInitNames();//name ���� �ʱ�ȭ

	gluLookAt(camera[index][0], camera[index][1], camera[index][2], camera[index][3], camera[index][4], camera[index][5], camera[index][6], camera[index][7], camera[index][8]);//index�� ���� ���� ����
	glPushName(100);//������� glPopName()���� �׷��� ��ü�� 100�̶�� �̸��� ����
	glPushMatrix();//���� ��� ����
	glTranslatef(0.1, 0.0, 0.0);//�¾��� ������ �θ� ȭ�� ���� �ϴ����� ġ��ġ�� ���̴� ���µ� ������Ʈ ���� ���Ͽ� �ִ� ����� �¾��� �޶� �����غ� ��� x������ 0.1 �̵��ϸ� ���Ͽ� �ִ� �¾�� ����� �Ȱ��� �̵���
	glColor3f(list[0].r, list[0].g, list[0].b);
	glutWireSphere(0.01, 20, 16);
	glPopMatrix();//���� ��ķ� ����
	glPopName();

	//����
	glPushName(101);//������� glPopName()���� �׷��� ��ü�� 101�̶�� �̸��� ����
	glPushMatrix();//���� ��� ����
	glTranslatef(0.1, 0.0, 0.0);//�¾�� �߽��� x������ 0.1 ������ �����Ƿ� x������ 0.1��ŭ �̵�
	glColor3f(list[1].r, list[1].g, list[1].b);
	glRotatef(revolution[0], 0.0, 1.0, 0.0);//����
	glTranslatef(0.015, 0.0, 0.0);//�¾����κ��� 0.015 ������ ��ġ�� �̵�
	glRotatef(revolution[0], 0.0, 1.0, 0.0);//����
	glutWireSphere(0.001, 10, 8);
	glPopMatrix();//���� ��ķ� ����
	glPopName();

	//�ݼ�
	glPushName(102);//������� glPopName()���� �׷��� ��ü�� 102��� �̸��� ����
	glPushMatrix();//���� ��� ����
	glTranslatef(0.1, 0.0, 0.0);//�¾�� �߽��� x������ 0.1 ������ �����Ƿ� x������ 0.1��ŭ �̵�
	glColor3f(list[2].r, list[2].g, list[2].b);
	glRotatef(revolution[1], 0.0, 1.0, 0.0);//����
	glTranslatef(0.02, 0.0, 0.0);//�¾����κ��� 0.02 ������ ��ġ�� �̵�
	glRotatef(revolution[1], 0.0, 1.0, 0.0);//����
	glutWireSphere(0.0025, 10, 8);
	glPopMatrix();//���� ��ķ� ����
	glPopName();

	//����
	glPushName(103);//������� glPopName()���� �׷��� ��ü�� 103�̶�� �̸��� ����
	glPushMatrix();//���� ��� ����
	glTranslatef(0.1, 0.0, 0.0);//�¾�� �߽��� x������ 0.1 ������ �����Ƿ� x������ 0.1��ŭ �̵�
	glColor3f(list[3].r, list[3].g, list[3].b);
	glRotatef(revolution[2], 0.0, 1.0, 0.0);//����
	glTranslatef(0.03, 0.0, 0.0);//�¾����κ��� 0.03 ������ ��ġ�� �̵�
	glRotatef(revolution[2], 0.0, 1.0, 0.0);//����
	glutWireSphere(0.0025, 10, 8);
	glPopMatrix();//���� ��ķ� ����
	glPopName();

	//��
	glPushName(104);//������� glPopName()���� �׷��� ��ü�� 104��� �̸��� ����
	glPushMatrix();//���� ��� ����
	glTranslatef(0.1, 0.0, 0.0);//�¾�� �߽��� x������ 0.1 ������ �����Ƿ� x������ 0.1��ŭ �̵�
	glColor3f(list[4].r, list[4].g, list[4].b);
	glRotatef(revolution[2], 0.0, 1.0, 0.0);//�¾� ����
	glTranslatef(0.03, 0.0, 0.0);//������ ��ġ�� �̵�
	glRotatef(revolution[3], 0.0, 1.0, 0.0);//���� ����
	glTranslatef(0.004, 0.0, 0.0);//�������κ��� 0.004 ������ ��ġ�� �̵�
	glRotatef(revolution[3], 0.0, 1.0, 0.0);//����
	glutWireSphere(0.0006, 10, 8);
	glPopMatrix();//���� ��ķ� ����
	glPopName();

	//ȭ��
	glPushName(105);//������� glPopName()���� �׷��� ��ü�� 105��� �̸��� ����
	glPushMatrix();//���� ��� ����
	glTranslatef(0.1, 0.0, 0.0);//�¾�� �߽��� x������ 0.1 ������ �����Ƿ� x������ 0.1��ŭ �̵�
	glColor3f(list[5].r, list[5].g, list[5].b);
	glRotatef(revolution[4], 0.0, 1.0, 0.0);//����
	glTranslatef(0.04, 0.0, 0.0);//�¾����κ��� 0.04 ������ ��ġ�� �̵�
	glRotatef(revolution[4], 0.0, 1.0, 0.0);//����
	glutWireSphere(0.00125, 10, 8);
	glPopMatrix();//���� ��ķ� ����
	glPopName();

	//��
	glPushName(106);//������� glPopName()���� �׷��� ��ü�� 106�̶�� �̸��� ����
	glPushMatrix();//���� ��� ����
	glTranslatef(0.1, 0.0, 0.0);//�¾�� �߽��� x������ 0.1 ������ �����Ƿ� x������ 0.1��ŭ �̵�
	glColor3f(list[6].r, list[6].g, list[6].b);
	glRotatef(revolution[5], 0.0, 1.0, 0.0);//����
	glTranslatef(0.0525, 0.0, 0.0);//�¾����κ��� 0.0525 ������ ��ġ�� �̵�
	glRotatef(revolution[5], 0.0, 1.0, 0.0);//����
	glutWireSphere(0.0075, 10, 8);
	glPopMatrix();//���� ��ķ� ����
	glPopName();

	//�伺
	glPushName(107);//������� glPopName()���� �׷��� ��ü�� 107�̶�� �̸��� ����
	glPushMatrix();//���� ��� ����
	glColor3f(list[7].r, list[7].g, list[7].b);
	glTranslatef(0.1, 0.0, 0.0);//�¾�� �߽��� x������ 0.1 ������ �����Ƿ� x������ 0.1��ŭ �̵�
	glRotatef(revolution[6], 0.0, 1.0, 0.0);//����
	glTranslatef(0.07, 0.0, 0.0);//�¾����κ��� 0.07 ������ ��ġ�� �̵�
	glRotatef(revolution[6], 0.0, 1.0, 0.0);//����
	glutWireSphere(0.0065, 10, 8);
	glPopMatrix();//���� ��ķ� ����
	glPopName();

	//õ�ͼ�
	glPushName(108);//������� glPopName()���� �׷��� ��ü�� 108�̶�� �̸��� ����
	glPushMatrix();//���� ��� ����
	glColor3f(list[8].r, list[8].g, list[8].b);
	glTranslatef(0.1, 0.0, 0.0);//�¾�� �߽��� x������ 0.1 ������ �����Ƿ� x������ 0.1��ŭ �̵�
	glRotatef(revolution[7], 0.0, 1.0, 0.0);//����
	glTranslatef(0.085, 0.0, 0.0);//�¾����κ��� 0.085 ������ ��ġ�� �̵�
	glRotatef(revolution[7], 0.0, 1.0, 0.0);//����
	glutWireSphere(0.00325, 10, 8);
	glPopMatrix();//���� ��ķ� ����
	glPopName();

	//�ؿռ�
	glPushName(109);//������� glPopName()���� �׷��� ��ü�� 109��� �̸��� ����
	glPushMatrix();//���� ��� ����
	glColor3f(list[9].r, list[9].g, list[9].b);
	glTranslatef(0.1, 0.0, 0.0);//�¾�� �߽��� x������ 0.1 ������ �����Ƿ� x������ 0.1��ŭ �̵�
	glRotatef(revolution[8], 0.0, 1.0, 0.0);//����
	glTranslatef(0.095, 0.0, 0.0);//�¾����κ��� 0.095 ������ ��ġ�� �̵�
	glRotatef(revolution[8], 0.0, 1.0, 0.0);//����
	glutWireSphere(0.00315, 10, 8);
	glPopMatrix();//���� ��ķ� ����
	glPopName();
}

//display �ݹ� �Լ�
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�÷� ���ۿ� ���� ���� �ʱ�ȭ
	glEnable(GL_DEPTH_TEST);//���� �׽�Ʈ Ȱ��ȭ
	draw();//�༺ �׸��� �Լ� ȣ��
	glutSwapBuffers();//����Ʈ ���ۿ� �� ���۸� ��ȯ
}

//reshape �ݹ� �Լ�
void reshape(int new_w, int new_h) {
	glViewport(0, 0, new_w, new_h);//����Ʈ ����
	glMatrixMode(GL_PROJECTION);//Projection ���� ��ȯ
	glLoadIdentity();//��� �ʱ�ȭ
	ratio = (GLfloat)new_w / (GLfloat)new_h;//ȭ�� �� ����
	gluPerspective(60.0, ratio, 0.01, 100.0);//������ ����
	glMatrixMode(GL_MODELVIEW);//Modelview ���� ��ȯ
	glLoadIdentity();//��� �ʱ�ȭ

	glutPostRedisplay();//�����츦 �ٽ� �׸����� ��û
}

//Ÿ�̸� �ݹ� �Լ�
void Rotate(int timer) {
	if (Rotation != 0) {//ȸ�� ���� ���
		//�Ųٷ� ���� ���� �����ϱ� ���� 0���Ϸ� �������� �ӵ��� �پ���� �ʵ��� ��
		if (0.01*(360 / 0.24) + speed[0] >= 0)//����
			revolution[0] = fmodf(revolution[0] + 0.01*(360 / 0.24) + speed[0], 360);//���� �ӵ��� �� �༺�� ���� ���� �ӵ��� �°� ����Ͽ� ����
		if (0.01*(306 / 0.6) + speed[1] >= 0)//�ݼ�
			revolution[1] = fmodf(revolution[1] + 0.01*(306 / 0.6) + speed[1], 360);
		if (0.01*(360 / 1.0) + speed[2] >= 0)//����
			revolution[2] = fmodf(revolution[2] + 0.01*(360 / 1.0) + speed[2], 360);
		if (0.01*(360 / 0.07) + speed[3] >= 0)//��
			revolution[3] = fmodf(revolution[3] + 0.01*(360 / 0.07) + speed[3], 360);
		if (0.01*(360 / 1.9) + speed[4] >= 0)//ȭ��
			revolution[4] = fmodf(revolution[4] + 0.01*(360 / 1.9) + speed[4], 360);
		if (0.01*(360 / 11.9) + speed[5] >= 0)//��
			revolution[5] = fmodf(revolution[5] + 0.01*(360 / 11.9) + speed[5], 360);
		if (0.01*(360 / 29.5) + speed[6] >= 0)//�伺
			revolution[6] = fmodf(revolution[6] + 0.01*(360 / 29.5) + speed[6], 360);
		if (0.01*(360 / 84) + speed[7] >= 0)//õ�ռ�
			revolution[7] = fmodf(revolution[7] + 0.01*(360 / 84) + speed[7], 360);
		if (0.01*(360 / 164.8) + speed[8] >= 0)//�ؿռ�
			revolution[8] = fmodf(revolution[8] + 0.01*(360 / 164.8) + speed[8], 360);
	}
	glutPostRedisplay();//�����츦 �ٽ� �׸����� ��û
	glutTimerFunc(30, Rotate, 0);
}

//Ư��Ű �ݹ� �Լ�
void special_keyboard(int key, int x, int y) {
	switch (key) {
	case 101://Ű���� �� ȭ��ǥ
		if (index == 0) {//�⺻ ������ ���
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//�¾���� �Ÿ� ���
			double rx = (camera[index][0] - 0.1) / 10;//ī�޶��� x�� �� ���� ����
			double ry = camera[index][1] / 10;//ī�޶��� y�� �� ���� ����
			double rz = camera[index][2] / 10;//ī�޶��� z�� �� ���� ����
			if (length > 0.02) {//ī�޶� �¾��� �հ� �ݴ�� ���� ���� �����ϱ� ���� ���ǹ�
				camera[index][0] -= rx;//������ ������ ���� ī�޶� x�� �� ����
				camera[index][1] -= ry;//������ ������ ���� ī�޶� y�� �� ����
				camera[index][2] -= rz;//������ ������ ���� ī�޶� z�� �� ����
			}
		}
		else if (index == 1) {//�� ������ ���, z�� ���� �����̹Ƿ� ����� �ʿ䰡 ����.
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//�¾���� �Ÿ� ���
			double rx = (camera[index][0] - 0.1) / 10;//ī�޶��� x�� �� ���� ����
			double ry = camera[index][1] / 10;//ī�޶��� y�� �� ���� ����
			if (length > 0.02) {//ī�޶� �¾��� �հ� �ݴ�� ���� ���� �����ϱ� ���� ���ǹ�
				camera[index][0] -= rx;//������ ������ ���� ī�޶� x�� �� ����
				camera[index][1] -= ry;//������ ������ ���� ī�޶� y�� �� ����
			}
		}
		else if (index == 2) {//�� ������ ���, y�� ���� �����̹Ƿ� ����� �ʿ䰡 ����.
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//�¾���� �Ÿ� ���
			double rx = (camera[index][0] - 0.1) / 10;//ī�޶��� x�� �� ���� ����
			double rz = camera[index][2] / 10;//ī�޶��� z�� �� ���� ����
			if (length > 0.02) {//ī�޶� �¾��� �հ� �ݴ�� ���� ���� �����ϱ� ���� ���ǹ�
				camera[index][0] -= rx;//������ ������ ���� ī�޶� x�� �� ����
				camera[index][2] -= rz;//������ ������ ���� ī�޶� z�� �� ����
			}
		}
		else if (index == 3) {//�� ������ ���, y�� ���� �����̹Ƿ� ����� �ʿ䰡 ����.
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);
			double rx = (camera[index][0] - 0.1) / 10;//ī�޶��� x�� �� ���� ����
			double rz = camera[index][2] / 10;//ī�޶��� z�� �� ���� ����
			if (length > 0.02) {//ī�޶� �¾��� �հ� �ݴ�� ���� ���� �����ϱ� ���� ���ǹ�
				camera[index][0] -= rx;//������ ������ ���� ī�޶� x�� �� ����
				camera[index][2] -= rz;//������ ������ ���� ī�޶� z�� �� ����
			}
		}
		break;
	case 103://Ű���� �Ʒ� ȭ��ǥ
		if (index == 0) {//�⺻����
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//�¾���� �Ÿ� ���
			double rx = (camera[index][0] - 0.1) / 10;//ī�޶��� x�� �� �ƿ� ���� ���
			double ry = camera[index][1] / 10;//ī�޶��� y�� �� �ƿ� ���� ���
			double rz = camera[index][2] / 10;//ī�޶��� z�� �� �ƿ� ���� ���
			camera[index][0] += rx;//������ ������ ���� x�� ����
			camera[index][1] += ry;//������ ������ ���� y�� ����
			camera[index][2] += rz;//������ ������ ���� z�� ����
		}
		else if (index == 1) {//�� ����
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//�¾���� �Ÿ� ���
			double rx = (camera[index][0] - 0.1) / 10;//ī�޶��� x�� �� �ƿ� ���� ���
			double ry = camera[index][1] / 10;//ī�޶��� y�� �� �ƿ� ���� ���
			camera[index][0] += rx;//������ ������ ���� x�� ����
			camera[index][1] += ry;//������ ������ ���� y�� ����
		}
		else if (index == 2) {//�� ����
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//�¾���� �Ÿ� ���
			double rx = (camera[index][0] - 0.1) / 10;//ī�޶��� x�� �� �ƿ� ���� ���
			double rz = camera[index][2] / 10;//ī�޶��� z�� �� �ƿ� ���� ���
			camera[index][0] += rx;//������ ������ ���� x�� ����
			camera[index][2] += rz;//������ ������ ���� z�� ����
		}
		else if (index == 3) {//�� ����
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//�¾���� �Ÿ� ���
			double rx = (camera[index][0] - 0.1) / 10;//ī�޶��� x�� �� �ƿ� ���� ���
			double rz = camera[index][2] / 10;//ī�޶��� z�� �� �ƿ� ���� ���
			camera[index][0] += rx;//������ ������ ���� x�� ����
			camera[index][2] += rz;//������ ������ ���� z�� ����
		}
		break;
	case 100://Ű���� ���� ȭ��ǥ
		if (index == 0) {//�⺻ ����
			angle[0] = fmodf(angle[0] - 0.05, 360);//ȸ�� ���� ���
			//������ǥ�迡�� ������ǥ�� ��ȯ ���� ���
			double lx = sin(33.6)*sin(angle[0]);
			double ly = cos(33.6);
			double lz = sin(33.6)*cos(angle[0]);
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//ī�޶�� �¾� ������ �Ÿ� ���
			camera[index][0] = 0.1 + length * lx;//�¾��� x������ 0.1 ������ �����Ƿ� 0.1�� ������ ������ ���� length�� lx ���� ������ ���Ѵ�
			camera[index][1] = length * -ly;//length�� ������ -ly�� ������ ī�޶� �迭�� ����
			camera[index][2] = length * lz;//length�� ������ lz�� ������ ī�޶� �迭�� ����
		}
		else if (index == 1) {//�� ����
			angle[1] = fmodf(angle[1] - 0.05, 360);//ȸ�� ���� ���
			double lx = sin(angle[1]);//sin �Լ��� �̿��Ͽ� x�� ���
			double ly = cos(angle[1]);//cos �Լ��� �̿��Ͽ� y�� ���
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//ī�޶�� �¾� ������ �Ÿ� ���
			camera[index][0] = 0.1 + length * lx;//�¾��� x������ 0.1 ������ �����Ƿ� 0.1�� ������ ������ ���� length�� lx ���� ������ ���Ѵ�
			camera[index][1] = length * ly;//length�� ������ ly�� ������ ī�޶� �迭�� ����
		}
		else if (index == 2) {//�� ����
			angle[2] = fmodf(angle[2] - 0.05, 360);//ȸ�� ���� ���
			double lx = -cos(angle[2]);//cos �Լ��� �̿��Ͽ� x�� ���
			double lz = sin(angle[2]);//sin �Լ��� �̿��Ͽ� z�� ���
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//ī�޶�� �¾� ������ �Ÿ� ���
			camera[index][0] = 0.1 + length * lx;//�¾��� x������ 0.1 ������ �����Ƿ� 0.1�� ������ ������ ���� length�� lx ���� ������ ���Ѵ�
			camera[index][2] = length * lz;//length�� ������ lz�� ������ ī�޶� �迭�� ����
		}
		else if (index == 3) {//��
			angle[3] = fmodf(angle[3] - 0.05, 360);//ȸ�� ���� ���
			double lx = sin(angle[3]);//sin �Լ��� �̿��Ͽ� x�� ���
			double lz = cos(angle[3]);//cos �Լ��� �̿��Ͽ� z�� ���
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//ī�޶�� �¾� ������ �Ÿ� ���
			camera[index][0] = 0.1 + length * lx;//�¾��� x������ 0.1 ������ �����Ƿ� 0.1�� ������ ������ ���� length�� lx ���� ������ ���Ѵ�
			camera[index][2] = length * lz;//length�� ������ lz�� ������ ī�޶� �迭�� ����
		}
		break;
	case 102://Ű���� ������ ȭ��ǥ
		if (index == 0) {
			angle[0] = fmodf(angle[0] + 0.05, 360);//ȸ�� ���� ���
			//������ǥ�迡�� ������ǥ�� ��ȯ ���� ���
			double lx = sin(33.6)*sin(angle[0]);
			double ly = cos(33.6);
			double lz = sin(33.6)*cos(angle[0]);
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//ī�޶�� �¾� ������ �Ÿ� ���
			camera[index][0] = 0.1 + length * lx;//�¾��� x������ 0.1 ������ �����Ƿ� 0.1�� ������ ������ ���� length�� lx ���� ������ ���Ѵ�
			camera[index][1] = length * -ly;//length�� ������ -ly�� ������ ī�޶� �迭�� ����
			camera[index][2] = length * lz;//length�� ������ lz�� ������ ī�޶� �迭�� ����
		}
		else if (index == 1) {
			angle[1] = fmodf(angle[1] + 0.05, 360);//ȸ�� ���� ���
			double lx = sin(angle[1]);//sin�Լ��� �̿��Ͽ� x�� ���
			double ly = cos(angle[1]);//cos�Լ��� �̿��Ͽ� y�� ���
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//ī�޶�� �¾� ������ �Ÿ� ���
			camera[index][0] = 0.1 + length * lx;//�¾��� x������ 0.1 ������ �����Ƿ� 0.1�� ������ ������ ���� length�� lx ���� ������ ���Ѵ�
			camera[index][1] = length * ly;//length�� ������ ly�� ������ ī�޶� �迭�� ����
		}
		else if (index == 2) {
			angle[2] = fmodf(angle[2] + 0.05, 360);//ȸ�� ���� ���
			double lx = -cos(angle[2]);//cos�Լ��� �̿��Ͽ� x�� ���
			double lz = sin(angle[2]);//sin�Լ��� �̿��Ͽ� y�� ���
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//ī�޶�� �¾� ������ �Ÿ� ���
			camera[index][0] = 0.1 + length * lx;//�¾��� x������ 0.1 ������ �����Ƿ� 0.1�� ������ ������ ���� length�� lx ���� ������ ���Ѵ�
			camera[index][2] = length * lz;//length�� ������ lz�� ������ ī�޶� �迭�� ����
		}
		else if (index == 3) {
			angle[3] = fmodf(angle[3] + 0.05, 360);//ȸ�� ���� ���
			double lx = sin(angle[3]);//sin�Լ��� �̿��Ͽ� x�� ���
			double lz = cos(angle[3]);//cos�Լ��� �̿��Ͽ� z�� ���
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//ī�޶�� �¾� ������ �Ÿ� ���
			camera[index][0] = 0.1 + length * lx;//�¾��� x������ 0.1 ������ �����Ƿ� 0.1�� ������ ������ ���� length�� lx ���� ������ ���Ѵ�
			camera[index][2] = length * lz;//length�� ������ lz�� ������ ī�޶� �迭�� ����
		}
		break;
	default:

		break;
	}
	glutPostRedisplay();//�����츦 �ٽ� �׸����� ��û
}

//Ű���� �ݹ� �Լ�
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 32://�����̽��� Ŭ����
		if (Rotation == 1)//ȸ�� ���̸�
			Rotation = 0;//Rotation�� 0���� �����Ͽ� ����
		else//ȸ�� ���� �ƴϸ�
			Rotation = 1;//Rotation�� 1�� �����Ͽ� ȸ��
		break;
	case 43://+��ư Ŭ����
		speed[0] += (0.01*(360 / 0.24)) / 10;
		speed[1] += (0.01*(306 / 0.6)) / 10;
		speed[2] += (0.01*(360 / 1.0)) / 10;
		speed[3] += (0.01*(360 / 0.07)) / 10;
		speed[4] += (0.01*(360 / 1.9)) / 10;
		speed[5] += (0.01*(360 / 11.9)) / 10;
		speed[6] += (0.01*(360 / 29.5)) / 10;
		speed[7] += (0.01*(360 / 84)) / 10;
		speed[8] += (0.01*(360 / 164.8)) / 10;
		break;
	case 45://-��ư Ŭ����
		speed[0] -= (0.01*(360 / 0.24)) / 10;
		speed[1] -= (0.01*(306 / 0.6)) / 10;
		speed[2] -= (0.01*(360 / 1.0)) / 10;
		speed[3] -= (0.01*(360 / 0.07)) / 10;
		speed[4] -= (0.01*(360 / 1.9)) / 10;
		speed[5] -= (0.01*(360 / 11.9)) / 10;
		speed[6] -= (0.01*(360 / 29.5)) / 10;
		speed[7] -= (0.01*(360 / 84)) / 10;
		speed[8] -= (0.01*(360 / 164.8)) / 10;
		break;
	default:
		break;
	}
}

//�޴� �ݹ� �Լ�
void popupMenu(int value) {
	switch (value) {
	case 1://�⺻ ���� 
		index = 0;
		break;
	case 2://�� ����
		index = 1;
		break;
	case 3://�� ����
		index = 2;
		break;
	case 4://�� ����
		index = 3;
		break;
	case 5://������ ����
		index = rand() % 4;//�� 4���� ���� �� �ϳ� �������� ����
		break;
	}
}

//���õ� ��ü�� RGB���� �������ִ� �Լ�
void ProcessSelect(GLuint index[64])
{
	int r = rand() % 256; //rgb���� �������� ����
	int g = rand() % 256;
	int b = rand() % 256;
	switch (index[3]) {//3���� �˻��ϹǷ� ���� ��ü�� ���õǾ�� �ϳ��� ����, ���õ� �༺�� rgb�� ����
	case 100://�¾�
		list[0].r = (float)r / 255;
		list[0].g = (float)g / 255;
		list[0].b = (float)b / 255;
		break;
	case 101://����
		list[1].r = (float)r / 255;
		list[1].g = (float)g / 255;
		list[1].b = (float)b / 255;
		break;
	case 102://�ݼ�
		list[2].r = (float)r / 255;
		list[2].g = (float)g / 255;
		list[2].b = (float)b / 255;
		break;
	case 103://����
		list[3].r = (float)r / 255;
		list[3].g = (float)g / 255;
		list[3].b = (float)b / 255;
		break;
	case 104://��
		list[4].r = (float)r / 255;
		list[4].g = (float)g / 255;
		list[4].b = (float)b / 255;
		break;
	case 105://ȭ��
		list[5].r = (float)r / 255;
		list[5].g = (float)g / 255;
		list[5].b = (float)b / 255;
		break;
	case 106://��
		list[6].r = (float)r / 255;
		list[6].g = (float)g / 255;
		list[6].b = (float)b / 255;
		break;
	case 107://�伺
		list[7].r = (float)r / 255;
		list[7].g = (float)g / 255;
		list[7].b = (float)b / 255;
		break;
	case 108://õ�ռ�
		list[8].r = (float)r / 255;
		list[8].g = (float)g / 255;
		list[8].b = (float)b / 255;
		break;
	case 109://�ؿռ�
		list[9].r = (float)r / 255;
		list[9].g = (float)g / 255;
		list[9].b = (float)b / 255;
		break;
	default: break;
	}
}

//���콺 �ݹ� �Լ�
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		GLuint selectBuff[64];//���õ� ��ü�� �̸��� ������ �迭
		GLint hits, viewport[4];//hits�� ���콺�� Ŭ���ؼ� ���õ� ��ü�� ������� ������ ����
		//viewport�� ����Ʈ ������ ������ ����
		glSelectBuffer(64, selectBuff);//select buffer�� ���� �迭�� ũ��� ���� �޸� ������ ����
		glGetIntegerv(GL_VIEWPORT, viewport);//����Ʈ�� �������� ���� viewport�迭�� ����
		glMatrixMode(GL_PROJECTION);//projection ���� ��ȯ
		glPushMatrix();//���� ��İ� ����
		glRenderMode(GL_SELECT);// �������Ҷ��� Render Mode�� Selection Buffer�� ������ �ϵ��� ����
		glLoadIdentity();//��� �ʱ�ȭ
		gluPickMatrix(x, viewport[3] - y, 5, 5, viewport);//��ŷ ���� ����
		gluPerspective(60.0, ratio, 0.01, 100.0);//������ ����
		glMatrixMode(GL_MODELVIEW);//Modelview ���� ��ȯ
		glLoadIdentity();//��� �ʱ�ȭ
		draw();//�༺ �׸���
		hits = glRenderMode(GL_RENDER);//�׸� �� Render Buffer�� �׸����� ����, �� ���� ��ü�� ���õǾ����� ��ȯ�ϹǷ� hits�� �� ���� ����
		if (hits > 0) ProcessSelect(selectBuff);//��ü�� �ϳ� �̻� ���õǾ����� ProcessSelect�Լ� ȣ��
		glMatrixMode(GL_PROJECTION);//Projection���� ��ȯ
		glPopMatrix();//���� ������ ����
		glMatrixMode(GL_MODELVIEW);//Modelview ���� ��ȯ
	}
}

//main�Լ�
int main(int argc, char** argv) {
	glutInit(&argc, argv);//GLUT ���� �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//���÷��̸������ ����: double buffer & rgb & depth ��� ����
	glutInitWindowSize(800, 500);//â�� ũ�� ����
	glutInitWindowPosition(100, 100);//â�� ��ġ ����

	glutCreateWindow("������Ʈ");//������ ����

	glutCreateMenu(popupMenu);//�޴� �ݹ� �Լ� ���
	glutAddMenuEntry("�⺻ ����", 1);//���� �޴��� ���� �׸� �߰�
	glutAddMenuEntry("�� ����", 2);
	glutAddMenuEntry("�� ����", 3);
	glutAddMenuEntry("�� ����", 4);
	glutAddMenuEntry("������ ����", 5);


	init();//�ʱ� ���� �Լ� ȣ��
	glutAttachMenu(GLUT_RIGHT_BUTTON);//�ش� ��ư�� ������ �Ҵ�� �޴��� �˾��ǵ��� ����
	glutDisplayFunc(display);//display �ݹ� �Լ� ���
	glutReshapeFunc(reshape);//reshape �ݹ� �Լ� ���
	glutKeyboardFunc(keyboard);//keyboard �ݹ� �Լ� ���
	glutSpecialFunc(special_keyboard);//special_keyboard �ݹ� �Լ� ���
	glutMouseFunc(mouse);//mouse �ݹ��Լ� ���
	glutTimerFunc(30, Rotate, 1);//Ÿ�̸� �ݹ��Լ� ���
	glutMainLoop();//�̺�Ʈ ó������ ����

	return 0;
}
