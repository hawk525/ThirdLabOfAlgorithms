#include <iostream>
#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <random>
#include <ctime>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;


struct node // ��������� ��� ������������� ����� ������
{
	string key; // ���� ����-�����
	string meaning; // �������� �����
	unsigned char height; // ������ ��������� � ������ � ������ ����
	node* left; // ��������� �� ����� ���������
	node* right; // ��������� �� ������ ���������
	node(string k, string m) { key = k; meaning = m; left = right = 0; height = 1; } //
};

unsigned char height(node* p) // �������� �������� ��� ���� height, ��� ����� �������� � � �������� ����������� (� ������� ���������)
{
	return p?p->height:0;
}

int bfactor(node* p) // ��������� balance factor ��������� ���� (� �������� ������ � ���������� �����������)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p) // ��������������� ���������� �������� ���� height ��������� ���� (��� �������, ��� �������� ����� ���� � ������ � ����� �������� ����� �������� �����������)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // ������ ������� ������ p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // ����� ������� ������ q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // ������������ ���� p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // ������������ �� �����
}

node* insert(node* p, string k, string m) // ������� ����� k � ��������� m � ������ � ������ p
{
	if( !p ) return new node(k,m);
	if( k<p->key )
		p->left = insert(p->left,k,m);
	else
		p->right = insert(p->right,k,m);
	return balance(p);
}

node* findmin(node* p) // ����� ���� � ����������� ������ � ������ p
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p) // �������� ���� � ����������� ������ �� ������ p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, string k, string m) // �������� ����� k � ��������� m �� ������ p
{
	if( !p ) return 0;
	if( k < p->key )
		p->left = remove(p->left,k,m);
	else if( k > p->key )
		p->right = remove(p->right,k,m);
	else //  k == p->key
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if( !r ) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}


int main(){

    setlocale(LC_ALL,"Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unordered_map<string, string> umap;

    // inserting values by using [] operator
    umap["auto"] = "������������ ���� ��� �������� ����������� ��������� ������� ��������� ����������(�� ���������)";
    umap["break"] = "�������� ������ �� �����";
    umap["case"] = "�������� �������� �������� ������(������������ ������ � switch)";
    umap["char"] = "���������� ��� ������";
    umap["const"] = "������� ���� const �� ����� ���� �������� ���������� �� ����� � ����������";
    umap["continue"] = "�������� ����������� ����� � ��������� ���������� ���������� �� ����� �����";
    umap["default"] = "�������� ������ �� ���������";
    umap["do"] = "�������� ����� � ������������ ��� ��������";
    umap["double"] = "��� ������ � ��������� ������� ������� ��������";
    umap["else"] = "�������� �������� '� ��������� ������'";
    umap["enum"] = "���������������� ��� ������ '������������� ���'";
    umap["extern"] = "������������ ���� ��� �������� ����������� ������� �������� ����������";
    umap["float"] = "��� ������ � ��������� �������";
    umap["for"] = "�������� ����� � ������������, � ���������";
    umap["goto"] = "�������� ������������ ��������";
    umap["if"] = "�������� �������� '����'";
    umap["int"] = "������������� ��� ������";
    umap["long"] = "����������� ���� ������ ��� ����������� ������� ����������";
    umap["register"] = "������������ ���� ��� �������� ���������� � ��������� ����������";
    umap["return"] = "�������� ��� �������� �� ������� ��������";
    umap["short"] = "����������� ���� ������ ��� ����������� �������� ����������(������ �� ������������)";

cout << "2 - ���������� ��������" << endl;
cout << "3 - �������� ��������" << endl;
cout << "4 - ����� ��������" << endl;
cout << "0 - �����" << endl;
cout << "�������� �����" << endl;
int choice;
while( choice!=0){
cin >> choice;

switch (choice)
{
case 0:
exit(0);
case 2:{
cout << "������� ����" << endl;
string k;
cin >> k;
cout << "������� ������" << endl;
string str;
cin >> str;
umap[k]=str;
 break;}
case 3:
{ cout << "������� ���� ��� ��������" << endl;
string k;
cin >> k;
umap.erase(k);
break;
}
case 4:
{cout << "������� ���� ��� ������" << endl;
string k;
cin >> k;
if (umap.count(k) == NULL)
cout << "������� �� ������" << endl;
else
cout << k << " - "<<umap[k];
break;
}
}
}
    return 0;
}
