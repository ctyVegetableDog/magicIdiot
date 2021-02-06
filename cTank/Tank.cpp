#include "Tank.h"

Tank::Tank() {}
Tank::Tank(int f_x, int f_y, int f_w, int f_h, char f_ch, int f_lf) : m_x(f_x), m_y(f_y), m_w(f_w), m_h(f_h), m_char(f_ch), m_life(f_lf) {}


void Tank::SetX(int f_x) { m_x = f_x; }
int Tank::GetX() const { return m_x; }

void Tank::SetY(int f_y) { m_y = f_y; }
int Tank::GetY() const { return m_y; }


char Tank::GetChar() const { return m_char; }

void Tank::SetLife(int f_lf) { m_life = f_lf; }
int Tank::GetLife() const {return m_life; }
