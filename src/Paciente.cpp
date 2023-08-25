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
			printf("Paciente %d esta com falta de ar.", m_PacienteId);

		Sleep(SLEEP_TIMER);
	} while (!m_RecebeuAlta);
}
