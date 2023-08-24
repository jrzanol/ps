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
	void Alterar(int, int, int, float);

	int m_PacienteId;
	int m_Idade;

	int GetFreqCardiaca() const { return m_FreqCardiaca; }
	int GetPressaoArterial() const { return m_PressaoArterial; }
	int GetFreqRespiratoria() const { return m_FreqRespiratoria; }
	float GetTempCorporal() const { return m_TempCorporal; }

private:
	int m_FreqCardiaca;
	int m_PressaoArterial;
	int m_FreqRespiratoria;

	float m_TempCorporal;

	pthread_mutex_t m_MutexAlter;
};

