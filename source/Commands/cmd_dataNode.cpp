#include "cmd_dataNode.h"
#include "datanode.h"

#include <maya/MArgParser.h>
#include <maya/MStatus.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MGlobal.h>


MStatus Mithrig::Commands::CmdDataNode::doIt(const MArgList& args) {
	CHECK_MSTATUS_AND_RETURN_IT(parse_args(args));
	return redoIt();
}


MStatus Mithrig::Commands::CmdDataNode::undoIt() {
	return MS::kSuccess;
}


MStatus Mithrig::Commands::CmdDataNode::redoIt() {

	MStatus status;

	MObject datanode = Mithrig::DataNode::create(m_name, m_type);

	MFnDependencyNode dep_fn(datanode, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	setResult(dep_fn.name());

	return status;
}


MSyntax Mithrig::Commands::CmdDataNode::syntax() {

	MSyntax syntax;
	syntax.enableEdit(true);
	syntax.enableQuery(true);

	syntax.addFlag(FLAG_NAME, FLAG_NAME, MSyntax::kString);

	return syntax;
}


MStatus Mithrig::Commands::CmdDataNode::parse_args(const MArgList& args) {

	MArgParser parsed(syntax(), args);

	m_name = parsed.flagArgumentString(FLAG_NAME, 0);
	m_type = parsed.flagArgumentString(FLAG_TYPE, 0);

	return MS::kSuccess;
}
