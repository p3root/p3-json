/*
 *  Copyright (c) 2014, p3root - Patrik Pfaffenbauer (patrik.pfaffenbauer@p3.co.at)
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 *
 *    Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright notice, this
 *    list of conditions and the following disclaimer in the documentation and/or
 *    other materials provided with the distribution.
 *
 *    Neither the name of the {organization} nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef VARIANT_H
#define VARIANT_H

#include <map>
#include <string>
#include <vector>

class Variant
{
public:
    enum VariantType {
        VARIANT_NULL,
        VARIANT_MAP,
        VARIANT_LIST,
        VARIANT_INT,
        VARIANT_STRING,
        VARIANT_DOUBLE,
        VARIANT_BOOL,
        VARIANT_STRINGLIST
    };

public:
    Variant();
    Variant(const std::map<std::string, Variant> &val);
    Variant(const std::vector<Variant> &list);
    Variant(const std::vector<std::string> &list);
    Variant(const std::string &val);
    Variant(bool b);
    Variant(double d);
    Variant(int i);

    bool isNull() { return _type == VARIANT_NULL; }
    bool isBool() { return _type == VARIANT_BOOL; }
    bool isInt() { return _type == VARIANT_INT; }
    bool isDouble() { return _type == VARIANT_DOUBLE; }
    bool isMap() { return _type == VARIANT_MAP; }
    bool isList() { return _type == VARIANT_LIST; }
    bool isString() { return _type == VARIANT_STRING; }
    bool isStringList() { return _type == VARIANT_STRINGLIST; }

    VariantType type() { return _type; }

    bool toBool() { return _boolValue; }
    int toInt() { return _intValue; }
    double toDouble() { return _doubleValue; }
    std::map<std::string, Variant> toVariantMap() { return _mapValue; }
    std::vector<Variant> toList() { return _listValue; }
    std::vector<std::string> toStringList() { return _strList; }
    std::string toString() { return _strValue; }

    template<typename T>
    static inline Variant fromValue(const T &value) { return Variant(value); }

private:
    VariantType _type;

    std::map<std::string, Variant>  _mapValue;
    std::vector<std::string> _strList;
    std::vector<Variant> _listValue;
    std::string _strValue;
    bool _boolValue;
    double _doubleValue;
    int _intValue;

};

typedef std::map<std::string, Variant> VariantMap;
typedef std::vector<Variant> VariantList;
typedef std::vector<std::string> StringList;

#endif // VARIANT_H
