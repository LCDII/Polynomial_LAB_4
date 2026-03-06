grammar Polynomial;

poly
    : term ((PLUS | MINUS) term)* EOF
    ;

term
    : coefficient? monomial
    | coefficient
    ;

coefficient
    : SIGN? NUMBER
    ;

monomial
    : factor+
    ;

factor
    : VARIABLE (POW SIGN? INTEGER)?
    ;

SIGN : '+' | '-';

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