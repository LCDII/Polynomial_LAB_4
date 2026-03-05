grammar Polynomial;

poly : signedTerm ((PLUS | MINUS) term)* EOF ;

signedTerm : MINUS? term ;

term
    : coefficient? monomial
    | coefficient
    ;

coefficient : NUMBER ;

monomial : factor+ ;

factor : VARIABLE (POW INTEGER)? ;

PLUS  : '+';
MINUS : '-';
POW   : '^';

VARIABLE : [xyz];

INTEGER : [0-9]+;

NUMBER
    : [0-9]+ '.' [0-9]*
    | '.' [0-9]+
    | [0-9]+
    ;

WS : [ \t\r\n]+ -> skip;