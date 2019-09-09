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
    // Конструктор из строки, содержащей Json-данные.
    explicit Json(const std::string& s);
    
    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array() const;
    // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object() const;
    
    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    std::any& operator[](const std::string& key);
    
    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    std::any& operator[](int index);
    
    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string& s);
    
    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const std::string& path_to_file);
};

#endif // INCLUDE_HEADER_HPP_
