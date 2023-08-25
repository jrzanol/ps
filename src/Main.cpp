// by jrzanol
// 

#include "stdafx.h"
#include "ProntoSocorro.h"
#include "Nebulizador.h"

ProntoSocorro g_PS;
pthread_t g_Thread[7];

void* NovaPessoa(void* arg)
{
	TipoPessoa tp = (TipoPessoa)(int)arg;
	Pessoa* p = NULL;

	if (tp == TipoPessoa::Paciente)
		p = new Paciente();
	else if (tp == TipoPessoa::Medico)
		p = new Medico();
	else if (tp == TipoPessoa::ChefeEnfermeiro)
		p = new ChefeEnfermeiro();
	else if (tp == TipoPessoa::Enfermeiro)
		p = new Enfermeiro();
	else if (tp == TipoPessoa::Nebulizador)
		p = new Nebulizador();

	g_PS.Chegada(p);

	if (p)
		p->Executa();

	return NULL;
}

int main(int argc, const char* argv[])
{
	srand((unsigned int)_time32(0));

	pthread_t th;

	int thc = 0;
	time_t init = time(0);
	const int MAX = 5 * 60;

	if (pthread_create(&g_Thread[thc++], NULL, NovaPessoa, (void*)TipoPessoa::Medico) != 0 ||
		pthread_create(&g_Thread[thc++], NULL, NovaPessoa, (void*)TipoPessoa::Medico) != 0 ||
		pthread_create(&g_Thread[thc++], NULL, NovaPessoa, (void*)TipoPessoa::ChefeEnfermeiro) != 0 ||
		pthread_create(&g_Thread[thc++], NULL, NovaPessoa, (void*)TipoPessoa::Enfermeiro) != 0 ||
		pthread_create(&g_Thread[thc++], NULL, NovaPessoa, (void*)TipoPessoa::Enfermeiro) ||
		pthread_create(&g_Thread[thc++], NULL, NovaPessoa, (void*)TipoPessoa::Nebulizador) ||
		pthread_create(&g_Thread[thc++], NULL, NovaPessoa, (void*)TipoPessoa::Nebulizador))
		printf("Falha ao criar as threads.\n");
	else
	{
		thc++;

		g_PS.Iniciar();

		do
		{
			if ((rand() % 100) < 2)
			{
				if (pthread_create(&th, NULL, NovaPessoa, (void*)TipoPessoa::Paciente) != 0)
					printf("Falha ao criar uma thread para um Paciente novo.\n");
			}

			Sleep(10);

		} while ((time(0) - init) < MAX);
	}

	g_PS.Fechamento();
	g_PS.Exibir();

	for (int thId = 0; thId < thc - 1; ++thId)
		pthread_join(g_Thread[thId], NULL);

	return EXIT_SUCCESS;
}

