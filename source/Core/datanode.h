#pragma once
#include <maya/MDGModifier.h>
#include <maya/MObjectArray.h>
#include <maya/MObject.h>


namespace Mithrig::DataNode {

	MObject create(const MString& name, const MString& type = "");

	MObjectArray get_links(
		const MObject& obj, 
		const MString& attr_name, 
		MStatus* return_status = nullptr
	);

	MObject get_link(
		const MObject& obj, 
		const MString& attr_name, 
		unsigned int index, 
		MStatus* return_status = nullptr
	);

	MStatus link(
		const MObject& src, 
		const MObject& trg, 
		const MString& attr_name, 
		MDGModifier* dg_mod = nullptr
	);

	MStatus link(
		const MObjectArray& srcs,
		const MObject& trg,
		const MString& attr_name,
		MDGModifier* dg_mod = nullptr
	);
}
