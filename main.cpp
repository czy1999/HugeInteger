#include<iostream>
#include<string>
#include <fstream>
#include"HugeInteger.h"
using namespace std;

/*
读取number.txt的内容，每行两个数字，最大长度为40位。负数前有符号，正数不需要。
程序将循环进行大数相加相减操作，直到读取到文件末尾为止。
(超出长度程序或输入非法字符会提示并且停止操作)
*/

int main() {
	//设定一个计数变量
	int count = 1; 
	HugeInteger a, b;

	//打开文件，并且检验是否打开成功
	ifstream file("number.txt");
	if (!file.is_open()) {
		cout << "Fail to open the file!" << endl;
		exit(0);
	}

	//开始循环求解
	while (!file.eof()) {
		file >> a >> b;
		cout << "Group" << count++ << ":"<<endl;
		cout << "sum=" << a + b<<endl;
		cout << "sub=" << a - b << endl;
		cout << endl;
	}
	//关闭文件输入流 
	file.close();            
	return 0;

}