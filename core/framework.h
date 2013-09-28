#pragma once

//STL
#define _USE_MATH_DEFINES
#include <memory>
#include <string>
#include <array>
#include <vector>
#include <map>

#include <core/framework/misc.h>
#include <core/framework/time.h>

//ECS architecture layer 1
#include <core/framework/IPlatform.h>
#include <core/framework/Identifiable.h>
#include <core/framework/IComponent.h>
//layer 2
#include <core/framework/IEntity.h>
#include <core/framework/IEntityFactory.h>
#include <core/framework/IArchetype.h>
#include <core/framework/ISystem.h>
//layer 3
#include <core/framework/AutonomousEntity.h>
#include <core/framework/AutonomousEntityFactory.h>
#include <core/framework/ManagedEntity.h>
#include <core/framework/ManagedEntityFactory.h>
#include <core/framework/PresetArchetype.h>