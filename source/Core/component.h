#pragma once
#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MObject.h>
#include <maya/MObjectArray.h>
#include <maya/MDGModifier.h>
#include <maya/MTransformationMatrix.h>
#include <nlohmann/json.hpp>
#include <vector>


namespace Mithrig 
{
	class System 
	{
	public:
		System(const MString& name, const nlohmann::json& params);
		virtual ~System() = default;

		MStatus virtual creator() = 0;
		MStatus virtual matcher(const std::vector<MTransformationMatrix>& data) { return MS::kNotImplemented; }

		MString virtual version() const { return "1.0.0"; };

		const MObject& datanode() const { return m_datanode; }
		const nlohmann::json& params() const { return m_params; }

		bool is_created() const { return m_created; }

		MStatus link(const MObject& node, const MString& attr, MDGModifier* dg_mod = nullptr) const;
		MObject get_link(const MString& attr, unsigned int index) const;
		MObjectArray get_links(const MString& attr) const;

	protected:
		MObject m_datanode;
		nlohmann::json m_params;

	private:
		bool m_created = false;

	};


	class Component
	{
	public:
		Component(const MString& name) : m_name(name) {}
		~Component() = default;

	private:
		MString m_name;

	};
}
