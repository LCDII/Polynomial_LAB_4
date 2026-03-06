#include "PolynomialVisitorImpl.h"


std::any PolynomialVisitorImpl::visitTerm(PolynomialParser::TermContext* ctx){
    double coeff = 1.0;
    int x = 0, y = 0, z = 0;

    if (ctx->coefficient()) {
        std::string text = ctx->coefficient()->getText();
        coeff = std::stod(text);
    }

    if (ctx->monomial()) {
        for (auto factorCtx : ctx->monomial()->factor()) {
            char var = factorCtx->VARIABLE()->getText()[0];
            int power = 1;

            if (factorCtx->POW()) {
                power = std::stoi(factorCtx->INTEGER()->getText());
                if (factorCtx->SIGN() && factorCtx->SIGN()->getText() == "-") {
                    power = -power;
                }
            }

            switch (var) {
            case 'x': x = power; break;
            case 'y': y = power; break;
            case 'z': z = power; break;
            }
        }
    }

    return Monom(coeff, x, y, z); // возвращаем через std::any
}


// visitPoly обходится по всем термам и добавляет их через + или -
std::any PolynomialVisitorImpl::visitPoly(PolynomialParser::PolyContext* ctx) {
    if (ctx->term().empty()) return result;

    // Первый терм
    std::any firstAny = visit(ctx->term(0));
    Monom firstMonom = std::any_cast<Monom>(firstAny);
    result = result + firstMonom;

    // Последующие термы
    for (size_t i = 1; i < ctx->term().size(); ++i) {
        std::any termAny = visit(ctx->term(i));
        Monom m = std::any_cast<Monom>(termAny);

        if (ctx->MINUS(i - 1)) {
            result = result - m; // используем перегруженный оператор -
        }
        else {
            result = result + m; // используем перегруженный оператор +
        }
    }

    return result;
}
