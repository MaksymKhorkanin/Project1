
#include "RelationMatrix.h"
#include "RelationCut.h"

RelationMatrix::RelationMatrix(int8_t size, Type type)
{
	size_ = size;
	type_ = type;

	matrix_ = new bool*[size_];
	for (size_t i = 0; i < size_; i++) {
		matrix_[i] = new bool[size_];
	}

	switch (type_)
	{
	case FULLZERO:
	{
		for (size_t i = 0; i < size_; i++)
			for (size_t j = 0; j < size_; j++)
				matrix_[i][j] = 0;
		break;
	}
	case FULLUNIT:
	{
		for (size_t i = 0; i < size_; i++)
			for (size_t j = 0; j < size_; j++)
				matrix_[i][j] = 1;
		break;
	}
	case DIAGONAL:
	{
		for (size_t i = 0; i < size_; i++)
			for (size_t j = 0; j < size_; j++)
				if ((i == j)) {
					matrix_[i][j] = 1;
				}
				else
				{
					matrix_[i][j] = 0;
				}
		break;
	}
	case RANDOM:
	{
		for (size_t i = 0; i < size_; i++)
			for (size_t j = 0; j < size_; j++)
			{
				matrix_[i][j] = rand() % 2;
			}
		break;
	}
	}
}

RelationMatrix::RelationMatrix(Relation& copy)
{
	if (this == &copy)
	{
		return;
	}
	size_ = copy.getSize();
	type_ = copy.getType();
	matrix_ = new bool*[size_];
	for (size_t i = 0; i < size_; i++)
		matrix_[i] = new bool[size_];

	for (size_t i = 0; i < size_; i++)
		for (size_t j = 0; j < size_; j++)
			matrix_[i][j] = copy.getElement(i, j);

}

RelationMatrix::RelationMatrix(int8_t size, bool matrix[sizeMatr][sizeMatr])
{
	size_ = size;
	type_ = RANDOM;

	matrix_ = new bool*[size_];
	for (size_t i = 0; i < size_; i++)
		matrix_[i] = new bool[size_];

	for (size_t i = 0; i < size_; i++) {
		for (size_t j = 0; j < size_; j++)
		{
			matrix_[i][j] = matrix[i][j];
		}
	}
}

RelationMatrix::RelationMatrix(int8_t size, bool** matrix)
{
	size_ = size;
	type_ = RANDOM;

	matrix_ = new bool*[size_];
	for (size_t i = 0; i < size_; i++)
		matrix_[i] = new bool[size_];

	for (size_t i = 0; i < size_; i++) {
		for (size_t j = 0; j < size_; j++)
		{
			matrix_[i][j] = matrix[i][j];
		}
	}
}

RelationMatrix& RelationMatrix::operator = (Relation& b)
{
	if (this == &b)
	{
		return *this;
	}
	size_ = b.getSize();
	type_ = b.getType();
	matrix_ = new bool*[size_];
	for (size_t i = 0; i < size_; i++)
		matrix_[i] = new bool[size_];

	for (size_t i = 0; i < size_; i++)
		for (size_t j = 0; j < size_; j++)
			matrix_[i][j] = b.getElement(i, j);
	return *this;
}

void RelationMatrix::setElement(int i, int j, int num) {
	matrix_[i][j] = static_cast<bool>(num);
};

bool RelationMatrix::getElement(int i, int j) {

	return matrix_[i][j];
};

RelationMatrix::~RelationMatrix()
{
	//for (size_t i = 0; i < size_; i++)
	//	delete matrix_[i];
	//delete matrix_;
}

void RelationMatrix::intersection(Relation& a, Relation& res)
{
	RelationMatrix result(size_, FULLZERO);

	if (size_ == a.getSize()) {
		for (size_t i = 0; i < size_; i++) {
			for (size_t j = 0; j < size_; j++) {
				if (matrix_[i][j] == 1 && a.getElement(i, j) == 1) {
					result.matrix_[i][j] = 1;
				}
			}
		}
		res = result;
		return;
	}
	else {
		res = result;
		return;
	}
}

void RelationMatrix::association(Relation& a, Relation& res)  // об'єднання
{
	RelationMatrix result(size_, FULLZERO);

	if (size_ == a.getSize()) {
		for (size_t i = 0; i < size_; i++) {
			for (size_t j = 0; j < size_; j++) {
				if (matrix_[i][j] == 1 || a.getElement(i, j) == 1) {
					result.matrix_[i][j] = 1;
				}
			}
		}
		res = result;
		return;
	}
	else {
		res = result;
		return;
	}
}// об'єднання

void RelationMatrix::difference(Relation& a, Relation& res) // різниця
{
	RelationMatrix result(size_, FULLZERO);

	if (size_ == a.getSize()) {
		for (size_t i = 0; i < size_; i++) {
			for (size_t j = 0; j < size_; j++) {
				if (matrix_[i][j] == 1 && a.getElement(i, j) == 0) {
					result.matrix_[i][j] = 1;
				}
			}
		}
		res = result;
		return;
	}
	else {
		res = result;
		return;
	}
}

void RelationMatrix::symmetricDiference(Relation& a, Relation& res)   // обернене відношення
{
	RelationMatrix result(size_, FULLZERO);

	if (size_ == a.getSize()) {

		RelationMatrix temp(size_, FULLZERO);
		RelationMatrix temp1(size_, FULLZERO);

		this->association(a, temp);
		this->intersection(a, temp1);
		temp.difference(temp1, res);
	}
	else {
		res = result;
	}
}

void RelationMatrix::addition(Relation &res)  // доповнення
{
	RelationMatrix result(size_, FULLZERO);
	for (size_t i = 0; i < size_; i++)
	{
		for (size_t j = 0; j < size_; j++)
		{
			if (matrix_[i][j] == 1) {
				result.matrix_[i][j] = 0;
			}
			else {
				result.matrix_[i][j] = 1;
			}
		}
	}
	res = result;
	return;
}

void RelationMatrix::inverse(Relation& res) // інвертування
{
	RelationMatrix result(size_, FULLZERO);
	for (size_t i = 0; i < size_; i++)
	{
		for (size_t j = 0; j < size_; j++)
		{
			result.matrix_[i][j] = matrix_[j][i];
		}
	}
	res = result;
}

void RelationMatrix::composition(Relation&  a, Relation &res) // композиція
{
	RelationMatrix result(size_, FULLZERO);

	if (size_ == a.getSize()) {
		int l = 0;
		for (size_t i = 0; i < size_; i++) {
			for (size_t j = 0; j < size_; j++) {
				l = 0;
				for (size_t k = 0; k < size_; k++) {
					l += this->matrix_[i][k] * a.getElement(k, j);
				}
				result.matrix_[i][j] = (l >= 1) ? 1 : 0;
			}
		}
		res = result;
		return;
	}
	else {
		res = result;
		return;
	}
}

bool RelationMatrix::affiliation(Relation& a) // належність
{
	for (size_t i = 0; i < size_; i++) {
		for (size_t j = 0; j < size_; j++) {
			if (matrix_[i][j] == 1 && a.getElement(i, j) == 1) {
				continue;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

void RelationMatrix::restriction(int8_t size, int* index, Relation& res) // звуження
{
	RelationMatrix result(size, FULLZERO);
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			result.matrix_[i][j] = this->matrix_[index[i]][index[j]];
		}
	}
	res = result;
}

int8_t RelationMatrix::getSize()
{
	return size_;
}

Type RelationMatrix::getType()
{
	return type_;
}

bool** RelationMatrix::getMatrix()
{
	return matrix_;
}

std::ostream& operator<< (std::ostream& cou, RelationMatrix& a)
{
	for (size_t i = 0; i < a.size_; i++)
	{
		for (size_t j = 0; j < a.size_; j++)
		{
			cou << a.matrix_[i][j] << " ";
		}
		cou << std::endl;
	}
	return cou;
}

bool RelationMatrix::refleksuvnist()  // рефлексивність
{
	for (int i = 0; i < size_; i++)
	{
		if (matrix_[i][i] != 1) return false;
	}
	return true;
}

bool RelationMatrix::anturefleksuvnist()  //антирефлексивність
{
	for (int i = 0; i < size_; i++)
	{
		if (matrix_[i][i] != 0) return false;
	}
	return true;
}

bool RelationMatrix::sumetruchnist()  // симетричність
{
	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			if (matrix_[i][j] != matrix_[j][i]) return false;
		}
	}
	return true;
}

 bool operator==(Relation & left, Relation & right)  // перевантажений оператор порівняння
{
	if (left.getSize() != right.getSize()) {
		return false;
	}
	else {
		for (int i = 0; i < right.getSize(); i++)
		{
			for (int j = 0; j < right.getSize(); j++)
			{
				if (left.getElement(i, j) != right.getElement(j, i)) {
					return false;
				}
			}
		}
	}
}

bool RelationMatrix::asumetruchnist() // асиметричність

{
	RelationMatrix temp1(size_, FULLZERO);
	RelationMatrix temp2(size_, FULLZERO);
	RelationMatrix temp3(size_, FULLZERO);

	this->inverseRelationship(temp1);

	this->intersection(temp1, temp2);

	if (temp2 == temp3) {
		return  true;
	}
	else {
		return false;
	}
}

bool RelationMatrix::antusemetruchnist()  // антисиметричне відношення
{
	RelationMatrix temp1(size_, FULLZERO);
	RelationMatrix temp2(size_, FULLZERO);

	this->inverseRelationship(temp1);

	this->intersection(temp1, temp2);

	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			if (i != j) {
				if ((temp2.matrix_[i][j] == temp2.matrix_[j][i]) && (temp2.matrix_[j][i] == 1))
					return false;
			}
		}
	}
	return  true;

}

bool RelationMatrix::inclusion(Relation & a)  // включеність
{
	bool answer;
	for (int i = 0; i < size_; i++)
		for (int j = 0; j < size_; j++)
			if ((matrix_[i][j] == 1) && (matrix_[i][j] == a.getElement(i, j))) {
				answer = true;
			}
			else
			{
				if ((matrix_[i][j] != 0)) {
					return false;
				}
			}
	return true;
}

bool RelationMatrix::tranzutuvnist() // транзитивність
{
	RelationMatrix temp1(size_, FULLZERO);

	this->composition(*this, temp1);
	if (temp1.inclusion(*this))return true;

	return false;
}

bool RelationMatrix::acyclicism()  // ациклічність
{
	RelationMatrix temp1(size_, FULLZERO);
	RelationMatrix temp2(size_, FULLZERO);
	RelationMatrix temp3(size_, DIAGONAL);
	RelationMatrix res(size_, FULLZERO);

	RelationMatrix *m2 = new RelationMatrix[size_];

	this->composition(*this, temp2);
	m2[0] = temp2;

	for (int i = 0; i < size_ - 1; i++) {
		this->composition(m2[i], temp2);
		m2[i + 1] = temp2;
	}
	this->association(m2[0], temp1);
	for (int i = 1; i < size_ - 2; i++) {
		temp1.association(m2[i], res);
		temp1 = res;
	}
	temp3.association(res, temp1);

	return 	temp1.antusemetruchnist();
}

bool RelationMatrix::connectivity()  // звязність
{
	RelationMatrix temp1(size_, FULLZERO);
	RelationMatrix diag(size_, DIAGONAL);

	RelationMatrix temp2(size_, FULLZERO);
	RelationMatrix res1(size_, FULLZERO);
	RelationMatrix res2(size_, FULLZERO);
	this->inverseRelationship(temp2);
	this->association(temp2, res1);

	res1.difference(diag, res2);
	temp1.difference(diag, res1);

	if (res2 == res1) {
		return true;
	}
	else {
		return false;
	}

}

bool RelationMatrix::tolerance()//толерантності
{
	if (this->refleksuvnist() && (this->sumetruchnist())) {
		return true;
	}
	else {
		return false;
	}

}

bool RelationMatrix::equivalence() // Еквівалентністю 
{
	if (this->refleksuvnist() && (this->sumetruchnist()) && (this->tranzutuvnist())) {
		return true;
	}
	else {
		return false;
	}

}

bool RelationMatrix::quasiorder() // квазіпорядк
{
	if (this->refleksuvnist() && (this->tranzutuvnist())) {
		return true;
	}
	else {
		return false;
	}
}

bool RelationMatrix::strictOrder() // Строгиий порядок 
{
	if (this->asumetruchnist() && (this->tranzutuvnist())) {
		return true;
	}
	else {
		return false;
	}
}

bool RelationMatrix::order() // Порядком 
{
	if (this->refleksuvnist() && (this->antusemetruchnist()) && (this->tranzutuvnist())) {
		return true;
	}
	else {
		return false;
	}
}

bool RelationMatrix::linearOrder() // Лінійним порядком 
{
	if (this->refleksuvnist() && (this->antusemetruchnist()) && (this->tranzutuvnist()) && (this->connectivity())) {
		return true;
	}
	else {
		return false;
	}
}

bool RelationMatrix::strictLinearOrder() // строгий лінійним порядком 
{
	if ((this->antusemetruchnist()) && (this->tranzutuvnist()) && (this->connectivity())) {
		return true;
	}
	else {
		return false;
	}
}

void RelationMatrix::symmetricСomponent(Relation &res_) // симетрична складова
{
	RelationMatrix temp1(size_, FULLZERO);
	RelationMatrix res(size_, FULLZERO);

	this->inverseRelationship(temp1); // P - 1;

	this->intersection(temp1, res);

	res_ = res;
}

void RelationMatrix::asymmetricСomponent(Relation &res_) // aсиметрична складова
{
	RelationMatrix res1(size_, FULLZERO);
	RelationMatrix res2(size_, FULLZERO);

	this->symmetricСomponent(res1);

	this->difference(res1, res2);
	res_ = res2;

}

void RelationMatrix::transitiveСlosure(Relation &res_)  //транзитивне замикання
{
	RelationMatrix temp1(size_, FULLZERO);
	RelationMatrix temp2(size_, FULLZERO);
	RelationMatrix res(size_, FULLZERO);

	RelationMatrix *m = new RelationMatrix[size_];  ///aaa

	this->composition(*this, temp2);

	m[0] = temp2;

	for (int i = 0; i < size_ - 1; i++) {
		this->composition(m[i], temp2);
		m[i + 1] = temp2;
	}

	this->association(m[0], temp1);

	for (int i = 1; i < size_ - 1; i++) {
		temp1.association(m[i], res);
		temp1 = res;
	}

	res_ = res;
}

void  RelationMatrix::reach(Relation &res_)  // досяжність
{
	RelationMatrix temp1(size_, FULLZERO);
	RelationMatrix temp2(size_, FULLZERO);
	RelationMatrix temp3(size_, DIAGONAL);
	RelationMatrix res(size_, FULLZERO);

	RelationMatrix *m1 = new RelationMatrix[size_];  /// aaa

	this->composition(*this, temp2);
	m1[0] = temp2;

	for (int i = 0; i < size_ - 1; i++) {
		this->composition(m1[i], temp2);
		m1[i + 1] = temp2;
	}
	this->association(m1[0], temp1);
	for (int i = 1; i < size_ - 2; i++) {
		temp1.association(m1[i], res);
		temp1 = res;
	}
	temp3.association(res, temp1);
	res_ = temp1;
}

void RelationMatrix::mutualReach(Relation &res_)  //  взаємна досяжність
{
	RelationMatrix temp1(size_, FULLZERO);
	RelationMatrix temp2(size_, FULLZERO);
	RelationMatrix res(size_, FULLZERO);

	this->reach(temp1);

	temp1.inverseRelationship(temp2);

	temp1.intersection(temp2, res);
	res_ = res;
}

void RelationMatrix::inverseRelationship(Relation & res)
{

	for (int i = 0; i < size_; i++)
	{
		for (int j = 0; j < size_; j++)
		{
			if (matrix_[j][i]) {
				res.setElement(i, j, 1);
			}
			else {
				res.setElement(i, j, 0);
			}
		}
	}
}

void RelationMatrix::getVector(int i, std::vector<bool>& res)
{
		for (int j = 0; j < size_; j++)
		{
			res.emplace_back(matrix_[i][j]);
		}
}

void RelationMatrix::factorization(Relation &a, Relation &res_)  //  факторизація
{
	RelationMatrix res(size_, FULLZERO);
	this->mutualReach(res);

	std::vector<int> top;

	std::vector<bool> temp;
	std::vector<bool> temp1;

	for (int i = 0; i < size_; i++)
	{
		res.getVector(i,temp);
		for (int j = i+1; j < size_; j++)
		{
			res.getVector(j, temp1);
			if (temp == temp1) {
				top.emplace_back(j);
				for (int k = 0; k < size_; k++) {
					res.setElement(k, j, 0);
				}
				temp1.clear();
				temp.clear();
				break;
			}
			temp1.clear();
		}
		temp.clear();
	}

	bool **matr = new bool*[size_ - top.size()];
	for (size_t i = 0; i < size_; i++) {
		matr[i] = new bool[size_- top.size()];
	}

	for (int i = 0; i < size_ - top.size(); i++)
	{
		for (int j = 0; j < size_ - top.size(); j++)
		{
			matr[i][j] = res.getElement(i,j);
			if (i == j) {
				matr[i][j] = 1;
			}
		}
	}

	RelationMatrix resss(size_ - top.size(), matr);
	RelationMatrix mes(size_ - top.size(), FULLZERO);
	resss.transitiveСlosure(mes);
	res_ = mes;
}

void RelationMatrix::showProperties()   // показати все
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

void RelationMatrix::showType()   // показати все
{
	std::cout << "\nTolerance           " << BoolToString(this->tolerance()) << std::endl;
	std::cout << "Equivalence         " << BoolToString(this->quasiorder()) << std::endl;
	std::cout << "Strict Order        " << BoolToString(this->strictOrder()) << std::endl;
	std::cout << "Order               " << BoolToString(this->order()) << std::endl;
	std::cout << "Linear Order        " << BoolToString(this->linearOrder()) << std::endl;
	std::cout << "Strict Linear Order " << BoolToString(this->strictLinearOrder()) << std::endl;

}
