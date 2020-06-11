#pragma warning(disable:4996)
#pragma warning(default:4716)
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

void	print_error(int id)
{
	exit(id);
}

class square_matrix
{
private:
	char* name_matrix;
	int size_matrix;
	double** my_matrix;


private:
	void my_swap(int i1, int i2);
	double	triangle_matrix();
	square_matrix reduceColRow(int row, int col);
public:
	explicit square_matrix(const char* name, int size);
	square_matrix(const square_matrix& other);
	square_matrix(square_matrix&& other);
	square_matrix();
	~square_matrix();

	int get_size() const;
	char* get_name() const;
	void get_matrix() const;
	void del_matrix();
	void print_matrix() const;
	void set_el(int i, int j, double el);
	void random_push_el(int n);
	double matrix_trace();
	void tran_matrix();
	double		det();
	square_matrix reverse();
	square_matrix exp(int n);

	square_matrix& operator =(const square_matrix& other);
	square_matrix& operator +=(const square_matrix& other);
	square_matrix& operator -=(const square_matrix& other);
	square_matrix& operator *=(const square_matrix& other);
	square_matrix& operator/=(int n);
	square_matrix& operator/(int n);
	bool operator ==(const square_matrix& other);
	bool operator !=(const square_matrix& other);
};

square_matrix operator +(const square_matrix& leftOperand, const square_matrix& rightOperand);
square_matrix operator -(const square_matrix& leftOperand, const square_matrix& rightOperand);
square_matrix operator *(const square_matrix& leftOperand, const square_matrix& rightOperand);

void square_matrix::set_el(int i, int j, double el)
{
	my_matrix[i][j] = el;
}

void square_matrix::print_matrix() const
{
	std::cout << "name_matrx : " << name_matrix << ' ' << "size_matrix : " << size_matrix << std::endl;
	get_matrix();
};

std::ostream& operator << (std::ostream& stream, const square_matrix& toOutput)
{
	toOutput.print_matrix();
	return stream;
};

double	square_matrix::matrix_trace()
{
	double result = 0;

	for (int i = 0; i < size_matrix; i++)
		result += my_matrix[i][i];
	return (result);
}

std::istream& operator >> (std::istream& stream, square_matrix& toInput)
{
	double el;

	cout << "write: " << toInput.get_size() << " element" << endl;

	for (int i = 0; i < toInput.get_size(); i++)
	{
		for (int j = 0; j < toInput.get_size(); j++)
		{
			cin >> el;
			toInput.set_el(i, j, el);
		}
	}

};

void square_matrix::random_push_el(int n)
{
	for (int i = 0; i < size_matrix; i++)
		for (int j = 0; j < size_matrix; j++)
			my_matrix[i][j] = rand() % n;
}

square_matrix::square_matrix(const square_matrix& other)
{
	size_matrix = other.size_matrix;

	name_matrix = strdup(other.name_matrix);
	my_matrix = (double**)malloc(sizeof(double*) * size_matrix);
	for (int i = 0; i < size_matrix; i++)
	{
		my_matrix[i] = (double*)malloc(sizeof(double) * size_matrix);
		for (int j = 0; j < size_matrix; j++)
			my_matrix[i][j] = other.my_matrix[i][j];
	}
};

square_matrix::square_matrix(square_matrix&& other)
{
	name_matrix = other.name_matrix;
	size_matrix = other.size_matrix;
	my_matrix = other.my_matrix;
	other.my_matrix = NULL;
	other.size_matrix = 0;
	other.name_matrix = NULL;
};

void	square_matrix::get_matrix() const
{
	for (int i = 0; i < size_matrix; i++)
	{
		for (int j = 0; j < size_matrix; j++)
			std::cout << my_matrix[i][j] << " ";
		std::cout << std::endl;
	}

};

int square_matrix::get_size() const
{
	return (size_matrix);
};

char* square_matrix::get_name() const
{
	return (name_matrix);
};

square_matrix::square_matrix(const char* name, int size)
{
	size_matrix = size;
	name_matrix = strdup(name);
	my_matrix = (double**)malloc(sizeof(double*) * size_matrix);
	for (int i = 0; i < size_matrix; i++)
	{
		my_matrix[i] = (double*)malloc(sizeof(double) * size_matrix);
		for (int j = 0; j < size_matrix; j++)
			if (i == j)
				my_matrix[i][j] = 1;
			else
				my_matrix[i][j] = 0;
	}
};

void square_matrix::del_matrix()
{
	for (int i = 0; i < size_matrix; i++)
		free(my_matrix[i]);
	free(my_matrix);
	free(name_matrix);
	size_matrix = 0;
};

square_matrix::square_matrix()
{
	size_matrix = 0;
	my_matrix = NULL;
	name_matrix = strdup("NULL");
};

square_matrix::~square_matrix()
{
	for (int i = 0; i < size_matrix; i++)
		free(my_matrix[i]);
	free(my_matrix);
	free(name_matrix);
};

bool square_matrix::operator ==(const square_matrix& other)
{
	if (size_matrix != other.size_matrix)
		return (false);
	for (int i = 0; i < size_matrix; i++)
		for (int j = 0; j < size_matrix; j++)
			if (my_matrix[i][j] != other.my_matrix[i][j])
				return (false);
	return (true);
}

bool square_matrix::operator !=(const square_matrix& other)
{
	return (!(*this == other));
}

square_matrix& square_matrix::operator =(const square_matrix& other)
{
	name_matrix = strdup(other.name_matrix);
	size_matrix = other.size_matrix;
	my_matrix = (double**)malloc(sizeof(double*) * size_matrix);
	for (int i = 0; i < size_matrix; i++)
	{
		my_matrix[i] = (double*)malloc(sizeof(double) * size_matrix);
		for (int j = 0; j < size_matrix; j++)
			my_matrix[i][j] = other.my_matrix[i][j];
	}
	return (*this);
};

square_matrix& square_matrix::operator +=(const square_matrix& other)
{
	if (size_matrix != other.size_matrix)
		print_error(-1);
	for (int i = 0; i < size_matrix; i++)
		for (int j = 0; j < size_matrix; j++)
			my_matrix[i][j] += other.my_matrix[i][j];
	return (*this);
};

square_matrix& square_matrix::operator -=(const square_matrix& other)
{
	if (size_matrix != other.size_matrix)
		print_error(-1);
	for (int i = 0; i < size_matrix; i++)
		for (int j = 0; j < size_matrix; j++)
			my_matrix[i][j] -= other.my_matrix[i][j];
	return (*this);
};

square_matrix& square_matrix::operator *=(const square_matrix& other)
{
	int temp;
	square_matrix temp_matrix(name_matrix, size_matrix);

	if (size_matrix != other.size_matrix)
		print_error(-1);
	for (int i = 0; i < size_matrix; i++)
		for (int j = 0; j < size_matrix; j++)
		{
			temp = 0;
			for (int k = 0; k < size_matrix; k++)
				temp = temp + my_matrix[i][k] * other.my_matrix[k][j];
			temp_matrix.my_matrix[i][j] = temp;
		}
	*this = temp_matrix;
	return (*this);
};

square_matrix operator +(const square_matrix& leftOperand, const square_matrix& rightOperand)
{
	square_matrix temp_matrix = leftOperand;

	temp_matrix += rightOperand;
	return (temp_matrix);
};

square_matrix operator -(const square_matrix& leftOperand, const square_matrix& rightOperand)
{
	square_matrix temp_matrix = leftOperand;

	temp_matrix -= rightOperand;
	return (temp_matrix);
};

square_matrix operator *(const square_matrix& leftOperand, const square_matrix& rightOperand)
{
	square_matrix temp_matrix = leftOperand;

	temp_matrix *= rightOperand;
	return (temp_matrix);
};

square_matrix& square_matrix::operator/=(int n)
{
	for (int i = 0; i < this->size_matrix; ++i) {
		for (int j = 0; j < this->size_matrix; ++j) {
			this->my_matrix[i][j] /= n;
		}
	}
	return (*this);
}

square_matrix& square_matrix::operator/(int n)
{
	return (*this /= n);
}

void	square_matrix::tran_matrix()
{
	square_matrix temp(name_matrix, size_matrix);

	for (int i = 0; i < size_matrix; i++)
		for (int j = 0; j < size_matrix; j++)
			temp.my_matrix[i][j] = my_matrix[j][i];
	*this = temp;
}

square_matrix square_matrix::exp(int n) {
	int d = 1;
	square_matrix result(this->name_matrix, this->size_matrix);
	square_matrix a = *this;

	for (int i = 0; i < this->size_matrix; ++i)
	{
		result = result + a / d++;
		a *= *this;
	}
	return (result);
}

void square_matrix::my_swap(int i1, int i2)
{
	double temp;

	for (int j = 0; j < size_matrix; j++)
	{
		temp = my_matrix[i1][j];
		my_matrix[i1][j] = my_matrix[i2][j];
		my_matrix[i2][j] = temp;
	}

}
double	square_matrix::triangle_matrix()
{
	double mnoj;

	mnoj = 1;
	for (int diag = 0; diag < size_matrix - 1; diag++)
	{
		if (!my_matrix[diag][diag])
			for (int i = diag; i < size_matrix - 1; i++)
				if (my_matrix[i][i])
				{
					my_swap(i, diag);
					mnoj *= -1;
				}
		for (int i = diag + 1; i < size_matrix; i++)
		{
			if (!my_matrix[i][diag])
				continue;
			for (int j = diag + 1; j < size_matrix; j++)
				my_matrix[i][j] = my_matrix[diag][diag] * my_matrix[i][j] - my_matrix[i][diag] * my_matrix[diag][j];
			mnoj *= my_matrix[diag][diag];
			my_matrix[i][diag] = 0;
		}
	}
	return (mnoj);
}

double		square_matrix::det()
{
	double det;
	double temp;
	square_matrix temp_matrix = *this;

	temp = temp_matrix.triangle_matrix();
	det = 1;
	for (int i = 0; i < size_matrix; i++)
		det *= temp_matrix.my_matrix[i][i];
	return (det / temp);
}

square_matrix square_matrix::reduceColRow(int row, int col)
{
	square_matrix temp("temp", size_matrix - 1);

	int ki = 0;
	for (int i = 0; i < size_matrix; i++)
	{
		if (i != row)
		{
			for (int j = 0, kj = 0; j < size_matrix; j++)
			{
				if (j != col)
				{
					temp.my_matrix[ki][kj] = my_matrix[i][j];
					kj++;
				}
			}
			ki++;
		}
	}
	return temp;
}

square_matrix square_matrix::reverse()
{
	int sgn = 1;
	double det_matrix = det();
	square_matrix adj(name_matrix, size_matrix);

	for (int i = 0; i < size_matrix; ++i)
	{
		for (int j = 0; j < size_matrix; ++j)
		{
			sgn = (((i + j) % 2 == 0) ? 1 : -1);
			square_matrix temp = reduceColRow(i, j);
			adj.my_matrix[i][j] = (sgn * temp.det()) / det_matrix;
		}
	}
	adj.tran_matrix();
	return adj;
}

int main()
{
	square_matrix m1("m1", 3);
	square_matrix m2("m2", 3);

	// m1.random_push_el(10);
	cin >> m1;
	cout << m1.reverse() << endl;
	// m1.exp(3);

	cout << m1.exp(3) << endl;
	cout << (m2 != m1) << endl;
	// m2 = m1 + m2;
	// cout << m2; 
}