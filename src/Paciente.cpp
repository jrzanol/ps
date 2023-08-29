// jrzanol
// 

#include "stdafx.h"
#include "Paciente.h"

Paciente::Paciente() : Pessoa(TipoPessoa::Paciente)
{
	static int g_PacienteIdCounter = 1;
	m_PacienteId = g_PacienteIdCounter++;

	m_Idade = (rand() % 60) + 20;
	m_FreqCardiaca = (rand() % 40) + 60;
	m_FreqRespiratoria = 16;

	m_PressaoArterial = 12 / 8.f;
	m_TempCorporal = 37.f;

	m_RecebeuAlta = false;
	m_UtilizandoNebulizador = false;
	m_SendoExaminado = false;
	m_UltimaVezExaminado = 0;
}

Paciente::~Paciente()
{
}

void Paciente::Executa()
{
	do
	{
		if (m_SinalVital == 0)
			Log("Paciente %d esta com falta de ar.", m_PacienteId);

		Sleep(SLEEP_TIMER);
	} while (!m_RecebeuAlta);
}
