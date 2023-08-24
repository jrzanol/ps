// jrzanol
// 

#include "stdafx.h"
#include "Paciente.h"

Paciente::Paciente() : Pessoa(TipoPessoa::Paciente)
{
	static int g_PacienteIdCounter = 1;
	m_PacienteId = g_PacienteIdCounter++;

	m_Idade = 0;
	m_FreqCardiaca = 0;
	m_PressaoArterial = 0;
	m_FreqRespiratoria = 0;

	m_TempCorporal = 0.f;

	pthread_mutex_init(&m_MutexAlter, NULL);
}

Paciente::~Paciente()
{
	pthread_mutex_destroy(&m_MutexAlter);
}

void Paciente::Executa()
{
}

void Paciente::Alterar(int car, int art, int res, float cor)
{
	pthread_mutex_lock(&m_MutexAlter);

	m_FreqCardiaca = car;
	m_PressaoArterial = art;
	m_FreqRespiratoria = res;

	m_TempCorporal = cor;

	pthread_mutex_unlock(&m_MutexAlter);
}

