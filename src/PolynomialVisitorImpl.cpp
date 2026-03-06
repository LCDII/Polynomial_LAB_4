#include "PolynomialVisitorImpl.h"


std::any PolynomialVisitorImpl::visitTerm(PolynomialParser::TermContext* ctx) {
    double coeff = 1.0;
    int x = 0, y = 0, z = 0;

    // 1️⃣ Коэффициент
    if (ctx->coefficient()) {
        coeff = std::stod(ctx->coefficient()->getText());
    }

    // 2️⃣ Моном
    if (ctx->monomial()) {
        for (auto factorCtx : ctx->monomial()->factor()) {
            char var = factorCtx->VARIABLE()->getText()[0];
            int power = 1;

            if (factorCtx->POW() && factorCtx->exponent()) {
                power = std::stoi(factorCtx->exponent()->getText());
            }

            switch (var) {
            case 'x': x = power; break;
            case 'y': y = power; break;
            case 'z': z = power; break;
            }
        }
    }

   

    return Monom(coeff, x, y, z);
}


// visitPoly обходится по всем термам и добавляет их через + или -
std::any PolynomialVisitorImpl::visitPoly(PolynomialParser::PolyContext* ctx) {
    Polynomial result;

    for (size_t i = 0; i < ctx->term().size(); ++i) {
        Monom m = std::any_cast<Monom>(visit(ctx->term(i)));

        // 1️⃣ Определяем знак перед термом
        bool isMinus = false;
        if (i > 0) { // первый терм всегда с плюсом
            // В дереве parse дерева между термами стоят токены '+' или '-'
            // Обычно они на позиции 2*i-1
            auto signToken = ctx->children[2 * i - 1]->getText();
            if (signToken == "-") {
                isMinus = true;
            }
        }

        // 2️⃣ Складываем или вычитаем моном в полином
        if (isMinus) {
            // вычитаем моном
            result = result - m;
        }
        else
        {
            result = result + m;
        }
    }

    return result;
}
