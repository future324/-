#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>
using namespace std;


class WorldT
{
public:
	cv::Mat RoteM, TransM;
	cv::Point3f Theta_W2C;
	cv::Point3f Theta_C2W;
	cv::Point3f Position_OwInC;
	cv::Point3f Position_OcInW;
	cv::Mat rvecs, tvecs;

public:	
	static void CodeRotateByZ(double x, double y, double thetaz, double& outx, double& outy)
	{
		double x1 = x;//����������һ�Σ���֤&x == &outx���������Ҳ�ܼ�����ȷ
		double y1 = y;
		double rz = thetaz * CV_PI / 180;
		outx = cos(rz) * x1 - sin(rz) * y1;
		outy = sin(rz) * x1 + cos(rz) * y1;
	}
	static void CodeRotateByY(double x, double z, double thetay, double& outx, double& outz)
	{
		double x1 = x;
		double z1 = z;
		double ry = thetay * CV_PI / 180;
		outx = cos(ry) * x1 + sin(ry) * z1;
		outz = cos(ry) * z1 - sin(ry) * x1;
	}
	static void CodeRotateByX(double y, double z, double thetax, double& outy, double& outz)
	{
		double y1 = y;//����������һ�Σ���֤&y == &y���������Ҳ�ܼ�����ȷ
		double z1 = z;
		double rx = thetax * CV_PI / 180;
		outy = cos(rx) * y1 - sin(rx) * z1;
		outz = cos(rx) * z1 + sin(rx) * y1;
	}
	void proTran(cv::Mat* rvec, cv::Mat* tvec)
	{
		/******��ȡ��ת����******/
		double rm[9];
		RoteM = cv::Mat(3, 3, CV_64FC1, rm);
		Rodrigues(*rvec, RoteM);
		double r11 = RoteM.ptr<double>(0)[0];
		double r12 = RoteM.ptr<double>(0)[1];
		double r13 = RoteM.ptr<double>(0)[2];
		double r21 = RoteM.ptr<double>(1)[0];
		double r22 = RoteM.ptr<double>(1)[1];
		double r23 = RoteM.ptr<double>(1)[2];
		double r31 = RoteM.ptr<double>(2)[0];
		double r32 = RoteM.ptr<double>(2)[1];
		double r33 = RoteM.ptr<double>(2)[2];
		TransM = *tvec;

		//������������ϵ��������תŷ���ǣ���ת�����ת����������ϵ��
		//��ת˳��Ϊz��y��x
		double thetaz = atan2(r21, r11) / CV_PI * 180;
		double thetay = atan2(-1 * r31, sqrt(r32*r32 + r33*r33)) / CV_PI * 180;
		double thetax = atan2(r32, r33) / CV_PI * 180;
		//���ϵ������ϵ��������תŷ���ǣ��������ϵ�մ���ת���������������ϵ��ȫƽ�С�
		//��ת˳��Ϊz��y��x
		//////THETAZ���������ж���z����ת���Ƕȱ仯����y�Ḻ����Ϊ��ʼ����
		//////����ͷ��aruco���z����ʱ��ת���Ƕ����ӣ�˳ʱ��ת���Ƕȼ�С
		Theta_C2W.z = thetaz;
		Theta_C2W.y = thetay;
		Theta_C2W.x = thetax;
		//���������ϵ�����ϵ��������תŷ���ǣ�����ϵ�մ���ת�����ת���������ϵ��
		//��ת˳��Ϊx��y��z
		Theta_W2C.x = -1 * thetax;
		Theta_W2C.y = -1 * thetay;
		Theta_W2C.z = -1 * thetaz;
		//���ƽ�ƾ��󣬱�ʾ���������ϵԭ�㣬��������(x,y,z)�ߣ��͵�����������ϵԭ��
		double tx = (*tvec).ptr<double>(0)[0];
		double ty = (*tvec).ptr<double>(0)[1];
		double tz = (*tvec).ptr<double>(0)[2];
		//x y z ΪΨһ���������ԭʼ����ϵ�µ�����ֵ
		//Ҳ��������OcOw���������ϵ�µ�ֵ
		double x = tx, y = ty, z = tz;
		Position_OwInC.x = x;
		Position_OwInC.y = y;
		Position_OwInC.z = z;
		//�������η�����ת
		CodeRotateByZ(x, y, -1 * thetaz, x, y);
		CodeRotateByY(x, z, -1 * thetay, x, z);
		CodeRotateByX(y, z, -1 * thetax, y, z);

		Position_OcInW.x = x*-1;
		Position_OcInW.y = y*-1;
		Position_OcInW.z = z*-1;

	}
};