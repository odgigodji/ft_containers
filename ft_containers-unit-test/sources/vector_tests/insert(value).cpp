#include "../system/system_methods.ipp"
#include "__service.ipp"

class B {
public:
	char *l;
	int i;
	B():l(nullptr), i(1) {};
	B(const int &ex) {
		this->i = ex;
		this->l = new char('a');
	};
	virtual ~B() {
		delete this->l;
		this->l = nullptr;
	};
};

class A : public B {
public:
	A():B(){};
	A(const B* ex){
		this->l = new char(*(ex->l));
		this->i = ex->i;
		if (ex->i == -1) throw "n";
	}
	~A() {
		delete this->l;
		this->l = nullptr;
	};
};

template <typename T>
std::vector<int> insert_test_1(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(26000000, 1);
    g_start1 = timer();
    v.push_back(*(vector.insert(vector.end() - 8000000, 44)));
    g_end1 = timer();

    return v;
}

template <typename T>
std::vector<int> insert_test_1(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(26000000, 1);
    g_start2 = timer();
    v.push_back(*(vector.insert(vector.end() - 8000000, 44)));
    g_end2 = timer();

    return v;
}

int main() {

    exit(run_vector_unit_test<int>("insert(value)", insert_test_1, insert_test_1));
}