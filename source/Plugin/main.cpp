#include "config.h"

#include "cmd_dataNode.h"

#include <maya/MFnPlugin.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MGlobal.h>
#include <maya/MString.h>


MStatus initializePlugin(MObject obj) {

	using namespace Mithrig;
	using namespace Mithrig::Commands;
	

	MFnPlugin plugin(obj);

	MString plugin_name(Config::kName);

	plugin.registerCommand(plugin_name + "DataNode", CmdDataNode::creator, CmdDataNode::syntax);


	return MS::kSuccess;
}


MStatus uninitializePlugin(MObject obj) {

	return MS::kSuccess;
}
