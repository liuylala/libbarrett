/*
 * kinematics-inl.h
 *
 *  Created on: Jan 14, 2010
 *      Author: dc
 */

#ifndef KINEMATICSINL_H_
#define KINEMATICSINL_H_


#include <libconfig.h>

#include <barrett/kinematics/kinematics.h>
#include "../../units.h"


namespace barrett {
namespace math {


template<size_t DOF>
Kinematics<DOF>::Kinematics(config_setting_t * config)
{
	if (bt_kinematics_create(&impl, config, DOF)) {
		throw(std::runtime_error("(math::Kinematics::Kinematics): Couldn't initialize Kinematics struct."));
	}
}

template<size_t DOF>
Kinematics<DOF>::~Kinematics()
{
	bt_kinematics_destroy(impl);
}

template<size_t DOF>
void Kinematics<DOF>::eval(const jp_type& jp, const jv_type& jv)
{
	bt_kinematics_eval(impl, jp.asGslVector(), jv.asGslVector());
}

template<size_t DOF>
units::CartesianPosition Kinematics<DOF>::operator() (const boost::tuple<jp_type, jv_type>& jointState)
{
	eval(boost::tuples::get<0>(jointState), boost::tuples::get<1>(jointState));
	return units::CartesianPosition(impl->tool->origin_pos);
}


}
}


#endif /* KINEMATICSINL_H_ */