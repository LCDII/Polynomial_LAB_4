grammar Polynomial;

// Полином
poly
    : term (('+'|'-') term)* EOF
    ;

// Термы
term
    : coefficient? monomial?
    ;

// Коэффициент: число с optional знаком
coefficient
    : NUMBER
    | INTEGER
    ;

// Моном: набор переменных с optional степенью
monomial
    : factor+
    ;

// Фактор: переменная с optional степенью
factor
    : VARIABLE (POW exponent)?
    ;

// Степень: целое число, может быть отрицательным
exponent
    : INTEGER
    ;

// Лексемы
INTEGER  : [+-]? [0-9]+ ;
NUMBER   : [+-]? [0-9]+ ('.' [0-9]+)? ;
VARIABLE : [xyz] ;
POW      : '^' ;
WS       : [ \t\r\n]+ -> skip ;