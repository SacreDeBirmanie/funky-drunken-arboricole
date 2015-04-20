#include "arbreCubes.hpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	arbrecubes * monarbre = new arbrecubes("cubes.txt");

	point pointT(0,0);
	cube table(pointT,201);

	point point5(18,18);
	cube cube5(point5,5);

	point point5bis(-10,-10);
	cube cube5bis(point5bis,5);

	point point70(70,-70);
	cube cube70(point70,11);


	vector<cube> poserT = monarbre->dessus(table);

	vector<cube>::iterator it =poserT.begin();
	
	for(it ;it != poserT.end();it++)
		cout<<"est soutenu :"<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;

	cube soutien5 = monarbre->soutien(cube5);
	cout<<"soutien 5 :"<<soutien5.centre().x<<endl;

	cube soutien70 = monarbre->soutien(cube70);
	cout<<"soutien 70 :"<<soutien70.centre().x<<endl;

	cube soutien5bis = monarbre->soutien(cube5bis);
	cout<<"soutien 5bis :"<<soutien5bis.centre().x<<endl;


	
}
