// by jrzanol
// 

#pragma once
#include "Pessoa.h"

class Paciente : public Pessoa
{
public:
	Paciente();
	~Paciente();

	void Executa();

	int m_PacienteId;
	int m_Idade;

	bool m_RecebeuAlta;
	bool m_UtilizandoNebulizador;
	bool m_SendoExaminado;
	long m_UltimaVezExaminado;

	int m_SinalVital;
	int m_FreqCardiaca;
	int m_FreqRespiratoria;

	float m_PressaoArterial;
	float m_TempCorporal;
};

