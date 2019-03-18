#pragma once

#include "iostream"
#include "stdio.h"
#include <map> 
#include <iterator>

#define  sizeMatr 5

enum Type
{
	FULLZERO,
	FULLUNIT,
	DIAGONAL,
	RANDOM
};

class Relation
{
public:

	virtual Relation& operator=(Relation& a) { return *this; };

	virtual ~Relation() {};  // віртуальний деструктор

	virtual void intersection(Relation& a, Relation& res) = 0;//перетин

	virtual void association(Relation& a, Relation& res) = 0;  // об'єднання

	virtual void difference(Relation& a, Relation& res) {}; // різниця

	virtual void symmetricDiference(Relation& a, Relation& res) {}; // обернене відношення

	virtual void addition(Relation &a) {};   // доповнення

	virtual void inverse(Relation &a) {};  // інвертування

	virtual void composition(Relation& a, Relation& res) {}; // композиція

	virtual void restriction(int8_t size, int* index, Relation& res) {};  // звуження

	virtual int8_t getSize() { return 0; };

	virtual void setElement(int, int, int) {};

	virtual bool getElement(int, int) { return true; };

	virtual Type getType() { return Type::RANDOM; };

	std::multimap<int8_t, int8_t> virtual &getCut() {

		std::multimap<int8_t, int8_t> m;

		return m;
	};

	virtual bool**  createMatrix() { bool **p = nullptr; return (p); }

	virtual void inverseRelationship(Relation& a) = 0; //  Оберненим до відношення 

	virtual bool affiliation(Relation& a) = 0;  // належність

	virtual bool refleksuvnist() = 0;  //рефлексивність

	virtual bool anturefleksuvnist() = 0;  //антирефлексивність

	virtual bool sumetruchnist() = 0;  // симетричність

	virtual bool asumetruchnist() = 0; // асиметричність

	virtual bool antusemetruchnist() = 0; // антисиметричне відношення

	virtual bool tranzutuvnist() = 0; // транзитивність

	virtual bool quasiorder() = 0; // квазіпорядк

	virtual bool strictOrder() = 0; // Строгиий порядок 

	virtual bool order() = 0; // Порядком 

	virtual bool linearOrder() = 0; // Лінійним порядком 

	virtual bool strictLinearOrder() = 0; // строгий лінійним порядком 

	virtual bool inclusion(Relation & a) = 0;  // включеність

	virtual bool acyclicism() = 0;  // ациклічність

	virtual bool connectivity() = 0;  // звязність

	virtual bool tolerance() = 0;   //толерантності

	virtual bool equivalence() = 0; // Еквівалентністю 

	virtual void showProperties() = 0;   // показати все

	virtual void symmetricСomponent(Relation &res) = 0; // симетрична складова

	virtual void asymmetricСomponent(Relation &res_) = 0; // aсиметрична складова

	virtual void transitiveСlosure(Relation &res_) = 0;  //транзитивне замикання

	virtual void  reach(Relation &res_) = 0;  // досягальності

	virtual void mutualReach(Relation &res_) = 0;  //  взаємна досяжність

};

inline const char * const BoolToString(bool b)
{
	return b ? "true" : "false";
}
