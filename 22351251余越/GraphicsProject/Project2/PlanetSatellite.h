#pragma once
#include "Planet.h"
class PlanetSatellite :
    public Planet
{
public:
	void setModel1(float T,//�ѹ���ʱ��
		float rRevolution, float rSRevolution,//�����ǹ�ת�뾶,���ǹ�ת�뾶
		float xStar, float yStar, float zStar,//��ת���ƺ�������
		float xRotation, float yRotation, float zRotation,//��ת���ƺ���ת��
		float xSRotation, float ySRotation, float zSRotation);//��ת��
	void setTRevolutionTSpin(float TRevolution, float TSRevolution, float TSpin);//��ת��ת����
protected:
	float rSRevolution,//���ǹ�ת�뾶
		xSRotation, ySRotation, zSRotation;//���ǹ�ת��תת��
	float TSRevolution;//���ǹ�ת����

};

