#include<iostream>
#include"HugeInteger.h"
#include<stdlib.h>
#include<string>
using namespace std;

//构造函数，初始化内部变量
HugeInteger::HugeInteger()
{
	//将初始值都赋值为0
	for (int i = 0; i < N; i++)
		num[i] = 0;

	size = 1;
	pos = true;
}

//输入函数
void HugeInteger::input()
{
	HugeInteger();//可能会多次赋值，因此要在输入前再初始化一次

	string s;//先把值存入一个字符串中
	cin >> s;


	//判断大数的正负，若第一个字符是负数，就设定符号为负数
	if (s.at(0) == '-') {
		s.erase(s.begin());
		pos = false;
	}
	if (s.size() > N) {
		cout << "The number is too long!" << endl;
		exit(1);
	}
	else {
		int i = s.size();//读取字符串大小
		size = i;
		//逐个读取字符，转换为数字进行存储
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

//输出函数
void HugeInteger::output()
{
	if (!pos)//如果是负数就输出一个减号
		cout << '-';
	for (int i = size - 1; i >= 0; i--)//循环输出数组
		cout << num[i];
	cout << endl;
}

//工具函数，与另一个大数的绝对值进行比较，大于等于返回true，小于返回false
bool HugeInteger::compareAbs(HugeInteger &a)const {

	bool flag = true; //设置初始标签为true

	if (size < a.size) {
		flag = false;
	}
	else if (a.size == size) { //从最高位往后开始比较大小
		for (int i = size - 1; i >= 0; i--) {
			if (num[i] > a.num[i])
				break;
			else if (num[i] < a.num[i]) {
				flag = false;
				break;
			}
		}
	}
	//返回判断结果
	return flag;
}

//加法函数
HugeInteger HugeInteger::add(HugeInteger &b)const
{
	int i;
	//sum用于存储结果
	HugeInteger sum;

	//判断是否是同号（如果非同号那么pos + b.pos 肯定等于0或2）
	if (pos + b.pos != 1) {

		if (size >= b.size) sum.size = size; //把两个数中最长的位数赋值给sum的位数
		else sum.size = b.size;

		//开始循环，同位相加
		for (i = 0; i < sum.size; i++) {
			sum.num[i] += num[i] + b.num[i];
			//如果大于9，则需要进位
			if (sum.num[i] > 9) {
				sum.num[i] = sum.num[i] - 10;
				sum.num[i + 1] = 1;
			}
		}
		//最后一步如果进位了，就要把数字的长度+1
		if (sum.num[i] != 0) sum.size++;

		//如果两个数都是负数，则最后把符号改为负
		if (!pos) sum.pos = !sum.pos;
	}
	//如果一正一负，则交给相减函数操作
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
	
	return sum;//返回结果
}

//减法函数
HugeInteger HugeInteger::subtract(HugeInteger &b)const
{
	int i;
	HugeInteger sub, a= *this;

	//比较两个数字的绝对值大小，让相减函数只处理大数减小数，简化程序
	if (!compareAbs(b))
		//这里使用*this会报错，所以使用了一个变量a
		//sub = b.subtract(*this); 
		sub = b.subtract(a); 

	//判断是否是同号（如果非同号那么pos + b.pos 肯定等于0或2）
	else if (pos + b.pos != 1) {
		sub.size = size; //给结果的位数赋值

		//开始循环相减
		for (i = 0; i < sub.size; i++) {
			sub.num[i] += num[i] - b.num[i];
			//若出现负数，则高位减一
			if (sub.num[i] < 0) {
				sub.num[i] = 10 + sub.num[i];
				sub.num[i + 1] = -1;
			}
		}
		//清除多余为0的位数，防止出现输出0000123的情况
		for (i = sub.size - 1; i > 0; i--) {
			if (sub.num[i] == 0) sub.size--;
			else break;
		}
		//符号判定
		if (!pos) sub.pos = !sub.pos;
	}
	//如果一正一负，则交给相加函数操作
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

//操作符+的重载，直接调用了add函数
HugeInteger HugeInteger::operator+(HugeInteger &a)const {
	return add(a);
}

//操作符-的重载，直接调用了sub函数
HugeInteger HugeInteger::operator-(HugeInteger &a)const {
	return subtract(a);
}

//操作符<<的重载，过程与输出函数类似
ostream &operator << (ostream &os, const HugeInteger &ob)
{
	if (!ob.pos)
		os << '-';
	for (int i = ob.size - 1; i >= 0; i--)
		os << ob.num[i];
	return os;
}

//操作符>>的重载,过程与输入函数类似
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
		abort();    //输入错误就以非正常方式结束程序
	}
	return is;
}


