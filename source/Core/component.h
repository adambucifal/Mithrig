#pragma once
#include <maya/MString.h>
#include <maya/MObject.h>
#include <maya/MFnPlugin.h>


namespace Mithrig {

	class ComponentTemplate {

	public:
		ComponentTemplate() = default;
		~ComponentTemplate() = default;
	
		virtual MString type() const = 0;
		virtual MStatus create() const = 0;

		const MObject& datanode() const { return m_datanode; }
		MObject& datanode() { return m_datanode; }

		static ComponentTemplate reinit(const MObject& node);

	private:
		MString m_name;
		MObject m_datanode;
	};
}
