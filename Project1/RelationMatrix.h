#pragma once

#include "Relation.h"
#include <vector>

class RelationMatrix : public Relation
{
public:
	RelationMatrix(int8_t size = 0, Type type = Type::FULLZERO);  // конструктор

	RelationMatrix(Relation& copy);  // конструктор копіювання

	RelationMatrix(int8_t size, bool matrix[sizeMatr][sizeMatr]); // конструктор

	RelationMatrix(int8_t size, bool** matrix);  // конструктор

	RelationMatrix& operator = (Relation& b);  //  визначення операції присвоєння

	friend  bool operator==(Relation & left, Relation & right);  // перевантажений оператор порівняння

	~RelationMatrix();  // деструктор

	void intersection(Relation& a, Relation& res); //перетин

	void association(Relation& a, Relation& res); // об'єднання

	void difference(Relation& a, Relation& res);  // різниця

	void symmetricDiference(Relation& a, Relation& res);   // обернене відношення

	void addition(Relation& res);  // доповнення

	void inverse(Relation& a);   // інвертування

	void composition(Relation& a, Relation& res);  // композиція

	bool affiliation(Relation& a);  // належність

	bool refleksuvnist();  //рефлексивність

	bool anturefleksuvnist();  //антирефлексивність

	bool sumetruchnist();  // симетричність

	bool asumetruchnist(); // асиметричність

	bool antusemetruchnist(); // антисиметричне відношення

	bool tranzutuvnist(); // транзитивність

	bool quasiorder(); // квазіпорядк

	bool strictOrder(); // Строгиий порядок 

	bool order(); // Порядком 

	bool linearOrder(); // Лінійним порядком 

	bool strictLinearOrder(); // строгий лінійним порядком 

	bool inclusion(Relation & a);  // включеність

	bool acyclicism();  // ациклічність

	bool connectivity();  // звязність

	bool tolerance();   //толерантності

	bool equivalence(); // Еквівалентністю 

	void showProperties();   // показати все

	void inverseRelationship(Relation& a); //  Оберненим до відношення 

	void symmetricСomponent(Relation &res); // симетрична складова

	void asymmetricСomponent(Relation &res_); // aсиметрична складова

	void transitiveСlosure(Relation &res_);  //транзитивне замикання

	void  reach(Relation &res_);  // досягальності

	void mutualReach(Relation &res_);  //  взаємна досяжність

	void factorization(Relation &a, Relation &res_);  //  факторизація

	void restriction(int8_t size, int* index, Relation& a);  // звуження

	void showType();  // показати все

	int8_t getSize();

	void setElement(int, int, int);

	bool getElement(int, int);

	void getVector(int i, std::vector<bool>& res); //витягнути вектор із матриці

	Type getType();

	bool** getMatrix();

	friend std::ostream& operator<< (std::ostream& os, RelationMatrix& a);

private:
	Type type_;
	bool** matrix_;
	int8_t size_;
};

