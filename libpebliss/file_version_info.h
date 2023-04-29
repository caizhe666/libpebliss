#pragma once
#include <string>
#include <map>
#include "stdint_defs.h"
#include "pe_structures.h"

namespace pe_bliss
{
	//Structure representing fixed file version info
	class file_version_info
	{
	public:
		//Enumeration of file operating system types
		enum file_os_type
		{
			file_os_unknown,
			file_os_dos,
			file_os_os216,
			file_os_os232,
			file_os_nt,
			file_os_wince,
			file_os_win16,
			file_os_pm16,
			file_os_pm32,
			file_os_win32,
			file_os_dos_win16,
			file_os_dos_win32,
			file_os_os216_pm16,
			file_os_os232_pm32,
			file_os_nt_win32
		};

		//Enumeration of file types
		enum file_type
		{
			file_type_unknown,
			file_type_application,
			file_type_dll,
			file_type_driver,
			file_type_font,
			file_type_vxd,
			file_type_static_lib
		};

	public:
		//Default constructor
		file_version_info() noexcept;
		//Constructor from Windows fixed version info structure
		explicit file_version_info(const pe_win::vs_fixedfileinfo& info) noexcept;

	public: //Getters
		//Returns true if file is debug-built
		bool is_debug() const noexcept;
		//Returns true if file is prerelease
		bool is_prerelease() const noexcept;
		//Returns true if file is patched
		bool is_patched() const noexcept;
		//Returns true if private build
		bool is_private_build() const noexcept;
		//Returns true if special build
		bool is_special_build() const noexcept;
		//Returns true if info inferred
		bool is_info_inferred() const noexcept;
		//Retuens file flags (raw DWORD)
		uint32_t get_file_flags() const noexcept;

		//Returns file version most significant DWORD
		uint32_t get_file_version_ms() const noexcept;
		//Returns file version least significant DWORD
		uint32_t get_file_version_ls() const noexcept;
		//Returns product version most significant DWORD
		uint32_t get_product_version_ms() const noexcept;
		//Returns product version least significant DWORD
		uint32_t get_product_version_ls() const noexcept;

		//Returns file OS type (raw DWORD)
		uint32_t get_file_os_raw() const noexcept;
		//Returns file OS type
		file_os_type get_file_os() const noexcept;

		//Returns file type (raw DWORD)
		uint32_t get_file_type_raw() const noexcept;
		//Returns file type
		file_type get_file_type() const noexcept;

		//Returns file subtype (usually non-zero for drivers and fonts)
		uint32_t get_file_subtype() const noexcept;

		//Returns file date most significant DWORD
		uint32_t get_file_date_ms() const noexcept;
		//Returns file date least significant DWORD
		uint32_t get_file_date_ls() const noexcept;

		//Returns file version string
		template<typename T>
		const std::basic_string<T> get_file_version_string() const
		{
			return get_version_string<T>(file_version_ms_, file_version_ls_);
		}

		//Returns product version string
		template<typename T>
		const std::basic_string<T> get_product_version_string() const
		{
			return get_version_string<T>(product_version_ms_, product_version_ls_);
		}

	public: //Setters
		//Sets if file is debug-built
		void set_debug(bool debug) noexcept;
		//Sets if file is prerelease
		void set_prerelease(bool prerelease) noexcept;
		//Sets if file is patched
		void set_patched(bool patched) noexcept;
		//Sets if private build
		void set_private_build(bool private_build) noexcept;
		//Sets if special build
		void set_special_build(bool special_build) noexcept;
		//Sets if info inferred
		void set_info_inferred(bool info_inferred) noexcept;
		//Sets flags (raw DWORD)
		void set_file_flags(uint32_t file_flags) noexcept;

		//Sets file version most significant DWORD
		void set_file_version_ms(uint32_t file_version_ms) noexcept;
		//Sets file version least significant DWORD
		void set_file_version_ls(uint32_t file_version_ls) noexcept;
		//Sets product version most significant DWORD
		void set_product_version_ms(uint32_t product_version_ms) noexcept;
		//Sets product version least significant DWORD
		void set_product_version_ls(uint32_t product_version_ls) noexcept;

		//Sets file OS type (raw DWORD)
		void set_file_os_raw(uint32_t file_os) noexcept;
		//Sets file OS type
		void set_file_os(file_os_type file_os) noexcept;

		//Sets file type (raw DWORD)
		void set_file_type_raw(uint32_t file_type) noexcept;
		//Sets file type
		void set_file_type(file_type file_type) noexcept;

		//Sets file subtype (usually non-zero for drivers and fonts)
		void set_file_subtype(uint32_t file_subtype) noexcept;

		//Sets file date most significant DWORD
		void set_file_date_ms(uint32_t file_date_ms) noexcept;
		//Sets file date least significant DWORD
		void set_file_date_ls(uint32_t file_date_ls) noexcept;

	private:
		//Helper to convert version DWORDs to string
		template<typename T>
		static const std::basic_string<T> get_version_string(uint32_t ms, uint32_t ls)
		{
			std::basic_stringstream<T> ss;
			ss << (ms >> 16) << static_cast<T>(L'.')
				<< (ms & 0xFFFF) << static_cast<T>(L'.')
				<< (ls >> 16) << static_cast<T>(L'.')
				<< (ls & 0xFFFF);
			return ss.str();
		}

		//Helper to set file flag
		void set_file_flag(uint32_t flag) noexcept;
		//Helper to clear file flag
		void clear_file_flag(uint32_t flag) noexcept;
		//Helper to set or clear file flag
		void set_file_flag(uint32_t flag, bool set_flag) noexcept;

		uint32_t file_version_ms_, file_version_ls_,
			product_version_ms_, product_version_ls_;
		uint32_t file_flags_;
		uint32_t file_os_;
		uint32_t file_type_, file_subtype_;
		uint32_t file_date_ms_, file_date_ls_;
	};
}
