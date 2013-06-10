#ifndef SYMBOL_HH
#define SYMBOL_HH

/*
  Definicja typu wyliczeniowego "Symbol" dla symboli  a, b, c, d, e.
*/
enum Symbol { e, a, b, c, d };



Symbol operator - (Symbol , Symbol );
Symbol operator + (Symbol , Symbol );
Symbol operator * (Symbol , Symbol );
Symbol operator / (Symbol , Symbol );
std::ostream &  operator << (std::ostream &  , Symbol );
std::istream &  operator >> (std::istream &  , Symbol &);
#endif
