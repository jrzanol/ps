// jrzanol
// 

#pragma once
#include "Paciente.h"

class Nebulizador : public Pessoa
{
public:
	Nebulizador();
	~Nebulizador();

	void Executa();
	void TrocaPaciente(Paciente*);

	bool m_SendoUtilizado;

private:
	Paciente* m_Utilizador;

	pthread_mutex_t m_MutexPac;
};

