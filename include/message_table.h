#pragma once
#include <string>
#include <map>
#include "stdint_defs.h"

namespace pe_bliss
{
	//Structure representing message table string
	class message_table_item
	{
	public:
		//Default constructor
		message_table_item() noexcept;
		//Constructors from ANSI and UNICODE strings
		explicit message_table_item(const std::string& str);
		explicit message_table_item(const std::wstring& str);

		//Returns true if string is UNICODE
		bool is_unicode() const noexcept;
		//Returns ANSI string
		const std::string& get_ansi_string() const noexcept;
		//Returns UNICODE string
		const std::wstring& get_unicode_string() const noexcept;

	public:
		//Sets ANSI or UNICODE string
		void set_string(const std::string& str);
		void set_string(const std::wstring& str);

	private:
		bool unicode_;
		std::string ansi_str_;
		std::wstring unicode_str_;
	};
}
