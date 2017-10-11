// ����������� ���� ���� ifdef - ��� ����������� ����� �������� ��������, ���������� ��������� 
// �������� �� ��������� DLL. ��� ����� ������ DLL �������������� � �������������� ������� SOUNDSYSTEM_EXPORTS,
// � ��������� ������. ���� ������ �� ������ ���� ��������� � �����-���� �������
// ������������ ������ DLL. ��������� ����� ����� ������ ������, ��� �������� ����� �������� ������ ����, ����� 
// ������� SOUNDSYSTEM_API ��� ��������������� �� DLL, ����� ��� ������ DLL ����� �������,
// ������������ ������ ��������, ��� ����������������.
#ifndef SND
#define SND
#ifdef SOUNDSYSTEM_EXPORTS
#define SOUNDSYSTEM_API __declspec(dllexport)
#else
#define SOUNDSYSTEM_API __declspec(dllimport)
#endif
#include <SFML/Audio.hpp>
#include "SoundStruct.hpp"
// ���� ����� ������������� �� SoundSystem.dll
namespace SoundSystem
{
	enum State { MainMenu, Game, Settings, Pause };
	class SOUNDSYSTEM_API SoundPlayer
	{
		float volume;
		State type;
		MainMSound *MainM;
	public:
		~SoundPlayer();
		SoundPlayer();
		int Inicialize();
		int PlaySound(int id);
		int ChangeType(State type);
		int ChangeSoundState();
		int SetOnElement(bool val) { MainM->onelement = val; return 0; }
		void SetVolume(float volume); // ��������� ���������� ���������
	private:
		int InicializeMainMenu();

		int UpdateVolume(); // ���������� ��������� ��� ���� ������]
		int UpdateVolMainM();
	
	};
}
#endif