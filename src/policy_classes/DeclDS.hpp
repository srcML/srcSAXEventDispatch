/**
 * @file DeclTypePolicy.hpp
 *
 * @copyright Copyright (C) 2013-2014 SDML (www.srcML.org)
 *
 * The srcML Toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML Toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef INCLUDED_DECL_DS_HPP
#define INCLUDED_DECL_DS_HPP

struct DeclData{
    DeclData(): linenumber{0}, isConst{false}, isConstAlias{false}, isAliasToConst{false}, isReference{false}, 
                isPointer{false}, isStatic{false}, isClassMember{false}, usesSubscript{false}{}
    void clear(){
        linenumber = -1;
        isConst = false;
        isStatic = false;
        isPointer = false;
        nameOfType.clear();
        namespaces.clear();
        isReference = false;
        isClassMember = false;
        usesSubscript = false;
        sLexicalCategory.clear();
        nameOfIdentifier.clear();
    }
    int linenumber;
    
    bool isConst;
    bool isStatic;
    bool isPointer;
    bool isReference;
    bool isConstAlias;
    bool isClassMember;
    bool usesSubscript;
    bool isAliasToConst;
    
    std::string nameOfType;
    std::string sLexicalCategory;
    std::string nameOfIdentifier;
    std::string nameOfContainingFile;
    std::string nameOfContainingFunction;

    std::vector<std::string> namespaces;
};

#endif