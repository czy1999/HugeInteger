#ifndef HUGENUM 
#define HUGENUM
#include<iostream>
#define N 40
using namespace std;

/*p(HugeInteger Class) Create a class HugeInteger that uses a 40-element array of digits to store integers as large as 40 digits each.
nProvide member functions input, output, add and subtract.
nOverload operator + and operator - which implement the add and subtract function.
nIf you feel ambitious, provide member functions multiply, divide and modulus.*/

class HugeInteger {
private:
	//数组num用来储存数字
	int num[N];

	//size为数字的位数
	int size;

	//pos表示数字的正负，True为正
	bool pos;

	//工具函数，与另一个大数的绝对值进行比较，大于等于返回true，小于返回false
	bool compareAbs(HugeInteger &a)const; 
public:
	//构造函数，初始化内部变量
	HugeInteger();

	//输入函数
	void input();

	//输出函数
	void output();

	//加法函数
	HugeInteger add(HugeInteger &b)const;

	//减法函数
	HugeInteger subtract(HugeInteger &b)const;

	//操作符+的重载，直接调用了add函数
	HugeInteger operator+ (HugeInteger &b)const;

	//操作符 - 的重载，直接调用了sub函数
	HugeInteger operator- (HugeInteger &b)const;

	//操作符 << 的重载
	friend ostream &operator << (ostream &os, const HugeInteger &ob);

	//操作符 >> 的重载
	friend istream &operator >> (istream &is,  HugeInteger &ob);
};
#endif // !HUGENUM