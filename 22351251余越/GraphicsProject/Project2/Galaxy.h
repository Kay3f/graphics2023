#pragma once
#include "Planet.h"
#include "PlanetSatellite.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define MAXPlanet 7
#define MAXSatellite 3
class Galaxy
{
public:
	Galaxy(int iGalaxy);
	void initGalaxy(float xStar, float yStar, float zStar);
	void setTimeStart(double timeStart);
	void setTime(glm::mat4 projection, glm::mat4 view, glm::vec3 viewPos);

	int n, nS;
	Planet P[MAXPlanet];//���Ƕ���
	PlanetSatellite S[MAXSatellite];//���Ƕ���
private:
	int numBig, iGalaxy;
	double timeStart, time0;

	float R[MAXPlanet],//�����ǰ뾶
		rRevolution[MAXPlanet],//�����ǹ�ת�뾶
		xStar, yStar, zStar,//��ת���ƺ�������
		xRotation, yRotation, zRotation,//��ת��
		xSpin, ySpin, zSpin,//��ת��
		TRevolution[MAXPlanet];//��ת����

	float RS[MAXSatellite],//�����ǰ뾶
		rSRevolution[MAXSatellite],//�����ǹ�ת�뾶
		xSRotation[MAXSatellite], ySRotation[MAXSatellite], zSRotation[MAXSatellite];//ת��
	int labelPlanet[MAXSatellite];//��ת�����Ǳ��

	int tex[MAXPlanet];//������������
	int texS[MAXSatellite];//������������
};

