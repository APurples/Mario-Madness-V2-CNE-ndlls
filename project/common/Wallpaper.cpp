#if defined(HX_WINDOWS)
	static value change_wallpaper(value _path)
	{
		wchar_t* wallpath = const_cast< wchar_t* >(val_wstring(_path));
		//wchar_t* wallpath = const_cast<wchar_t*>(path.wchar_str());
		SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, reinterpret_cast<void*>(wallpath), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
		return alloc_bool(true);
	}
	DEFINE_PRIME1 (change_wallpaper);

	static value get_wallpaper()
	{
		WCHAR buffer[1024] = {0};
		SystemParametersInfoW(SPI_GETDESKWALLPAPER, 256, &buffer, NULL);
		//return alloc_string(reinterpret_cast<const char*>(buffer));
		return alloc_wstring_len(buffer, wcslen(buffer));
	}
	DEFINE_PRIME0 (get_wallpaper);
#else
    static value change_wallpaper(value _path) {
		return alloc_bool(false);
	}
	DEFINE_PRIME1 (change_wallpaper);

	static value get_wallpaper() {
		return alloc_string("");
	}
	DEFINE_PRIME0 (get_wallpaper);
#endif