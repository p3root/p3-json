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

#include "Variant.h"


Variant::Variant()
{
    _type = VARIANT_NULL;
    _mapValue = std::map<std::string, Variant>();
    _listValue = std::vector<Variant>();
    _strValue = std::string();
    _boolValue = false;
    _doubleValue = 0.0;
    _intValue = 0;
}

Variant::Variant(const std::map<std::string, Variant> &val)
{
    _mapValue = std::map<std::string, Variant>(val);
    _type = VARIANT_MAP;
}

Variant::Variant(const std::vector<Variant> &list)
{
    _listValue = std::vector<Variant>(list);
    _type = VARIANT_LIST;
}

Variant::Variant(const std::vector<std::string> &list)
{
    _type = VARIANT_STRINGLIST;
    _strList = std::vector<std::string>(list);
}

Variant::Variant(const std::string &val)
{
    _strValue = std::string(val);
    _type = VARIANT_STRING;
}

Variant::Variant(bool b)
{
    _boolValue = b;
    _type = VARIANT_BOOL;
}

Variant::Variant(double d)
{
    _doubleValue = d;
    _type = VARIANT_DOUBLE;
}

Variant::Variant(int i)
{
    _intValue = i;
    _type = VARIANT_INT;
}
