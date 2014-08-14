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

#include "Json.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Variant Json::parse(std::string &string)
{
    std::stringstream ss;
    ss << string;
    bool error = false;
    Variant v = parseValue(ss, error);

    if(error)
        return Variant();

    return v;

}

std::string Json::stringify(Variant &v)
{
    std::ostringstream str;

    if(v.isNull()) {
        str << "null";
        return str.str();
    }

    Variant::VariantType type = v.type();

    if(type == Variant::VARIANT_BOOL) {
        str << (v.toBool() ? "true" : "false");
        return str.str();
    }
    else if(type == Variant::VARIANT_INT) {
        str << v.toInt();
        return str.str();
    }
    else if(type == Variant::VARIANT_DOUBLE) {
        str << v.toDouble();
        return str.str();
    }
    else if(type == Variant::VARIANT_STRING) {
        str << "\"";
        str << v.toString();
         str << "\"";
        return str.str();
    }
    else if(type == Variant::VARIANT_MAP) {
        str << "{";

        VariantMap m = v.toVariantMap();
        typedef VariantMap::iterator it_type;
        for(it_type iterator = m.begin(); iterator != m.end(); iterator++) {
            // iterator->first = key
            // iterator->second = value
            // Repeat if you also want to iterate through the second map.

            str << "\"";
            str << iterator->first;
            str << "\":";
            str << stringify(iterator->second);
            str << ",";

        }
        std::string json = str.str();
        if(json.length() > 1 && m.size() > 1) {
            json = json.substr(0, json.size()-1);
        }
        std::ostringstream str2;
        str2 << json;
        str2 << "}";

        return str2.str();
    }
    else if(type == Variant::VARIANT_LIST) {
        str << "[";
        VariantList l = v.toList();

        for(VariantList::iterator it = l.begin(); it != l.end(); ++it)
        {
            str << stringify(*it);
        }

        std::string json = str.str();
        if(json.length() > 1 && l.size() > 1) {
            json = json.substr(0, json.size()-1);
        }
        std::ostringstream str2;
        str2 << json;
        str2 << "]";

        return str2.str();
    }
    else if(type == Variant::VARIANT_STRINGLIST) {
        str << "[";
        StringList l = v.toStringList();

        for(StringList::iterator it = l.begin(); it != l.end(); ++it)
        {
            str << "\"";
            str << *it;
            str << "\"";
        }

        std::string json = str.str();
        if(json.length() > 1 && l.size() > 1) {
            json = json.substr(0, json.size()-1);
        }
        std::ostringstream str2;
        str2 << json;
        str2 << "]";

        return str2.str();
    }

    return std::string();
}

Variant Json::parseValue(std::stringstream &s, bool &error)
{
    char c;

    while(!s.eof() && !error) {
        s >> std::hex >> c;

        if(c == '{') {
            return parseObject(s, error);
        }
        else if(c == '"') {
            return parseString(s, error);
        }
        else if(c == '[') {
            return parseArray(s, error);
        }
        else {
            return parseLiteral(s, error);
        }
    }

    return Variant();
}

VariantMap Json::parseObject(std::stringstream &s, bool &error)
{
    VariantMap o;
    std::string key;
    bool atVal=false;

    char c;
    while(!s.eof() &&!error) {
        s >> std::hex >> c;

        if(c == '}') {
            return o;
        }
        else if(c== ',' || c== ':') {
            //nothing to do
        }
        else if (c=='"') {
            if(atVal) {
                Variant v = Variant(parseString(s, error));
                o.insert(std::pair<std::string, Variant>(key, v));
                atVal = false;
            } else {
                key = parseString(s, error);
                atVal = true;
            }
        }
        else if (c=='[') {
            if(atVal) {
                Variant v = Variant(parseArray(s, error));
                o.insert(std::pair<std::string, Variant>(key, v));
                atVal = false;
            }
            else {
                error = true;
                return VariantMap();
            }

        }
        else if (c=='{') {
            if(atVal) {
                Variant v = Variant(parseObject(s, error));
                o.insert(std::pair<std::string, Variant>(key, v));
                atVal = false;
            }
            else {
                error = true;
                return VariantMap();
            }
        }
        else {
            if(atVal) {
                s.putback(c);
                Variant v = Variant(parseLiteral(s, error));
                o.insert(std::pair<std::string, Variant>(key, v));
                atVal = false;
            }
            else {
                error = true;
                return VariantMap();
            }

        }
    }

    error = true;
    return VariantMap();
}

std::string Json::parseString(std::stringstream &ss, bool &error)
{
    std::ostringstream str;
    char c;

    while(!ss.eof() && !error) {
        ss >> std::hex >> c;

        if(c == '"') {
            return str.str();
        }
        else if(c == '\\') {
            ss >> std::hex >> c;
            if(c=='b') {
                str << '\b';
            } else if(c=='f') {
                str << '\f';
            } else if(c=='n') {
                str << '\n';
            } else if(c=='r') {
                str << '\r';
            } else if(c=='t') {
                str << '\t';
            } else if(c=='u') {
                char buf[4];
                ss.read(buf, 4);
                str << strtoul(buf, NULL, 16);

            } else {
                str << c;
            }
        } else {
            str << c;
        }
    }
    error = true;
    return std::string();
}

VariantList Json::parseArray(std::stringstream &ss, bool &error)
{
    VariantList l;
    char c;

    while(!ss.eof() && !error) {
        ss >> std::hex >> c;
        if (c==']') {
            return l;
        } else if (c==',') {
        } else if (c=='"') {
            Variant v = Variant(parseString(ss, error));
            l.push_back(v);
        } else if (c=='[') {
            Variant v = Variant(parseArray(ss, error));
            l.push_back(v);
        } else if (c=='{') {
            Variant v = Variant(parseObject(ss, error));
            l.push_back(v);
        } else {
            Variant v = Variant(parseLiteral(ss, error));
            l.push_back(v);
        }
    }

    error = true;
    return VariantList();
}

Variant Json::parseLiteral(std::stringstream &s, bool &error)
{

    char c;
    while(!s.eof() && !error) {
        s >> std::hex >> c;
        if (c=='t') {
            s >> std::hex >> c;//r
            s >> std::hex >> c;//u
            s >> std::hex >> c;//e
            Variant v = Variant(true);
            return v;
        } else if (c=='f') {
            s >> std::hex >> c;//a
            s >> std::hex >> c;//l
            s >> std::hex >> c;//s
            s >> std::hex >> c;//e
            Variant v = Variant(false);
            return v;
        } else if (c=='n') {
            s >> std::hex >> c;//u
            s >> std::hex >> c;//l
            s >> std::hex >> c;//l
            return Variant();
        }
        else if (c == '-' || isdigit(c)) {
             std::ostringstream str;

            while((isdigit(c) || (c == '.') || (c == 'E') || (c == 'e') || (c == '-') || (c == '+'))) {
                str << c;
                if(s.eof() || error) {
                    break;
                }
                s >> std::hex >> c;
            }
            s.putback(c);
            std::string val = str.str();
            if(val.find('.') != std::string::npos) {
                Variant v = Variant(atof(val.c_str()));
                return v;
            }
            else {
                Variant v = Variant(atoi(val.c_str()));
                return v;
            }
        }
    }

    error = true;
    return Variant();
}
