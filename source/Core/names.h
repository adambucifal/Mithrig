#pragma once

#include <maya/MString.h>


namespace Mithrig::Names 
{

	MString create(const MString& single_name, const MString& multi_name);
	MString create_standard(const MString& name, const MString& affix_str);

}
