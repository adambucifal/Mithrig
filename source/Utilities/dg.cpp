#include "dg.h"

#include <maya/MSelectionList.h>


bool Mithrig::Utilities::Dg::object_exists(const MString& name) 
{
	MSelectionList sl;
	return sl.add(name) == MS::kSuccess;
}
