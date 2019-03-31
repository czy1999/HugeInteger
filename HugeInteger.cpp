#include<iostream>
#include"HugeInteger.h"
#include<stdlib.h>
#include<string>
using namespace std;

//���캯������ʼ���ڲ�����
HugeInteger::HugeInteger()
{
	//����ʼֵ����ֵΪ0
	for (int i = 0; i < N; i++)
		num[i] = 0;

	size = 1;
	pos = true;
}

//���뺯��
void HugeInteger::input()
{
	HugeInteger();//���ܻ��θ�ֵ�����Ҫ������ǰ�ٳ�ʼ��һ��

	string s;//�Ȱ�ֵ����һ���ַ�����
	cin >> s;


	//�жϴ���������������һ���ַ��Ǹ��������趨����Ϊ����
	if (s.at(0) == '-') {
		s.erase(s.begin());
		pos = false;
	}
	if (s.size() > N) {
		cout << "The number is too long!" << endl;
		exit(1);
	}
	else {
		int i = s.size();//��ȡ�ַ�����С
		size = i;
		//�����ȡ�ַ���ת��Ϊ���ֽ��д洢
		for (auto c : s) {
			if (c - '0' < 0 || c - '0'>9) {
				cout << "Invaid Input!" << endl;
				exit(1);
			}
			else
				num[--i] = c - '0';
		}
	}
}

//�������
void HugeInteger::output()
{
	if (!pos)//����Ǹ��������һ������
		cout << '-';
	for (int i = size - 1; i >= 0; i--)//ѭ���������
		cout << num[i];
	cout << endl;
}

//���ߺ���������һ�������ľ���ֵ���бȽϣ����ڵ��ڷ���true��С�ڷ���false
bool HugeInteger::compareAbs(HugeInteger &a)const {

	bool flag = true; //���ó�ʼ��ǩΪtrue

	if (size < a.size) {
		flag = false;
	}
	else if (a.size == size) { //�����λ����ʼ�Ƚϴ�С
		for (int i = size - 1; i >= 0; i--) {
			if (num[i] > a.num[i])
				break;
			else if (num[i] < a.num[i]) {
				flag = false;
				break;
			}
		}
	}
	//�����жϽ��
	return flag;
}

//�ӷ�����
HugeInteger HugeInteger::add(HugeInteger &b)const
{
	int i;
	//sum���ڴ洢���
	HugeInteger sum;

	//�ж��Ƿ���ͬ�ţ������ͬ����ôpos + b.pos �϶�����0��2��
	if (pos + b.pos != 1) {

		if (size >= b.size) sum.size = size; //�������������λ����ֵ��sum��λ��
		else sum.size = b.size;

		//��ʼѭ����ͬλ���
		for (i = 0; i < sum.size; i++) {
			sum.num[i] += num[i] + b.num[i];
			//�������9������Ҫ��λ
			if (sum.num[i] > 9) {
				sum.num[i] = sum.num[i] - 10;
				sum.num[i + 1] = 1;
			}
		}
		//���һ�������λ�ˣ���Ҫ�����ֵĳ���+1
		if (sum.num[i] != 0) sum.size++;

		//������������Ǹ����������ѷ��Ÿ�Ϊ��
		if (!pos) sum.pos = !sum.pos;
	}
	//���һ��һ�����򽻸������������
	else if (pos) {
		HugeInteger temp = b;
		temp.pos = true;
		sum = subtract(temp);
	}
	else {
		HugeInteger temp = *this;
		temp.pos = true;
		sum = b.subtract(temp);
	}
	
	return sum;//���ؽ��
}

//��������
HugeInteger HugeInteger::subtract(HugeInteger &b)const
{
	int i;
	HugeInteger sub, a= *this;

	//�Ƚ��������ֵľ���ֵ��С�����������ֻ���������С�����򻯳���
	if (!compareAbs(b))
		//����ʹ��*this�ᱨ������ʹ����һ������a
		//sub = b.subtract(*this); 
		sub = b.subtract(a); 

	//�ж��Ƿ���ͬ�ţ������ͬ����ôpos + b.pos �϶�����0��2��
	else if (pos + b.pos != 1) {
		sub.size = size; //�������λ����ֵ

		//��ʼѭ�����
		for (i = 0; i < sub.size; i++) {
			sub.num[i] += num[i] - b.num[i];
			//�����ָ��������λ��һ
			if (sub.num[i] < 0) {
				sub.num[i] = 10 + sub.num[i];
				sub.num[i + 1] = -1;
			}
		}
		//�������Ϊ0��λ������ֹ�������0000123�����
		for (i = sub.size - 1; i > 0; i--) {
			if (sub.num[i] == 0) sub.size--;
			else break;
		}
		//�����ж�
		if (!pos) sub.pos = !sub.pos;
	}
	//���һ��һ�����򽻸���Ӻ�������
	else if (pos) {
		HugeInteger temp;
		temp = b;
		temp.pos = true;
		sub = add(temp);
	}

	else {
		HugeInteger temp;
		temp = b;
		temp.pos = false;
		sub = add(temp);
	}

	return sub;
}

//������+�����أ�ֱ�ӵ�����add����
HugeInteger HugeInteger::operator+(HugeInteger &a)const {
	return add(a);
}

//������-�����أ�ֱ�ӵ�����sub����
HugeInteger HugeInteger::operator-(HugeInteger &a)const {
	return subtract(a);
}

//������<<�����أ������������������
ostream &operator << (ostream &os, const HugeInteger &ob)
{
	if (!ob.pos)
		os << '-';
	for (int i = ob.size - 1; i >= 0; i--)
		os << ob.num[i];
	return os;
}

//������>>������,���������뺯������
istream &operator >> (istream &is,  HugeInteger &ob)
{
	for (int i = 0; i < N; i++)
		ob.num[i]= 0;
	ob.size = 0;
	ob.pos = true;

	string s;
	is >> s;
	int i = s.size();
	if (s.at(0) == '-') {
		s.erase(s.begin());
		ob.pos = false;
		i--;
	}
	if (i > N) {
		cout << "The number is too long!" << endl;
		exit(1);
	}
	else {
		ob.size = i;
		for (auto c : s)
		{
			if (c - '0' < 0 || c - '0'>9) {
				cout << "Invaid Input!" << endl;
				exit(0);
			}
			else
				ob.num[--i] = c - '0';
		}
	}
	if (is.fail())
	{
		cout << "Input Error" << endl;
		abort();    //���������Է�������ʽ��������
	}
	return is;
}


