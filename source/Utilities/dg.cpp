#include "dg.h"

#include <maya/MSelectionList.h>


bool Mithrig::Dg::object_exists(const MString& name) 
{
	return MSelectionList().add(name) == MS::kSuccess;
}


bool Mithrig::Dg::object_exists(const MObject& obj)
{
	return !obj.isNull();
}
