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
	//����num������������
	int num[N];

	//sizeΪ���ֵ�λ��
	int size;

	//pos��ʾ���ֵ�������TrueΪ��
	bool pos;

	//���ߺ���������һ�������ľ���ֵ���бȽϣ����ڵ��ڷ���true��С�ڷ���false
	bool compareAbs(HugeInteger &a)const; 
public:
	//���캯������ʼ���ڲ�����
	HugeInteger();

	//���뺯��
	void input();

	//�������
	void output();

	//�ӷ�����
	HugeInteger add(HugeInteger &b)const;

	//��������
	HugeInteger subtract(HugeInteger &b)const;

	//������+�����أ�ֱ�ӵ�����add����
	HugeInteger operator+ (HugeInteger &b)const;

	//������ - �����أ�ֱ�ӵ�����sub����
	HugeInteger operator- (HugeInteger &b)const;

	//������ << ������
	friend ostream &operator << (ostream &os, const HugeInteger &ob);

	//������ >> ������
	friend istream &operator >> (istream &is,  HugeInteger &ob);
};
#endif // !HUGENUM