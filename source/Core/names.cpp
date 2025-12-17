#include "names.h"
#include "dg.h"
#include "config.h"
#include "strings.h"


MString Mithrig::Names::create(const MString& single_name, const MString& multi_name) 
{
	if (!Utilities::Dg::object_exists(single_name))
	{
		return single_name;
	}

	const int padding = Utilities::Strings::sequential_count(multi_name, Config::kNamingIncrementChar);

	int index = 1;
	MString name = multi_name;

	while (true)
	{
		MString increment = Utilities::Strings::pad(index, padding);
		name.substitute(Config::kNamingIncrement, increment);

		if (!Utilities::Dg::object_exists(name)) {
			break;
		}

		index++;
	}

	return name;
}

