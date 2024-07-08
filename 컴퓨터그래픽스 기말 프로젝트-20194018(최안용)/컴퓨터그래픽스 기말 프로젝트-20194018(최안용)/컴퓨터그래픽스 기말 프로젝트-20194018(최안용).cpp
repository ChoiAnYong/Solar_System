//제목: OpenGL을 이용한 태양계 구현
//작성자: 최안용
//최종 수정일: 2023.06.14

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>

GLfloat ratio;//화면비율을 저장할 변수

typedef struct color {//rgb값을 저장할 color구조체
	float r, g, b;
}color;
float speed[9] = { 0.0 };//속도 증가와 감소를 시키기 위한 속도 변수
float revolution[9] = { 0.0 };//각 행성의 공전 속도를 저장할 배열
int Rotation = 1;//회전 여부를 확인할 변수 1이면 회전 0이면 정지
//기본 시점, 위 시점, 옆 시점, 앞 시점을 저장할 배열
double camera[4][9] = { {0.1,0.1,0.1,0.1,0.0,0.0,1.0,1.5,0.0},{0.1,0.1,0.0,0.1,0.0,0.0,0.0,0.0,-1.0},{0.0,0.0,0.0,0.1,0.0,0.0,0.0,1.0,0.0},{0.1,0.0,0.1,0.1,0.0,0.0,0.0,1.0,0.0} };
int index = 0;//현재 시점을 저장하기 위한 변수
double angle[4] = { 0.0,0.0,0.0,0.0 };//시점별 카메라 회전 각도
//태양~해왕성 초기 색상 지정
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
double center[3] = { 0.1,0.0,0.0 };//태양 중심

//초기 설정함수
void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);//배경을 검은색으로 설정
	glShadeModel(GL_SMOOTH);//버텍스마다 지정된 색이 폴리곤에 부드럽게 쉐이딩되도록 설정
	srand(time(NULL));//seed값 설정
}

//점과 점 사이의 거리 구하는 함수
double getDistance(double x, double y, double z) {
	return sqrt(pow(x - center[0], 2.0) + pow(y - center[1], 2.0) + pow(z - center[2], 2.0));
}

//행성 그리는 함수
void draw() {
	glLoadIdentity();//행렬 초기화

	glInitNames();//name 스택 초기화

	gluLookAt(camera[index][0], camera[index][1], camera[index][2], camera[index][3], camera[index][4], camera[index][5], camera[index][6], camera[index][7], camera[index][8]);//index에 따라 시점 설정
	glPushName(100);//여기부터 glPopName()까지 그려진 물체에 100이라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glTranslatef(0.1, 0.0, 0.0);//태양을 원점에 두면 화면 왼쪽 하단으로 치우치고 보이는 형태도 프로젝트 설명 파일에 있는 영상속 태양계와 달라 수정해본 결과 x축으로 0.1 이동하면 파일에 있는 태양계 모습과 똑같아 이동함
	glColor3f(list[0].r, list[0].g, list[0].b);
	glutWireSphere(0.01, 20, 16);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();

	//수성
	glPushName(101);//여기부터 glPopName()까지 그려진 물체에 101이라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glTranslatef(0.1, 0.0, 0.0);//태양계 중심이 x축으로 0.1 떨어져 있으므로 x축으로 0.1만큼 이동
	glColor3f(list[1].r, list[1].g, list[1].b);
	glRotatef(revolution[0], 0.0, 1.0, 0.0);//공전
	glTranslatef(0.015, 0.0, 0.0);//태양으로부터 0.015 떨어진 위치로 이동
	glRotatef(revolution[0], 0.0, 1.0, 0.0);//자전
	glutWireSphere(0.001, 10, 8);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();

	//금성
	glPushName(102);//여기부터 glPopName()까지 그려진 물체에 102라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glTranslatef(0.1, 0.0, 0.0);//태양계 중심이 x축으로 0.1 떨어져 있으므로 x축으로 0.1만큼 이동
	glColor3f(list[2].r, list[2].g, list[2].b);
	glRotatef(revolution[1], 0.0, 1.0, 0.0);//공전
	glTranslatef(0.02, 0.0, 0.0);//태양으로부터 0.02 떨어진 위치로 이동
	glRotatef(revolution[1], 0.0, 1.0, 0.0);//자전
	glutWireSphere(0.0025, 10, 8);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();

	//지구
	glPushName(103);//여기부터 glPopName()까지 그려진 물체에 103이라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glTranslatef(0.1, 0.0, 0.0);//태양계 중심이 x축으로 0.1 떨어져 있으므로 x축으로 0.1만큼 이동
	glColor3f(list[3].r, list[3].g, list[3].b);
	glRotatef(revolution[2], 0.0, 1.0, 0.0);//공전
	glTranslatef(0.03, 0.0, 0.0);//태양으로부터 0.03 떨어진 위치로 이동
	glRotatef(revolution[2], 0.0, 1.0, 0.0);//자전
	glutWireSphere(0.0025, 10, 8);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();

	//달
	glPushName(104);//여기부터 glPopName()까지 그려진 물체에 104라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glTranslatef(0.1, 0.0, 0.0);//태양계 중심이 x축으로 0.1 떨어져 있으므로 x축으로 0.1만큼 이동
	glColor3f(list[4].r, list[4].g, list[4].b);
	glRotatef(revolution[2], 0.0, 1.0, 0.0);//태양 공전
	glTranslatef(0.03, 0.0, 0.0);//지구의 위치로 이동
	glRotatef(revolution[3], 0.0, 1.0, 0.0);//지구 공전
	glTranslatef(0.004, 0.0, 0.0);//지구으로부터 0.004 떨어진 위치로 이동
	glRotatef(revolution[3], 0.0, 1.0, 0.0);//자전
	glutWireSphere(0.0006, 10, 8);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();

	//화성
	glPushName(105);//여기부터 glPopName()까지 그려진 물체에 105라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glTranslatef(0.1, 0.0, 0.0);//태양계 중심이 x축으로 0.1 떨어져 있으므로 x축으로 0.1만큼 이동
	glColor3f(list[5].r, list[5].g, list[5].b);
	glRotatef(revolution[4], 0.0, 1.0, 0.0);//공전
	glTranslatef(0.04, 0.0, 0.0);//태양으로부터 0.04 떨어진 위치로 이동
	glRotatef(revolution[4], 0.0, 1.0, 0.0);//자전
	glutWireSphere(0.00125, 10, 8);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();

	//목성
	glPushName(106);//여기부터 glPopName()까지 그려진 물체에 106이라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glTranslatef(0.1, 0.0, 0.0);//태양계 중심이 x축으로 0.1 떨어져 있으므로 x축으로 0.1만큼 이동
	glColor3f(list[6].r, list[6].g, list[6].b);
	glRotatef(revolution[5], 0.0, 1.0, 0.0);//공전
	glTranslatef(0.0525, 0.0, 0.0);//태양으로부터 0.0525 떨어진 위치로 이동
	glRotatef(revolution[5], 0.0, 1.0, 0.0);//자전
	glutWireSphere(0.0075, 10, 8);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();

	//토성
	glPushName(107);//여기부터 glPopName()까지 그려진 물체에 107이라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glColor3f(list[7].r, list[7].g, list[7].b);
	glTranslatef(0.1, 0.0, 0.0);//태양계 중심이 x축으로 0.1 떨어져 있으므로 x축으로 0.1만큼 이동
	glRotatef(revolution[6], 0.0, 1.0, 0.0);//공전
	glTranslatef(0.07, 0.0, 0.0);//태양으로부터 0.07 떨어진 위치로 이동
	glRotatef(revolution[6], 0.0, 1.0, 0.0);//자전
	glutWireSphere(0.0065, 10, 8);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();

	//천와성
	glPushName(108);//여기부터 glPopName()까지 그려진 물체에 108이라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glColor3f(list[8].r, list[8].g, list[8].b);
	glTranslatef(0.1, 0.0, 0.0);//태양계 중심이 x축으로 0.1 떨어져 있으므로 x축으로 0.1만큼 이동
	glRotatef(revolution[7], 0.0, 1.0, 0.0);//공전
	glTranslatef(0.085, 0.0, 0.0);//태양으로부터 0.085 떨어진 위치로 이동
	glRotatef(revolution[7], 0.0, 1.0, 0.0);//자전
	glutWireSphere(0.00325, 10, 8);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();

	//해왕성
	glPushName(109);//여기부터 glPopName()까지 그려진 물체에 109라는 이름을 지정
	glPushMatrix();//현재 행렬 저장
	glColor3f(list[9].r, list[9].g, list[9].b);
	glTranslatef(0.1, 0.0, 0.0);//태양계 중심이 x축으로 0.1 떨어져 있으므로 x축으로 0.1만큼 이동
	glRotatef(revolution[8], 0.0, 1.0, 0.0);//공전
	glTranslatef(0.095, 0.0, 0.0);//태양으로부터 0.095 떨어진 위치로 이동
	glRotatef(revolution[8], 0.0, 1.0, 0.0);//자전
	glutWireSphere(0.00315, 10, 8);
	glPopMatrix();//기존 행렬로 복귀
	glPopName();
}

//display 콜백 함수
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//컬러 버퍼와 깊이 버퍼 초기화
	glEnable(GL_DEPTH_TEST);//깊이 테스트 활성화
	draw();//행성 그리기 함수 호출
	glutSwapBuffers();//프론트 버퍼와 백 버퍼를 교환
}

//reshape 콜백 함수
void reshape(int new_w, int new_h) {
	glViewport(0, 0, new_w, new_h);//뷰포트 설정
	glMatrixMode(GL_PROJECTION);//Projection 모드로 전환
	glLoadIdentity();//행렬 초기화
	ratio = (GLfloat)new_w / (GLfloat)new_h;//화면 비 저장
	gluPerspective(60.0, ratio, 0.01, 100.0);//투영값 설정
	glMatrixMode(GL_MODELVIEW);//Modelview 모드로 전환
	glLoadIdentity();//행렬 초기화

	glutPostRedisplay();//윈도우를 다시 그리도록 요청
}

//타이머 콜백 함수
void Rotate(int timer) {
	if (Rotation != 0) {//회전 중인 경우
		//거꾸로 도는 것을 방지하기 위해 0이하로 떨어지면 속도가 줄어들지 않도록 함
		if (0.01*(360 / 0.24) + speed[0] >= 0)//수성
			revolution[0] = fmodf(revolution[0] + 0.01*(360 / 0.24) + speed[0], 360);//공전 속도를 각 행성의 실제 공전 속도에 맞게 계산하여 대입
		if (0.01*(306 / 0.6) + speed[1] >= 0)//금성
			revolution[1] = fmodf(revolution[1] + 0.01*(306 / 0.6) + speed[1], 360);
		if (0.01*(360 / 1.0) + speed[2] >= 0)//지구
			revolution[2] = fmodf(revolution[2] + 0.01*(360 / 1.0) + speed[2], 360);
		if (0.01*(360 / 0.07) + speed[3] >= 0)//달
			revolution[3] = fmodf(revolution[3] + 0.01*(360 / 0.07) + speed[3], 360);
		if (0.01*(360 / 1.9) + speed[4] >= 0)//화성
			revolution[4] = fmodf(revolution[4] + 0.01*(360 / 1.9) + speed[4], 360);
		if (0.01*(360 / 11.9) + speed[5] >= 0)//목성
			revolution[5] = fmodf(revolution[5] + 0.01*(360 / 11.9) + speed[5], 360);
		if (0.01*(360 / 29.5) + speed[6] >= 0)//토성
			revolution[6] = fmodf(revolution[6] + 0.01*(360 / 29.5) + speed[6], 360);
		if (0.01*(360 / 84) + speed[7] >= 0)//천왕성
			revolution[7] = fmodf(revolution[7] + 0.01*(360 / 84) + speed[7], 360);
		if (0.01*(360 / 164.8) + speed[8] >= 0)//해왕성
			revolution[8] = fmodf(revolution[8] + 0.01*(360 / 164.8) + speed[8], 360);
	}
	glutPostRedisplay();//윈도우를 다시 그리도록 요청
	glutTimerFunc(30, Rotate, 0);
}

//특수키 콜백 함수
void special_keyboard(int key, int x, int y) {
	switch (key) {
	case 101://키보드 위 화살표
		if (index == 0) {//기본 시점인 경우
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//태양과의 거리 계산
			double rx = (camera[index][0] - 0.1) / 10;//카메라의 x축 줌 비율 설정
			double ry = camera[index][1] / 10;//카메라의 y축 줌 비율 설정
			double rz = camera[index][2] / 10;//카메라의 z축 줌 비율 설정
			if (length > 0.02) {//카메라가 태양을 뚫고 반대로 가는 것을 방지하기 위한 조건문
				camera[index][0] -= rx;//정해진 비율에 따라 카메라 x축 값 감소
				camera[index][1] -= ry;//정해진 비율에 따라 카메라 y축 값 감소
				camera[index][2] -= rz;//정해진 비율에 따라 카메라 z축 값 감소
			}
		}
		else if (index == 1) {//위 시점인 경우, z축 값은 고정이므로 계산할 필요가 없다.
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//태양과의 거리 계산
			double rx = (camera[index][0] - 0.1) / 10;//카메라의 x축 줌 비율 설정
			double ry = camera[index][1] / 10;//카메라의 y축 줌 비율 설정
			if (length > 0.02) {//카메라가 태양을 뚫고 반대로 가는 것을 방지하기 위한 조건문
				camera[index][0] -= rx;//정해진 비율에 따라 카메라 x축 값 감소
				camera[index][1] -= ry;//정해진 비율에 따라 카메라 y축 값 감소
			}
		}
		else if (index == 2) {//옆 시점인 경우, y축 값은 고정이므로 계산할 필요가 없다.
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//태양과의 거리 계산
			double rx = (camera[index][0] - 0.1) / 10;//카메라의 x축 줌 비율 설정
			double rz = camera[index][2] / 10;//카메라의 z축 줌 비율 설정
			if (length > 0.02) {//카메라가 태양을 뚫고 반대로 가는 것을 방지하기 위한 조건문
				camera[index][0] -= rx;//정해진 비율에 따라 카메라 x축 값 감소
				camera[index][2] -= rz;//정해진 비율에 따라 카메라 z축 값 감소
			}
		}
		else if (index == 3) {//앞 시점인 경우, y축 값은 고정이므로 계산할 필요가 없다.
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);
			double rx = (camera[index][0] - 0.1) / 10;//카메라의 x축 줌 비율 설정
			double rz = camera[index][2] / 10;//카메라의 z축 줌 비율 설정
			if (length > 0.02) {//카메라가 태양을 뚫고 반대로 가는 것을 방지하기 위한 조건문
				camera[index][0] -= rx;//정해진 비율에 따라 카메라 x축 값 감소
				camera[index][2] -= rz;//정해진 비율에 따라 카메라 z축 값 감소
			}
		}
		break;
	case 103://키보드 아래 화살표
		if (index == 0) {//기본시점
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//태양과의 거리 계산
			double rx = (camera[index][0] - 0.1) / 10;//카메라의 x축 줌 아웃 비율 계산
			double ry = camera[index][1] / 10;//카메라의 y축 줌 아웃 비율 계산
			double rz = camera[index][2] / 10;//카메라의 z축 줌 아웃 비율 계산
			camera[index][0] += rx;//정해진 비율에 따라 x값 증가
			camera[index][1] += ry;//정해진 비율에 따라 y값 증가
			camera[index][2] += rz;//정해진 비율에 따라 z값 증가
		}
		else if (index == 1) {//위 시점
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//태양과의 거리 계산
			double rx = (camera[index][0] - 0.1) / 10;//카메라의 x축 줌 아웃 비율 계산
			double ry = camera[index][1] / 10;//카메라의 y축 줌 아웃 비율 계산
			camera[index][0] += rx;//정해진 비율에 따라 x값 증가
			camera[index][1] += ry;//정해진 비율에 따라 y값 증가
		}
		else if (index == 2) {//옆 시점
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//태양과의 거리 계산
			double rx = (camera[index][0] - 0.1) / 10;//카메라의 x축 줌 아웃 비율 계산
			double rz = camera[index][2] / 10;//카메라의 z축 줌 아웃 비율 계산
			camera[index][0] += rx;//정해진 비율에 따라 x값 증가
			camera[index][2] += rz;//정해진 비율에 따라 z값 증가
		}
		else if (index == 3) {//앞 시점
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//태양과의 거리 계산
			double rx = (camera[index][0] - 0.1) / 10;//카메라의 x축 줌 아웃 비율 계산
			double rz = camera[index][2] / 10;//카메라의 z축 줌 아웃 비율 계산
			camera[index][0] += rx;//정해진 비율에 따라 x값 증가
			camera[index][2] += rz;//정해진 비율에 따라 z값 증가
		}
		break;
	case 100://키보드 왼쪽 화살표
		if (index == 0) {//기본 시점
			angle[0] = fmodf(angle[0] - 0.05, 360);//회전 각도 계산
			//구면좌표계에서 직교좌표계 변환 공식 사용
			double lx = sin(33.6)*sin(angle[0]);
			double ly = cos(33.6);
			double lz = sin(33.6)*cos(angle[0]);
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//카메라와 태양 사이의 거리 계산
			camera[index][0] = 0.1 + length * lx;//태양이 x축으로 0.1 떨어져 있으므로 0.1을 더한후 위에서 구한 length를 lx 값에 곱한후 더한다
			camera[index][1] = length * -ly;//length에 구해진 -ly를 곱한후 카메라 배열에 대입
			camera[index][2] = length * lz;//length에 구해진 lz를 곱한후 카메라 배열에 대입
		}
		else if (index == 1) {//위 시점
			angle[1] = fmodf(angle[1] - 0.05, 360);//회전 각도 계산
			double lx = sin(angle[1]);//sin 함수를 이용하여 x값 계산
			double ly = cos(angle[1]);//cos 함수를 이용하여 y값 계산
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//카메라와 태양 사이의 거리 계산
			camera[index][0] = 0.1 + length * lx;//태양이 x축으로 0.1 떨어져 있으므로 0.1을 더한후 위에서 구한 length를 lx 값에 곱한후 더한다
			camera[index][1] = length * ly;//length에 구해진 ly를 곱한후 카메라 배열에 대입
		}
		else if (index == 2) {//옆 시점
			angle[2] = fmodf(angle[2] - 0.05, 360);//회전 각도 계산
			double lx = -cos(angle[2]);//cos 함수를 이용하여 x값 계산
			double lz = sin(angle[2]);//sin 함수를 이용하여 z값 계산
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//카메라와 태양 사이의 거리 계산
			camera[index][0] = 0.1 + length * lx;//태양이 x축으로 0.1 떨어져 있으므로 0.1을 더한후 위에서 구한 length를 lx 값에 곱한후 더한다
			camera[index][2] = length * lz;//length에 구해진 lz를 곱한후 카메라 배열에 대입
		}
		else if (index == 3) {//앞
			angle[3] = fmodf(angle[3] - 0.05, 360);//회전 각도 계산
			double lx = sin(angle[3]);//sin 함수를 이용하여 x값 계산
			double lz = cos(angle[3]);//cos 함수를 이용하여 z값 계산
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//카메라와 태양 사이의 거리 계산
			camera[index][0] = 0.1 + length * lx;//태양이 x축으로 0.1 떨어져 있으므로 0.1을 더한후 위에서 구한 length를 lx 값에 곱한후 더한다
			camera[index][2] = length * lz;//length에 구해진 lz를 곱한후 카메라 배열에 대입
		}
		break;
	case 102://키보드 오른쪽 화살표
		if (index == 0) {
			angle[0] = fmodf(angle[0] + 0.05, 360);//회전 각도 계산
			//구면좌표계에서 직교좌표계 변환 공식 사용
			double lx = sin(33.6)*sin(angle[0]);
			double ly = cos(33.6);
			double lz = sin(33.6)*cos(angle[0]);
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//카메라와 태양 사이의 거리 계산
			camera[index][0] = 0.1 + length * lx;//태양이 x축으로 0.1 떨어져 있으므로 0.1을 더한후 위에서 구한 length를 lx 값에 곱한후 더한다
			camera[index][1] = length * -ly;//length에 구해진 -ly를 곱한후 카메라 배열에 대입
			camera[index][2] = length * lz;//length에 구해진 lz를 곱한후 카메라 배열에 대입
		}
		else if (index == 1) {
			angle[1] = fmodf(angle[1] + 0.05, 360);//회전 각도 계산
			double lx = sin(angle[1]);//sin함수를 이용하여 x값 계산
			double ly = cos(angle[1]);//cos함수를 이용하여 y값 계산
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//카메라와 태양 사이의 거리 계산
			camera[index][0] = 0.1 + length * lx;//태양이 x축으로 0.1 떨어져 있으므로 0.1을 더한후 위에서 구한 length를 lx 값에 곱한후 더한다
			camera[index][1] = length * ly;//length에 구해진 ly를 곱한후 카메라 배열에 대입
		}
		else if (index == 2) {
			angle[2] = fmodf(angle[2] + 0.05, 360);//회전 각도 계산
			double lx = -cos(angle[2]);//cos함수를 이용하여 x값 계산
			double lz = sin(angle[2]);//sin함수를 이용하여 y값 계산
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//카메라와 태양 사이의 거리 계산
			camera[index][0] = 0.1 + length * lx;//태양이 x축으로 0.1 떨어져 있으므로 0.1을 더한후 위에서 구한 length를 lx 값에 곱한후 더한다
			camera[index][2] = length * lz;//length에 구해진 lz를 곱한후 카메라 배열에 대입
		}
		else if (index == 3) {
			angle[3] = fmodf(angle[3] + 0.05, 360);//회전 각도 계산
			double lx = sin(angle[3]);//sin함수를 이용하여 x값 계산
			double lz = cos(angle[3]);//cos함수를 이용하여 z값 계산
			double length = getDistance(camera[index][0], camera[index][1], camera[index][2]);//카메라와 태양 사이의 거리 계산
			camera[index][0] = 0.1 + length * lx;//태양이 x축으로 0.1 떨어져 있으므로 0.1을 더한후 위에서 구한 length를 lx 값에 곱한후 더한다
			camera[index][2] = length * lz;//length에 구해진 lz를 곱한후 카메라 배열에 대입
		}
		break;
	default:

		break;
	}
	glutPostRedisplay();//윈도우를 다시 그리도록 요청
}

//키보드 콜백 함수
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 32://스페이스바 클릭시
		if (Rotation == 1)//회전 중이면
			Rotation = 0;//Rotation을 0으로 설정하여 정지
		else//회전 중이 아니면
			Rotation = 1;//Rotation을 1로 설정하여 회전
		break;
	case 43://+버튼 클릭시
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
	case 45://-버튼 클릭시
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

//메뉴 콜백 함수
void popupMenu(int value) {
	switch (value) {
	case 1://기본 시점 
		index = 0;
		break;
	case 2://위 시점
		index = 1;
		break;
	case 3://옆 시점
		index = 2;
		break;
	case 4://앞 시점
		index = 3;
		break;
	case 5://무작위 시점
		index = rand() % 4;//위 4가지 시점 중 하나 랜덤으로 설정
		break;
	}
}

//선택된 물체의 RGB값을 변경해주는 함수
void ProcessSelect(GLuint index[64])
{
	int r = rand() % 256; //rgb값을 랜덤으로 설정
	int g = rand() % 256;
	int b = rand() % 256;
	switch (index[3]) {//3번만 검사하므로 여려 물체가 선택되었어도 하나만 변경, 선택된 행성의 rgb값 변경
	case 100://태양
		list[0].r = (float)r / 255;
		list[0].g = (float)g / 255;
		list[0].b = (float)b / 255;
		break;
	case 101://수성
		list[1].r = (float)r / 255;
		list[1].g = (float)g / 255;
		list[1].b = (float)b / 255;
		break;
	case 102://금성
		list[2].r = (float)r / 255;
		list[2].g = (float)g / 255;
		list[2].b = (float)b / 255;
		break;
	case 103://지구
		list[3].r = (float)r / 255;
		list[3].g = (float)g / 255;
		list[3].b = (float)b / 255;
		break;
	case 104://달
		list[4].r = (float)r / 255;
		list[4].g = (float)g / 255;
		list[4].b = (float)b / 255;
		break;
	case 105://화성
		list[5].r = (float)r / 255;
		list[5].g = (float)g / 255;
		list[5].b = (float)b / 255;
		break;
	case 106://목성
		list[6].r = (float)r / 255;
		list[6].g = (float)g / 255;
		list[6].b = (float)b / 255;
		break;
	case 107://토성
		list[7].r = (float)r / 255;
		list[7].g = (float)g / 255;
		list[7].b = (float)b / 255;
		break;
	case 108://천왕성
		list[8].r = (float)r / 255;
		list[8].g = (float)g / 255;
		list[8].b = (float)b / 255;
		break;
	case 109://해왕성
		list[9].r = (float)r / 255;
		list[9].g = (float)g / 255;
		list[9].b = (float)b / 255;
		break;
	default: break;
	}
}

//마우스 콜백 함수
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		GLuint selectBuff[64];//선택된 물체의 이름을 저장할 배열
		GLint hits, viewport[4];//hits는 마우스로 클릭해서 선택된 물체가 몇개인지를 저장할 변수
		//viewport는 뷰포트 정보를 저장할 변수
		glSelectBuffer(64, selectBuff);//select buffer로 사용될 배열의 크기와 사용될 메모리 영역을 설정
		glGetIntegerv(GL_VIEWPORT, viewport);//뷰포트의 영역값을 얻어와 viewport배열에 저장
		glMatrixMode(GL_PROJECTION);//projection 모드로 전환
		glPushMatrix();//현재 행렬값 저장
		glRenderMode(GL_SELECT);// 렌더링할때의 Render Mode를 Selection Buffer에 렌더링 하도록 지정
		glLoadIdentity();//행렬 초기화
		gluPickMatrix(x, viewport[3] - y, 5, 5, viewport);//피킹 영역 정의
		gluPerspective(60.0, ratio, 0.01, 100.0);//투영값 설정
		glMatrixMode(GL_MODELVIEW);//Modelview 모드로 전환
		glLoadIdentity();//행렬 초기화
		draw();//행성 그리기
		hits = glRenderMode(GL_RENDER);//그릴 때 Render Buffer에 그리도록 설정, 몇 개의 물체가 선택되었는지 반환하므로 hits에 그 값을 저장
		if (hits > 0) ProcessSelect(selectBuff);//물체가 하나 이상 선택되었으면 ProcessSelect함수 호출
		glMatrixMode(GL_PROJECTION);//Projection모드로 전환
		glPopMatrix();//기존 정보로 복귀
		glMatrixMode(GL_MODELVIEW);//Modelview 모드로 전환
	}
}

//main함수
int main(int argc, char** argv) {
	glutInit(&argc, argv);//GLUT 상태 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//디스플레이모드형식 선택: double buffer & rgb & depth 모드 선택
	glutInitWindowSize(800, 500);//창의 크기 설정
	glutInitWindowPosition(100, 100);//창의 위치 설정

	glutCreateWindow("프로젝트");//윈도우 생성

	glutCreateMenu(popupMenu);//메뉴 콜백 함수 등록
	glutAddMenuEntry("기본 시점", 1);//현재 메뉴에 세부 항목 추가
	glutAddMenuEntry("위 시점", 2);
	glutAddMenuEntry("옆 시점", 3);
	glutAddMenuEntry("앞 시점", 4);
	glutAddMenuEntry("무작위 시점", 5);


	init();//초기 설정 함수 호출
	glutAttachMenu(GLUT_RIGHT_BUTTON);//해당 버튼이 눌리면 할당된 메뉴가 팝업되도록 설정
	glutDisplayFunc(display);//display 콜백 함수 등록
	glutReshapeFunc(reshape);//reshape 콜백 함수 등록
	glutKeyboardFunc(keyboard);//keyboard 콜백 함수 등록
	glutSpecialFunc(special_keyboard);//special_keyboard 콜백 함수 등록
	glutMouseFunc(mouse);//mouse 콜백함수 등록
	glutTimerFunc(30, Rotate, 1);//타이머 콜백함수 등록
	glutMainLoop();//이벤트 처리엔진 시작

	return 0;
}
