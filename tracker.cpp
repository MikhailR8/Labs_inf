#include <iostream>
#include <map>
#include <vector>

//Находим локацию элемента по времени и id
int find_location(std::string id, int time, std::map<std::string, std::map<int, std::string>>& data) {
    auto locs = data[id];
    if (locs.begin() == locs.end()) { //Если не было информации об объекте
        std::cout << "no data" << std::endl;
        return 0;
    }
    auto bound = locs.upper_bound(time); 
    if (bound == locs.begin()) { //Если все данные об объекте позже искомого времени
        std::cout << "no data" << std::endl;
        return 1;
    }
    else {
        std::cout << std::prev(bound)->second << std::endl; 
        return 2;
    }
}

void find_objects_in_loc(std::string loc, int time, std::map<std::string, std::map<int, std::string>>& data) {
    auto info = 0; //Если 0, то инфы об объекте нет совсем,
    //1 - значит есть информация, но пусто, 2 - выводим объекты
    for (auto it = data.begin(); it != data.end(); it++) {
        //Проверяем, есть ли упоминание об объекте
        auto iterator = std::find_if(std::begin(it->second), std::end(it->second),
            [loc](auto p) { return p.second == loc; });
        if (iterator != it->second.end()) {
            info = 1;
        }
        //Находим верхнюю границу времени
        auto bound = it->second.upper_bound(time);
        if (bound == it->second.begin()) {
            continue;
        }
        else {
            if (std::prev(bound)->second == loc) {
                std::cout << it->first << " ";
                info = 2;
            }
        }
    }
    if (info == 0) {
        std::cout << "no data" << std::endl;
    } 
    else {
        std::cout << std::endl;
    }
}


int main() {
    std::map<std::string, std::map<int, std::string>> data;

    int N;
    std::cin >> N;
    std::string id, loc;
    int time;
    for (auto i = 0; i < N; i++) {
        std::cin >> id >> loc >> time;
        data[id][time] = loc;
    }

    std::cin >> N;
    std::string key, second;
    std::vector<std::pair<int, std::pair<std::string, int>>> requests;
    for (auto i = 0; i < N; i++) {
        std::cin >> key >> second >> time;
        if (key == "object") {
            requests.push_back({ 1, { second, time } });
        }
        else {
            requests.push_back({ 2, { second, time } });
        }
    }
    for (auto req : requests) {
        if (req.first == 1) {
            find_location(req.second.first, req.second.second, data);
        }
        else {
            find_objects_in_loc(req.second.first, req.second.second, data);
        }
    }
    return 0;
}
