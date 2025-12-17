#include "datanode.h"

#include <maya/MFnMessageAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnStringData.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>

#include "config.h"
#include "names.h"
#include "strings.h"


namespace Mithrig::DataNode {
	
	MObject create(const MString& name, const MString& type) 
	{
		MFnDependencyNode fn;
		MObject datanode = fn.create("network");


		const MString unique_name = Names::create(
			name + Config::kDataNodeAffix,
			name + "_" + Config::kNamingIncrement + "_" + Config::kDataNodeAffix
		);

		fn.setName(unique_name);

		MFnTypedAttribute string_fn;

		MObject attr = string_fn.create(
			Config::kDataNodeAttributeType, 
			Config::kDataNodeAttributeType, 
			MFnData::kString, 
			MFnStringData().create(type)
		);

		CHECK_MSTATUS_AND_RETURN(fn.addAttribute(attr), datanode);

		return datanode;
	}

	MObjectArray get_links(
		const MObject& obj, 
		const MString& attr_name, 
		MStatus* return_status
	) {
		MStatus status;
		MObjectArray nodes;

		MFnDependencyNode dep_fn(obj, &status);
		CHECK_MSTATUS_AND_RETURN(status, nodes);

		MPlug attr_plug = dep_fn.findPlug(attr_name, true, &status);
		CHECK_MSTATUS_AND_RETURN(status, nodes);

		if (attr_plug.isArray()) {
			for (unsigned int index = 0; index < attr_plug.numElements(); index++) {
				MPlug plug = attr_plug.elementByLogicalIndex(index, &status);

				if (status != MS::kSuccess || plug.isNull()) {
					continue;
				}

				MPlugArray plug_connections;
				plug.connectedTo(plug_connections, true, true, &status);

				for (const MPlug& plug_connection : plug_connections) {
					nodes.append(plug_connection.node());
				}
			}
		}
		else {
			MPlugArray plug_connections;
			attr_plug.connectedTo(plug_connections, true, true, &status);
			CHECK_MSTATUS_AND_RETURN(status, nodes);

			nodes.setLength(plug_connections.length());
			for (unsigned int index = 0; index < plug_connections.length(); index++) {
				nodes.set(plug_connections[index].node(), index);
			}
		}

		return nodes;
	}

	MObject get_link(
		const MObject& obj,
		const MString& attr_name,
		unsigned int index,
		MStatus* return_status
	) {
		MObjectArray connections = get_links(obj, attr_name, return_status);
		
		if (connections.length() > index) {
			return connections[index];
		}
		else {
			return MObject::kNullObj;
		}
	}

	MStatus link(
		const MObject& src, 
		const MObject& trg, 
		const MString& attr_name, 
		MDGModifier* dg_mod
	) {
		MStatus status;
		MFnMessageAttribute msg_fn;

		MObject attr_obj = msg_fn.create(attr_name, attr_name, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		MDGModifier dg_mod_a;
		MDGModifier dg_mod_b;
		if (!dg_mod) {
			dg_mod = &dg_mod_a;
		}

		status = dg_mod_b.addAttribute(trg, attr_obj);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		CHECK_MSTATUS_AND_RETURN_IT(dg_mod_b.doIt());

		MFnDependencyNode src_fn(src, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		MFnDependencyNode trg_fn(trg, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		MPlug src_plug = src_fn.findPlug("message", true, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		MPlug trg_plug = trg_fn.findPlug(attr_name, true, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		status = dg_mod->connect(src_plug, trg_plug);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		if (dg_mod == &dg_mod_a) {
			return dg_mod->doIt();
		}

		return MS::kSuccess;
	}

	MStatus link(
		const MObjectArray& srcs,
		const MObject& trg,
		const MString& attr_name,
		MDGModifier* dg_mod
	) {
		MStatus status;
		MFnMessageAttribute msg_fn;

		MObject attr_obj = msg_fn.create(attr_name, attr_name, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		msg_fn.setArray(true);

		MDGModifier dg_mod_a;
		MDGModifier dg_mod_b;
		if (!dg_mod) {
			dg_mod = &dg_mod_a;
		}

		status = dg_mod_b.addAttribute(trg, attr_obj);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		CHECK_MSTATUS_AND_RETURN_IT(dg_mod_b.doIt());

		MFnDependencyNode trg_fn(trg, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		MPlug trg_plug = trg_fn.findPlug(attr_name, true, &status);
		CHECK_MSTATUS_AND_RETURN_IT(status);

		for (unsigned int index = 0; index < srcs.length(); index++) {
			MFnDependencyNode src_fn(srcs[index], &status);
			CHECK_MSTATUS_AND_RETURN_IT(status);

			MPlug src_plug = src_fn.findPlug("message", true, &status);
			CHECK_MSTATUS_AND_RETURN_IT(status);

			status = dg_mod->connect(src_plug, trg_plug.elementByLogicalIndex(index));
			CHECK_MSTATUS_AND_RETURN_IT(status);
		}

		if (dg_mod == &dg_mod_a) {
			return dg_mod->doIt();
		}

		return MS::kSuccess;
	}
}
