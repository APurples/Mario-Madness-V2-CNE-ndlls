#if defined(HX_WINDOWS)
	static value hide_window_icon () {
		HWND window = GetActiveWindow();
		// Remove the WS_SYSMENU style
		SetWindowLongPtr(window, GWL_STYLE, GetWindowLongPtr(window, GWL_STYLE) & ~WS_SYSMENU);

		// Force the window to redraw
		SetWindowPos(window, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		return alloc_bool(true);
	}
	DEFINE_PRIME0 (hide_window_icon);

	// Custom
	static value show_window_icon () {
		HWND window = GetActiveWindow();
		// Add the WS_SYSMENU style
		SetWindowLongPtr(window, GWL_STYLE, GetWindowLongPtr(window, GWL_STYLE) | WS_SYSMENU);

		// Force the window to redraw
		SetWindowPos(window, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER);
		return alloc_bool(true);
	}
	DEFINE_PRIME0 (show_window_icon);
#else
	static value hide_window_icon () {
		return alloc_bool(false);
	}
	DEFINE_PRIME0 (hide_window_icon);

	static value show_window_icon () {
		return alloc_bool(false);
	}
	DEFINE_PRIME0 (show_window_icon);
#endif