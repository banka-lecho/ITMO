#include <iostream>
#include <vector>

using namespace std;

template <typename T>
bool compare (T first, T second) {
    return second > first ? true : false;
};

template <typename T>
bool positive(const T character){
    return  character > 0;
}
template <typename T>
bool less_than(const T  character, int count){
    return character > count;
}

template <typename T>
bool check_parity(const T  character){
    return character % 2 == 0;
}


template <typename T, typename Func>
bool all_of(const T& begin, const T& end, Func any_function){
    for(T iter = begin; iter != end; ++iter){
        if (!any_function(*iter)) {
            return false;
        }
    }
    return true;
}

template <typename T, typename Func>
bool any_of(const T& begin, const T& end, Func any_function){
    for(T iter = begin; iter != end; ++iter){
        if(any_function(*iter)){
            return true;
        }
    }
    return false;
}

template <typename T, typename Func>
bool none_of(const T& begin, const T& end, Func any_function, int count){
    int sum = 0;
    for(T iter = begin; iter != end; iter++){
        if(!any_function(*iter)){
            sum++;
        }
    }
    if(sum == count){
        return true;
    }
    return false;
}

template <typename T, typename Func>
bool one_of(const T& begin, const T& end, Func any_function) {
    int sum = 0;
    for (T iter = begin; iter != end; ++iter) {
        if (any_function(*iter)) {
            sum++;
        }
    }
    if (sum == 1) {
        return true;
    }
    return false;
}
template <typename T, typename Func>
bool is_sorted(const T& begin, const T& end, Func any_function) {
    for (T iter = begin; iter != end; ++iter) {
        if (any_function(*iter, *(iter - 1))) {
            return false;
        }
    }
    return true;
}
template <typename T, typename Func>
bool is_partitioned(const T& begin, const T& end, Func any_function, int count){
    int left = 0, right  = 0;
    T iter1;
    for(T iter = begin; iter != begin;++iter){
        if(any_function(*iter) == any_function(*iter - 1)){
            left++;
            iter1 = iter;
        } else{
            break;
        }
    }
    for(T iter = iter1 + 1; iter != begin;++iter){
        if(any_function(*iter) == any_function(*iter - 1)){
            right++;
        } else{
            break;
        }
    }
    // ищем стык этих элементов
    if(left + right == count){
        return true;
    }
    return false;
}

template <typename T, typename Object>
Object find_out(const T& begin, const T& end, Object element){
    for(T iter = begin; iter != end;++iter){
        if(*iter != element){
            return *iter;
        }
    }
}

template <typename T, typename Object>
Object find_backward(const T& begin, const T& end, Object element){
    for(T iter = end - 1; iter != end;--iter){
        if(*iter == element){
            return *iter;
        }
    }
}
template <typename T>
bool is_palindrome(const T& begin, const T& end, const T& med){
    for(T iter = begin;iter != med;++iter){
        for(T iter1 = end - 1;iter1 != med;++iter1){
            if(*iter != *iter1){
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector <int> vector1 = {1, 2, 3, 4, 5};
    vector <int> vector2 = {2, 2, 2, 2, 2};

    cout << "all_of - " << (all_of(vector2.begin(), vector2.end(), check_parity<int>) ? "Yes" : "No")  << endl;
    cout << "any_of - " << (any_of(vector1.begin(), vector1.end(), check_parity<int>) ? "Yes" : "No") << endl;
    cout << "is_sorted - " << (is_sorted(vector1.begin(), vector1.end(), compare<int>) ? "Yes" : "No") << endl;
    cout << "find_not - " << (find_out(vector1.begin(), vector1.end(), 1) ? "Yes" : "No") << endl;
    cout << "find_backward - " << find_backward(vector1.begin(), vector1.end(), 5) << endl;


    return 0;
}