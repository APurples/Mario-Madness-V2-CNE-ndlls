#if defined(HX_WINDOWS)
	static value hide_taskbar () {
		HWND taskbar = FindWindowW(L"Shell_TrayWnd", NULL);
		if (!taskbar) {
			std::cout << "Finding taskbar failed with error: " << GetLastError() << std::endl;
			return alloc_bool(false);
		}
		bool taskbarVisible = IsWindowVisible(taskbar);
		ShowWindow(taskbar, SW_HIDE);
		return alloc_bool(taskbarVisible);
	}
	DEFINE_PRIME0 (hide_taskbar);

	static value show_taskbar() {
		HWND taskbar = FindWindowW(L"Shell_TrayWnd", NULL);
		if (!taskbar) {
			std::cout << "Finding taskbar failed with error: " << GetLastError() << std::endl;
			return alloc_bool(false);
		}
		ShowWindow(taskbar, SW_SHOWNOACTIVATE);
		return alloc_bool(true);
	}
	DEFINE_PRIME0 (show_taskbar);
#else
    static value hide_taskbar () {
		return alloc_bool(false);
	}
	DEFINE_PRIME0 (hide_taskbar);

	static value show_taskbar () {
		return alloc_bool(false);
	}
	DEFINE_PRIME0 (show_taskbar);
#endif