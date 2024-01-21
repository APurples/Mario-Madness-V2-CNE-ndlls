#if defined(HX_WINDOWS)
	static BOOL CALLBACK enumWinProc(HWND hwnd, LPARAM lparam) {
		std::vector<std::string> *names = reinterpret_cast<std::vector<std::string> *>(lparam);
		char title_buffer[512] = {0};
		int ret = GetWindowTextA(hwnd, title_buffer, 512);
		//title blacklist: "Program Manager", "Setup"
		if (IsWindowVisible(hwnd) && ret != 0 && std::string(title_buffer) != names->at(0) && std::string(title_buffer) != "Program Manager" && std::string(title_buffer) != "Setup") {
			ShowWindow(hwnd, SW_HIDE);
			names->insert(names->begin() + 1, std::string(title_buffer));
		}
		return 1;
	}

	static value hide_windows (value _windowTitle) {
		const char* windowTitle = val_string(_windowTitle);
		std::vector<std::string> winNames = {};
		winNames.emplace_back(std::string(windowTitle));
		EnumWindows(enumWinProc, reinterpret_cast<LPARAM>(&winNames));
		ShowWindow(FindWindowA(NULL, windowTitle), SW_SHOW);

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
				ShowWindow(hwnd, SW_SHOWNA);
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