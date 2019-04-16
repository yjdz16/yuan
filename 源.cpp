#include<iostream>
using namespace std;

class Fraction {
public:
	int numerator;  //分子
	int denominator;  //分母
	double Value() {
		return 1.0 * numerator / denominator;
	}
	friend istream& operator >> (istream&, Fraction&);  //输入流重定义
};

istream& operator >> (istream& input, Fraction& C)
{
	input >> C.numerator >> C.denominator;
	return input;
}

int Gcd(int a, int b);
int Gcd(int a, int b) {
	if (a%b == 0)
		return b;
	else
		return Gcd(b, a%b);
}

template<class T>
class Cassemblage {
public:
	int num;
	//T *x;
	T x[2000];
	void Set(T *a, int n);
	void Show();
	//~Cassemblage();
	Cassemblage() {};
	Cassemblage(const Cassemblage& a);
	Cassemblage<T> operator + (Cassemblage<T> b) { //定义重载运算符函数
		int num_new = num;
		//T *x_new = new T[a.num + b.num];
		T x_new[2000];
		for (int i = 0; i<num; i++) {
			x_new[i].numerator = x[i].numerator;
			x_new[i].denominator = x[i].denominator;
		}
		for (int i = 0; i<b.num; i++) {
			for (int j = 0; j<num_new; j++) {
				if (b.x[i].Value() == x_new[j].Value())
					break;
				if (j == num_new - 1) {
					x_new[num_new++] = b.x[i];
				}
			}
		}
		Cassemblage <T> z_new;
		z_new.Set(x_new, num_new);
		//delete(x_new);
		return z_new;
	}
	Cassemblage<T> operator - (Cassemblage<T> b) { //定义重载运算符函数
		int num_new = 0;
		//T *x_new = new T[a.num];
		T x_new[1000];
		for (int i = 0; i<num; i++) {
			for (int j = 0; j<b.num; j++) {
				if (x[i].Value() == b.x[j].Value())
					break;
				if (j == b.num - 1) {
					x_new[num_new++] = x[i];
				}
			}
		}
		Cassemblage <T> z_new;
		z_new.Set(x_new, num_new);
		//delete(x_new);
		return z_new;
	}

	Cassemblage<T> operator & (Cassemblage<T> b) { //定义重载运算符函数
		int num_new = 0;
		//T *x_new = new T[a.num > b.num ? a.num : b.num];
		T x_new[1000];
		for (int i = 0; i<num; i++) {
			for (int j = 0; j<b.num; j++) {
				if (x[i].Value() == b.x[j].Value()) {
					x_new[num_new++] = x[i];
					break;
				}
			}
		}
		Cassemblage <T> z_new;
		z_new.Set(x_new, num_new);
		//delete(x_new);
		return z_new;
	}
};

//template<class T>
//Cassemblage<T>::~Cassemblage() {
//	delete(x);
//}

template<class T>
Cassemblage<T>::Cassemblage(const Cassemblage& a) { //定义重载运算符函数
	num = a.num;
	//x = new T[num];
	for (int i = 0; i<num; i++) {  //将元素存入集合
		x[i] = a.x[i];
	}
}

template<class T>
void Cassemblage<T>::Set(T *a, int n) {
	//x = new T[n];
	num = 0;
	for (int i = 0; i<n; i++) {  //将元素存入集合
		if (num == 0) {
			x[num] = a[i];
			int gcd = Gcd(x[num].numerator, x[num].denominator);
			x[num].numerator = x[num].numerator / gcd;
			x[num].denominator = x[num].denominator / gcd;
			num++;
		}
		else
			for (int j = 0; j < num; j++) {
				if (x[j].Value() == a[i].Value())
					break;
				if (j == i - 1) {
					x[num] = a[i];
					int gcd = Gcd(x[num].numerator, x[num].denominator);
					x[num].numerator = x[num].numerator / gcd;
					x[num].denominator = x[num].denominator / gcd;
					num++;
				}
			}
	}
}

template<class T>
void Cassemblage<T>::Show() {
	if (num == 0) {
		cout << "empty" << endl;
		return;
	}
	double next_x = x[0].Value();
	int next_dir = 0;
	double last_x = -9999999999;
	while (1) {
		next_x = x[0].Value();
		int k = 0;
		for (int i = 0; i < num; i++) {
			if (k == 0) {
				if (x[i].Value() > last_x) {
					next_x = x[i].Value();
					next_dir = i;
					k = 1;
				}
			}
			else if (x[i].Value() > last_x && x[i].Value()<next_x) {
				next_x = x[i].Value();
				next_dir = i;
			}
		}
		if (k != 0) {
			if (x[next_dir].numerator % x[next_dir].denominator == 0) {
				cout << int(x[next_dir].numerator / x[next_dir].denominator) << " ";
			}
			else {
				cout << x[next_dir].numerator << "/" << x[next_dir].denominator << " ";
			}
			last_x = next_x;
		}
		else {
			cout << endl;
			break;
		}
	}
}

int main(int argc, char* argv[]) {
	Cassemblage <Fraction> z1, z2, x1;
	Fraction a1[1000], a2[1000];
	int i, n1, n2;
	char op;
	cin >> n1;
	for (i = 0; i<n1; i++) {
		cin >> a1[i];
	}
	z1.Set(a1, n1);

	cin >> n2;
	for (i = 0; i<n2; i++) {
		cin >> a2[i];
	}
	z2.Set(a2, n2);
	cin >> op;
	switch (op) {
	case '+':
		x1 = z1 + z2;
		x1.Show();
		break;
	case '-':
		x1 = z1 - z2;
		x1.Show();
		break;
	case '&':
		x1 = z1&z2;
		x1.Show();
		break;
	default:
		cout << "Inxalid operator!";
	}

	return 0;
}
