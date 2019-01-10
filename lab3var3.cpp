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


struct node // структура для представления узлов дерева
{
	string key; // ключ узла-слово
	string meaning; // значение слова
	unsigned char height; // высота поддерева с корнем в данном узле
	node* left; // указатель на левое поддерево
	node* right; // указатель на правое поддерево
	node(string k, string m) { key = k; meaning = m; left = right = 0; height = 1; } //
};

unsigned char height(node* p) // является оберткой для поля height, она может работать и с нулевыми указателями (с пустыми деревьями)
{
	return p?p->height:0;
}

int bfactor(node* p) // вычисляет balance factor заданного узла (и работает только с ненулевыми указателями)
{
	return height(p->right)-height(p->left);
}

void fixheight(node* p) // восстанавливает корректное значение поля height заданного узла (при условии, что значения этого поля в правом и левом дочерних узлах являются корректными)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // балансировка узла p
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
	return p; // балансировка не нужна
}

node* insert(node* p, string k, string m) // вставка ключа k с значением m в дерево с корнем p
{
	if( !p ) return new node(k,m);
	if( k<p->key )
		p->left = insert(p->left,k,m);
	else
		p->right = insert(p->right,k,m);
	return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p
{
	return p->left?findmin(p->left):p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, string k, string m) // удаление ключа k с значением m из дерева p
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
    umap["auto"] = "Спецификатор типа для указания компилятору локальной области видимости переменной(по умолчанию)";
    umap["break"] = "Оператор выхода из цикла";
    umap["case"] = "Оператор указания варианта выбора(используется вместе с switch)";
    umap["char"] = "Символьный тип данных";
    umap["const"] = "Объекты типа const не могут быть изменены программой во время её выполнения";
    umap["continue"] = "Оператор продолжения цикла с пропуском оставшихся операторов до конца блока";
    umap["default"] = "Оператор выбора по умолчанию";
    umap["do"] = "Оператор цикла с постусловием без счётчика";
    umap["double"] = "Тип данных с плавающей запятой двойной точности";
    umap["else"] = "Условный оператор 'в противном случае'";
    umap["enum"] = "Пользовательский тип данных 'перечисляемый тип'";
    umap["extern"] = "Спецификатор типа для указания компилятору внешней привязки переменной";
    umap["float"] = "Тип данных с плавающей запятой";
    umap["for"] = "Оператор цикла с предусловием, с счётчиком";
    umap["goto"] = "Оператор безусловного перехода";
    umap["if"] = "Условный оператор 'если'";
    umap["int"] = "Целочисленный тип данных";
    umap["long"] = "Модификатор типа данных для определения длинных переменных";
    umap["register"] = "Спецификатор типа для хранения переменной в регистрах процессора";
    umap["return"] = "Оператор для возврата из функции значения";
    umap["short"] = "Модификатор типа данных для определения коротких переменных(обычно не используется)";

cout << "2 - добавление элемента" << endl;
cout << "3 - удаление элемента" << endl;
cout << "4 - поиск элемента" << endl;
cout << "0 - выход" << endl;
cout << "сделайте выбор" << endl;
int choice;
while( choice!=0){
cin >> choice;

switch (choice)
{
case 0:
exit(0);
case 2:{
cout << "введите ключ" << endl;
string k;
cin >> k;
cout << "введите строку" << endl;
string str;
cin >> str;
umap[k]=str;
 break;}
case 3:
{ cout << "введите ключ для удаления" << endl;
string k;
cin >> k;
umap.erase(k);
break;
}
case 4:
{cout << "введите ключ для поиска" << endl;
string k;
cin >> k;
if (umap.count(k) == NULL)
cout << "Элемент не найден" << endl;
else
cout << k << " - "<<umap[k];
break;
}
}
}
    return 0;
}
