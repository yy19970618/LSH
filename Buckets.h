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

private:
	std::vector<Point> array;//Ͱ�����ݼ�
	std::string filename;//���Ͱ���ļ���
	int size;//Ͱ�����ݵ����

};

void Buckets::addPoint(Point p)
{
	array.push_back(p);
}

void Buckets::findMIn(Point p)
{

}
