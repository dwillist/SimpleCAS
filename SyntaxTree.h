#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_

#include <map>
#include <string>

#include "Expression.h"
#include "Rational.h"


class SyntaxTree{
private:
  Expression* root;

  /**
    @params: None
    @return: None
      operations preformed by simplify:
      - simplify each Expression recursively
      - sort operands of each Expression into canonical form
  */

  //bool simplify();

public:

  //
  // CONSTRUCTORS
  //

  SyntaxTree();
  SyntaxTree(SyntaxTree & const other); // copy constructor
  /**
    @params: string that will be parsed into expresions
    @return: none / follows c++ constructor conventions
  */
  SyntaxTree(std::string)

  //
  // DTOR
  //
  ~SyntaxTree();

  //
  // INTERFACE
  //

  std::string to_string();

  /**
    @params: a mapping of expressions so that map[exp1] will replace all occurences of expr1
    @return: boolean indicating if one or more such substitutions were preformed
  */
  bool substitue(std::map<Expression,Expression> mapping);


  /**
    @params: None
    @return: None
      operations preformed by simplify:
      - simplify each Expression recursively
      - sort operands of each Expression into canonical form
      
    TODO: make this a private method as soon as tesing is done
    @params: None
    @return
  */
  bool simplify();

};



#endif
