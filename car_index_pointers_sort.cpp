#include <iostream>
#include <string> // подключаем строки
#include <fstream> // подключаем файлы
#include <vector>
#include <algorithm>

using namespace std;

struct Car {
    string maker, model, fuel_type;
    int mileage, manufacture_year, engine_power, price_eur;

    Car(string &_maker, string &_model, int _mileage, int _manufacture_year, int _engine_power, string &_fuel_type,
        int _price_eur) :
            maker(_maker),
            model(_model),
            fuel_type(_fuel_type),
            mileage(_mileage),
            manufacture_year(_manufacture_year),
            engine_power(_engine_power),
            price_eur(_price_eur) {
        //cout << "Created: " << full_info() << endl;
    }

    string full_info() const {
        return maker + " " +
               model + " " +
               fuel_type + " " +
               to_string(mileage) + " " +
               to_string(manufacture_year) + " " +
               to_string(engine_power) + " " +
               to_string(price_eur);
    }
};

void add_to_base(vector <Car> &Cars, vector <string> &data){
    int arr[] = {0, 1, 5};
    vector <int> arr_int;
    vector <string> arr_str;
    for (int i=0; i<data.size(); ++i){
        bool all_ok = true;
        for(int j=0; all_ok and j<sizeof(arr)/sizeof(int); ++j){
            if (i == arr[j]) all_ok = false;
        }
        if (all_ok) arr_int.push_back(stoi(data[i]));
        else        arr_str.push_back(data[i]);
    }
    Cars.emplace_back(Car(arr_str[0], arr_str[1], arr_int[0], arr_int[1], arr_int[2], arr_str[2], arr_int[3]));
}
int ulala(int i){
    return i;
}

template <typename Comp_func>
void distcount(vector <int> &A, int MAX, Comp_func func = [](int i){return i;}) {
    int i;
    if (MAX == 0) {      //максимум неизвестен
        for (i = 0; i < A.size(); ++i) {
            if (func(A[i]) > MAX) {
                MAX = func(A[i]);
            }
        }
    }
    ++MAX;              // 0<->(MAX-1) --> 1<->(MAX)
    vector <int> k(MAX), B(A.size());
    for (i = 0; i < MAX;      ++i) k[i] = 0;
    for (i = 0; i < A.size(); ++i) k[func(A[i]) + 1]++;
    for (i = 0; i < MAX;      ++i) k[i] += k[i - 1];
    for (i = 0; i < A.size(); ++i) B[k[func(A[i])]++] = A[i];
    for (i = 0; i < A.size(); ++i) A[i] = B[i];
}

int main() {
    vector <Car> Cars;
    string s;
    ifstream file("../dataset.txt");

    while (getline(file, s)) {
        std::string delimiter = ", ";

        size_t pos = 0;
        string token;
        vector<string> carcar;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            //    std::cout << token  << " ";
            carcar.push_back(token);

            s.erase(0, pos + delimiter.length());
        }
        add_to_base(Cars, carcar);
    }

    vector <Car *> pointers_sort(Cars.size());// = Cars;

    for (int i = 0; i < Cars.size(); ++i) {
        pointers_sort[i] = &Cars[i];
    }

    sort(pointers_sort.begin(), pointers_sort.end(), [](Car *A, Car *B) {
        int maker_size_A = A->maker.size();
        int maker_size_B = B->maker.size();

        string space_A = string(max(maker_size_B - maker_size_A, 0), ' ');
        string space_B = string(max(maker_size_A - maker_size_B, 0), ' ');

        return (A->maker + space_A + A->model <
                B->maker + space_B + B->model);
    });

    for (Car *car: pointers_sort) {
        cout << car->full_info() << endl;
    }

    cout << "#################################################################################" << endl;

    vector <int> INDEX_sort(Cars.size());

    for (int i = 0; i < INDEX_sort.size(); ++i) INDEX_sort[i] = i;

    sort(INDEX_sort.begin(), INDEX_sort.end(), [&Cars](int A, int B) {
        int maker_size_A = Cars[A].maker.size();
        int maker_size_B = Cars[B].maker.size();

        string space_A = string(max(maker_size_B - maker_size_A, 0), ' ');
        string space_B = string(max(maker_size_A - maker_size_B, 0), ' ');

        return (Cars[A].maker + space_A + Cars[A].model <
                Cars[B].maker + space_B + Cars[B].model);
    });

    for (int &indexes: INDEX_sort) {
        cout << Cars[indexes].full_info() << endl;
    }

    cout << "#################################################################################" << endl;

    for (int i = 0; i < INDEX_sort.size(); ++i) {
        INDEX_sort[i] = i;
    }

    distcount(INDEX_sort, 0, [Cars](int index) { return Cars[index].engine_power; });



    for (int &indexes: INDEX_sort) {
        cout << Cars[indexes].full_info() << endl;
    }

    cout << "Cars size: " << (Cars.end() - Cars.begin())*sizeof(Car) << endl;
    cout << "Pointers size: " << (sizeof(Car *) * pointers_sort.size()) << endl;
    cout << "Index size: "    << (sizeof(int)   * INDEX_sort.size())    << endl;

    file.close();
    return 0;
}
