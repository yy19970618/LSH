#include<iostream>
#include<vector>
#include<string>
typedef struct Point {
	int id;
	float value[1024];
};
/*基本数据结构之桶，桶是查询的基本单位
*/
class Buckets
{
public:
	void addPoint(Point p);//往桶里加点
	void findMIn(Point p);//在桶中找到点p的最邻近

private:
	std::vector<Point> array;//桶的数据集
	std::string filename;//存放桶的文件名
	int size;//桶中数据点个数

};

void Buckets::addPoint(Point p)
{
	array.push_back(p);
}

void Buckets::findMIn(Point p)
{

}
