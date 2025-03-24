#include <iostream>
#include <vector>
#include <ostream>

using namespace std;

class Elements{
private:
    double coef;
    int pow;
public:
    Elements(){}
    Elements(double c, int power): coef(c),pow(power){}
    double getCoef() const{
        return coef;
    }
    int getPow() const{
        return pow;
    }
    double setCoef(double c) {
        coef = c;
    }
    int setPow(double power) {
        pow = power;
    }
    void operator=(const Elements& el){
        coef = el.getCoef();
        pow = el.getPow();
    }
    ~Elements(){}
};

class Polynom{
private:
    vector<Elements> coefs;
public:
    Polynom() {  };
    Polynom(vector<Elements> &a) : coefs(a){}

    void SumCoeef (vector <Elements> &a) {
        if (a.size() > 0) {
            for (unsigned i = 0; i < a.size(); i++) {
                for (unsigned j = (i + 1); j < a.size(); j++) {
                    if (a[i].getPow() == a[j].getPow()) {
                        a[i].setCoef(a[i].getCoef() + a[j].getCoef());
                        a.erase(a.begin() + j);
                        --j;
                    }
                }
            }
        }
    }

    Polynom operator= (const Polynom &new_coefs){
        coefs.resize(new_coefs.coefs.size());
        for(int i = 0;i < new_coefs.coefs.size();++i){
            coefs[i] = new_coefs.coefs[i];
        }
        SumCoeef(coefs);
        return *this;
    }

    bool operator==(const Polynom &new_coefs){
        int size2 = new_coefs.coefs.size();
        int size1 = coefs.size();
        if(size1 != size2){
            return false;
        }
        for(int i = 0;i < size1;i++){
            if(coefs[i].getCoef() != new_coefs.coefs[i].getCoef()){
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Polynom &new_coefs){
        return !operator==(new_coefs);
    }
    Polynom operator+(Polynom &new_coefs){
        vector<Elements> summary;
        for(int i = 0;i < coefs.size();i++){
            summary.push_back(coefs[i]);
        }
        int size = new_coefs.coefs.size();
        for(int i = 0;i < size;i++){
            summary.push_back(new_coefs.coefs[i]);
        }
        SumCoeef(summary);
        return Polynom(summary);
    }
    void operator+=(const Polynom &new_coefs) {
        int size = new_coefs.coefs.size();
        vector<Elements> coef1;
        for (int i = 0; i < size; i++) {
            coef1.push_back(new_coefs.coefs[i]);
        }
    }
    Polynom operator-(const Polynom &new_coefs){
        vector<Elements> coef1;
        double co;
        for(int i = 0;i < coefs.size();i++){
            co = coefs[i].getCoef() + new_coefs.coefs[i].getCoef() * (-1);
            coef1.push_back(Elements(co, coefs[i].getPow()));
        }
        return coef1;
    }
    Polynom operator-=(const Polynom &new_coefs){
        *this = *this - new_coefs;
        return new_coefs;
    }

    Polynom operator*(const Polynom &new_coefs){
        int size = new_coefs.coefs.size();
        vector<Elements> coef1(size);
        for(int i = 0;i < size;i++){
            for(int j = 0;j < size;j++){
                coef1.push_back(Elements(new_coefs.coefs[j].getCoef() * coefs[i].getCoef(),new_coefs.coefs[j].getPow() + coefs[i].getPow()));
            }
        }
        SumCoeef(coef1);
        return Polynom(coef1);
    }
    Polynom operator*=(const Polynom &new_coefs){
        *this = *this * new_coefs;
        return Polynom(new_coefs);
    }
    Polynom operator/ (const Polynom &new_coefs) {
        int degree = 0;
        int degree1 = 0;
        for(int i = 0;i <coefs.size();i++){
            if(coefs[i].getPow() > degree){
                degree = coefs[i].getPow();
            }
        }
        for(int i = 0;i < new_coefs.coefs.size();i++){
            if(new_coefs.coefs[i].getPow() > degree1){
                degree1 = new_coefs.coefs[i].getPow();
            }
        }
        int rdeg = degree - degree1 + 1;
        vector<Elements> res;
        for (int i = 0; i < rdeg; i++) {
            double kek;

            kek = coefs[degree - i - 1].getCoef() / new_coefs.coefs[degree1 - 1].getCoef();
            res.push_back(Elements(kek, degree));
            for (int j = 0; j < degree1; j++) {
                double kek1 = new_coefs.coefs[degree1 - j - 1].getCoef() * res[rdeg - i - 1].getCoef();
                coefs.push_back(Elements(kek1, degree));
            }
        }
        return res;
    }
    Polynom operator/= (Polynom &new_coefs) {
        *this = *this / new_coefs;
        return Polynom(new_coefs);
    }

    friend Polynom operator>> ( istream &in, Polynom &new_coefs) {
        double factr;
        int pow;
        cin >> factr >> pow;
        vector < Elements> sum;
        for (unsigned i = 0; i < new_coefs.coefs.size(); ++i) {
            sum.push_back(new_coefs.coefs[i]);
        }
        sum.push_back( Elements(factr, pow));
        new_coefs = sum;
        return Polynom(new_coefs);
    }

    friend void operator<< ( ostream &out, Polynom &new_coefs) {
        for (unsigned i = 0; i < new_coefs.coefs.size(); ++i) {
            cout << new_coefs.coefs[i].getCoef() << "^" << new_coefs.coefs[i].getPow() <<  endl;
        }
    }


    Elements operator[] (int i) {
        return coefs[i];
    }
    ~Polynom () {}
};

int main() {
    Elements a(2, 1), d(3, 1), k(1, 1);
    Elements b(1, 2), e(1, 2), l(1, 2);
    Elements c(4, 3), f(1, 3), m(1, 3);
    vector<Elements> Arr1(3);
    vector<Elements> Arr2(3);
    vector<Elements> Arr3(3);
    Arr1 = {a, d, k};
    Arr2 = {b, e, l};
    Arr3 = {c, f, m};
    Polynom polynom1(Arr1);
    Polynom polynom2(Arr2);
    Polynom polynom3(Arr3);

    polynom1 = polynom2;

    if (polynom1 == polynom2) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    polynom2 += polynom1;
    cout << polynom2;
    return 0;
}