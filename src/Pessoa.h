// jrzanol
// 

#pragma once

enum class TipoPessoa
{
	Paciente = 0,
	Medico,
	ChefeEnfermeiro,
	Enfermeiro,
	Nebulizador
};

class Pessoa
{
public:
	Pessoa(TipoPessoa t) { m_Type = t; }
	~Pessoa() { }

	virtual void Executa() = 0;
	TipoPessoa Tipo() { return m_Type; }

private:
	TipoPessoa m_Type;
};

