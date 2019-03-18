#pragma once

#include "Relation.h"
#include <vector>

class RelationCut : public Relation
{
public:

	typedef std::multimap<int8_t, int8_t>::iterator itrat;

	RelationCut(int8_t size = 0, Type type = Type::FULLZERO);  // конструктор

	RelationCut(int8_t size, bool matrix[sizeMatr][sizeMatr]);  // конструктор

	RelationCut(int8_t size, bool** matrix); // конструктор

	RelationCut(Relation& a); // конструктор копіювання

	~RelationCut();  // деструктор

	RelationCut& operator=(Relation& a); //   визначення операції присвоєннядеструктор

	friend std::ostream& operator<< (std::ostream& os, RelationCut& a);

	void intersection(Relation& a, Relation& res); //перетин

	void association(Relation& a, Relation& res);  // об'єднання

	void difference(Relation& a, Relation& res); // різниця

	void symmetricDiference(Relation& a, Relation& res);  // обернене відношення

	void addition(Relation& a); // доповнення

	void inverse(Relation& res);  // інвертування

	void composition(Relation& a, Relation& res);  // композиція

	bool affiliation(Relation& a);  // належність

	void restriction(int8_t size, int* index, Relation& res); // звуження

	void inverseRelationship(Relation& a); //  Оберненим до відношення 

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

	void showType();   // показати все

	void symmetricСomponent(Relation &res); // симетрична складова

	void asymmetricСomponent(Relation &res_); // aсиметрична складова

	void transitiveСlosure(Relation &res_);  //транзитивне замикання

	void  reach(Relation &res_);  // досягальності

	void mutualReach(Relation &res_);  //  взаємна досяжність

	void getVector(int i, std::vector<bool>& res); //витягнути вектор значень за ключем

	void factorization(Relation &a, Relation &res_);  //  факторизація

	bool getElement(int, int);

	int8_t getSize();

	void setElement(int, int, int) {};

	Type getType();

	std::multimap<int8_t, int8_t> &getCut();

	bool** createMatrix();

private:
	std::multimap<int8_t, int8_t> cut_;
	int8_t size_;
	Type type_;

};

