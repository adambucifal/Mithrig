#pragma once

#include <maya/MString.h>


namespace Mithrig::Dg {

	bool object_exists(const MString& name);
	bool object_exists(const MObject& obj);

}
