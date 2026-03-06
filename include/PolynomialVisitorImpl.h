#pragma once

#include "PolynomialBaseVisitor.h"
#include "Polynomial.h"
#include <any>

class PolynomialVisitorImpl : public PolynomialBaseVisitor
{
public:

    // visitTerm создаёт Monom и возвращает его через std::any
    std::any visitTerm(PolynomialParser::TermContext* ctx) override;

    // visitPoly обходится по всем термам и добавляет их через + или -
    std::any visitPoly(PolynomialParser::PolyContext* ctx) override;
};
