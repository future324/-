#pragma once


//�������Ȼ�̣����Ƕ��ڵ�ͼ��ǳ�����
class MapBuild
{
public:
	//rows��ÿ��aruco���������cols���������������Ϊÿ��aruco�����������space����������ĵ�֮�����ʵ���
#define rows 10
#define cols 10
#define space 1.0
	int row = 0;
	int col = 0;

public:
	//************two functions of translating id to location*************//
double idTranx(int id)
{
	row = id % cols;
	return (row*space);
}
double idTrany(int id)
{
	col = id / cols;
	return (col*space);
}

};













