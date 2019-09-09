// Copyright 2018 Sabitov Egor <q.st.stream@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <iostream>
#include <any>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cmath>

class Json {
private:
    std::map<std::string, std::any> m1;
    std::vector<std::any> v1;

public:
    explicit Json(const std::string& s);

    bool is_array() const;

    bool is_object() const;

    std::any& operator[](const std::string& key);

    std::any& operator[](int index);

    static Json parse(const std::string& s);

    static Json parseFile(const std::string& path_to_file);
};

#endif // INCLUDE_HEADER_HPP_
