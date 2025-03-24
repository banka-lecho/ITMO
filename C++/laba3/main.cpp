#include <iostream>
using namespace std;

class Transport {
private:
    map <string, int> transp;
    string vechile;
public:
    Transport () {
    }

    void print_transport () {
        string name;
        map <string, int>::iterator iter;

        for (iter = transp.begin(); iter != transp.end(); ++iter) {
            cout << "name_routes = " << iter->first << "\t count_routes = " << iter->second << endl;
        }
    }
//парсинг
    void routes () {
        pugi::xml_document doc;
        doc.load_file("dataset.xml");
        pugi::xml_node panels = doc.first_child();
        cout << panels.name() << endl;
        for (pugi::xml_node panel1 = panels.first_child(); panel1; panel1 = panel1.next_sibling()) {
            cout << panel1.name() << endl;
            string transport;
            for (pugi::xml_node panel2 = panel1.first_child(); panel2; panel2 = panel2.next_sibling()) {
                // name - это имя узла, который является именем элемента
                // value - это значение узла, которое является текстом узла
                string name = panel2.name();
                string value = panel2.child_value();
                cout << name << " - " << value << endl;
                if (name == "type_of_vehicle") {
                    transport = value;
                }
                if ((transport == "Автобус") && (name == "routes")) {
                    int size = value.length();
                    string value_temp;

                    for (int i = 0; i < size; ++i) {
                        char ch;
                        ch = value[i];
                        if ((ch == '.') || (ch == ',')) {
                            transp[value_temp]++; // количество остановок
                            value_temp = "";
                        }
                        else {
                            value_temp += ch;
                        }

                    }
                    if (value_temp != "") { // проверка для битых данных
                        transp[value_temp]++;
                    }

                }
                if ((transport == "Трамвай") && (name == "routes")) {
                    int size = value.length();
                    string value_temp;

                    for (int i = 0; i < size; ++i) {
                        char ch;
                        ch = value[i];
                        if ((ch == '.') || (ch == ',')) {
                            transp[value_temp]++;
                            value_temp = "";
                        }
                        else {
                            value_temp += ch;
                        }

                    }
                    if (value_temp != "") {
                        transp[value_temp]++;
                    }

                }
                if ((transport == "Троллейбус") && (name == "routes")) {
                    int size = value.length();
                    string value_temp;

                    for (int i = 0; i < size; ++i) {
                        char ch;
                        ch = value[i];
                        if ((ch == '.') || (ch == ',')) {
                            transp[value_temp]++;
                            value_temp = "";
                        }
                        else {
                            value_temp += ch;
                        }

                    }
                    if (value_temp != "") {
                        transp[value_temp]++;
                    }

                }

            }

        }

    }


};


int main () {
    setlocale(LC_ALL, "Russian");
    Transport t1;
    t1.routes();
    t1.print_transport();
    return 0;
}