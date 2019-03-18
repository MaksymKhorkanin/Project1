
#include "Relation.h"
#include "RelationCut.h"
#include "RelationMatrix.h"


#include "iostream"
#include <stdio.h>
#include <map> 
#include <iterator> 

using namespace std;

void main()
{
	bool dataP[sizeMatr][sizeMatr] = {

	{0, 1, 1, 0, 1},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 0, 1},
	{0, 0, 1, 0, 1},
	{0, 0, 0, 0, 0}

	};

	bool dataQ[sizeMatr][sizeMatr] = {
		{1, 1, 0, 0, 1},
		{1, 1, 0, 0, 1},
		{0, 0, 1, 1, 0},
		{0, 0, 1, 1, 0},
		{1, 1, 0, 0, 1}
	};

	bool dataR[sizeMatr][sizeMatr] = {
		{0, 0, 0, 1, 0},
		{0, 0, 1, 1, 1},
		{0, 1, 0, 0, 1},
		{0, 0, 0, 1, 0},
		{0, 0, 1, 1, 0}
	};

	RelationMatrix P(sizeMatr, dataP);
	RelationMatrix Q(sizeMatr, dataQ);
	RelationMatrix R(sizeMatr, dataR);
	puts("Matrix P :\n");
	cout << P << endl;
	puts("Matrix Q :\n");
	cout << Q << endl;
	puts("Matrix R :\n");
	cout << R << endl;
	puts("Additional task :\n");
	
	cout << "\nProperties of attitude Q :";
	Q.showProperties();
	cout << "\nThe type of relation Q :";
	Q.showType();
	cout << "\nProperties of attitude P :";
	P.showProperties();
	cout << "\nThe type of relation P :";
	P.showType();
	cout << "\nProperties of attitude R :";
	R.showProperties();
	cout << "\nThe type of relation R :";
	R.showType();
	
	{
	
		cout << "\nTransitive closure ratio P :\n";	
	
		RelationMatrix res(sizeMatr, FULLZERO);
	
		P.transitiveСlosure(res);
		cout << res;
	
		//////----------  ++++++++++++++++++++  -------------- 
		cout << "\nProperties of P ratio after transitive closure :";   // Властивості відношення P після транзитивного замикання
		res.showProperties();
		cout << "\nType of relation P after a transient closure :";  // Тип відношення P після транзитивного замикання
		res.showType();
		//////----------  ++++++++++++++++++++  -------------- 
	
	}
	
	{
		////----------  ++++++++++++++++++++  --------------
		cout << "\nSymmetric component of the relation P : \n";   // Симетрична складова відношення
		RelationMatrix res1(sizeMatr, FULLZERO);
		P.symmetricСomponent(res1);
		cout << res1;
	
		cout << "\nAsymmetric component of relation P : \n";   //Асиметрична складова відношення P
		RelationMatrix res2(sizeMatr, FULLZERO);
		P.asymmetricСomponent(res2);
		cout << res2;
		////----------  ++++++++++++++++++++  --------------
	}
	
	{
		//----------  ++++++++++++++++++++  --------------
		cout << "\nAttitude ratio for P :\n";   // Відношення досяжності для P: 
		RelationMatrix res3(sizeMatr, FULLZERO);
		P.reach(res3);
		cout << res3;
	
		cout << "\nMutual reach ratio for P :\n";   //Відношення взаємної досяжності для P :
		RelationMatrix res4(sizeMatr, FULLZERO);
		P.mutualReach(res4);
		cout << res4;
		////----------  ++++++++++++++++++++  --------------
	}
	
	{
	
		cout << "\nFactorization of the relation P on the ratio of mutual reach P:\n";  // Факторизація відношення P за відношенням взаємної досягальності : 
		RelationMatrix res4(sizeMatr, FULLZERO);
		P.factorization(P,res4);
		cout << res4;
	
	}
	 
	system("pause");

}



////////
////////RelationMatrix P(sizeMatr, dataP);
////////RelationMatrix Q(sizeMatr, dataQ);
////////RelationMatrix R(sizeMatr, dataR);
////////puts("Matrix P :\n");
////////cout << P << endl;
////////puts("Matrix Q :\n");
////////cout << Q << endl;
////////puts("Matrix R :\n");
////////cout << R << endl;
////////puts("Additional task :\n");
////////
////////cout << "\nProperties of attitude Q :";
////////Q.showProperties();
////////cout << "\nThe type of relation Q :";
////////Q.showType();
////////cout << "\nProperties of attitude P :";
////////P.showProperties();
////////cout << "\nThe type of relation P :";
////////P.showType();
////////cout << "\nProperties of attitude R :";
////////R.showProperties();
////////cout << "\nThe type of relation R :";
////////R.showType();
////////
////////{
////////
////////	cout << "\nTransitive closure ratio P :\n";
////////
////////
////////	RelationMatrix res(sizeMatr, FULLZERO);
////////
////////	P.transitiveСlosure(res);
////////	cout << res;
////////
////////	//////----------  ++++++++++++++++++++  -------------- 
////////	cout << "\nProperties of P ratio after transitive closure :";   // Властивості відношення P після транзитивного замикання
////////	res.showProperties();
////////	cout << "\nType of relation P after a transient closure :";  // Тип відношення P після транзитивного замикання
////////	res.showType();
////////	//////----------  ++++++++++++++++++++  -------------- 
////////
////////}
////////
////////{
////////	////----------  ++++++++++++++++++++  --------------
////////	cout << "\nSymmetric component of the relation P : \n";   // Симетрична складова відношення
////////	RelationMatrix res1(sizeMatr, FULLZERO);
////////	P.symmetricСomponent(res1);
////////	cout << res1;
////////
////////	cout << "\nAsymmetric component of relation P : \n";   //Асиметрична складова відношення P
////////	RelationMatrix res2(sizeMatr, FULLZERO);
////////	P.asymmetricСomponent(res2);
////////	cout << res2;
////////	////----------  ++++++++++++++++++++  --------------
////////}
////////
////////{
////////	//----------  ++++++++++++++++++++  --------------
////////	cout << "\nAttitude ratio for P :\n";   // Відношення досяжності для P: 
////////	RelationMatrix res3(sizeMatr, FULLZERO);
////////	P.reach(res3);
////////	cout << res3;
////////
////////	cout << "\nMutual reach ratio for P :\n";   //Відношення взаємної досяжності для P :
////////	RelationMatrix res4(sizeMatr, FULLZERO);
////////	P.mutualReach(res4);
////////	cout << res4;
////////	////----------  ++++++++++++++++++++  --------------
////////}
////////
////////{
////////
////////	////cout << "\nFactorization of the relation P on the ratio of mutual reach P:\n";  // Факторизація відношення P за відношенням взаємної досягальності : 
////////	////RelationMatrix res4(sizeMatr, FULLZERO);
////////	////R.mutualReach(res4);
////////	////cout << res4;
////////
////////}
