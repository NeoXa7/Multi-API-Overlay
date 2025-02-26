#include "../Overlay.h"

namespace Alice::Overlay
{
	void ShowErrorBox(const std::wstring& errorMessage, const std::wstring& errorTitle)
	{
		std::thread([errorMessage, errorTitle]() {
			MessageBoxW(nullptr, errorMessage.c_str(), errorTitle.c_str(), MB_ICONERROR | MB_OK);
			}).detach();
	}

	void ShowWarningBox(const std::wstring& warningMessage, const std::wstring& warningTitle)
	{
		std::thread([warningMessage, warningTitle]() {
			MessageBoxW(nullptr, warningMessage.c_str(), warningTitle.c_str(), MB_ICONWARNING | MB_OK);
			}).detach();
	}

	void ShowMessage(const std::wstring& message, const std::wstring& messageTitle)
	{
		std::thread([message, messageTitle]() {
			MessageBoxW(nullptr, message.c_str(), messageTitle.c_str(), MB_ICONWARNING | MB_OK);
			}).detach();
	}
}