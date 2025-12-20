#include "names.h"
#include "dg.h"
#include "config.h"
#include "strings.h"

#include <maya/MGlobal.h>


MString Mithrig::Names::create(const MString& single_name, const MString& multi_name) 
{
	MString single_short_name = Strings::short_name(single_name);
	MString multi_short_name = Strings::short_name(multi_name);

	if (!Dg::object_exists(single_short_name))
	{
		return single_short_name;
	}

	int pad_by = Strings::sequential_count(multi_name, Config::kNamingIncrementChar);

	int index = 1;
	MString name;

	while (true)
	{
		MString padding = Strings::pad(index, pad_by);
		
		name = multi_short_name;
		name.substitute(Config::kNamingIncrement, padding);
		
		if (!Dg::object_exists(name)) 
		{
			break;
		}

		index++;
	}

	return name;
}
