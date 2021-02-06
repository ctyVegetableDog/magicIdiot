#ifndef _TANK_H_
#define _TANK_H_

class Tank {
    public:
	Tank();
	Tank(int f_x, int f_y, int f_w, int f_h, char f_ch, int f_lf);
	void SetX(int f_x);
	int GetX() const;

	void SetY(int f_y);
	int GetY() const;

	char GetChar() const;

	void SetLife(int f_lf);
	int GetLife() const;
    private:
	int m_x, m_y, m_w, m_h;		// Position and size
	char m_char;	//what character represents the entity
	int m_life;	//Entity's HP
	
	
};

#endif
