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
            while (s[i] != '"') {
                i++;
                if (s[i] == '}') return;
            }
            if (s[i] == '"') {//  Первая кавычка
                auto p = words(s, i);
                key = p.first;
                i = p.second;
            }
            while (s[i] != ':')
                i++;
            i++;
            while ((s[i] == ' ') || (s[i] == '\n'))
                i++;
            if (s[i] == '"') {//  Первая кавычка
                auto p = words(s, i);
                value = p.first;
                i = p.second;
                i++;
            } else if (s[i] == '[') {
                auto p = scob_qv(s, i);
                value = p.first;
                i = p.second;
            } else if (s[i] == '{') {
                auto p = scob_syst(s, i);
                value = p.first;
                i = p.second;
            } else if (s[i] >= '0' && s[i] <= '9') {
                auto p = nums(s, i);
                value = p.first;
                i = p.second;
            } else if (s[i] == 'f' || s[i] == 't' || s[i] == 'n') {
                auto p = this->bool_word(s, i);
                value = p.first;
                i = p.second;
            }
            m1.insert(std::make_pair(key, value));
        }
    } else if (s[i] == '[') {
        i++;
        while (1) {
            while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
                i++;
            std::any val;
            auto p = nums(s, i);
            val = p.first;
            i = p.second;
            if (s[i] == '"') {
                std::string buf;
                while (s[i] != '"') {
                    buf += s[i];
                    i++;
                }
                val = buf;
            } else if (s[i] == 'f' || s[i] == 't' || s[i] == 'n') {
                p = this->bool_word(s, i);
                val = p.first;
                i = p.second;
            } else if (s[i] == '{') {
                p = scob_syst(s, i);
                val = p.first;
                i = p.second;
            } else if (s[i] == '[') {
                p = scob_qv(s, i);
                val = p.first;
                i = p.second;
            }
            v1.push_back(val);
            if (s[i] == ',' || s[i] == '\n') {
                i++;
                continue;
            } else if (s[i] == ']') {
                i++;
                break;
            } else {
                throw std::invalid_argument("Wrong word!");
            }
        }
    } else {
        throw std::invalid_argument("Error!!!");
    }
}

std::pair<std::string, size_t> Json::words(const std::string &s, size_t pos) {
    std::string key;
    pos++;
    std::string buf = "";
    while (s[pos] != '"') {
        buf += s[pos];
        pos++;
    }
    key = buf;
    return std::make_pair(key, pos);
}

std::pair<std::any, size_t> Json::nums(const std::string &s, size_t pos) {
    std::any val;
    bool zn = 0;
    int i1 = 0;
    double d1 = 0;
    if (s[pos] == '-') {
        zn = 1;
        pos++;
    }
    while (s[pos] >= '0' && s[pos] <= '9') {
        i1 = 10 * i1 + (s[pos] - 48);
        pos++;
    }
    if (s[pos] == '.') {
        int chet = -1;
        pos++;
        while (s[pos] >= '0' && s[pos] <= '9') {
            d1 += (s[pos] - 48) / pow(10, chet);
            pos++;
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
        if (zn == 1) {
            val = -i1;
        } else {
            val = i1;
        }
    }
    return std::make_pair(val, pos);
}


std::pair<std::any, size_t> Json::scob_qv(const std::string &s, size_t pos) {
    std::any val;
    size_t ch = 1;
    size_t fl = 1;
    while (fl > 0) {
        if (s[pos + ch] == '[')
            fl++;
        if (s[pos + ch] == ']')
            fl--;
        ch++;
    }
    val = Json(s.substr(pos, ch));
    pos += ch;
    return std::make_pair(val, pos);
}

std::pair<std::any, size_t> Json::scob_syst(const std::string &s, size_t pos) {
    std::any val;
    size_t ch = 1;
    size_t fl = 1;
    while (fl > 0) {
        if (s[pos + ch] == '{')
            fl++;
        if (s[pos + ch] == '}')
            fl--;
        ch++;
    }
    val = Json(s.substr(pos, ch));
    pos += ch;
    return std::make_pair(val, pos);
}

std::pair<std::any, size_t> Json::bool_word(const std::string &s, size_t pos) {
    std::any val;
    if (s.substr(pos, 5) == "false") {
        bool fl = false;
        val = fl;
        pos += 5;
    } else if (s.substr(pos, 4) == "true") {
        bool fl = true;
        val = fl;
        pos += 4;
    } else if (s.substr(pos, 4) == "null") {
        pos += 4;
    } else {
        throw std::invalid_argument("Wrong word!");
    }
    return std::make_pair(val, pos);
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

std::any &Json::operator[](const std::string &key) {
    if (is_array() == false)
        return m1[key];
    else
        throw std::logic_error("Not Array!");
}

std::any &Json::operator[](int index) {
    if (is_array()) return v1[index];
    else
        throw std::logic_error("Not Array!");
}

Json Json::parse(const std::string &s) { return Json(s); }

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
