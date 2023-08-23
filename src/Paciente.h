// by jrzanol
// 

#pragma once

#include "Pessoa.h"

class Paciente : public Pessoa
{
public:
	Paciente(int pacId) : Pessoa(TipoPessoa::Paciente) { m_PacienteId = pacId; }
	~Paciente() { }

	void Executa() { }

private:
	int m_PacienteId;
};