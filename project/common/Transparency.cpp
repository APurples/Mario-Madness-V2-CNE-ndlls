#if defined(HX_WINDOWS)
	static value set_transparent (bool active, int r, int g, int b) {
		HWND hWnd = GetActiveWindow();
		int res = SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		if (res)
		{
			SetLayeredWindowAttributes(hWnd, RGB(r, g, b), active?1:0, LWA_COLORKEY);
		}
		return alloc_bool(res != 0);
	}
	DEFINE_PRIME4 (set_transparent);

	static value remove_transparent () {
		HWND hWnd = GetActiveWindow();
		int res = SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) ^ ~WS_EX_LAYERED);
		return alloc_bool(res != 0);
	}
	DEFINE_PRIME0 (remove_transparent);
#else
    static value set_transparent (bool active, int r, int g, int b) {
		return alloc_bool(false);
	}
	DEFINE_PRIME4 (set_transparent);

	static value remove_transparent () {
		return alloc_bool(false);
	}
	DEFINE_PRIME0 (remove_transparent);
#endif