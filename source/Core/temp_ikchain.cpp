#include "temp_ikchain.h"
#include "serialization.h"

#include <maya/MFnIkHandle.h>
#include <maya/MDagPath.h>
#include <maya/MStatus.h>

#include <nlohmann/json.hpp>

MStatus Mithrig::IkChain::creator()
{
	if (!m_params.contains("start_joint"))
	{
		return MS::kInvalidParameter;
	}

	if (!m_params.contains("end_joint"))
	{
		return MS::kInvalidParameter;
	}

	MObject start_obj = Deserialize::obj(m_params.at("start_joint"));
	MObject end_obj = Deserialize::obj(m_params.at("end_joint"));

	if (!start_obj.hasFn(MFn::kDagNode) || !end_obj.hasFn(MFn::kDagNode))
	{
		return MS::kInvalidParameter;
	}

	MDagPath start_dag;
	MDagPath end_dag;

	MDagPath::getAPathTo(start_obj, start_dag);
	MDagPath::getAPathTo(end_obj, end_dag);


	MFnIkHandle fn;
	fn.create(start_dag, end_dag);

	return MS::kSuccess;
}

