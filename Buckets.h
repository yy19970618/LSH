#include<iostream>
#include<vector>
#include<string>
typedef struct Point {
	int id;
	float value[1024];
};
/*�������ݽṹ֮Ͱ��Ͱ�ǲ�ѯ�Ļ�����λ
*/
class Buckets
{
public:
	void addPoint(Point p);//��Ͱ��ӵ�
	void findMIn(Point p);//��Ͱ���ҵ���p�����ڽ�
	std::string filename;//���Ͱ���ļ���

private:
	std::vector<Point> array;//Ͱ�����ݼ�
	int size;//Ͱ�����ݵ����

};

void Buckets::addPoint(Point p)
{
	
}

void Buckets::findMIn(Point p)
{

}
