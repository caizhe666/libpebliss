#include "file_version_info.h"
#include "pe_structures.h"

namespace pe_bliss
{
	using namespace pe_win;

	//Default const noexceptructor
	file_version_info::file_version_info() noexcept
		:file_version_ms_(0), file_version_ls_(0),
		product_version_ms_(0), product_version_ls_(0),
		file_flags_(0),
		file_os_(0),
		file_type_(0), file_subtype_(0),
		file_date_ms_(0), file_date_ls_(0)
	{}

	//Constructor from Windows fixed version info structure
	file_version_info::file_version_info(const vs_fixedfileinfo& info) noexcept
		:file_version_ms_(info.dwFileVersionMS), file_version_ls_(info.dwFileVersionLS),
		product_version_ms_(info.dwProductVersionMS), product_version_ls_(info.dwProductVersionLS),
		file_flags_(info.dwFileFlags),
		file_os_(info.dwFileOS),
		file_type_(info.dwFileType), file_subtype_(info.dwFileSubtype),
		file_date_ms_(info.dwFileDateMS), file_date_ls_(info.dwFileDateLS)
	{}

	//Returns true if file is debug-built
	bool file_version_info::is_debug() const noexcept
	{
		return file_flags_ & vs_ff_debug ? true : false;
	}

	//Returns true if file is release-built
	bool file_version_info::is_prerelease() const noexcept
	{
		return file_flags_ & vs_ff_prerelease ? true : false;
	}

	//Returns true if file is patched
	bool file_version_info::is_patched() const noexcept
	{
		return file_flags_ & vs_ff_patched ? true : false;
	}

	//Returns true if private build
	bool file_version_info::is_private_build() const noexcept
	{
		return file_flags_ & vs_ff_privatebuild ? true : false;
	}

	//Returns true if special build
	bool file_version_info::is_special_build() const noexcept
	{
		return file_flags_ & vs_ff_specialbuild ? true : false;
	}

	//Returns true if info inferred
	bool file_version_info::is_info_inferred() const noexcept
	{
		return file_flags_ & vs_ff_infoinferred ? true : false;
	}

	//Retuens file flags (raw DWORD)
	uint32_t file_version_info::get_file_flags() const noexcept
	{
		return file_flags_;
	}

	//Returns file version most significant DWORD
	uint32_t file_version_info::get_file_version_ms() const noexcept
	{
		return file_version_ms_;
	}

	//Returns file version least significant DWORD
	uint32_t file_version_info::get_file_version_ls() const noexcept
	{
		return file_version_ls_;
	}

	//Returns product version most significant DWORD
	uint32_t file_version_info::get_product_version_ms() const noexcept
	{
		return product_version_ms_;
	}

	//Returns product version least significant DWORD
	uint32_t file_version_info::get_product_version_ls() const noexcept
	{
		return product_version_ls_;
	}

	//Returns file OS type (raw DWORD)
	uint32_t file_version_info::get_file_os_raw() const noexcept
	{
		return file_os_;
	}

	//Returns file OS type
	file_version_info::file_os_type file_version_info::get_file_os() const noexcept
	{
		//Determine file operation system type
		switch (file_os_)
		{
		case vos_dos:
			return file_os_dos;

		case vos_os216:
			return file_os_os216;

		case vos_os232:
			return file_os_os232;

		case vos_nt:
			return file_os_nt;

		case vos_wince:
			return file_os_wince;

		case vos__windows16:
			return file_os_win16;

		case vos__pm16:
			return file_os_pm16;

		case vos__pm32:
			return file_os_pm32;

		case vos__windows32:
			return file_os_win32;

		case vos_dos_windows16:
			return file_os_dos_win16;

		case vos_dos_windows32:
			return file_os_dos_win32;

		case vos_os216_pm16:
			return file_os_os216_pm16;

		case vos_os232_pm32:
			return file_os_os232_pm32;

		case vos_nt_windows32:
			return file_os_nt_win32;

		default:
			return file_os_unknown;
		}

		return file_os_unknown;
	}

	//Returns file type (raw DWORD)
	uint32_t file_version_info::get_file_type_raw() const noexcept
	{
		return file_type_;
	}

	//Returns file type
	file_version_info::file_type file_version_info::get_file_type() const noexcept
	{
		//Determine file type
		switch (file_type_)
		{
		case vft_app:
			return file_type_application;

		case vft_dll:
			return file_type_dll;

		case vft_drv:
			return file_type_driver;

		case vft_font:
			return file_type_font;

		case vft_vxd:
			return file_type_vxd;

		case vft_static_lib:
			return file_type_static_lib;

		default:
			return file_type_unknown;
		}

		return file_type_unknown;
	}

	//Returns file subtype (usually non-zero for drivers and fonts)
	uint32_t file_version_info::get_file_subtype() const noexcept
	{
		return file_subtype_;
	}

	//Returns file date most significant DWORD
	uint32_t file_version_info::get_file_date_ms() const noexcept
	{
		return file_date_ms_;
	}

	//Returns file date least significant DWORD
	uint32_t file_version_info::get_file_date_ls() const noexcept
	{
		return file_date_ls_;
	}

	//Helper to set file flag
	void file_version_info::set_file_flag(uint32_t flag) noexcept
	{
		file_flags_ |= flag;
	}

	//Helper to clear file flag
	void file_version_info::clear_file_flag(uint32_t flag) noexcept
	{
		file_flags_ &= ~flag;
	}

	//Helper to set or clear file flag
	void file_version_info::set_file_flag(uint32_t flag, bool set_flag) noexcept
	{
		set_flag ? set_file_flag(flag) : clear_file_flag(flag);
	}

	//Sets if file is debug-built
	void file_version_info::set_debug(bool debug) noexcept
	{
		set_file_flag(vs_ff_debug, debug);
	}

	//Sets if file is prerelease
	void file_version_info::set_prerelease(bool prerelease) noexcept
	{
		set_file_flag(vs_ff_prerelease, prerelease);
	}

	//Sets if file is patched
	void file_version_info::set_patched(bool patched) noexcept
	{
		set_file_flag(vs_ff_patched, patched);
	}

	//Sets if private build
	void file_version_info::set_private_build(bool private_build) noexcept
	{
		set_file_flag(vs_ff_privatebuild, private_build);
	}

	//Sets if special build
	void file_version_info::set_special_build(bool special_build) noexcept
	{
		set_file_flag(vs_ff_specialbuild, special_build);
	}

	//Sets if info inferred
	void file_version_info::set_info_inferred(bool info_inferred) noexcept
	{
		set_file_flag(vs_ff_infoinferred, info_inferred);
	}

	//Sets flags (raw DWORD)
	void file_version_info::set_file_flags(uint32_t file_flags) noexcept
	{
		file_flags_ = file_flags;
	}

	//Sets file version most significant DWORD
	void file_version_info::set_file_version_ms(uint32_t file_version_ms) noexcept
	{
		file_version_ms_ = file_version_ms;
	}

	//Sets file version least significant DWORD
	void file_version_info::set_file_version_ls(uint32_t file_version_ls) noexcept
	{
		file_version_ls_ = file_version_ls;
	}

	//Sets product version most significant DWORD
	void file_version_info::set_product_version_ms(uint32_t product_version_ms) noexcept
	{
		product_version_ms_ = product_version_ms;
	}

	//Sets product version least significant DWORD
	void file_version_info::set_product_version_ls(uint32_t product_version_ls) noexcept
	{
		product_version_ls_ = product_version_ls;
	}

	//Sets file OS type (raw DWORD) noexcept
	void file_version_info::set_file_os_raw(uint32_t file_os) noexcept
	{
		file_os_ = file_os;
	}

	//Sets file OS type
	void file_version_info::set_file_os(file_os_type file_os) noexcept
	{
		//Determine file operation system type
		switch (file_os)
		{
		case file_os_dos:
			file_os_ = vos_dos;
			return;

		case file_os_os216:
			file_os_ = vos_os216;
			return;

		case file_os_os232:
			file_os_ = vos_os232;
			return;

		case file_os_nt:
			file_os_ = vos_nt;
			return;

		case file_os_wince:
			file_os_ = vos_wince;
			return;

		case file_os_win16:
			file_os_ = vos__windows16;
			return;

		case file_os_pm16:
			file_os_ = vos__pm16;
			return;

		case file_os_pm32:
			file_os_ = vos__pm32;
			return;

		case file_os_win32:
			file_os_ = vos__windows32;
			return;

		case file_os_dos_win16:
			file_os_ = vos_dos_windows16;
			return;

		case file_os_dos_win32:
			file_os_ = vos_dos_windows32;
			return;

		case file_os_os216_pm16:
			file_os_ = vos_os216_pm16;
			return;

		case file_os_os232_pm32:
			file_os_ = vos_os232_pm32;
			return;

		case file_os_nt_win32:
			file_os_ = vos_nt_windows32;
			return;

		default:
			return;
		}
	}

	//Sets file type (raw DWORD)
	void file_version_info::set_file_type_raw(uint32_t file_type) noexcept
	{
		file_type_ = file_type;
	}

	//Sets file type
	void file_version_info::set_file_type(file_type file_type) noexcept
	{
		//Determine file type
		switch (file_type)
		{
		case file_type_application:
			file_type_ = vft_app;
			return;

		case file_type_dll:
			file_type_ = vft_dll;
			return;

		case file_type_driver:
			file_type_ = vft_drv;
			return;

		case file_type_font:
			file_type_ = vft_font;
			return;

		case file_type_vxd:
			file_type_ = vft_vxd;
			return;

		case file_type_static_lib:
			file_type_ = vft_static_lib;
			return;

		default:
			return;
		}
	}

	//Sets file subtype (usually non-zero for drivers and fonts)
	void file_version_info::set_file_subtype(uint32_t file_subtype) noexcept
	{
		file_subtype_ = file_subtype;
	}

	//Sets file date most significant DWORD
	void file_version_info::set_file_date_ms(uint32_t file_date_ms) noexcept
	{
		file_date_ms_ = file_date_ms;
	}

	//Sets file date least significant DWORD
	void file_version_info::set_file_date_ls(uint32_t file_date_ls) noexcept
	{
		file_date_ls_ = file_date_ls;
	}
}
