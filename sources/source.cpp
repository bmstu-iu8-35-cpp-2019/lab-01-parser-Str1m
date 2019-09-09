// Copyright 2019 Sabitov Egor <q.st.stream@gmail.com>

#include <header.hpp>

Json::Json() {}

Json::Json(const std::string &s) {
    size_t i = 0;
    std::string key;
    std::any value;
    while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
        i++;
    if (s[i] == '{') {
        i++;
        while (s[i] != '}') {
            while (s[i] != '"') //{
                i++;
            if (s[i] == '"') {//  Первая кавычка
                i++;
                std::string buf = "";
                //size_t j = 0;
                while (s[i] != '"') {
                    buf += s[i];
                    i++;
                    //j++;
                }
                key = buf;
            }
            while (s[i] != ':')
                i++;
            i++;
            while ((s[i] == ' ') || (s[i] == '\n'))
                i++;
            if (s[i] == '"') {//  Первая кавычка
                i++;
                std::string buf;
                while (s[i] != '"') {
                    //size_t j = 0;
                    //buf[j] = s[i];
                    buf += s[i];
                    i++;
                    //j++;
                }
                value = buf;
                i++;
            } else if (s[i] == '[') {
                size_t ch = 1;
                size_t fl = 1;
                while (fl > 0) {
                    if (s[i + ch] == '[')
                        fl++;
                    if (s[i + ch] == ']')
                        fl--;
                    ch++;
                }
                value = Json(s.substr(i, ch));
                i += ch;
            } else if (s[i] == '{') {
                size_t ch = 1;
                size_t fl = 1;
                while (fl > 0) {
                    if (s[i + ch] == '{')
                        fl++;
                    if (s[i + ch] == '}')
                        fl--;
                    ch++;
                }
                value = Json(s.substr(i, ch));
                i += ch;
            } else if (s[i] >= '0' && s[i] <= '9') {
                bool zn = 0;
                int i1 = 0;
                double d1 = 0;
                if (s[i] == '-') {
                    zn = 1;
                    i++;
                }
                while (s[i] >= '0' && s[i] <= '9') {
                    i1 = 10 * i1 + (s[i] - 48);
                    i++;
                }
                if (s[i] == '.') {
                    int chet = -1;
                    i++;
                    while (s[i] >= '0' && s[i] <= '9') {
                        d1 += (s[i] - 48) / pow(10, chet);
                        i++;
                        chet--;
                    }
                    d1 += i1;
                    if (zn == 1) {
                        d1 = -d1;
                        value = d1;
                    } else {
                        value = d1;
                    }
                }
                if (d1 == 0) {
                    if (zn == 1) {
                        value = -i1;
                        i++;
                    } else {
                        value = i1;
                        i++;
                    }
                }
            } else if (s[i] == 'f' || s[i] == 't' || s[i] == 'n') {
                if (s.substr(i, 5) == "false") {
                    bool fl = false;
                    value = fl;
                    i += 5;
                } else if (s.substr(i, 4) == "true") {
                    bool fl = true;
                    value = fl;
                    i += 4;
                } else if (s.substr(i, 4) == "null") {
                    i += 4;
                } else {
                    throw std::invalid_argument("Wrong word!");
                }
            }
            m1.insert(std::make_pair(key, value));
            //}
        }
    } else if (s[i] == '[') {
        i++;
        while (1) {
            while (s[i] == ' ' || s[i] == '\n')
                i++;
            std::any val;
            bool zn = 0;
            int i1 = 0;
            double d1 = 0;
            if (s[i] == '-') {
                zn = 1;
                i++;
            }
            while (s[i] >= '0' && s[i] <= '9') {
                i1 = 10 * i1 + s[i] - 48;
                i++;
            }
            if (s[i] == '.') {
                int chet = -1;
                i++;
                while (s[i] >= '0' && s[i] <= '9') {
                    d1 += (s[i] - 48) / pow(10, chet);
                    i++;
                    chet--;
                }
                d1 += i1;
                if (zn == 1) {
                    d1 = -d1;
                    val = d1;
                } else {
                    val = d1;
                }
            }
            if (d1 == 0) {
                if (zn == 1)
                    val = -i1;
                else
                    //std::cout << i1<<std::endl;
                    val = i1;
            }
            if (s[i] == '"') {
                std::string buf;
                while (s[i] != '"') {
                    //size_t k = 0;
                    buf += s[i];
                    i++;
                    //k++;
                }
                val = buf;
            } else if (s[i] == 'f' || s[i] == 't' || s[i] == 'n') {
                if (s.substr(i, 5) == "false") {
                    bool fl = false;
                    val = fl;
                    i += 5;
                } else if (s.substr(i, 4) == "true") {
                    bool fl = true;
                    val = fl;
                    i += 4;
                } else if (s.substr(i, 4) == "null") {
                    i += 4;
                } else {
                    throw std::invalid_argument("Wrong word!");
                }
            } else if (s[i] == '{') {
                size_t ch = 1;
                size_t fl = 1;
                while (fl > 0) {
                    if (s[i + ch] == '{')
                        fl++;
                    if (s[i + ch] == '}')
                        fl--;
                    ch++;
                }
                val = Json(s.substr(i, ch));
                i += ch;
            } else if (s[i] == '[') {
                size_t ch = 1;
                size_t fl = 1;
                while (fl > 0) {
                    if (s[i + ch] == '[')
                        fl++;
                    if (s[i + ch] == ']')
                        fl--;
                    ch++;
                }
                value = Json(s.substr(i, ch));
                i += ch;
            }
            v1.push_back(val);
            //////
            if (s[i] == ',') {
                i++;
                continue;
            } else if (s[i] == ']') {
                i++;
                break;
            } else {
                throw std::invalid_argument("Wrong word!");
            }
        }
        //m1.insert(std::make_pair(key, value));
    } else {
        throw std::invalid_argument("Error!!!");
    }
}

bool Json::is_array() const {
    if (v1.empty()) return false;
    else
        return true;
}

bool Json::is_object() const {
    if (v1.empty()) return true;
    else
        return false;
}

std::any& Json::operator[](const std::string& key) {
    if (is_array() == false)
        return m1[key];
    else
        throw std::logic_error("Not Array!");
}

std::any & Json::operator[](int index) {
    if (is_array()) return v1[index];
    else
        throw std::logic_error("Not Array!");
}
Json Json::parse(const std::string &s) { return Json(s);}

Json Json::parseFile(const std::string &path_to_file) {
    std::ifstream f(path_to_file);
    std::string st1;
    if (!f) {
        std::cout << "File not found" << std::endl;
    } else {
        while (f) {
            getline(f, st1);
        }
    }
    f.close();
    return Json(st1);
}
