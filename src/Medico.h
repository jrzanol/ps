// jrzanol
// 

#pragma once
#include "Pessoa.h"

class Medico : public Pessoa
{
public:
	Medico();
	~Medico();

	void Executa();
	bool Waiting;
};

