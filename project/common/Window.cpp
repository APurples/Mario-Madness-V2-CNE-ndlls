#if defined(HX_WINDOWS)
	void _hide_window(HWND hwnd) {
		//ShowWindow(hwnd, SW_HIDE);
		//int res = SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		//if (res)
		//	SetLayeredWindowAttributes(window, 0, 127, LWA_ALPHA);
	}
	void _show_window(HWND hwnd, bool active) {
		//ShowWindow(hwnd, active ? SW_SHOW : SW_SHOWNA);
		//SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
		//int res = SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		//if (res)
		//	SetLayeredWindowAttributes(window, 0, 255, LWA_ALPHA);
	}
	void _show_window2(HWND hwnd, bool active) {
		//ShowWindow(hwnd, active ? SW_SHOW : SW_SHOWNA);
		_show_window(hwnd, active);
		//SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
	}

	static BOOL CALLBACK enumWinProc(HWND hwnd, LPARAM lparam) {
		std::vector<std::string> *names = reinterpret_cast<std::vector<std::string> *>(lparam);
		char title_buffer[512] = {0};
		int ret = GetWindowTextA(hwnd, title_buffer, 512);
		//title blacklist: "Program Manager", "Setup"
		std::string title = std::string(title_buffer);
		printf("Hiding: %s", title.c_str());
		if (IsWindowVisible(hwnd) && ret != 0 && title != names->at(0) && title != "Program Manager" && title != "Setup") {
			_hide_window(hwnd);
			names->insert(names->begin() + 1, title);
		}
		return 1;
	}

	static value hide_windows (value _windowTitle) {
		const char* windowTitle = val_string(_windowTitle);
		std::vector<std::string> winNames = {};
		winNames.emplace_back(std::string(windowTitle));
		EnumWindows(enumWinProc, reinterpret_cast<LPARAM>(&winNames));
		_show_window(FindWindowA(NULL, windowTitle), true);

		value hxNames = alloc_array(winNames.size());
		for (int i = 1; i < winNames.size(); i++) {
			val_array_set_i(hxNames, i - 1, alloc_string(winNames[i].c_str()));
		}
		val_array_set_i(hxNames, winNames.size() - 1, alloc_string(winNames[0].c_str()));
		//Array_obj<String> *hxNames = new Array_obj<String>(winNames.size(), winNames.size());
		//for (int i = 1; i < winNames.size(); i++) {
		//	hxNames->Item(i - 1) = String(winNames[i].c_str());
		//}
		//hxNames->Item(winNames.size() - 1) = String(winNames[0].c_str());
		return hxNames;
	}
	DEFINE_PRIME1 (hide_windows);

	static value show_windows(value prevHidden) {
		int length = val_array_size(prevHidden);
		for (int i = 0; i < length; i++) {
			//HWND hwnd = FindWindowA(NULL, prevHidden->Item(i).c_str());
			HWND hwnd = FindWindowA(NULL, val_string(val_array_i(prevHidden, i)));
			if (hwnd != NULL) {
				_show_window2(hwnd, false);
				//ShowWindow(hwnd, SW_SHOWNA);
			}
		}
		return alloc_bool(true);
	}
	DEFINE_PRIME1 (show_windows);
#else
	static value hide_windows (value _windowTitle) {
		return alloc_bool(false);
	}
	DEFINE_PRIME1 (hide_windows);

	static value show_windows (value prevHidden) {
		return alloc_bool(false);
	}
	DEFINE_PRIME1 (show_windows);
#endif