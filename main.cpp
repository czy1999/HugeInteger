#include<iostream>
#include<string>
#include <fstream>
#include"HugeInteger.h"
using namespace std;

/*
��ȡnumber.txt�����ݣ�ÿ���������֣���󳤶�Ϊ40λ������ǰ�з��ţ���������Ҫ��
����ѭ�����д���������������ֱ����ȡ���ļ�ĩβΪֹ��
(�������ȳ��������Ƿ��ַ�����ʾ����ֹͣ����)
*/

int main() {
	//�趨һ����������
	int count = 1; 
	HugeInteger a, b;

	//���ļ������Ҽ����Ƿ�򿪳ɹ�
	ifstream file("number.txt");
	if (!file.is_open()) {
		cout << "Fail to open the file!" << endl;
		exit(0);
	}

	//��ʼѭ�����
	while (!file.eof()) {
		file >> a >> b;
		cout << "Group" << count++ << ":"<<endl;
		cout << "sum=" << a + b<<endl;
		cout << "sub=" << a - b << endl;
		cout << endl;
	}
	//�ر��ļ������� 
	file.close();            
	return 0;

}