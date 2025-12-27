#include "serialization.h"

#include <maya/MFnDependencyNode.h>
#include <maya/MUuid.h>
#include <maya/MSelectionList.h>


std::string Mithrig::Serialize::obj(const MObject& obj)
{
	MFnDependencyNode fn(obj);
	return std::string(fn.uuid().asString().asChar());
}


MObject Mithrig::Deserialize::obj(const std::string& uuid)
{
	MSelectionList sl;
	sl.add(uuid.c_str());

	MObject obj;
	sl.getDependNode(0, obj);

	return obj;
}
