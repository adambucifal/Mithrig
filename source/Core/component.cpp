#include "component.h"
#include "datanode.h"
#include "logger.h"


Mithrig::System::System(const MString& name, const nlohmann::json& params) 
	:
	m_datanode(DataNode::create(name)),
	m_params(params)
{}


MStatus Mithrig::System::link(const MObject& node, const MString& attr, MDGModifier* dg_mod) const
{
	return DataNode::link(node, m_datanode, attr, dg_mod);
}


MObject Mithrig::System::get_link(const MString& attr, unsigned int index) const
{
	return DataNode::get_link(m_datanode, attr, index);
}


MObjectArray Mithrig::System::get_links(const MString& attr) const
{
	return DataNode::get_links(m_datanode, attr);
}
