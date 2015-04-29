#include "arbreCubes.cpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	arbrecubes * monarbre = new arbrecubes("cubes10_5.txt");

	cout<<"debut des operations"<<endl;
	point pointT(0,0);
	cube table(pointT,319);

	point point7(-138,-138);
	cube cube7(point7,7);

	point point31(-138,105);
	cube cube31(point31,31);

	point point103(0,105);
	cube cube103(point103,103);

	point point400(-105,0);
	cube cube400(point400,103);

	/*vector<cube> poserT = monarbre->dessus(table);

	vector<cube>::iterator it =poserT.begin();
	cout<<" la table soutien les cubes :"<<endl;
	for(it ;it != poserT.end();it++)
		cout<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;
	cout<<"this is the end"<<endl;

	poserT = monarbre->dessus(cube400);

	it =poserT.begin();
	cout<<" le cube 400 soutien les cubes :"<<endl;
	for(it ;it != poserT.end();it++)
		cout<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;
	cout<<"this is the end"<<endl;


	poserT = monarbre->dessus(cube7);

	it =poserT.begin();
	cout<<" le cube 7 soutien les cubes :"<<endl;
	for(it ;it != poserT.end();it++)
		cout<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;
	cout<<"this is the end"<<endl;

	poserT = monarbre->dessus(cube31);

	it =poserT.begin();
	cout<<" le cube 40 soutien les cubes :"<<endl;
	for(it ;it != poserT.end();it++)
		cout<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;
	cout<<"this is the end"<<endl;

	poserT = monarbre->dessus(cube103);

	it =poserT.begin();
	cout<<" le cube 36 soutien les cubes :"<<endl;
	for(it ;it != poserT.end();it++)
		cout<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;
	cout<<"this is the end"<<endl;

///////////////////////////////////////////////////////////////////////////////////////
	cout<<"debut suppression"<<endl;
	monarbre->supprimer(cube400);

	poserT = monarbre->dessus(table);

	it =poserT.begin();
	cout<<" la table soutien les cubes :"<<endl;
	for(it ;it != poserT.end();it++)
		cout<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;
	cout<<"this is the end"<<endl;

	poserT = monarbre->dessus(cube7);

	it =poserT.begin();
	cout<<" le cube 5 soutien les cubes :"<<endl;
	for(it ;it != poserT.end();it++)
		cout<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;
	cout<<"this is the end"<<endl;

	poserT = monarbre->dessus(cube31);

	it =poserT.begin();
	cout<<" le cube 40 soutien les cubes :"<<endl;
	for(it ;it != poserT.end();it++)
		cout<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;
	cout<<"this is the end"<<endl;

	poserT = monarbre->dessus(cube103);

	it =poserT.begin();
	cout<<" le cube 36 soutien les cubes :"<<endl;
	for(it ;it != poserT.end();it++)
		cout<<(*it).cote()<< "=>"<<(*it).centre().x<<","<<(*it).centre().y<<endl;
	cout<<"this is the end"<<endl;

	point goutte1(-100,-100);
	point goutte2(0,0);
	cube haha = monarbre->cubede(goutte1);
	int hihi = monarbre->hauteur(goutte1);

	cout<<haha.cote()<<endl;
	cout<<hihi<<endl;
	haha = monarbre->cubede(goutte2);
	hihi = monarbre->hauteur(goutte2);

	cout<<haha.cote()<<endl;
	cout<<hihi<<endl;*/


	
}
