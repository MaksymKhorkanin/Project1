//////#include "RelationCut.h"
//////#include "RelationMatrix.h"
//////
//////
//////RelationCut::RelationCut(int8_t size, Type type)
//////{
//////	size_ = size;
//////	type_ = type;
//////
//////	switch (type)
//////	{
//////	default:
//////	case FULLZERO:
//////		break;
//////	case FULLUNIT:
//////		for (size_t i = 0; i < size_; i++)
//////		{
//////			for (size_t j = 0; j < size_; j++)
//////			{
//////				cut_.insert(std::pair<unsigned, unsigned>(i, j));
//////			}
//////		}
//////		break;
//////	case DIAGONAL:
//////		for (size_t i = 0; i < size_; i++)
//////		{
//////			cut_.insert(std::pair<int8_t, int8_t>(i, i));
//////		}
//////		break;
//////	}
//////}
//////
//////RelationCut::RelationCut(int8_t size, bool matrix[sizeMatr][sizeMatr])
//////{
//////	size_ = size;
//////	type_ = ELSE;
//////	for (size_t i = 0; i < size_; i++)
//////	{
//////		for (size_t j = 0; j < size_; j++)
//////		{
//////			if (matrix[j][i] == 1)
//////				cut_.insert(std::pair<unsigned, unsigned>(i, j));
//////		}
//////	}
//////}
//////
//////RelationCut::RelationCut(unsigned size, bool** matrix)
//////{
//////	size_ = size;
//////	type_ = ELSE;
//////	for (size_t i = 0; i < size_; i++)
//////	{
//////		for (size_t j = 0; j < size_; j++)
//////		{
//////			if (matrix[j][i] == 1) cut_.insert(std::pair<unsigned, unsigned>(i, j));
//////		}
//////	}
//////}
//////
//////RelationCut::RelationCut(Relation& a) :
//////	size_(a.getSize()), cut_(a.getCut()), type_(a.getType())
//////{
//////}
//////
//////RelationCut::~RelationCut()
//////{
//////}
//////
//////RelationCut& RelationCut::operator=(Relation& a)
//////{
//////	if (this != &a)
//////	{
//////		size_ = a.getSize();
//////		type_ = a.getType();
//////		cut_ = a.getCut();
//////	}
//////	return *this;
//////}
//////
//////void RelationCut::intersection(Relation& b, Relation& res_)
//////{
//////
//////	auto a = dynamic_cast<RelationCut&>(b);
//////	if (size_ == a.getSize()) {
//////		std::multimap<unsigned, unsigned>::iterator pos1;
//////		std::multimap<unsigned, unsigned>::iterator pos2;
//////		RelationCut result(size_, EMPTY);
//////		bool flag;
//////		for (size_t i = 0; i < size_; i++) {
//////			std::pair <std::multimap<unsigned, unsigned>::iterator, std::multimap<unsigned, unsigned>::iterator> ret;
//////			std::pair <std::multimap<unsigned, unsigned>::iterator, std::multimap<unsigned, unsigned>::iterator> ret1;
//////			ret = cut_.equal_range(i);
//////			ret1 = a.cut_.equal_range(i);
//////			for (std::multimap<unsigned, unsigned>::iterator it = ret.first; it != ret.second; it++) {
//////				for (std::multimap<unsigned, unsigned>::iterator jt = ret1.first; jt != ret1.second; jt++)
//////				{
//////					if (it->second == jt->second)
//////						result.getCut().insert(std::pair<unsigned, unsigned>(i, it->second));
//////					break;
//////				}
//////			}
//////		};
//////		res_ = result;
//////		return;
//////	}
//////	else {
//////		std::cerr << "ERROR  intersection !!! sizes not equal";
//////		RelationCut result(sizeMatr, EMPTY);
//////		res_ = result;
//////		return;
//////	}
//////
//////
//////
//////}
//////
//////void RelationCut::composition(Relation&  cut, Relation  &res) // композиц≥¤
//////{
//////	RelationMatrix a(this->getSize(), this->toMatrix());
//////	RelationMatrix b(cut.getSize(), cut.toMatrix());
//////	RelationMatrix c(cut.getSize(), EMPTY);
//////
//////	a.composition(b,c);
//////
//////	RelationCut result(c.getSize(), c.getMatrix());
//////	res = result;
//////	return;
//////}
//////
//////void RelationCut::association(Relation& cut, Relation& res)  // об'Їднанн¤
//////{
//////	RelationMatrix a(this->getSize(), this->toMatrix());
//////	RelationMatrix b(cut.getSize(), cut.toMatrix());
//////	RelationMatrix c(cut.getSize(), EMPTY);
//////
//////	a.association(b,c);
//////
//////	RelationCut result(c.getSize(), c.getMatrix());
//////	res = result;
//////	return;
//////}
//////
//////void RelationCut::difference(Relation& cut, Relation& res) // р≥зниц¤
//////{
//////	RelationMatrix a(this->getSize(), this->toMatrix());
//////	RelationMatrix b(cut.getSize(), cut.toMatrix());
//////	RelationMatrix c(cut.getSize(), EMPTY);
//////
//////	a.difference(b,c);
//////
//////	RelationCut result(c.getSize(), c.getMatrix());
//////	res=result;
//////	return;
//////}
//////
//////void RelationCut::symmetricDiference(Relation& cut, Relation& res)  // обернене в≥дношенн¤
//////{
//////	RelationMatrix a(this->getSize(), this->toMatrix());
//////	RelationMatrix b(cut.getSize(), cut.toMatrix());
//////	RelationMatrix c(cut.getSize(), EMPTY);
//////
//////	a.symmetricDiference(b,c);
//////
//////	RelationCut result(c.getSize(), c.getMatrix());
//////	res = result;
//////	return ;
//////}
//////
//////void RelationCut::addition(Relation &res)   // доповненн¤
//////{
//////	RelationMatrix a(this->getSize(), this->toMatrix());
//////	RelationMatrix resMatr(this->getSize(), EMPTY);
//////	
//////	a.addition(resMatr);
//////
//////RelationCut result(resMatr.getSize(), resMatr.getMatrix());
//////	res = result;
//////	return;
//////}
//////
//////void RelationCut::inverse(Relation &res)  // ≥нвертуванн¤
//////{
//////	RelationMatrix a(this->getSize(), this->toMatrix());
//////
//////	RelationMatrix resMatr(this->getSize(), EMPTY);
//////
//////	a.inverse(resMatr);
//////
//////	RelationCut result(resMatr.getSize(), resMatr.getMatrix());
//////
//////	res = result;
//////	return;
//////}
//////
//////bool RelationCut::affiliation(Relation& cut)  // належн≥сть
//////{
//////	RelationMatrix a(this->getSize(), this->toMatrix());
//////	RelationMatrix b(cut.getSize(), cut.toMatrix());
//////
//////	return a.affiliation(b);
//////}
//////
//////void RelationCut::restriction(unsigned size, int* index, Relation& res)  // звуженн¤
//////{
////////	RelationMatrix a(this->size_, this->toMatrix());
//////	RelationMatrix result(size, EMPTY);
//////	a.restriction(size, index, result);
//////	RelationCut result1(size, result.getMatrix());
//////	res = result1;
//////}
//////
//////std::ostream& operator<< (std::ostream& os, RelationCut& a)
//////{
//////	std::multimap<unsigned, unsigned>::iterator pos;
//////	for (size_t i = 0; i < a.getSize(); i++) {
//////		os << "R+(" << i + 1 << ") : { ";
//////		for (pos = a.cut_.lower_bound(i); pos != a.cut_.upper_bound(i); pos++) {
//////			os << pos->second + 1 << ", ";
//////		}
//////		os << "};" << std::endl;
//////	}
//////	return os;
//////}
//////
//////unsigned RelationCut::getSize()
//////{
//////	return size_;
//////}
//////
//////Type RelationCut::getType()
//////{
//////	return type_;
//////}
//////
//////void RelationCut::setElement(int i, int j, int num) {
//////
//////};
//////
//////bool RelationCut::getElement(int i, int j) {
//////
//////return true;
//////};
//////
//////std::multimap<unsigned, unsigned> &RelationCut::getCut()
//////{
//////	return cut_;
//////}
//////
//////bool** RelationCut::toMatrix()
//////{
//////	bool** matrix;
//////	matrix = new bool*[size_];
//////	for (size_t i = 0; i < size_; i++)
//////	{
//////		matrix[i] = new bool[size_];
//////		for (size_t j = 0; j < size_; j++)
//////		{
//////			matrix[i][j] = 0;
//////		}
//////	}
//////
//////	for (size_t i = 0; i < size_; i++) {
//////		std::pair <std::multimap<unsigned, unsigned>::iterator, std::multimap<unsigned, unsigned>::iterator> ret;
//////		ret = cut_.equal_range(i);
//////		for (std::multimap<unsigned, unsigned>::iterator it = ret.first; it != ret.second; it++)
//////			matrix[it->second][i] = 1;
//////	}
//////	return matrix;
//////}

#include "RelationCut.h"
#include "RelationMatrix.h"

RelationCut::RelationCut(int8_t size, Type type)
{

	switch (type)
	{
	default:
	case FULLZERO:
		break;
	case FULLUNIT:
		for (size_t i = 0; i < size_; i++)
		{
			for (size_t j = 0; j < size_; j++)
			{
				cut_.insert(std::pair<int8_t, int8_t>(i, j));
			}
		}
		break;
	case DIAGONAL:
		for (size_t i = 0; i < size_; i++)
		{
			cut_.insert(std::pair<int8_t, int8_t>(i, i));
		}
		break;
	}

	size_ = size;
	type_ = type;
}

RelationCut::RelationCut(int8_t size, bool matrix[sizeMatr][sizeMatr])
{
	size_ = size;
	type_ = RANDOM;
	for (size_t i = 0; i < size_; i++)
	{
		for (size_t j = 0; j < size_; j++)
		{
			if (matrix[j][i] == 1)
				cut_.insert(std::pair<int8_t, int8_t>(i, j));
		}
	}
}

RelationCut::RelationCut(int8_t size, bool** matrix)
{
	size_ = size;
	type_ = RANDOM;
	for (size_t i = 0; i < size_; i++)
	{
		for (size_t j = 0; j < size_; j++)
		{
			if (matrix[j][i] == 1) cut_.insert(std::pair<int8_t, int8_t>(i, j));
		}
	}
}

RelationCut::RelationCut(Relation& a)
{
	size_ = a.getSize();
	cut_ = a.getCut();
	type_ = a.getType();

}

RelationCut::~RelationCut()
{
}

RelationCut& RelationCut::operator=(Relation& a)
{
	if (this == &a)
	{
		return *this;
	}
	else {
		size_ = a.getSize();
		type_ = a.getType();
		cut_ = a.getCut();
	}
	return *this;
}

void RelationCut::intersection(Relation& b, Relation& res_)
{
	RelationCut result(size_, FULLZERO);
	auto a = dynamic_cast<RelationCut&>(b);

	if (size_ == a.getSize()) {
		itrat pos1, pos2;

		for (size_t i = 0; i < size_; i++) {
			std::pair <itrat, itrat> ret, ret1;
			ret = cut_.equal_range(i);
			ret1 = a.cut_.equal_range(i);
			for (itrat it = ret.first; it != ret.second; it++) {
				for (itrat jt = ret1.first; jt != ret1.second; jt++)
				{
					if (it->second == jt->second)
						result.getCut().insert(std::pair<int8_t, int8_t>(i, it->second));
					break;
				}
			}
		};
		res_ = result;
		return;
	}
	else {
		res_ = result;
		return;
	}



}

void RelationCut::composition(Relation&  cut, Relation  &res) // композиція
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	RelationMatrix b(cut.getSize(), cut.createMatrix());
	RelationMatrix c(cut.getSize(), FULLZERO);
	a.composition(b, c);

	RelationCut result(c.getSize(), c.getMatrix());
	res = result;
}

void RelationCut::association(Relation& cut, Relation& res)  // об'єднання
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	RelationMatrix b(cut.getSize(), cut.createMatrix());
	RelationMatrix c(cut.getSize(), FULLZERO);

	a.association(b, c);

	RelationCut result(c.getSize(), c.getMatrix());
	res = result;
}

void RelationCut::difference(Relation& cut, Relation& res) // різниця
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	RelationMatrix b(cut.getSize(), cut.createMatrix());
	RelationMatrix c(cut.getSize(), FULLZERO);

	a.difference(b, c);

	RelationCut result(c.getSize(), c.getMatrix());
	res = result;
}

void RelationCut::symmetricDiference(Relation& cut, Relation& res)  // обернене відношення
{

	RelationMatrix a(this->getSize(), this->createMatrix());
	RelationMatrix b(cut.getSize(), cut.createMatrix());
	RelationMatrix c(cut.getSize(), FULLZERO);

	a.symmetricDiference(b, c);

	RelationCut result(c.getSize(), c.getMatrix());
	res = result;
}

void RelationCut::addition(Relation &res)   // доповнення
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	RelationMatrix resMatr(this->getSize(), FULLZERO);

	a.addition(resMatr);

	RelationCut result(resMatr.getSize(), resMatr.getMatrix());
	res = result;
}

void RelationCut::inverse(Relation &res)  // інвертування
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	RelationMatrix resMatr(this->getSize(), FULLZERO);

	a.inverse(resMatr);

	RelationCut result(resMatr.getSize(), resMatr.getMatrix());
	res = result;
}

bool RelationCut::affiliation(Relation& cut)  // належність
{

	RelationMatrix a(this->getSize(), this->createMatrix());
	RelationMatrix b(cut.getSize(), cut.createMatrix());

	return a.affiliation(b);
}

void RelationCut::restriction(int8_t size, int* index, Relation& res)  // звуження
{
	RelationMatrix a(this->size_, this->createMatrix());
	RelationMatrix result(size, FULLZERO);
	a.restriction(size, index, result);
	RelationCut result1(size, result.getMatrix());
	res = result1;
}

std::ostream& operator<< (std::ostream& cou, RelationCut& a)
{
	std::multimap<int8_t, int8_t>::iterator pos;

	for (size_t i = 0; i < a.getSize(); i++) {
		cou << "R+(" << i + 1 << ") : { ";
		for (pos = a.cut_.lower_bound(i); pos != a.cut_.upper_bound(i); pos++) {
			cou << pos->second + 1 << ", ";
		}
		cou << "};" << std::endl;
	}
	return cou;
}

int8_t RelationCut::getSize()
{
	return size_;
}

Type RelationCut::getType()
{
	return type_;
}

bool RelationCut::getElement(int i, int j) {

	return true;
};

std::multimap<int8_t, int8_t> &RelationCut::getCut()
{
	return cut_;
}

bool** RelationCut::createMatrix()
{
	bool** matrix;
	matrix = new bool*[size_];
	for (size_t i = 0; i < size_; i++)
	{
		matrix[i] = new bool[size_];
		for (size_t j = 0; j < size_; j++)
		{
			matrix[i][j] = 0;
		}
	}

	for (size_t i = 0; i < size_; i++) {
		std::pair <itrat, itrat> ret;
		ret = cut_.equal_range(i);
		for (itrat it = ret.first; it != ret.second; it++)
			matrix[it->second][i] = 1;
	}
	return matrix;
}

bool RelationCut::refleksuvnist()  // рефлексивність
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.refleksuvnist();
}

bool RelationCut::anturefleksuvnist()  //антирефлексивність
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.anturefleksuvnist();
}

bool RelationCut::sumetruchnist()  // симетричність
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.sumetruchnist();
}

bool RelationCut::asumetruchnist() // асиметричність
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.asumetruchnist();
}

bool RelationCut::antusemetruchnist()  // антисиметричне відношення
{

	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.antusemetruchnist();
}

bool RelationCut::tranzutuvnist() // транзитивність
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.tranzutuvnist();
}

bool RelationCut::acyclicism()  // ациклічність
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.acyclicism();
}

bool RelationCut::connectivity()  // звязність
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.connectivity();
}

bool RelationCut::tolerance()//толерантності
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.tolerance();
}

bool RelationCut::equivalence() // Еквівалентністю 
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.equivalence();
}

bool RelationCut::quasiorder() // квазіпорядк
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.quasiorder();
}

bool RelationCut::strictOrder() // Строгиий порядок 
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.strictOrder();
}

bool RelationCut::order() // Порядком 
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.order();
}

bool RelationCut::linearOrder() // Лінійним порядком 
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.linearOrder();
}

bool RelationCut::strictLinearOrder() // строгий лінійним порядком 
{
	RelationMatrix a(this->getSize(), this->createMatrix());
	return a.strictLinearOrder();
}

bool RelationCut::inclusion(Relation & a)  // включеність
{
	RelationMatrix b(this->getSize(), this->createMatrix());
	return b.inclusion(a);
}

void RelationCut::showProperties()   // показати все
{
	std::cout << "\nRefleksuvnist       " << BoolToString(this->refleksuvnist()) << std::endl;
	std::cout << "Anturefleksuvnist   " << BoolToString(this->anturefleksuvnist()) << std::endl;
	std::cout << "Sumetruchnist       " << BoolToString(this->sumetruchnist()) << std::endl;
	std::cout << "Asumetruchnist      " << BoolToString(this->asumetruchnist()) << std::endl;
	std::cout << "Antusemetruchnist   " << BoolToString(this->antusemetruchnist()) << std::endl;
	std::cout << "Tranzutuvnist       " << BoolToString(this->tranzutuvnist()) << std::endl;
	std::cout << "Acyclicist          " << BoolToString(this->acyclicism()) << std::endl;
	std::cout << "Connectivity        " << BoolToString(this->connectivity()) << std::endl;
}

void RelationCut::showType()   // показати все
{
	std::cout << "\nTolerance           " << BoolToString(this->tolerance()) << std::endl;
	std::cout << "Equivalence         " << BoolToString(this->quasiorder()) << std::endl;
	std::cout << "Strict Order        " << BoolToString(this->strictOrder()) << std::endl;
	std::cout << "Order               " << BoolToString(this->order()) << std::endl;
	std::cout << "Linear Order        " << BoolToString(this->linearOrder()) << std::endl;
	std::cout << "Strict Linear Order " << BoolToString(this->strictLinearOrder()) << std::endl;

}

void RelationCut::symmetricСomponent(Relation &res_) // симетрична складова
{
	RelationMatrix res(size_, FULLZERO);
	RelationMatrix b(this->getSize(), this->createMatrix());
	b.symmetricСomponent(res);
	RelationCut result(res.getSize(), res.getMatrix());

	res_ = result;
}

void RelationCut::asymmetricСomponent(Relation &res_) // aсиметрична складова
{
	RelationMatrix res(size_, FULLZERO);
	RelationMatrix b(this->getSize(), this->createMatrix());
	b.asymmetricСomponent(res);
	RelationCut result(res.getSize(), res.getMatrix());

	res_ = result;
}

void RelationCut::transitiveСlosure(Relation &res_)  //транзитивне замикання
{
	RelationMatrix res(size_, FULLZERO);


	RelationMatrix b(this->getSize(), this->createMatrix());
	b.transitiveСlosure(res);
	RelationCut result(res.getSize(), res.getMatrix());

	res_ = result;
}

void  RelationCut::reach(Relation &res_)  // досяжність
{
	RelationMatrix res(size_, FULLZERO);	
	RelationMatrix b(this->getSize(), this->createMatrix());
	b.reach(res);
	RelationCut result(res.getSize(), res.getMatrix());

	res_ = result;
}

void RelationCut::mutualReach(Relation &res_)  //  взаємна досяжність
{
	RelationMatrix res(size_, FULLZERO);
	RelationMatrix b(this->getSize(), this->createMatrix());
	b.mutualReach(res);
	RelationCut result(res.getSize(), res.getMatrix());

	res_ = result;
}

void RelationCut::inverseRelationship(Relation & res_)
{

	RelationMatrix res(size_, FULLZERO);
	RelationMatrix b(this->getSize(), this->createMatrix());
	b.inverseRelationship(res);
	RelationCut result(res.getSize(), res.getMatrix());

	res_ = result;
}

void RelationCut::getVector(int i, std::vector<bool>& res) //витягнути вектор значень за ключем
{

	auto range = cut_.equal_range(i);

	for (auto j = range.first; j != range.second; ++j)
	{
		res.emplace_back(j->second);
	}

}

void RelationCut::factorization(Relation &a, Relation &res_)  //  факторизація
{

	//////RelationCut res(size_, FULLZERO);
	//////this->mutualReach(res);

	//////std::cout << res;
	//////int clas = 0;

	//////std::vector<bool> temp;
	//////std::vector<bool> temp1;	

	//////for (int i = 0; i < size_; i++)
	//////{
	//////	res.getVector(i, temp);
	//////	clas++;
	//////	for (int j = i + 1; j < size_; j++)
	//////	{
	//////		res.getVector(j, temp1);
	//////		if (temp == temp1) {
	//////			i++;
	//////			break;
	//////		}
	//////		temp1.clear();
	//////	}
	//////	temp.clear();
	//////}


	//////std::cout << "   ==   " << clas << std::endl;
	//////std::cout << "\n" << res << std::endl;
	//////res_ = res;


}
